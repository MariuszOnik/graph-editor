-- tests/core_serializer_roundtrip.lua
package.path = package.path .. ";./graph/?.lua;./?.lua"

local Graph      = require("graph.core.graph")
local Node       = require("graph.core.node")
local Serializer = require("graph.core.serializer")
local Registry   = require("graph.core.registry")

local function makeNumber(id)
  local n = Node:new(id,"Number","Number")
  n:addOutput("out","data","number")
  return n
end
local function makeAdd(id)
  local n = Node:new(id,"Add","Add")
  n:addInput("a","data","number")
  n:addInput("b","data","number")
  n:addOutput("out","data","number")
  return n
end

-- zbuduj graf
local g = Graph:new()
local n1, n2, add = makeNumber("n1"), makeNumber("n2"), makeAdd("add")
n1.x, n1.y = 10, 10
n2.x, n2.y = 10, 60
add.x, add.y = 200, 35
g:addNode(n1); g:addNode(n2); g:addNode(add)
g:addLink("n1","out","add","a")
g:addLink("n2","out","add","b")

-- zapisz
local blob = Serializer.save(g)
print("Saved nodes:", #blob.nodes, "links:", #blob.links)

-- przygotuj registry (dla load z fabrykami)
local reg = Registry.new()
reg:register("Number", makeNumber)
reg:register("Add",    makeAdd)

-- odczytaj
local g2 = Serializer.load(blob, reg)

-- sanity
local sorted = g2:topologicalSort()
for i,n in ipairs(sorted) do print(i, n.id, n.type, n.x, n.y) end
print("Roundtrip OK")
