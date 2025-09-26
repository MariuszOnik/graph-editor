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
