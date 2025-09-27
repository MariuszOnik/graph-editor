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
