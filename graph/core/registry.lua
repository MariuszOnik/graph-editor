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
-- Registry zarządza typami węzłów i ich fabrykami

local class = require("lib.middleclass")
local Node = require("graph.core.node")

local Registry = class("Registry")

--- Constructor
function Registry:initialize()
  self.types = {}      -- typeName -> factoryFn
  self.metadata = {}   -- typeName -> metadata table
  
  -- Register built-in node types
  self:registerBuiltinNodes()
end

--- Register a node type
-- @param typeName string
-- @param factoryFn function(id, ...) -> Node
-- @param metadata table (optional) - describes the node type
function Registry:register(typeName, factoryFn, metadata)
  assert(typeName, "Type name required")
  assert(factoryFn, "Factory function required")
  
  self.types[typeName] = factoryFn
  self.metadata[typeName] = metadata or {}
end

--- Create node instance by type
-- @param typeName string
-- @param id string
-- @param ... additional arguments for factory
-- @return Node
function Registry:create(typeName, id, ...)
  local factory = self.types[typeName]
  if not factory then
    error("Unknown node type: " .. tostring(typeName))
  end
  
  return factory(id, ...)
end

--- Get metadata for node type
-- @param typeName string
-- @return table metadata
function Registry:getMetadata(typeName)
  return self.metadata[typeName] or {}
end

--- Get list of registered type names
-- @return array of string
function Registry:getTypeNames()
  local result = {}
  for typeName, _ in pairs(self.types) do
    table.insert(result, typeName)
  end
  return result
end

--- Check if type is registered
-- @param typeName string
-- @return boolean
function Registry:hasType(typeName)
  return self.types[typeName] ~= nil
end

--- Register built-in node types
function Registry:registerBuiltinNodes()
  -- Number node - outputs a constant number
  self:register("Number", function(id, x, y)
    local node = Node:new(id, "Number", "Number", x, y)
    node:addOutput("out", "data", "number")
    node:setProp("value", 0)
    return node
  end, {
    category = "Constants",
    description = "Outputs a constant number value",
    color = "#4CAF50"
  })
  
  -- Add node - adds two numbers
  self:register("Add", function(id, x, y)
    local node = Node:new(id, "Add", "Add", x, y)
    node:addInput("a", "data", "number")
    node:addInput("b", "data", "number")
    node:addOutput("result", "data", "number")
    return node
  end, {
    category = "Math",
    description = "Adds two numbers together",
    color = "#2196F3"
  })
  
  -- Display node - shows a value
  self:register("Display", function(id, x, y)
    local node = Node:new(id, "Display", "Display", x, y)
    node:addInput("value", "data", "any")
    return node
  end, {
    category = "Debug",
    description = "Displays the input value",
    color = "#FF9800"
  })
  
  -- Start node - execution entry point
  self:register("Start", function(id, x, y)
    local node = Node:new(id, "Start", "Start", x, y)
    node:addOutput("exec", "exec")
    return node
  end, {
    category = "Execution",
    description = "Entry point for execution flow",
    color = "#9C27B0"
  })
  
  -- Delay node - waits for specified time
  self:register("Delay", function(id, x, y)
    local node = Node:new(id, "Delay", "Delay", x, y)
    node:addInput("exec", "exec")
    node:addInput("seconds", "data", "number")
    node:addOutput("exec", "exec")
    node:setProp("seconds", 1.0)
    return node
  end, {
    category = "Execution",
    description = "Delays execution for specified seconds",
    color = "#9C27B0"
  })
  
  -- Branch node - conditional execution
  self:register("Branch", function(id, x, y)
    local node = Node:new(id, "Branch", "Branch", x, y)
    node:addInput("exec", "exec")
    node:addInput("condition", "data", "boolean")
    node:addOutput("true", "exec")
    node:addOutput("false", "exec")
    return node
  end, {
    category = "Execution",
    description = "Conditional execution branch",
    color = "#9C27B0"
  })
end

return Registry
