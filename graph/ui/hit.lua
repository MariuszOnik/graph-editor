--[[
Hit (Hit-testing)
-----------------
Odpowiedzialność:
- Odpowiada na pytania: "co jest pod kursorem/punktem/obszarem?"
- Używany przez Controller.

Publiczne API (stub):
- hitNode(graph, x, y, camera, layout)   -> nodeId|nil
- hitPort(graph, x, y, camera, layout)   -> {nodeId, portName, kind}|nil
- hitLink(graph, x, y, camera)           -> linkId|nil
- hitRect(graph, rectWorld)              -> { nodeIds = {...}, linkIds = {...} }

Uwagi:
- Współrzędne wejściowe w screen-space; funkcje same przeliczają na world-space albo przyjmują już world.
]]

--[[
Hit (Hit-testing)
-----------------
Kontrakty + pseudokod dla detekcji trafień w edytorze grafu.

Założenia:
- Wejście funkcji przyjmuje współrzędne EKRANOWE (screen-space).
- Layout odpowiada za geometrię i konwersje: screen<->world, nodeRect, portPosition, linkPath, itp.
- Theme determinuje tolerancję trafienia (np. szerokość linii linku).
- rshapes* dostarcza prymitywy kolizyjne (point-rect, point-circle, point-line, recs).

Struktury pomocnicze (przykład):
selection = { nodes = { [nodeId]=true, ... }, links = { [linkId]=true, ... } }
camera    = { ox:number, oy:number, zoom:number }
theme     = { sizes = { portRadius=6, portExecSize=10, linkWidth=2 }, ... }

Wydajność:
- Zawsze rób pre-check AABB zanim wejdziesz w drogie testy (szczególnie linki).
- Cache’uj wynik aproksymacji krzywej linku do polyline: link._poly = {p0,p1,...}, link._aabb = {x,y,w,h}
  i unieważniaj przy ruchu node/port (to zrobi później warstwa UI/Renderer).

API (publiczne):
- hitNode(graph, x_screen, y_screen, camera, layout)          -> nodeId|nil
- hitPort(graph, x_screen, y_screen, camera, layout, theme)   -> {nodeId, portName, kind}|nil
- hitLink(graph, x_screen, y_screen, camera, layout, theme)   -> linkId|nil
- hitRect(graph, rectWorld, layout)                            -> { nodeIds={...}, linkIds={...} }
  (Uwaga: hitRect przyjmuje już rect w world-space, bo zwykle pochodzi z box-select liczonego w world.)
]]


-- TODO: wstrzyknij zależności rshapes przez require na górze modułu:
-- local rshapes = require("rshapes")


--[[
hitNode
-------
Cel: zwrócić ID pierwszego (najwyższego) noda pod kursorem.

Kroki:
1) Przelicz punkt ekranu na świat:
   local wx, wy = layout.screenToWorld(camera, x_screen, y_screen)
2) Iteruj po nodach w kolejności od "góry" (jeśli masz Z-order; jeśli nie, w odwrotnej kolejności dodawania).
3) Dla każdego noda:
   - local rect = layout.nodeRect(node)  -- {x,y,w,h} w world
   - if rshapes.CheckCollisionPointRec({x=wx,y=wy}, rect) then return node.id end
4) Jeśli nic nie trafiono -> nil.
]]
function hitNode(graph, x_screen, y_screen, camera, layout)
  -- stub
  return nil
end


--[[
hitPort
-------
Cel: znaleźć port (data/exec) pod kursorem.

Kroki:
1) (wx,wy) = screen->world
2) Dla każdego node:
   - Pobierz listę portów: node.inputs + node.outputs
   - Dla każdego portu:
     * local px, py = layout.portPosition(node, port) -- środek portu (world)
     * jeśli port.kind == "data":
         - promień = theme.sizes.portRadius (np. 6)
         - if rshapes.CheckCollisionPointCircle({x=wx,y=wy}, {x=px,y=py}, promień) -> trafiony
     * jeśli port.kind == "exec":
         - zdefiniuj mały rect wokół (px,py): np. {x=px-s/2, y=py-s/2, w=s, h=s}, gdzie s=theme.sizes.portExecSize
         - if rshapes.CheckCollisionPointRec({x=wx,y=wy}, rect) -> trafiony
   - Zwróć pierwsze trafienie: { nodeId=node.id, portName=port.name, kind=port.kind }
3) Jeśli nic -> nil.
]]
function hitPort(graph, x_screen, y_screen, camera, layout, theme)
  -- stub
  return nil
end


--[[
hitLink
-------
Cel: kliknięcie w link (krzywa Beziera albo polilinia).

Kroki:
1) (wx,wy) = screen->world
2) Zdefiniuj tolerancję trafienia:
   local tol = (theme.sizes.linkWidth or 2) * 0.6 + 3   -- UX-friendly
3) Iteruj po linkach:
   - Szybki pre-check AABB:
     * local aabb = link._aabb or layout.linkAABB(link, graph)  -- jeśli masz taką funkcję; w przeciwnym razie policz z polyline
     * jeżeli aabb i rshapes.CheckCollisionPointRec({x=wx,y=wy}, aabb) == false -> pomiń
   - Weź polyline:
     * local poly = link._poly
     * jeśli brak cache: poly = layout.linkPolyline(link, graph) i opcjonalnie policz/cachuj AABB
   - Iteruj segmenty polyline: (p[i], p[i+1])
     * if rshapes.CheckCollisionPointLine({x=wx,y=wy}, p[i], p[i+1], tol) -> return link.id
4) Jeśli nic -> nil.

Uwaga:
- Jeśli nie masz jeszcze layout.linkPolyline, możesz:
  * wziąć (p0,c0,c1,p1) = layout.linkPath(link, graph)
  * zasamplować Bezier w N równych krokach (np. N=16) do polyline.
- Cache link._poly musi być unieważniany przy:
  * ruchu któregokolwiek z końców portów albo zmianie geometrii nody.
]]
function hitLink(graph, x_screen, y_screen, camera, layout, theme)
  -- stub
  return nil
end


--[[
hitRect
-------
Cel: zaznaczenie obszarem (box select). Przyjmujemy rect w world-space.

Parametry:
- rectWorld = { x, y, w, h } (world)

Kroki:
1) Zainicjalizuj wyniki: res = { nodeIds={}, linkIds={} }
2) Nody:
   - dla każdego noda:
     * local r = layout.nodeRect(node)
     * jeśli rshapes.CheckCollisionRecs(r, rectWorld) -> table.insert(res.nodeIds, node.id)
3) Linki (opcjonalnie – droższe):
   - Szybki pre-check: aabb linku vs rectWorld → jeśli brak przecięcia, pomiń.
   - Wykonaj „gęstość punktów testowych” lub szybkie heurystyki:
     * sprawdź, czy któryś z segmentów polyline przecina granice recta:
       - np. testuj „segment vs każda krawędź recta” za pomocą rshapes.CheckCollisionLines
       - lub několka punktów wewnątrz recta: jeżeli point-line <= tol dla któregokolwiek segmentu → trafienie
   - Jeśli trafiony → table.insert(res.linkIds, link.id)
4) Zwróć res.
]]
function hitRect(graph, rectWorld, layout)
  -- stub
  return { nodeIds = {}, linkIds = {} }
end


--[[
Pomocnicze zalecenia (do implementacji później):
- Priorytety trafienia: port > link > node (albo node > port — wybierz i trzymaj spójnie).
- Warstwa "Editor" może robić multi-hit: wywołać najpierw hitPort, jak nil to hitLink, jak nil to hitNode.
- Kolejność iteracji: jeżeli masz pojęcie Z-order, iteruj od najwyższego.
- Wszystkie liczby (tol, rozmiary) bierz z theme.sizes; nie zostawiaj „magicznych stałych” w kodzie.
- Funkcje layoutu:
  * screenToWorld(camera, sx, sy) -> wx, wy
  * nodeRect(node) -> {x,y,w,h}
  * portPosition(node, port) -> {x,y}
  * linkPath(link, graph) -> {p0,c0,c1,p1}  -- jeżeli używasz Beziera
  * linkPolyline(link, graph) -> { {x,y}, ... }  -- aproksymacja; N=12..24
  * linkAABB(link, graph) -> {x,y,w,h}  -- jeśli nie policzysz, da się wyznaczyć z polyline
]]

