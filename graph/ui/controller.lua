-- graph/ui/controller.lua
-- Controller (Input -> Actions): TOUCH (via gestures.lua) + GAMEPAD. Bez myszy i klawiatury.
-- Zwraca listę akcji do warstwy Editor. Zero rysowania i zero runtime'u.

local rcore    = require("rcore")
local layout   = require("graph.ui.layout")
local hit      = require("graph.ui.hit")
local theme    = require("graph.ui.theme")
local Gestures = require("graph.ui.gestures")

local Controller = {}
Controller.__index = Controller

-- Konfiguracja (tylko to, czego faktycznie używamy)
local DEFAULTS = {
  -- Gamepad
  gp_id        = 0,
  cursor_speed = 900,   -- px/s (screen)
  pan_speed    = 1200,  -- px/s (screen) -> world przeliczane przez zoom
  zoom_speed   = 1.4,   -- mnożnik/s przez triggery
  deadzone     = 0.18,
  -- Touch/gestures
  longpress_ms = 350,   -- pasuje do gestures
  box_min_px   = 6,
  pinch_k      = 1.0,
}

local function clamp(v, a, b) return (v<a) and a or ((v>b) and b or v) end
local function dz(x, y, dzv)
  local m = math.sqrt(x*x + y*y)
  if m < dzv then return 0,0 end
  local k = (m - dzv) / (1 - dzv)
  return (x/m)*k, (y/m)*k
end

-- Konstruktor
function Controller.new(opts)
  opts = opts or {}
  local self = setmetatable({}, Controller)
  self.cfg = {
    gp_id        = opts.gp_id        or DEFAULTS.gp_id,
    cursor_speed = opts.cursor_speed or DEFAULTS.cursor_speed,
    pan_speed    = opts.pan_speed    or DEFAULTS.pan_speed,
    zoom_speed   = opts.zoom_speed   or DEFAULTS.zoom_speed,
    deadzone     = opts.deadzone     or DEFAULTS.deadzone,
    longpress_ms = opts.longpress_ms or DEFAULTS.longpress_ms,
    box_min_px   = opts.box_min_px   or DEFAULTS.box_min_px,
    pinch_k      = opts.pinch_k      or DEFAULTS.pinch_k,
  }

  -- Gestures: tylko dotyk (bez myszy/klawiatury)
  self.gestures = Gestures.new({ enable_mouse = false, longpress_ms = self.cfg.longpress_ms, pinch_k = self.cfg.pinch_k })

  -- Stan
  self.state = {
    mode = "idle", -- "idle" | "dragNode" | "dragLink" | "box"
    -- Gamepad cursor (screen-space)
    cx = rcore.GetScreenWidth()/2,
    cy = rcore.GetScreenHeight()/2,
    press_pos = nil,
    drag_node = nil,   -- {nodeId, lastWX, lastWY}
    drag_link = nil,   -- {from=hitPortResult}
    box_rect_screen = nil, -- {x,y,w,h}
  }

  return self
end

-- Publiczne API
-- update(dt, graph, selection, camera) -> {actions}
function Controller:update(dt, graph, selection, camera)
  local actions = {}

  -- 1) Touch: pobierz zdarzenia wysokopoziomowe
  local tev = self.gestures:update(nil, dt)  -- nil => użyj rcore wewnątrz gestures
  if tev and #tev > 0 then
    self:_handleTouchEvents(tev, graph, camera, actions)
  end

  -- 2) Gamepad
  self:_handleGamepad(dt, graph, camera, actions)

  return actions
end

----------------------------------------------------------------
-- TOUCH via gestures.lua
----------------------------------------------------------------
function Controller:_handleTouchEvents(events, graph, camera, actions)
  for _,e in ipairs(events) do
    if e.type == "pinch" then
      -- zoom względny z pivotem w world
      local wx, wy = layout.screenToWorld(camera, e.centerX, e.centerY)
      table.insert(actions, { type="zoom", scale=e.scale, pivotX=wx, pivotY=wy })

    elseif e.type == "dragStart" then
      -- ustal co pod palcem: port > node > box
      local hp = hit.hitPort(graph, e.x, e.y, camera, layout, theme)
      if hp then
        self.state.mode = "dragLink"
        self.state.drag_link = { from = hp }
        table.insert(actions, { type="link.begin", nodeId=hp.nodeId, portName=hp.portName, side=hp.side })
      else
        local nid = hit.hitNode(graph, e.x, e.y, camera, layout)
        if nid then
          local wx, wy = layout.screenToWorld(camera, e.x, e.y)
          self.state.mode = "dragNode"
          self.state.drag_node = { nodeId=nid, lastWX=wx, lastWY=wy }
          table.insert(actions, { type="node.dragStart", id=nid, at={x=wx,y=wy} })
        else
          self.state.mode = "box"
          self.state.box_rect_screen = { x=e.x, y=e.y, w=0, h=0 }
          table.insert(actions, { type="select.boxStart", at={x=e.x,y=e.y}, space="screen" })
        end
      end

    elseif e.type == "drag" then
      if self.state.mode == "dragNode" and self.state.drag_node then
        local wx, wy = layout.screenToWorld(camera, e.x, e.y)
        local dx, dy = wx - self.state.drag_node.lastWX, wy - self.state.drag_node.lastWY
        if dx ~= 0 or dy ~= 0 then
          self.state.drag_node.lastWX, self.state.drag_node.lastWY = wx, wy
          table.insert(actions, { type="node.drag", id=self.state.drag_node.nodeId, dx=dx, dy=dy })
        end
      elseif self.state.mode == "dragLink" and self.state.drag_link then
        local wx, wy = layout.screenToWorld(camera, e.x, e.y)
        table.insert(actions, { type="link.preview", to={x=wx,y=wy} })
      elseif self.state.mode == "box" and self.state.box_rect_screen then
        self.state.box_rect_screen.w = e.x - self.state.box_rect_screen.x
        self.state.box_rect_screen.h = e.y - self.state.box_rect_screen.y
      end

    elseif e.type == "dragEnd" then
      if self.state.mode == "dragNode" and self.state.drag_node then
        table.insert(actions, { type="node.dragEnd", id=self.state.drag_node.nodeId })
      elseif self.state.mode == "dragLink" and self.state.drag_link then
        local hp = hit.hitPort(graph, e.x, e.y, camera, layout, theme)
        if hp then
          table.insert(actions, { type="link.commit", from=self.state.drag_link.from, to=hp })
        else
          table.insert(actions, { type="link.cancel" })
        end
      elseif self.state.mode == "box" and self.state.box_rect_screen then
        local r = self.state.box_rect_screen
        if math.abs(r.w) >= self.cfg.box_min_px and math.abs(r.h) >= self.cfg.box_min_px then
          local x0,y0 = layout.screenToWorld(camera, r.x, r.y)
          local x1,y1 = layout.screenToWorld(camera, r.x+r.w, r.y+r.h)
          local rx, ry = math.min(x0,x1), math.min(y0,y1)
          local rw, rh = math.abs(x1-x0), math.abs(y1-y0)
          table.insert(actions, { type="select.boxEnd", rect={x=rx,y=ry,w=rw,h=rh} })
        else
          table.insert(actions, { type="select.boxCancel" })
        end
      end
      -- reset
      self.state.mode = "idle"
      self.state.drag_node = nil
      self.state.drag_link = nil
      self.state.box_rect_screen = nil

    elseif e.type == "longpress" then
      -- możesz tu dodać np. kontekstowe menu – na razie pomijamy
    elseif e.type == "click" then
      -- nic – cały „link/node” robimy gestem drag
    end
  end
end

----------------------------------------------------------------
-- GAMEPAD (bez klawiatury/myszy)
----------------------------------------------------------------
function Controller:_handleGamepad(dt, graph, camera, actions)
  local id = self.cfg.gp_id
  if not (rcore.IsGamepadAvailable and rcore.IsGamepadAvailable(id)) then return end

  local W, H = rcore.GetScreenWidth(), rcore.GetScreenHeight()
  local s = self.state
  local cfg = self.cfg

  -- Gałki
  local lx = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_LEFT_X or 0)
  local ly = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_LEFT_Y or 1)
  local rx = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_RIGHT_X or 2)
  local ry = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_RIGHT_Y or 3)
  lx, ly = dz(lx, ly, cfg.deadzone)
  rx, ry = dz(rx, ry, cfg.deadzone)

  -- Triggery -> zoom
  local lt = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_LEFT_TRIGGER or 4)
  local rt = rcore.GetGamepadAxisMovement(id, rcore.GAMEPAD_AXIS_RIGHT_TRIGGER or 5)

  -- Przyciski
  local A_down = rcore.IsGamepadButtonDown(id, rcore.GAMEPAD_BUTTON_RIGHT_FACE_DOWN or 0)
  local A_rel  = rcore.IsGamepadButtonReleased and rcore.IsGamepadButtonReleased(id, rcore.GAMEPAD_BUTTON_RIGHT_FACE_DOWN or 0)
  local B_hit  = rcore.IsGamepadButtonPressed and rcore.IsGamepadButtonPressed(id, rcore.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT or 1)
  local RB     = rcore.IsGamepadButtonDown(id, rcore.GAMEPAD_BUTTON_RIGHT_TRIGGER_1 or 7) -- pan mode (alternatywa do prawej gałki)

  -- Panning kamerą prawą gałką (screen) -> world
  if math.abs(rx) > 0 or math.abs(ry) > 0 or RB then
    local z = (camera.zoom == 0) and 1 or camera.zoom
    local pdx = -rx * cfg.pan_speed * dt / z
    local pdy = -ry * cfg.pan_speed * dt / z
    if RB then pdx = pdx * 1.2; pdy = pdy * 1.2 end
    if pdx ~= 0 or pdy ~= 0 then
      table.insert(actions, { type="pan", dx=pdx, dy=pdy })
    end
  end

  -- Wirtualny kursor lewą gałką (screen-space)
  s.cx = clamp(s.cx + (lx * cfg.cursor_speed * dt), 0, W)
  s.cy = clamp(s.cy + (ly * cfg.cursor_speed * dt), 0, H)

  -- Zoom triggerami (pivot = pod kursorem, w world)
  local zoomAxis = (rt - math.max(0, lt))
  if math.abs(zoomAxis) > 0.01 then
    local factor = 1.0 + (zoomAxis * cfg.zoom_speed * dt)
    factor = clamp(factor, 0.5, 1.5)
    local wx, wy = layout.screenToWorld(camera, s.cx, s.cy)
    table.insert(actions, { type="zoom", scale=factor, pivotX=wx, pivotY=wy })
  end

  -- Interakcje A (drag node/link, box select)
  if A_down and self.state.mode == "idle" then
    self.state.press_pos = {x=s.cx, y=s.cy}
    -- priorytet: port -> node -> box
    local hp = hit.hitPort(graph, s.cx, s.cy, camera, layout, theme)
    if hp then
      self.state.mode = "dragLink"
      self.state.drag_link = { from = hp }
      table.insert(actions, { type="link.begin", nodeId=hp.nodeId, portName=hp.portName, side=hp.side })
    else
      local nid = hit.hitNode(graph, s.cx, s.cy, camera, layout)
      if nid then
        local wx, wy = layout.screenToWorld(camera, s.cx, s.cy)
        self.state.mode = "dragNode"
        self.state.drag_node = { nodeId=nid, lastWX=wx, lastWY=wy }
        table.insert(actions, { type="node.dragStart", id=nid, at={x=wx,y=wy} })
      else
        self.state.mode = "box"
        self.state.box_rect_screen = { x=s.cx, y=s.cy, w=0, h=0 }
        table.insert(actions, { type="select.boxStart", at={x=s.cx,y=s.cy}, space="screen" })
      end
    end
  end

  if A_down then
    if self.state.mode == "dragNode" and self.state.drag_node then
      local wx, wy = layout.screenToWorld(camera, s.cx, s.cy)
      local dx, dy = wx - self.state.drag_node.lastWX, wy - self.state.drag_node.lastWY
      if dx ~= 0 or dy ~= 0 then
        self.state.drag_node.lastWX, self.state.drag_node.lastWY = wx, wy
        table.insert(actions, { type="node.drag", id=self.state.drag_node.nodeId, dx=dx, dy=dy })
      end
    elseif self.state.mode == "dragLink" and self.state.drag_link then
      local wx, wy = layout.screenToWorld(camera, s.cx, s.cy)
      table.insert(actions, { type="link.preview", to={x=wx,y=wy} })
    elseif self.state.mode == "box" and self.state.box_rect_screen then
      self.state.box_rect_screen.w = s.cx - self.state.box_rect_screen.x
      self.state.box_rect_screen.h = s.cy - self.state.box_rect_screen.y
    end
  end

  if A_rel then
    if self.state.mode == "dragLink" and self.state.drag_link then
      local hp = hit.hitPort(graph, s.cx, s.cy, camera, layout, theme)
      if hp then
        table.insert(actions, { type="link.commit", from=self.state.drag_link.from, to=hp })
      else
        table.insert(actions, { type="link.cancel" })
      end
    elseif self.state.mode == "dragNode" and self.state.drag_node then
      table.insert(actions, { type="node.dragEnd", id=self.state.drag_node.nodeId })
    elseif self.state.mode == "box" and self.state.box_rect_screen then
      local r = self.state.box_rect_screen
      if math.abs(r.w) >= self.cfg.box_min_px and math.abs(r.h) >= self.cfg.box_min_px then
        local x0,y0 = layout.screenToWorld(camera, r.x, r.y)
        local x1,y1 = layout.screenToWorld(camera, r.x+r.w, r.y+r.h)
        local rx, ry = math.min(x0,x1), math.min(y0,y1)
        local rw, rh = math.abs(x1-x0), math.abs(y1-y0)
        table.insert(actions, { type="select.boxEnd", rect={x=rx,y=ry,w=rw,h=rh} })
      else
        table.insert(actions, { type="select.boxCancel" })
      end
    end
    -- reset
    self.state.mode = "idle"
    self.state.drag_node = nil
    self.state.drag_link = nil
    self.state.box_rect_screen = nil
  end

  -- B = cancel bieżącej operacji
  if B_hit then
    if self.state.mode == "dragLink" then
      table.insert(actions, { type="link.cancel" })
    elseif self.state.mode == "dragNode" then
      table.insert(actions, { type="node.dragCancel", id = self.state.drag_node and self.state.drag_node.nodeId })
    elseif self.state.mode == "box" then
      table.insert(actions, { type="select.boxCancel" })
    end
    self.state.mode = "idle"
    self.state.drag_node = nil
    self.state.drag_link = nil
    self.state.box_rect_screen = nil
  end
end

return Controller
