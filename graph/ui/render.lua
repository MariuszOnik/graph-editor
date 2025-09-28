-- graph/ui/renderer.lua
-- Renderer (View) – minimalna implementacja pod stuby:
-- drawGrid, drawGraph, drawNode, drawPort, drawLink, drawOverlay

local rcore   = require("rcore")
local rshape  = require("rshapes")
local rtext   = require("rtext")
local layout  = require("graph.ui.layout")
local theme   = require("graph.ui.theme")

local R = {}

----------------------------------------------------------------
-- Bezpieczne metryki/kolory z theme
----------------------------------------------------------------
local function S()
  local s = theme.sizes or theme.metrics or {}
  return {
    gridSize       = s.gridSize       or 16,
    gridBoldEvery  = s.gridBoldEvery  or 8,
    nodeRadius     = s.nodeRadius     or 0.1,  -- 0..1 dla DrawRectangleRounded
    nodeRoundSeg   = s.nodeRoundSeg   or 6,
    headerHeight   = s.headerHeight   or 28,
    rowHeight      = s.rowHeight      or 22,
    nodePaddingX   = s.nodePaddingX   or 10,
    nodePaddingY   = s.nodePaddingY   or 8,
    portRadius     = s.portRadius     or 5,
    portExecSize   = s.portExecSize   or 10,
    linkWidth      = s.linkWidth      or 2,
    linkHoverWidth = s.linkHoverWidth or 3,
    fontSize       = s.fontSize       or 16,
  }
end

local function C()
  local c = theme.colors or {}
  local function pick(x, d) return x or d end
  return {
    bg        = pick(c.bg,        {r=18,g=18,b=22,a=255}),
    grid      = pick(c.grid,      {r=35,g=35,b=40,a=255}),
    gridBold  = pick(c.gridBold,  {r=45,g=45,b=52,a=255}),
    node = {
      body     = (c.node and c.node.body)     or {r=34,g=37,b=44,a=255},
      header   = (c.node and c.node.header)   or {r=52,g=56,b=66,a=255},
      title    = (c.node and c.node.title)    or {r=220,g=220,b=230,a=255},
      selected = (c.node and c.node.selected) or {r=62,g=84,b=180,a=255},
      border   = (c.node and c.node.border)   or {r=80,g=80,b=95,a=255},
    },
    port = {
      data = (c.port and c.port.data) or {r=160,g=196,b=255,a=255},
      exec = (c.port and c.port.exec) or {r=255,g=204,b=102,a=255},
    },
    link = {
      data = (c.link and c.link.data) or {r=140,g=180,b=255,a=255},
      exec = (c.link and c.link.exec) or {r=255,g=204,b=102,a=255},
      sel  = (c.link and c.link.sel)  or {r=255,g=255,b=255,a=255},
    },
    overlay = pick(c.overlay, {r=200,g=200,b=210,a=200}),
  }
end

----------------------------------------------------------------
-- Grid
----------------------------------------------------------------
function R.drawGrid(camera, _theme)
  local s, c = S(), C()
  local W, H = rcore.GetScreenWidth(), rcore.GetScreenHeight()

  -- zakres w world
  local wx0, wy0 = layout.screenToWorld(camera, 0, 0)
  local wx1, wy1 = layout.screenToWorld(camera, W, H)
  local step     = s.gridSize

  local startX = math.floor(wx0 / step) * step
  local endX   = math.ceil(wx1 / step) * step
  local startY = math.floor(wy0 / step) * step
  local endY   = math.ceil(wy1 / step) * step

  for x = startX, endX, step do
    local sx = select(1, layout.worldToScreen(camera, x, 0))
    local col = ((((x/step) % s.gridBoldEvery) == 0) and c.gridBold) or c.grid
    rshape.DrawLine(sx, 0, sx, H, col)
  end
  for y = startY, endY, step do
    local sy = select(2, layout.worldToScreen(camera, 0, y))
    local col = ((((y/step) % s.gridBoldEvery) == 0) and c.gridBold) or c.grid
    rshape.DrawLine(0, sy, W, sy, col)
  end
end

----------------------------------------------------------------
-- Node
----------------------------------------------------------------
function R.drawNode(node, isSelected, camera, _theme, _layout)
  local s, c = S(), C()
  local r = layout.nodeRect(node, _theme)

  -- tło nody (world coords)
  rshape.DrawRectangleRounded(
    {x=r.x, y=r.y, width=r.w, height=r.h},
    s.nodeRadius, s.nodeRoundSeg,
    isSelected and c.node.selected or c.node.body
  )

  -- header
  rshape.DrawRectangle(r.x, r.y, r.w, s.headerHeight, c.node.header)

  -- border (opcjonalnie delikatny)
  rshape.DrawRectangleLines(r.x, r.y, r.w, r.h, c.node.border)

  -- tytuł
  local title = node.title or node.type or ("Node#" .. (node.id or "?"))
  rtext.DrawText(title, r.x + s.nodePaddingX, r.y + math.floor((s.headerHeight - s.fontSize)/2), s.fontSize, c.node.title)
end

----------------------------------------------------------------
-- Port
----------------------------------------------------------------
-- port: obiekt z node.inputs[i] / node.outputs[j]
function R.drawPort(node, port, camera, _theme, _layout)
  local s, c = S(), C()
  local x, y = layout.portPosition(node, port, _theme)
  local kind = (port.kind == "exec") and "exec" or "data"

  if kind == "exec" then
    local sz = s.portExecSize
    -- Rysujemy kwadrat centrowany w (x,y)
    rshape.DrawRectangle(math.floor(x - sz/2), math.floor(y - sz/2), sz, sz, c.port.exec)
  else
    rshape.DrawCircle(x, y, s.portRadius, c.port.data)
  end

  -- (opcjonalnie) etykieta przy porcie data
  if port.label or port.name then
    local label = port.label or port.name
    local isInput = (port.__side == "in") or port.is_input
    local px = isInput and (x + s.portRadius + 6) or (x - s.portRadius - 6 - (#label * (s.fontSize*0.6)))
    rtext.DrawText(label, px, y - math.floor(s.fontSize/2), s.fontSize, C().overlay)
  end
end

----------------------------------------------------------------
-- Link
----------------------------------------------------------------
function R.drawLink(link, camera, _theme, _layout, isSelected)
  local s, c = S(), C()

  -- Polyline po world
  local poly = layout.linkPolyline(link, nil, _theme, {segments=16})
  if #poly < 2 then return end

  local col
  if isSelected then
    col = c.link.sel
  else
    -- wykryj, czy to exec czy data (po typie portu źródłowego jeśli dostępny)
    local kind = (link.kind == "exec") and "exec" or link.type
    col = (kind == "exec") and c.link.exec or c.link.data
  end

  local w = isSelected and s.linkHoverWidth or s.linkWidth
  for i = 1, #poly - 1 do
    local a, b = poly[i], poly[i+1]
    rshape.DrawLineEx(a.x, a.y, b.x, b.y, w, col)
  end
end

----------------------------------------------------------------
-- Cały graf
----------------------------------------------------------------
function R.drawGraph(graph, selection, camera, _theme, _layout)
  selection = selection or { nodes = {}, links = {} }

  -- Linki pod spodem
  if graph.links then
    for _,link in ipairs(graph.links) do
      local sel = selection.links and (selection.links[link.id] or false)
      R.drawLink(link, camera, _theme, _layout, sel)
    end
  end

  -- Nody + porty
  if graph.nodes then
    for _,node in ipairs(graph.nodes) do
      local sel = selection.nodes and (selection.nodes[node.id] or false)
      R.drawNode(node, sel, camera, _theme, _layout)

      -- porty wej/wyj
      if node.inputs then
        for _,p in ipairs(node.inputs) do
          -- zaznacz „stronę” – pomaga portPosition
          p.__side = "in"
          R.drawPort(node, p, camera, _theme, _layout)
        end
      end
      if node.outputs then
        for _,p in ipairs(node.outputs) do
          p.__side = "out"
          R.drawPort(node, p, camera, _theme, _layout)
        end
      end
    end
  end
end

----------------------------------------------------------------
-- Overlay (np. debug info)
----------------------------------------------------------------
-- info: { lines = {"text1","text2",...}, x?, y? }
function R.drawOverlay(info, camera, _theme, _layout)
  if not info then return end
  local s, c = S(), C()
  local x = info.x or 8
  local y = info.y or 8
  local lines = info.lines or {}
  for i, txt in ipairs(lines) do
    rtext.DrawText(txt, x, y + (i-1)*(s.fontSize+2), s.fontSize, c.overlay)
  end
end

----------------------------------------------------------------
-- Szkielet głównego „kadru” (opcjonalnie, jeśli chcesz mieć jedno wywołanie)
----------------------------------------------------------------
function R.drawFrame(state)
  -- state: { graph, selection, camera }
  rcore.ClearBackground(C().bg)
  R.drawGrid(state.camera, theme)
  R.drawGraph(state.graph, state.selection, state.camera, theme, layout)
  if state.overlay then
    R.drawOverlay(state.overlay, state.camera, theme, layout)
  end
end

return R
