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
]]-- graph/core/serializer.lua
-- Warstwa I/O nad Graph: zapis/odczyt format v1, z użyciem Registry przy load.

local Graph = require("graph.core.graph")

local Serializer = {}

-- save: prosty delegat do Graph:serialize(), ale miejsce na przyszłe rozszerzenia (np. metadane)
function Serializer.save(graph)
  assert(graph and graph.serialize, "Serializer.save: need Graph")
  local tbl = graph:serialize()
  tbl.version = 1
  return tbl
end

-- load: tworzy nowy Graph, węzły przez registry (gdy dostępny), linki przez Graph.deserialize/Link.deserialize
-- wspiera też ładowanie „gołego” Graph.deserialize, jeśli nie chcesz registry
function Serializer.load(tbl, registry)
  assert(type(tbl) == "table", "Serializer.load: table required")
  local g = Graph:new()

  -- węzły
  local Node = require("graph.core.node")
  for _, n in ipairs(tbl.nodes or {}) do
    local node
    if registry and registry.create then
      node = registry:create(n.type, n.id)
      -- pozycja/tytuł/props z blobu
      node.title = n.title or node.title
      node.x, node.y = n.x or node.x or 0, n.y or node.y or 0
      node.w, node.h = n.w or node.w, n.h or node.h
      node.props = node.props or {}
      for k,v in pairs(n.props or {}) do node.props[k] = v end
      -- Uwaga: portów z blobu NIE dodajemy, skoro factory już je zdefiniowała.
    else
      node = Node.deserialize(n) -- tu porty są brane z blobu
    end
    
    g:addNode(node)
  end

  -- linki (używamy Link.deserialize przez Graph.deserialize logic — mamy już to w graph.lua)
  for _, l in ipairs(tbl.links or {}) do
    -- Nie dodajemy przez Graph:addLink(), bo deserialize ma już walidacje i potrafi odtworzyć porty po id.
    local Link = require("graph.core.link")
    local link = Link.deserialize(l, g)
    -- zarejestruj jak w Graph.deserialize
    g.linksById[link.id] = link
    local f = g.linksFrom[link.fromNode.id] or {}; g.linksFrom[link.fromNode.id] = f
    local lf = f[link.fromPort.name] or {}; f[link.fromPort.name] = lf
    table.insert(lf, link)
    local t = g.linksTo[link.toNode.id] or {}; g.linksTo[link.toNode.id] = t
    t[link.toPort.name] = link
  end

  return g
end

return Serializer


