--[[
Node
----
Reprezentuje pojedynczy węzeł w grafie.

Odpowiedzialność:
- Przechowuje porty (wejścia/wyjścia: data, exec).
- Przechowuje właściwości (props).
- Udostępnia metody do odczytu/zapisu portów.

Pola:
- id (string, unikalny w grafie)
- type (string, np. "Add", "Number")
- title (string, nazwa wyświetlana)
- inputs (lista Port)
- outputs (lista Port)
- props (mapa -> wartości konfiguracyjne)

Metody (stub):
- addInput(name, kind, typeName)
- addOutput(name, kind, typeName)
- getInput(name) -> Port
- getOutput(name) -> Port
- serialize() -> table
- deserialize(tbl) -> Node
]]

-- graph/core/node.lua
-- Node reprezentuje pojedynczy węzeł w grafie z portami i właściwościami

local class = require("lib.middleclass")
local Port = require("graph.core.port")

local Node = class("Node")

--- Constructor
-- @param id     string (unique in graph)
-- @param type   string (e.g. "Add", "Number") 
-- @param title  string (display name)
-- @param x      number (position x, optional)
-- @param y      number (position y, optional)
function Node:initialize(id, type, title, x, y)
  self.id = assert(id, "Node ID required")
  self.type = type or "Unknown"
  self.title = title or self.type
  self.x = x or 0
  self.y = y or 0
  self.w = 120  -- default width
  self.h = 40   -- default height
  self.inputs = {}
  self.outputs = {}
  self.props = {}
end

--- Add input port
-- @param name      string
-- @param kind      "data" | "exec"  
-- @param typeName  string (optional, defaults to "any")
function Node:addInput(name, kind, typeName)
  local port = Port:new(name, kind, typeName, self)
  table.insert(self.inputs, port)
  return port
end

--- Add output port
-- @param name      string
-- @param kind      "data" | "exec"
-- @param typeName  string (optional, defaults to "any")  
function Node:addOutput(name, kind, typeName)
  local port = Port:new(name, kind, typeName, self)
  table.insert(self.outputs, port)
  return port
end

--- Get input port by name
-- @param name string
-- @return Port or nil
function Node:getInput(name)
  for _, port in ipairs(self.inputs) do
    if port.name == name then
      return port
    end
  end
  return nil
end

--- Get output port by name
-- @param name string
-- @return Port or nil
function Node:getOutput(name)
  for _, port in ipairs(self.outputs) do
    if port.name == name then
      return port
    end
  end
  return nil
end

--- Set property value
-- @param name  string
-- @param value any
function Node:setProp(name, value)
  self.props[name] = value
end

--- Get property value
-- @param name string
-- @return any
function Node:getProp(name)
  return self.props[name]
end

--- Serialize node to table
function Node:serialize()
  local inputsData = {}
  for _, port in ipairs(self.inputs) do
    table.insert(inputsData, port:serialize())
  end
  
  local outputsData = {}
  for _, port in ipairs(self.outputs) do
    table.insert(outputsData, port:serialize())
  end

  return {
    id = self.id,
    type = self.type,
    title = self.title,
    x = self.x,
    y = self.y, 
    w = self.w,
    h = self.h,
    inputs = inputsData,
    outputs = outputsData,
    props = self.props
  }
end

--- Deserialize node from table
-- @param tbl table
-- @return Node
function Node.deserialize(tbl)
  local node = Node:new(tbl.id, tbl.type, tbl.title, tbl.x, tbl.y)
  node.w = tbl.w or 120
  node.h = tbl.h or 40
  node.props = tbl.props or {}
  
  -- Restore input ports
  if tbl.inputs then
    for _, portData in ipairs(tbl.inputs) do
      node:addInput(portData.name, portData.kind, portData.typeName)
    end
  end
  
  -- Restore output ports
  if tbl.outputs then
    for _, portData in ipairs(tbl.outputs) do
      node:addOutput(portData.name, portData.kind, portData.typeName)
    end
  end
  
  return node
end

return Node