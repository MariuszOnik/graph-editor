--[[
Link
----
Reprezentuje krawędź pomiędzy dwoma portami.

Odpowiedzialność:
- Łączy port wyjściowy (out) z portem wejściowym (in).
- Zapewnia zgodność typów i kind (exec/data).

Pola:
- id (string, unikalny w grafie)
- fromNode (Node)
- fromPort (Port)
- toNode (Node)
- toPort (Port)
- kind (string: "data" | "exec")

Metody (stub):
- serialize() -> table
- deserialize(tbl, graph) -> Link
]]
