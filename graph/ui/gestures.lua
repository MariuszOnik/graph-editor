--[[
Gestures
--------
Odpowiedzialność:
- Składanie prymitywów wejścia w gesty (drag, click, double-click, pinch-zoom, long-press).
- Uproszczenie dla Controller.

Publiczne API (stub):
- update(input, dt) -> {events}
  -- events: { type="dragStart"/"drag"/"dragEnd", x,y, dx,dy, button },
            { type="click", x,y, button, count },
            { type="wheel", delta, x,y },
            { type="pinch", scale, centerX, centerY },
            { type="key", code, pressed/released }

Uwagi:
- Brak bezpośredniej zależności od graph.
]]
-- graph/ui/gestures.lua
-- Składanie prymitywów wejścia w gesty (touch + opcjonalnie mouse/wheel).
-- Public API: update(input, dt) -> {events}
--  - input może być nil => użyjemy rcore bezpośrednio
--  - events: { type="dragStart"/"drag"/"dragEnd", x,y, dx,dy, button }
--            { type="click", x,y, button, count }
--            { type="wheel", delta, x,y }
--            { type="pinch", scale, centerX, centerY }
--            { type="longpress", x,y, button }
--            { type="key", code, pressed }   -- (opcjonalne; tylko gdy input.keyEvents dostępne)

local rcore_ok, rcore = pcall(require, "rcore")

local G = {}
G.__index = G

local DEFAULTS = {
  enable_mouse     = true,     -- wygoda na PC; wyłącz na urządzeniach touch-only
  double_ms        = 250,      -- okno 2x kliknięcia
  longpress_ms     = 400,      -- kiedy traktować przytrzymanie jako long-press
  tap_slop_px      = 6,        -- ruch dopuszczalny dla "tapu"
  drag_threshold_px= 3,        -- ile ruszyć zanim zaczniemy "drag"
  pinch_k          = 1.0,      -- 1.0 = bez modyfikatora; ewentualna czułość mnożnikowa
}

local function now_ms()
  if rcore_ok and rcore.GetTimeMs then return rcore.GetTimeMs() end
  -- fallback: sekundy * 1000
  if rcore_ok and rcore.GetTime then return math.floor(rcore.GetTime() * 1000) end
  return math.floor(os.clock() * 1000)
end

local function dist2(x1,y1,x2,y2)
  local dx, dy = x2 - x1, y2 - y1
  return dx*dx + dy*dy
end

-- Konstruktor
function G.new(opts)
  opts = opts or {}
  local self = setmetatable({}, G)
  self.cfg = {
    enable_mouse      = (opts.enable_mouse ~= nil) and opts.enable_mouse or DEFAULTS.enable_mouse,
    double_ms         = opts.double_ms         or DEFAULTS.double_ms,
    longpress_ms      = opts.longpress_ms      or DEFAULTS.longpress_ms,
    tap_slop_px       = opts.tap_slop_px       or DEFAULTS.tap_slop_px,
    drag_threshold_px = opts.drag_threshold_px or DEFAULTS.drag_threshold_px,
    pinch_k           = opts.pinch_k           or DEFAULTS.pinch_k,
  }

  -- Stan dotyku
  self.touch = {
    active     = {},     -- [id] = {sx,sy, x,y, start_ms, last_ms}
    order      = {},     -- posortowane identyfikatory (do pinch)
    dragging   = false,
    drag_id    = nil,
    drag_started = false,
    last_x     = 0, last_y = 0,
    click_ms   = 0,      -- ostatni czas tap/click (dla double)
    click_pos  = {x=0,y=0},
    pinch_last = nil,    -- ostatnia odległość dla pinch
  }

  -- Stan myszy (opcjonalnie)
  self.mouse = {
    down       = false,
    button     = 0,      -- 0=LPM 1=PPM 2=ŚPM (upraszczamy)
    start_ms   = 0,
    sx=0, sy=0,
    x=0, y=0,
    dragging   = false,
    last_x=0, last_y=0,
    click_ms   = 0,
    click_pos  = {x=0,y=0},
  }

  return self
end

-- Pomoc: odczyt źródeł inputu
local function read_touch_points()
  if not rcore_ok or not rcore.GetTouchPointCount then return 0, {} end
  local n = rcore.GetTouchPointCount()
  local list = {}
  for i=0,n-1 do
    local id = rcore.GetTouchPointId(i)
    local x,y = rcore.GetTouchPosition(i)
    list[#list+1] = {id=id,x=x,y=y}
  end
  return n, list
end

local function read_mouse()
  if not rcore_ok then return nil end
  local x = rcore.GetMouseX and rcore.GetMouseX() or 0
  local y = rcore.GetMouseY and rcore.GetMouseY() or 0
  local wheel = rcore.GetMouseWheelMove and rcore.GetMouseWheelMove() or 0
  local l = rcore.IsMouseButtonDown and rcore.IsMouseButtonDown(rcore.MOUSE_BUTTON_LEFT or 0) or false
  local r = rcore.IsMouseButtonDown and rcore.IsMouseButtonDown(rcore.MOUSE_BUTTON_RIGHT or 1) or false
  local m = rcore.IsMouseButtonDown and rcore.IsMouseButtonDown(rcore.MOUSE_BUTTON_MIDDLE or 2) or false
  local pressedL = rcore.IsMouseButtonPressed and rcore.IsMouseButtonPressed(rcore.MOUSE_BUTTON_LEFT or 0) or false
  local releasedL= rcore.IsMouseButtonReleased and rcore.IsMouseButtonReleased(rcore.MOUSE_BUTTON_LEFT or 0) or false
  return {
    x=x,y=y, wheel=wheel,
    l=l,r=r,m=m,
    pressedL=pressedL, releasedL=releasedL,
  }
end

-- Główne API
-- input: opcjonalny adapter z polami:
--  * keyEvents(): zwraca listę { {code=..., pressed=true/false}, ... }
function G:update(input, dt)
  local ev = {}

  -- --- TOUCH ---
  do
    local n, pts = read_touch_points()
    local t = self.touch
    local now = now_ms()
    local seen = {}

    -- aktualizacja/nowe
    for _,p in ipairs(pts) do
      seen[p.id] = true
      local slot = t.active[p.id]
      if not slot then
        t.active[p.id] = { sx=p.x, sy=p.y, x=p.x, y=p.y, start_ms=now, last_ms=now }
        t.order[#t.order+1] = p.id
      else
        slot.x, slot.y, slot.last_ms = p.x, p.y, now
      end
    end
    -- usunięte (lift)
    for id,slot in pairs(t.active) do
      if not seen[id] then
        -- end of finger
        if t.dragging and t.drag_id == id and t.drag_started then
          table.insert(ev, { type="dragEnd", x=slot.x, y=slot.y, dx=0, dy=0, button=0 })
        else
          -- kandydat na click/tap/longpress (jeśli nie było drag)
          local d2 = dist2(slot.sx, slot.sy, slot.x, slot.y)
          local within_slop = d2 <= (self.cfg.tap_slop_px*self.cfg.tap_slop_px)
          local dur = now - slot.start_ms
          if within_slop then
            if dur >= self.cfg.longpress_ms then
              table.insert(ev, { type="longpress", x=slot.x, y=slot.y, button=0 })
            else
              -- click/double-click
              local dc = (now - t.click_ms <= self.cfg.double_ms and
                          dist2(t.click_pos.x,t.click_pos.y, slot.x,slot.y) <= (self.cfg.tap_slop_px*self.cfg.tap_slop_px))
              local count = dc and 2 or 1
              table.insert(ev, { type="click", x=slot.x, y=slot.y, button=0, count=count })
              t.click_ms = now
              t.click_pos.x, t.click_pos.y = slot.x, slot.y
            end
          end
        end
        -- usuń
        t.active[id] = nil
        -- usuń z order
        for i=#t.order,1,-1 do if t.order[i]==id then table.remove(t.order,i) break end end
        t.dragging, t.drag_id, t.drag_started = false, nil, false
        t.pinch_last = nil
      end
    end

    -- aktualny stan: 0/1/2+ palców
    local count = 0
    for _ in pairs(t.active) do count = count + 1 end

    if count == 1 then
      local id = t.order[1]
      local s = t.active[id]
      if s then
        local d2 = dist2(s.sx,s.sy,s.x,s.y)
        if not t.dragging and d2 >= (self.cfg.drag_threshold_px*self.cfg.drag_threshold_px) then
          t.dragging, t.drag_id = true, id
          t.drag_started = true
          t.last_x, t.last_y = s.x, s.y
          table.insert(ev, { type="dragStart", x=s.x, y=s.y, dx=0, dy=0, button=0 })
        elseif t.dragging and t.drag_id == id then
          local dx, dy = s.x - t.last_x, s.y - t.last_y
          if dx ~= 0 or dy ~= 0 then
            t.last_x, t.last_y = s.x, s.y
            table.insert(ev, { type="drag", x=s.x, y=s.y, dx=dx, dy=dy, button=0 })
          end
        end
      end

    elseif count >= 2 then
      -- PINCH (bierzemy 2 pierwsze id dla deterministyczności)
      local id1, id2 = t.order[1], t.order[2]
      local a, b = t.active[id1], t.active[id2]
      if a and b then
        local cx, cy = (a.x + b.x)/2, (a.y + b.y)/2
        local dist = math.sqrt(dist2(a.x,a.y,b.x,b.y))
        if t.pinch_last then
          local dd = dist - t.pinch_last
          if dd ~= 0 then
            local scale = 1.0 + (dd / 200.0) * self.cfg.pinch_k
            table.insert(ev, { type="pinch", scale=scale, centerX=cx, centerY=cy })
          end
        end
        t.pinch_last = dist
      end
    end
  end

  -- --- MOUSE / WHEEL (opcjonalnie) ---
  if self.cfg.enable_mouse and rcore_ok then
    local m = read_mouse()
    if m then
      local now = now_ms()
      -- wheel
      if m.wheel and m.wheel ~= 0 then
        table.insert(ev, { type="wheel", delta = m.wheel, x = m.x, y = m.y })
      end
      -- button L
      if m.pressedL and not self.mouse.down then
        self.mouse.down = true
        self.mouse.button = 0
        self.mouse.start_ms = now
        self.mouse.sx, self.mouse.sy = m.x, m.y
        self.mouse.x,  self.mouse.y  = m.x, m.y
        self.mouse.last_x, self.mouse.last_y = m.x, m.y
        self.mouse.dragging = false
      end
      if self.mouse.down then
        self.mouse.x, self.mouse.y = m.x, m.y
        local d2 = dist2(self.mouse.sx, self.mouse.sy, m.x, m.y)
        if not self.mouse.dragging and d2 >= (self.cfg.drag_threshold_px*self.cfg.drag_threshold_px) then
          self.mouse.dragging = true
          table.insert(ev, { type="dragStart", x=m.x, y=m.y, dx=0, dy=0, button=0 })
        elseif self.mouse.dragging then
          local dx, dy = m.x - self.mouse.last_x, m.y - self.mouse.last_y
          if dx ~= 0 or dy ~= 0 then
            table.insert(ev, { type="drag", x=m.x, y=m.y, dx=dx, dy=dy, button=0 })
          end
        end
        self.mouse.last_x, self.mouse.last_y = m.x, m.y
      end
      if m.releasedL and self.mouse.down then
        if self.mouse.dragging then
          table.insert(ev, { type="dragEnd", x=m.x, y=m.y, dx=0, dy=0, button=0 })
        else
          local dur = now - self.mouse.start_ms
          local within_slop = dist2(self.mouse.sx, self.mouse.sy, m.x, m.y) <= (self.cfg.tap_slop_px*self.cfg.tap_slop_px)
          if within_slop then
            if dur >= self.cfg.longpress_ms then
              table.insert(ev, { type="longpress", x=m.x, y=m.y, button=0 })
            else
              local dc = (now - self.mouse.click_ms <= self.cfg.double_ms and
                          dist2(self.mouse.click_pos.x,self.mouse.click_pos.y, m.x,m.y) <= (self.cfg.tap_slop_px*self.cfg.tap_slop_px))
              local count = dc and 2 or 1
              table.insert(ev, { type="click", x=m.x, y=m.y, button=0, count=count })
              self.mouse.click_ms = now
              self.mouse.click_pos.x, self.mouse.click_pos.y = m.x, m.y
            end
          end
        end
        self.mouse.down = false
        self.mouse.dragging = false
      end
    end
  end

  -- --- KEYS (opcjonalnie przez adapter) ---
  if input and input.keyEvents then
    local keys = input.keyEvents()
    if keys then
      for _,k in ipairs(keys) do
        table.insert(ev, { type="key", code=k.code, pressed = not not k.pressed })
      end
    end
  end

  return ev
end

return G
