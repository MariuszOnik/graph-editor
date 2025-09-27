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

-- graph/core/link.lua
-- Link łączy wyjściowy port (from) z wejściowym (to). Przechowujemy też ID/nazwy do serializacji.

local class = require("middleclass")

-- lokalny generator ID (bez zależności od utils)
local function make_id()
  make_id._c = (make_id._c or 0) + 1
  return ("l%06d"):format(make_id._c)
end

local Link = class("Link")

--- ctor
-- @param id?        string
-- @param fromNode   Node
-- @param fromPort   Port (OUTPUT)
-- @param toNode     Node
-- @param toPort     Port (INPUT)
function Link:initialize(id, fromNode, fromPort, toNode, toPort)
  self.id       = id or make_id()
  self.fromNode = assert(fromNode, "fromNode required")
  self.fromPort = assert(fromPort, "fromPort required")
  self.toNode   = assert(toNode,   "toNode required")
  self.toPort   = assert(toPort,   "toPort required")
  self.kind     = self.fromPort.kind

  -- Walidacje podstawowe
  if self.fromPort.node ~= self.fromNode then
    error("fromPort doesn't belong to fromNode")
  end
  if self.toPort.node ~= self.toNode then
    error("toPort doesn't belong to toNode")
  end
  if self.fromPort.kind ~= self.toPort.kind then
    error("Port kinds must match (data<->data, exec<->exec)")
  end
  -- data-typy: sprawdź kompatybilność
  if self.kind == "data" and not self.fromPort:isCompatible(self.toPort) then
    error(("Incompatible port types: %s -> %s"):format(self.fromPort.typeName, self.toPort.typeName))
  end
end

-- Przydatne skróty do serializacji
function Link:fromRef() return { self.fromNode.id, self.fromPort.name } end
function Link:toRef()   return { self.toNode.id,   self.toPort.name   } end

--- JSON-friendly zapis
function Link:serialize()
  return {
    id   = self.id,
    from = self:fromRef(), -- {"nodeId","portName"}
    to   = self:toRef(),   -- {"nodeId","portName"}
    kind = self.kind,
  }
end

--- Odtworzenie linku z tabeli przy pomocy grafu (żeby znaleźć węzły/porty)
-- @param t      table {id, from={nid,pname}, to={nid,pname}, kind}
-- @param graph  Graph (musi mieć findNodeById, Node:getInput/getOutput)
function Link.deserialize(t, graph)
  local fid, fp = t.from[1], t.from[2]
  local tid, tp = t.to[1],   t.to[2]

  local fromNode = assert(graph:findNodeById(fid), "deserialize: from node not found: "..tostring(fid))
  local toNode   = assert(graph:findNodeById(tid), "deserialize: to node not found: "..tostring(tid))

  -- zakładamy, że link zawsze idzie z OUTPUT -> INPUT
  local fromPort = fromNode:getOutput(fp) or fromNode:getInput(fp) -- fallback, gdyby typy były odwrotnie zdefiniowane
  local toPort   = toNode:getInput(tp)    or toNode:getOutput(tp)

  if not fromPort or not toPort then
    error(("deserialize: port(s) not found (from:%s.%s, to:%s.%s)"):format(fid, tostring(fp), tid, tostring(tp)))
  end

  return Link:new(t.id, fromNode, fromPort, toNode, toPort)
end

return Link

