--[[
Registry
--------
Rejestr typów węzłów.

Odpowiedzialność:
- Pozwala rejestrować nowe typy węzłów.
- Tworzy instancje na podstawie typu (dla deserializacji).

Pola:
- types (mapa: typeName -> factoryFn)

Metody (stub):
- register(typeName, factoryFn, metadata)
- create(typeName, id) -> Node
- getMetadata(typeName) -> table
]]

-- graph/core/registry.lua
-- Prosty rejestr typów węzłów: register(typeName, factory, meta), create(typeName, id)
-- factory: function(id) -> Node (z już zdefiniowanymi portami/props)

local Registry = {}
Registry.__index = Registry

function Registry.new()
  return setmetatable({ _types = {} }, Registry)
end

function Registry:register(typeName, factory, meta)
  assert(type(typeName) == "string" and typeName ~= "", "registry.register: bad typeName")
  assert(type(factory) == "function", "registry.register: factory must be function(id)->Node")
  self._types[typeName] = { factory = factory, meta = meta or {} }
  return self
end

function Registry:create(typeName, id)
  local rec = self._types[typeName]
  if not rec then error("registry.create: unknown type "..tostring(typeName)) end
  local node = rec.factory(id)
  -- upewnij się, że pola bazowe są ustawione
  if not node.type then node.type = typeName end
  return node
end

function Registry:meta(typeName)
  local rec = self._types[typeName]
  return rec and rec.meta or nil
end

-- przykładowe rejestracje (opcjonalnie w innym miejscu projektu):
-- local Node = require("graph.core.node")
-- reg:register("Number", function(id) local n=Node:new(id,"Number","Number"); n:addOutput("out","data","number"); return n end)

return Registry

