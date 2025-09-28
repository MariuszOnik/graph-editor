-- graph/ui/hit.lua
-- Hit-testing dla edytora grafu: node / port / link / rect.
-- Zależności: layout (nodeRect/portPosition/linkPolyline/linkAABB/screenToWorld), theme.sizes.

local layout  = require("graph.ui.layout")
local theme   = require("graph.ui.theme")

local H = {}

-- --- helpers (czysta matematyka) ------------------------------------------

local function S()
  local s = theme.sizes or theme.metrics or {}
  return {
    portRadius     = s.portRadius     or 5,
    portExecSize   = s.portExecSize   or 10,
    linkWidth      = s.linkWidth      or 2,
    hitExtra       = s.hitExtra       or 3,   -- dodatkowy luz dla UX
  }
end

local function pointInRect(px, py, r)
  return (px >= r.x) and (px <= r.x + r.w) and (py >= r.y) and (py <= r.y + r.h)
end

local function rectsOverlap(a, b)
  return not (a.x + a.w < b.x or b.x + b.w < a.x or a.y + a.h < b.y or b.y + b.h < a.y)
end

local function dist2(a, b) -- kwadrat odległości
  local dx, dy = a.x - b.x, a.y - b.y
  return dx*dx + dy*dy
end

-- Odległość punkt–odcinek (a,b) w 2D
local function pointSegmentDistance(px, py, ax, ay, bx, by)
  local vx, vy = bx - ax, by - ay
  local wx, wy = px - ax, py - ay
  local vv = vx*vx + vy*vy
  if vv == 0 then
    local dx, dy = px - ax, py - ay
    return math.sqrt(dx*dx + dy*dy)
  end
  local t = (wx*vx + wy*vy) / vv
  if t < 0 then t = 0 elseif t > 1 then t = 1 end
  local cx, cy = ax + t*vx, ay + t*vy
  local dx, dy = px - cx, py - cy
  return math.sqrt(dx*dx + dy*dy)
end

local function segmentIntersect(ax, ay, bx, by, cx, cy, dx, dy)
  local function orient(px, py, qx, qy, rx, ry)
    return (qy - py) * (rx - qx) - (qx - px) * (ry - qy)
  end
  local o1 = orient(ax, ay, bx, by, cx, cy)
  local o2 = orient(ax, ay, bx, by, dx, dy)
  local o3 = orient(cx, cy, dx, dy, ax, ay)
  local o4 = orient(cx, cy, dx, dy, bx, by)
  if (o1 == 0 and o2 == 0 and o3 == 0 and o4 == 0) then
    -- kolinearne: sprawdź pokrywanie się proj. na x i y
    local function between(p, q, r) return math.min(p, r) <= q and q <= math.max(p, r) end
    return (between(ax, cx, bx) and between(ay, cy, by)) or
           (between(ax, dx, bx) and between(ay, dy, by)) or
           (between(cx, ax, dx) and between(cy, ay, dy)) or
           (between(cx, bx, dx) and between(cy, by, dy))
  end
  return (o1 == 0 or o2 == 0 or (o1 > 0) ~= (o2 > 0)) and
         (o3 == 0 or o4 == 0 or (o3 > 0) ~= (o4 > 0))
end

local function segmentIntersectsRect(ax, ay, bx, by, r)
  if pointInRect(ax, ay, r) or pointInRect(bx, by, r) then return true end
  local x0, y0 = r.x, r.y
  local x1, y1 = r.x + r.w, r.y + r.h
  return segmentIntersect(ax, ay, bx, by, x0, y0, x1, y0) or
         segmentIntersect(ax, ay, bx, by, x1, y0, x1, y1) or
         segmentIntersect(ax, ay, bx, by, x1, y1, x0, y1) or
         segmentIntersect(ax, ay, bx, by, x0, y1, x0, y0)
end

-- --- API: hitNode ----------------------------------------------------------

-- Zwraca id najwyższego noda pod kursorem (screen-space -> world).
function H.hitNode(graph, x_screen, y_screen, camera, _layout)
  if not (graph and graph.nodes) then return nil end
  local wx, wy = layout.screenToWorld(camera, x_screen, y_screen)
  -- iteruj od góry (ostatni rysowany = najwyższy)
  for i = #graph.nodes, 1, -1 do
    local node = graph.nodes[i]
    local r = layout.nodeRect(node)
    if pointInRect(wx, wy, r) then
      return node.id or node.uid or node.name or i
    end
  end
  return nil
end

-- --- API: hitPort ----------------------------------------------------------

-- Zwraca {nodeId, portName, kind ("data"|"exec"), side ("in"|"out"), index} lub nil
function H.hitPort(graph, x_screen, y_screen, camera, _layout, _theme)
  if not (graph and graph.nodes) then return nil end
  local s = S()
  local wx, wy = layout.screenToWorld(camera, x_screen, y_screen)

  -- od najwyższego noda
  for i = #graph.nodes, 1, -1 do
    local node = graph.nodes[i]

    local function testPorts(ports, side)
      if not ports then return nil end
      for idx, port in ipairs(ports) do
        local p = { __side = side, __index = idx, name = port.name, kind = port.kind }
        local px, py = layout.portPosition(node, p)
        local kind = (port.kind == "exec") and "exec" or "data"
        if kind == "data" then
          if dist2({x=wx,y=wy}, {x=px,y=py}) <= (s.portRadius * s.portRadius) then
            return { nodeId = node.id, portName = port.name, kind = "data", side = side, index = idx }
          end
        else
          local half = s.portExecSize * 0.5
          local r = { x = px - half, y = py - half, w = s.portExecSize, h = s.portExecSize }
          if pointInRect(wx, wy, r) then
            return { nodeId = node.id, portName = port.name, kind = "exec", side = side, index = idx }
          end
        end
      end
      return nil
    end

    -- najpierw porty (żeby miały priorytet nad tłem nody)
    local hit = testPorts(node.inputs, "in") or testPorts(node.outputs, "out")
    if hit then return hit end
  end

  return nil
end

-- --- API: hitLink ----------------------------------------------------------

-- Zwraca linkId|nil
function H.hitLink(graph, x_screen, y_screen, camera, _layout, _theme)
  if not (graph and graph.links) then return nil end
  local s = S()
  local wx, wy = layout.screenToWorld(camera, x_screen, y_screen)
  local tol = (s.linkWidth * 0.6) + s.hitExtra

  for i = #graph.links, 1, -1 do
    local link = graph.links[i]

    -- AABB pre-check (z tolerancją)
    local aabb = link._aabb or layout.linkAABB(link, graph)
    if aabb then
      local expanded = { x = aabb.x - tol, y = aabb.y - tol, w = aabb.w + 2*tol, h = aabb.h + 2*tol }
      if not pointInRect(wx, wy, expanded) then goto continue end
    end

    -- Polyline (cache lub licz)
    local poly = link._poly or layout.linkPolyline(link, graph, nil, {segments=16})
    if #poly >= 2 then
      for j = 1, #poly - 1 do
        local a, b = poly[j], poly[j+1]
        local d = pointSegmentDistance(wx, wy, a.x, a.y, b.x, b.y)
        if d <= tol then
          return link.id or i
        end
      end
    end

    ::continue::
  end

  return nil
end

-- --- API: hitRect ----------------------------------------------------------

-- Zaznaczenie obszarem (rect w world-space).
-- Zwraca { nodeIds = {...}, linkIds = {...} }
function H.hitRect(graph, rectWorld, _layout)
  local out = { nodeIds = {}, linkIds = {} }
  if not graph then return out end

  -- Nody
  if graph.nodes then
    for _, node in ipairs(graph.nodes) do
      local r = layout.nodeRect(node)
      if rectsOverlap(r, rectWorld) then
        table.insert(out.nodeIds, node.id)
      end
    end
  end

  -- Linki (opcjonalnie droższe, więc tylko jeśli są)
  if graph.links then
    for _, link in ipairs(graph.links) do
      local aabb = link._aabb or layout.linkAABB(link, graph)
      if aabb and rectsOverlap(aabb, rectWorld) then
        local poly = link._poly or layout.linkPolyline(link, graph, nil, {segments=16})
        -- heurystyka: czy któryś segment wchodzi w rect
        local hit = false
        for i = 1, #poly - 1 do
          local a, b = poly[i], poly[i+1]
          if segmentIntersectsRect(a.x, a.y, b.x, b.y, rectWorld) then
            hit = true
            break
          end
        end
        if hit then table.insert(out.linkIds, link.id) end
      end
    end
  end

  return out
end

return H
