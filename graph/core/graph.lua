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

-- graph/core/graph.lua
-- Graph zarządza kolekcją węzłów i linków

local class = require("lib.middleclass")
local Node = require("graph.core.node")
local Link = require("graph.core.link")

local Graph = class("Graph")

--- Constructor
function Graph:initialize()
  self.nodes = {}  -- id -> Node mapping
  self.links = {}  -- array of Link objects
end

--- Add node to graph
-- @param node Node
function Graph:addNode(node)
  assert(node, "Node required")
  assert(node.id, "Node must have ID")
  if self.nodes[node.id] then
    error("Node with ID '" .. node.id .. "' already exists")
  end
  self.nodes[node.id] = node
end

--- Remove node from graph (and all connected links)
-- @param nodeId string
function Graph:removeNode(nodeId)
  local node = self.nodes[nodeId]
  if not node then return false end
  
  -- Remove all links connected to this node
  local linksToRemove = {}
  for i, link in ipairs(self.links) do
    if link.fromNode.id == nodeId or link.toNode.id == nodeId then
      table.insert(linksToRemove, i)
    end
  end
  
  -- Remove links in reverse order to maintain indices
  for i = #linksToRemove, 1, -1 do
    table.remove(self.links, linksToRemove[i])
  end
  
  -- Remove node
  self.nodes[nodeId] = nil
  return true
end

--- Add link between two ports
-- @param fromNodeId string
-- @param fromPortName string
-- @param toNodeId string  
-- @param toPortName string
-- @return Link or nil on error
function Graph:addLink(fromNodeId, fromPortName, toNodeId, toPortName)
  local fromNode = self:findNodeById(fromNodeId)
  local toNode = self:findNodeById(toNodeId)
  
  if not fromNode or not toNode then
    return nil
  end
  
  local fromPort = fromNode:getOutput(fromPortName) or fromNode:getInput(fromPortName)
  local toPort = toNode:getInput(toPortName) or toNode:getOutput(toPortName)
  
  if not fromPort or not toPort then
    return nil
  end
  
  -- Prevent self-loops
  if fromNode == toNode then
    return nil
  end
  
  -- Check port compatibility
  if not fromPort:isCompatible(toPort) then
    return nil
  end
  
  local link = Link:new(nil, fromNode, fromPort, toNode, toPort)
  table.insert(self.links, link)
  return link
end

--- Remove link by ID
-- @param linkId string
-- @return boolean success
function Graph:removeLink(linkId)
  for i, link in ipairs(self.links) do
    if link.id == linkId then
      table.remove(self.links, i)
      return true
    end
  end
  return false
end

--- Find node by ID
-- @param id string
-- @return Node or nil
function Graph:findNodeById(id)
  return self.nodes[id]
end

--- Get all nodes as array
-- @return array of Node
function Graph:getNodes()
  local result = {}
  for _, node in pairs(self.nodes) do
    table.insert(result, node)
  end
  return result
end

--- Get all links as array
-- @return array of Link
function Graph:getLinks()
  return self.links
end

--- Serialize graph to table (version 1 format)
function Graph:serialize()
  local nodesData = {}
  for _, node in pairs(self.nodes) do
    table.insert(nodesData, node:serialize())
  end
  
  local linksData = {}
  for _, link in ipairs(self.links) do
    table.insert(linksData, link:serialize())
  end
  
  return {
    version = 1,
    nodes = nodesData,
    links = linksData,
    locals = {}  -- Reserved for future use
  }
end

--- Deserialize graph from table
-- @param tbl table
-- @param registry Registry (optional, for node creation)
-- @return Graph
function Graph.deserialize(tbl, registry)
  local graph = Graph:new()
  
  -- First pass: create all nodes
  if tbl.nodes then
    for _, nodeData in ipairs(tbl.nodes) do
      local node = Node.deserialize(nodeData)
      graph:addNode(node)
    end
  end
  
  -- Second pass: create all links
  if tbl.links then
    for _, linkData in ipairs(tbl.links) do
      local link = Link.deserialize(linkData, graph)
      table.insert(graph.links, link)
    end
  end
  
  return graph
end

--- Simple topological sort for dataflow execution
-- @return array of Node in execution order
function Graph:topologicalSort()
  local result = {}
  local visited = {}
  local visiting = {}
  
  local function visit(node)
    if visiting[node.id] then
      error("Circular dependency detected")
    end
    if visited[node.id] then
      return
    end
    
    visiting[node.id] = true
    
    -- Visit dependencies (nodes that this node depends on)
    for _, link in ipairs(self.links) do
      if link.toNode.id == node.id and link.kind == "data" then
        visit(link.fromNode)
      end
    end
    
    visiting[node.id] = nil
    visited[node.id] = true
    table.insert(result, node)
  end
  
  -- Visit all nodes
  for _, node in pairs(self.nodes) do
    if not visited[node.id] then
      visit(node)
    end
  end
  
  return result
end

return Graph
