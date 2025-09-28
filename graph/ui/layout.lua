-- graph/ui/layout.lua
-- Czysty layout: geometria i transformacje (bez rysowania).
-- Utrzymuje kompatybilność wstecz: aliasy node_rect/port_local_pos/link_polyline.

local L = {}

----------------------------------------------------------------
-- Konfiguracja / Theme
----------------------------------------------------------------
local theme = require("graph.ui.theme")

local function sizes()
  -- Wymagane pola w theme.sizes (z sensownymi fallbackami):
  local s = theme.sizes or theme.metrics or {}
  return {
    nodeMinW       = s.nodeMinW       or 140,
    nodePaddingX   = s.nodePaddingX   or 10,
    nodePaddingY   = s.nodePaddingY   or 8,
    rowHeight      = s.rowHeight      or 22,
    headerHeight   = s.headerHeight   or 28,
    portRadius     = s.portRadius     or 5,   -- data port (circle)
    portExecSize   = s.portExecSize   or 10,  -- exec port (square)
    bezierMinTx    = s.bezierMinTx    or 40,
    bezierMaxTx    = s.bezierMaxTx    or 200,
    bezierTensionY = s.bezierTensionY or 0,
    gridSize       = s.gridSize       or 16,
  }
end

----------------------------------------------------------------
-- Kamera / transformacje
----------------------------------------------------------------
-- camera = { ox, oy, zoom }
local function _ensureCam(camera)
  local z = (camera and camera.zoom) or 1
  return {
    ox = (camera and camera.ox) or 0,
    oy = (camera and camera.oy) or 0,
    zoom = (z == 0) and 1 or z
  }
end

-- API: worldToScreen(camera, wx, wy) -> sx, sy
function L.worldToScreen(camera, wx, wy)
  local cam = _ensureCam(camera)
  local sx = (wx * cam.zoom) + cam.ox
  local sy = (wy * cam.zoom) + cam.oy
  return sx, sy
end

-- API: screenToWorld(camera, sx, sy) -> wx, wy
function L.screenToWorld(camera, sx, sy)
  local cam = _ensureCam(camera)
  local wx = (sx - cam.ox) / cam.zoom
  local wy = (sy - cam.oy) / cam.zoom
  return wx, wy
end

----------------------------------------------------------------
-- Node geometry
----------------------------------------------------------------
-- Wspierane pola node:
-- node.x, node.y, node.w?, node.h?, node.title?
-- node.inputs (array), node.outputs (array)
-- (opcjonalnie) node.execIn (array), node.execOut (array)
-- -> Zwraca {x,y,w,h} w world-space
function L.nodeRect(node, _theme)
  local s = sizes()
  local x = node.x or (node.pos and node.pos.x) or 0
  local y = node.y or (node.pos and node.pos.y) or 0

  -- width
  local minW = s.nodeMinW + 2 * s.nodePaddingX
  local w = node.w or (node.size and node.size.w) or minW
  if w < minW then w = minW end

  -- rows (data)
  local inCount  = (node.inputs  and #node.inputs)  or 0
  local outCount = (node.outputs and #node.outputs) or 0
  local rows = math.max(inCount, outCount)

  -- exec wiersze (opcjonalnie – można pominąć, jeśli exec-y rysujesz w kolumnach)
  local execH = 0
  if node.execIn  and #node.execIn  > 0 then execH = execH + s.rowHeight end
  if node.execOut and #node.execOut > 0 then execH = execH + s.rowHeight end

  local h = s.headerHeight + (rows * s.rowHeight) + execH + 2 * s.nodePaddingY
  -- explicit height ma prio
  if node.h or (node.size and node.size.h) then
    h = node.h or (node.size and node.size.h) or h
  end

  return { x = x, y = y, w = w, h = h }
end

----------------------------------------------------------------
-- Port position (world-space, center)
----------------------------------------------------------------
-- port: tabela portu albo wskaźnik na stronę/indeks.
-- Konwencja:
--  - jeśli port.__side == "in"/"out" i port.__index podane → użyj ich,
--  - w innym wypadku spróbuj znaleźć indeks portu w node.inputs / node.outputs,
--  - data porty w kolumnach: inputs lewa krawędź, outputs prawa krawędź.
local function _findPortSideIndex(node, port)
  if port.__side and port.__index then
    return port.__side, port.__index
  end
  -- Szukamy po referencji lub po nazwie
  if node.inputs then
    for i, p in ipairs(node.inputs) do
      if p == port or (port.name and p.name == port.name) then
        return "in", i
      end
    end
  end
  if node.outputs then
    for i, p in ipairs(node.outputs) do
      if p == port or (port.name and p.name == port.name) then
        return "out", i
      end
    end
  end
  -- fallback: załóż output #1
  return "out", 1
end

-- Zwraca {x,y} środka portu (world).
function L.portPosition(node, port, _theme)
  local s = sizes()
  local r = L.nodeRect(node, _theme)
  local side, idx = _findPortSideIndex(node, port)

  -- Y: wiersze data zaczynają się pod headerem
  local baseY = r.y + s.headerHeight + s.nodePaddingY
  local cy    = baseY + (idx - 0.5) * s.rowHeight

  -- X: lewa/prawa krawędź (z lekkim wyprowadzeniem „na zewnątrz”)
  if side == "in" then
    return (r.x - s.portRadius), cy
  else
    return (r.x + r.w + s.portRadius), cy
  end
end

----------------------------------------------------------------
-- Link path (cubic Bezier)
----------------------------------------------------------------
-- link: { fromNode, fromPort, toNode, toPort } (port może być obiektem z name/kind)
-- Zwraca { p0, c0, c1, p1 } (każdy {x,y})
function L.linkPath(link, graph, _theme)
  local s = sizes()
  local fromNode = link.fromNode or (graph and graph:getNodeById(link.from))
  local toNode   = link.toNode   or (graph and graph.getNodeById and graph:getNodeById(link.to))
  if not (fromNode and toNode) then
    return { {x=0,y=0},{x=0,y=0},{x=0,y=0},{x=0,y=0} }
  end

  local p0x, p0y = L.portPosition(fromNode, link.fromPort or { __side="out", __index=link.fromSlot or 1 })
  local p1x, p1y = L.portPosition(toNode,   link.toPort   or { __side="in",  __index=link.toSlot   or 1 })

  local dx = math.abs(p1x - p0x)
  local tx = math.max(s.bezierMinTx, math.min(s.bezierMaxTx, dx * 0.5))

  local c0x, c0y = p0x + tx, p0y
  local c1x, c1y = p1x - tx, p1y

  if s.bezierTensionY ~= 0 then
    local sign = (p1y >= p0y) and 1 or -1
    c0y = c0y + sign * s.bezierTensionY
    c1y = c1y - sign * s.bezierTensionY
  end

  return { {x=p0x,y=p0y}, {x=c0x,y=c0y}, {x=c1x,y=c1y}, {x=p1x,y=p1y} }
end

----------------------------------------------------------------
-- Bezier sampling -> polyline
----------------------------------------------------------------
local function _bezierPoint(p0, c0, c1, p1, t)
  local u = 1 - t
  local x = (u*u*u)*p0.x + 3*(u*u)*t*c0.x + 3*u*(t*t)*c1.x + (t*t*t)*p1.x
  local y = (u*u*u)*p0.y + 3*(u*u)*t*c0.y + 3*u*(t*t)*c1.y + (t*t*t)*p1.y
  return x, y
end

-- Zwraca listę punktów { {x,y}, ... }
function L.linkPolyline(link, graph, _theme, opts)
  opts = opts or {}
  local seg = math.max(2, opts.segments or 16)
  local path = L.linkPath(link, graph, _theme)
  local p0, c0, c1, p1 = path[1], path[2], path[3], path[4]

  local poly = {}
  for i = 0, seg do
    local t = i / seg
    local x, y = _bezierPoint(p0, c0, c1, p1, t)
    poly[#poly+1] = { x = x, y = y }
  end
  return poly
end

----------------------------------------------------------------
-- Polyline AABB
----------------------------------------------------------------
function L.linkAABB(link, graph, _theme, opts)
  local poly = (link._poly and not opts) and link._poly or L.linkPolyline(link, graph, _theme, opts)
  if #poly == 0 then return { x=0, y=0, w=0, h=0 } end
  local minx, miny = math.huge, math.huge
  local maxx, maxy = -math.huge, -math.huge
  for _,p in ipairs(poly) do
    if p.x < minx then minx = p.x end
    if p.y < miny then miny = p.y end
    if p.x > maxx then maxx = p.x end
    if p.y > maxy then maxy = p.y end
  end
  return { x = minx, y = miny, w = (maxx - minx), h = (maxy - miny) }
end

----------------------------------------------------------------
-- Grid
----------------------------------------------------------------
function L.snapToGrid(wx, wy, gridSize)
  local g = gridSize or sizes().gridSize
  local gx = math.floor((wx / g) + 0.5) * g
  local gy = math.floor((wy / g) + 0.5) * g
  return gx, gy
end

----------------------------------------------------------------
-- Alias’y wsteczne (z pliku, który już miałeś)
----------------------------------------------------------------
-- Lokalna pozycja portu była kiedyś obliczana „względem nody” – teraz zwracamy world.
-- Jeśli ktoś oczekuje local, może odjąć r.x/r.y.
function L.node_rect(node, _theme)
  return L.nodeRect(node, _theme)
end

function L.port_local_pos(node, slot_index, is_output, _theme)
  -- Zbuduj tymczasowy „port” tak jak oczekiwał stary kod.
  local side  = is_output and "out" or "in"
  local port  = { __side = side, __index = slot_index }
  local x, y  = L.portPosition(node, port, _theme)
  local r     = L.nodeRect(node, _theme)
  return { x = x - r.x, y = y - r.y }
end

function L.link_polyline(fromNode, fromSlot, toNode, toSlot, opts)
  local link = {
    fromNode = fromNode, fromPort = { __side="out", __index=fromSlot },
    toNode   = toNode,   toPort   = { __side="in",  __index=toSlot  },
  }
  return L.linkPolyline(link, nil, nil, opts)
end

return L
