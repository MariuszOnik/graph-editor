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

-- graph/core/serializer.lua
-- Serializer zarządza zapisem i odczytem grafów

local Graph = require("graph.core.graph")

local Serializer = {}
Serializer.__index = Serializer

local CURRENT_VERSION = 1

--- Create new serializer instance
function Serializer.new()
  local self = setmetatable({}, Serializer)
  return self
end

--- Serialize graph to table (JSON-friendly)
-- @param graph Graph
-- @return table
function Serializer:serializeGraph(graph)
  assert(graph, "Graph required")
  return graph:serialize()
end

--- Deserialize graph from table
-- @param tbl table
-- @param registry Registry (optional)
-- @return Graph
function Serializer:deserializeGraph(tbl, registry)
  assert(tbl, "Table required")
  
  -- Migrate to current version if needed
  tbl = self:migrate(tbl)
  
  return Graph.deserialize(tbl, registry)
end

--- Migrate table to current version
-- @param tbl table
-- @return table (migrated)
function Serializer:migrate(tbl)
  if not tbl.version then
    -- Assume version 0, migrate to version 1
    tbl = self:migrateV0ToV1(tbl)
  end
  
  if tbl.version < CURRENT_VERSION then
    -- Future migrations would go here
    -- if tbl.version == 1 then tbl = self:migrateV1ToV2(tbl) end
  end
  
  return tbl
end

--- Migrate from version 0 to version 1
-- @param tbl table
-- @return table
function Serializer:migrateV0ToV1(tbl)
  return {
    version = 1,
    nodes = tbl.nodes or {},
    links = tbl.links or {},
    locals = tbl.locals or {}
  }
end

--- Validate serialized data structure
-- @param tbl table
-- @return boolean, string (success, error_message)
function Serializer:validate(tbl)
  if not tbl then
    return false, "No data provided"
  end
  
  if not tbl.version then
    return false, "Missing version field"
  end
  
  if type(tbl.nodes) ~= "table" then
    return false, "Invalid nodes field"
  end
  
  if type(tbl.links) ~= "table" then  
    return false, "Invalid links field"
  end
  
  -- Validate nodes
  for i, node in ipairs(tbl.nodes) do
    if not node.id or type(node.id) ~= "string" then
      return false, "Node " .. i .. " missing or invalid ID"
    end
    if not node.type or type(node.type) ~= "string" then
      return false, "Node " .. node.id .. " missing or invalid type"
    end
  end
  
  -- Validate links
  for i, link in ipairs(tbl.links) do
    if not link.from or type(link.from) ~= "table" or #link.from ~= 2 then
      return false, "Link " .. i .. " invalid 'from' field"
    end
    if not link.to or type(link.to) ~= "table" or #link.to ~= 2 then
      return false, "Link " .. i .. " invalid 'to' field"
    end
    if not link.kind or (link.kind ~= "data" and link.kind ~= "exec") then
      return false, "Link " .. i .. " invalid kind"
    end
  end
  
  return true
end

--- Serialize graph to JSON string
-- @param graph Graph  
-- @return string JSON
function Serializer:toJSON(graph)
  local data = self:serializeGraph(graph)
  -- In a real implementation, you'd use a JSON library here
  -- For now, return a simple string representation
  local function tableToJSON(t, indent)
    indent = indent or 0
    local spaces = string.rep("  ", indent)
    local result = "{\n"
    
    for k, v in pairs(t) do
      result = result .. spaces .. "  \"" .. k .. "\": "
      if type(v) == "table" then
        if #v > 0 then  -- array
          result = result .. "[\n"
          for i, item in ipairs(v) do
            result = result .. spaces .. "    "
            if type(item) == "table" then
              result = result .. tableToJSON(item, indent + 2)
            else
              result = result .. "\"" .. tostring(item) .. "\""
            end
            if i < #v then result = result .. "," end
            result = result .. "\n"
          end
          result = result .. spaces .. "  ]"
        else  -- object
          result = result .. tableToJSON(v, indent + 1)
        end
      else
        result = result .. "\"" .. tostring(v) .. "\""
      end
      result = result .. ",\n"
    end
    
    result = result .. spaces .. "}"
    return result
  end
  
  return tableToJSON(data)
end

--- Create global serializer instance
local globalSerializer = Serializer.new()

-- Export both class and global instance
return {
  Serializer = Serializer,
  serialize = function(graph) return globalSerializer:serializeGraph(graph) end,
  deserialize = function(tbl, registry) return globalSerializer:deserializeGraph(tbl, registry) end,
  validate = function(tbl) return globalSerializer:validate(tbl) end,
  toJSON = function(graph) return globalSerializer:toJSON(graph) end
}
