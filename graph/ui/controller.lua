--[[
Controller (Input -> Actions)
-----------------------------
Odpowiedzialność:
- Zbiera wejścia (mysz/klawiatura/gamepad/dotyk) i emituje AKCJE edytora.
- Nie rysuje, nie wykonuje grafu.

Wejścia:
- input : abstrakcja wejść (rcore + własne mapowania)
- hit   : moduł detekcji "co pod kursorem"
- camera: { ox, oy, zoom }

Akcje (emitowane; przykłady):
- { type="pan", dx, dy }
- { type="zoom", scale, pivotX, pivotY }
- { type="node.dragStart", id, at }
- { type="node.drag", id, dx, dy }
- { type="link.begin", nodeId, portName }
- { type="link.commit", from={...}, to={...} }
- { type="select.boxStart"/"select.boxEnd" }
- { type="delete.selection" }

Publiczne API (stub):
- new(opts) -> Controller
- update(dt, graph, selection, camera) -> {actions} -- lista akcji do wykonania przez wyższą warstwę (Editor)
]]
