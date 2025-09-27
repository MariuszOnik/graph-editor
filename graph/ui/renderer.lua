--[[
Renderer (View)
---------------
Odpowiedzialność:
- Rysowanie edytora grafu (grid, nody, porty, linki, selekcje, overlaye).
- Zero logiki grafu i runtime; tylko prezentacja.

Wejścia (dane wejściowe):
- graph     : Graph (z core)
- selection : { nodes = set(nodeId), links = set(linkId) }
- camera    : { ox, oy, zoom } -- world->screen
- theme     : Theme
- layout    : Layout (pozycje portów w nodzie itp.)

Publiczne API (stub):
- drawGrid(camera, theme)
- drawGraph(graph, selection, camera, theme, layout)
- drawNode(node, isSelected, camera, theme, layout)
- drawPort(node, port, camera, theme, layout)
- drawLink(link, camera, theme)
- drawOverlay(info) -- np. podpowiedzi, statusy

Uwagi:
- Używa rcore/rshapes/rtext/rtextures do rysowania.
- Nie modyfikuje graph; nic nie zapisuje stanu.
]]
