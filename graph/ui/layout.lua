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


--[[
Layout
------
Cel: wszystkie obliczenia geometrii edytora (bez rysowania).
Zero zależności od runtime/UI — czysta matematyka.

Kamera / układ współrzędnych
- "world"  = układ roboczy grafu (pozycje nodów, portów)
- "screen" = piksele okna (po zoom/pan)
- camera = { ox:number, oy:number, zoom:number }
  gdzie (ox,oy) to przesunięcie świata względem ekranu (pan),
  a zoom > 0 (1.0 = 100%).

Konfiguracja layoutu
- theme: dostarcza metryki (rozmiary nodów, portów, spacing)
- Reużyj pola z theme.sizes, np.:
  nodePaddingX, nodePaddingY,
  portRadius (dla data), portExecSize (dla exec),
  rowHeight, headerHeight, linkWidth, gridSize

API (publiczne)
- worldToScreen(camera, wx, wy) -> sx, sy
- screenToWorld(camera, sx, sy) -> wx, wy
- nodeRect(node, theme) -> { x, y, w, h }           -- w world
- portPosition(node, port, theme) -> { x, y }       -- w world (środek portu)
- linkPath(link, graph, theme) -> { p0, c0, c1, p1 } -- punkty dla krzywej Beziera
- linkPolyline(link, graph, theme, opts) -> { {x,y}, ... } -- aproksymacja krzywej
- linkAABB(link, graph, theme, opts) -> { x, y, w, h }
- snapToGrid(wx, wy, gridSize) -> gx, gy

Ustalenia:
- porty wejściowe (inputs) po lewej, wyjściowe (outputs) po prawej nodzie (domyślnie).
- porty exec (prostokąt) po „górze/dole” węzła lub nad/pod listą — decyzję trzymamy spójnie.
- node posiada: node.x, node.y (lewy–górny róg world), node.w?, node.h? (opcjonalnie; gdy brak → liczymy z treści/portów).
- port posiada: port.name, port.kind ("data"|"exec"), port.side? (opcjonalnie wymusza stronę).

Wydajność:
- Cache’uj wyniki (np. node._rect, link._poly, link._aabb) i unieważniaj przy zmianach.
]]


--[[
worldToScreen / screenToWorld
-----------------------------
Formuły (proste 2D bez obrotów):
sx = (wx * zoom) + ox
sy = (wy * zoom) + oy
wx = (sx - ox) / zoom
wy = (sy - oy) / zoom
]]
local function worldToScreen(camera, wx, wy)
  -- stub
  return 0, 0
end

local function screenToWorld(camera, sx, sy)
  -- stub
  return 0, 0
end


--[[
nodeRect
--------
Zwraca prostokąt w world-space dla nody.

Wejście:
- node: { x, y, w?, h?, title?, inputs:[], outputs:[], execIn?:[], execOut?:[] }
- theme: sizes.nodeMinW, sizes.nodePaddingX/Y, sizes.rowHeight, sizes.headerHeight, sizes.portGap

Pseudokod:
1) width:
   - Jeżeli node.w podany → użyj.
   - W przeciwnym razie minimum: sizes.nodeMinW.
   - (opcjonalnie: dopasuj do najdłuższej etykiety portu)
2) height:
   - header = sizes.headerHeight
   - rows   = max(#inputs, #outputs) * sizes.rowHeight
   - execRows (opcjonalnie) = (#execIn > 0 and rowHeight or 0) + (#execOut > 0 and rowHeight or 0)
   - h = header + rows + execRows + 2 * sizes.nodePaddingY
3) w = max(node.w or minW, minW) + 2 * sizes.nodePaddingX
4) return { x=node.x, y=node.y, w=w, h=h }
]]
local function nodeRect(node, theme)
  -- stub
  return { x=0, y=0, w=0, h=0 }
end


--[[
portPosition
------------
Pozycja środka portu (world). Zakładamy dwa pionowe „słupki” portów data:
- inputs (po lewej krawędzi nody)
- outputs (po prawej krawędzi nody)
Porty exec (jeśli używamy góra/dół) — wg osobnej reguły.

Wejście:
- node, port, theme
- użyj nodeRect(node, theme)

Pseudokod:
1) local r = nodeRect(node, theme)
2) jeśli port.kind == "data":
   - wyznacz indeks w kolumnie (np. i dla inputs lub j dla outputs)
   - y = r.y + sizes.headerHeight + sizes.nodePaddingY + index * sizes.rowHeight + sizes.rowHeight/2
   - jeśli port jest input:
       x = r.x  -- docelowo środek portu będzie lekko „na zewnątrz” krawędzi
       x = x - sizes.portRadius  (jeśli chcemy „odstawić” kółko w lewo)
     jeśli port jest output:
       x = r.x + r.w
       x = x + sizes.portRadius
3) jeśli port.kind == "exec":
   - np. execIn: w linii pod headerem (nad data)
     y = r.y + sizes.headerHeight/2  (lub dedykowana wysokość)
     x = r.x + (r.w * t), gdzie t∈[0..1] zależnie od pozycji/indeksu exec portu
   - analogicznie execOut: w dole nody
4) return { x, y }
]]
local function portPosition(node, port, theme)
  -- stub
  return { x=0, y=0 }
end


--[[
linkPath
--------
Zwraca punkty do krzywej Beziera 2D: p0 (start), c0, c1, p1 (end).
- p0 = pozycja portu źródłowego (output)
- p1 = pozycja portu docelowego (input)
- c0, c1 = kontrolne — bazują na dystansie poziomym i małym offsetcie pionowym.

Wejście:
- link: { fromNode, fromPort, toNode, toPort }
- graph: by pobrać referencje do nodów/portów
- theme: wpływ na „siłę” wybrzuszenia (sizes.bezierTensionX, sizes.bezierTensionY)

Pseudokod:
1) p0 = portPosition(fromNode, fromPort)
2) p1 = portPosition(toNode, toPort)
3) dx = |p1.x - p0.x|
   tx = clamp(dx * 0.5, min=40, max=200)  -- min/max możesz trzymać w theme
   c0 = { x = p0.x + tx, y = p0.y }
   c1 = { x = p1.x - tx, y = p1.y }
4) (opcjonalnie) dorzuć lekki offset Y zależny od różnicy wysokości:
   c0.y = c0.y + sign(p1.y - p0.y) * sizes.bezierTensionY
   c1.y = c1.y - sign(p1.y - p0.y) * sizes.bezierTensionY
5) return { p0, c0, c1, p1 }
]]
local function linkPath(link, graph, theme)
  -- stub
  return { {x=0,y=0}, {x=0,y=0}, {x=0,y=0}, {x=0,y=0} }
end


--[[
linkPolyline
------------
Aproksymuje krzywą Beziera polyline’em (lista punktów).
Przydaje się do hit-testu (point-line) i do rysowania bez funkcji krzywych.

Wejście:
- opts: { segments?:number }  -- domyślnie 16..24
Pseudokod:
1) local path = linkPath(link, graph, theme)
2) N = opts.segments or 16
3) for i=0..N:
     t = i / N
     B(t) = (1-t)^3*p0 + 3(1-t)^2*t*c0 + 3(1-t)*t^2*c1 + t^3*p1  -- (osobno x i y)
     table.insert(poly, {x=Bx, y=By})
4) return poly
]]
local function linkPolyline(link, graph, theme, opts)
  -- stub
  return {}
end


--[[
linkAABB
--------
Axis-Aligned Bounding Box polyline’u (szybki pre-check kolizji).
Pseudokod:
1) local poly = link._poly or linkPolyline(...)
2) minx,miny = +inf ; maxx,maxy = -inf
3) for p in poly: minx=min(minx,p.x) ... maxy=...
4) return { x=minx, y=miny, w=maxx-minx, h=maxy-miny }
]]
local function linkAABB(link, graph, theme, opts)
  -- stub
  return { x=0, y=0, w=0, h=0 }
end


--[[
snapToGrid
----------
Zaokrąglenie punktu world do siatki.
gx = round(wx / grid) * grid
gy = round(wy / grid) * grid
]]
local function snapToGrid(wx, wy, gridSize)
  -- stub
  return wx, wy
end


--[[
Uwagi implementacyjne:
- Zwracaj TYLKO liczby / tabele liczb — zero obiektów UI/raylib w tym module.
- Nie czytaj bezpośrednio z rcore/rtext/rshapes — layout to czysta matematyka,
  dzięki temu łatwo testować bez okna.
- Współpracuj z Theme: żadnych „magicznych stałych”. Wszystkie rozmiary i odstępy z theme.sizes.
- Jeżeli node ma dynamiczne wymiary (np. zależne od tekstu), przekaż preliczone w node (node.measuredW/H)
  albo zapewnij funkcję „measureNode(node, theme)” w innym module, a layout tylko to wykorzysta.
- Caching:
  * node._rect → unieważnij przy zmianie node.x/y/w/h lub zmianie portów
  * link._poly, link._aabb → unieważnij przy zmianie pozycji któregokolwiek końca

Eksport API:
Zdecyduj, czy zwracamy pojedynczą tabelę z funkcjami, np.:

local M = {
  worldToScreen = worldToScreen,
  screenToWorld = screenToWorld,
  nodeRect      = nodeRect,
  portPosition  = portPosition,
  linkPath      = linkPath,
  linkPolyline  = linkPolyline,
  linkAABB      = linkAABB,
  snapToGrid    = snapToGrid,
}
return M
]]
