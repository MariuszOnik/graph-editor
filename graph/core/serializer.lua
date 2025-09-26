--[[
Serializer
----------
Odpowiada za zapis i odczyt grafu do/z tabeli (JSON friendly).

Format (v1):
{
  version = 1,
  nodes = {
    { id="n1", type="Number", x=100, y=200, props={value=3} },
    { id="n2", type="Add", x=250, y=200 }
  },
  links = {
    { id="l1", from={"n1","out"}, to={"n2","a"}, kind="data" }
  }
}

Metody (stub):
- serializeGraph(graph) -> table
- deserializeGraph(tbl, registry) -> Graph
- migrate(tbl) -> tbl (dla wersjonowania)
]]
