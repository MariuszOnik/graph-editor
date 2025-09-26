--[[
Layout
------
Odpowiedzialność:
- Geometria nodów i portów: oblicza pozycje portów, rect-y, punkty zaczepienia linków.

Publiczne API (stub):
- nodeRect(node) -> {x,y,w,h}
- portPosition(node, port) -> {x,y} (world-space)
- linkPath(link, graph) -> {p0, p1, c0, c1}  -- np. krzywa Beziera
- worldToScreen(camera, x,y) / screenToWorld(camera, x,y)

Uwagi:
- Zero rysowania; tylko matematyka/położenia.
]]
