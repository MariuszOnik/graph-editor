--[[
Graph
-----
Kontener na wszystkie węzły i linki.

Odpowiedzialność:
- Zarządza dodawaniem/usuwaniem węzłów i linków.
- Waliduje połączenia.
- Udostępnia metody serializacji.

Pola:
- nodes (mapa: id -> Node)
- links (lista Link)

Metody (stub):
- addNode(node)
- removeNode(nodeId)
- addLink(fromNode, fromPort, toNode, toPort) -> Link
- removeLink(linkId)
- findNodeById(id) -> Node
- serialize() -> table
- deserialize(tbl, registry) -> Graph
- topologicalSort() -> lista Node (dla podgrafów dataflow)
]]
