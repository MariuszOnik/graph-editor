--sprawdzi najważniejsze przypadki Graph:
-- dodawanie nodów, linkowanie, błędne połączenia, cykl w dataflow.
-- tests/core_graph_sanity.lua
-- Proste sanity testy dla Graph/Node/Port/Link

--package.path = package.path .. ";./graph/?.lua;./?.lua"

local Graph = require("graph.core.graph")
local Node  = require("graph.core.node")

-- mały helper do tworzenia node z portami
local function makeNumberNode(id)
  local n = Node:new(id, "Number", "Number")
  n:addOutput("out", "data", "number")
  return n
end

local function makeAddNode(id)
  local n = Node:new(id, "Add", "Add")
  n:addInput("a", "data", "number")
  n:addInput("b", "data", "number")
  n:addOutput("out", "data", "number")
  return n
end

local function makeExecNode(id)
  local n = Node:new(id, "Start", "Start")
  n:addOutput("exec", "exec")
  return n
end

local function divider(name)
  print(("\n=== %s ==="):format(name))
end

-- TEST 1: prosty graf (Number1 + Number2 -> Add)
divider("TEST 1: simple add graph")
local g1 = Graph:new()
local n1, n2, add = makeNumberNode("n1"), makeNumberNode("n2"), makeAddNode("add")
g1:addNode(n1); g1:addNode(n2); g1:addNode(add)
g1:addLink("n1","out","add","a")
g1:addLink("n2","out","add","b")
local sorted = g1:topologicalSort()
for i,node in ipairs(sorted) do print(i,node.id,node.type) end

-- TEST 2: podwójne wejście (powinno rzucić błąd)
divider("TEST 2: double input link")
local ok, err = pcall(function()
  g1:addLink("n1","out","add","a") -- jeszcze raz do add.a
end)
print("error?", not ok, err)

-- TEST 3: złe kind (data->exec)
divider("TEST 3: kind mismatch")
local g2 = Graph:new()
local data = makeNumberNode("n")
local exec = makeExecNode("s")
g2:addNode(data); g2:addNode(exec)
ok, err = pcall(function()
  g2:addLink("n","out","s","exec") -- data -> exec
end)
print("error?", not ok, err)

-- TEST 4: cykl (powinien wykryć)
divider("TEST 4: cycle detection")
local g3 = Graph:new()
local a,b = makeAddNode("a"), makeAddNode("b")
g3:addNode(a); g3:addNode(b)
g3:addLink("a","out","b","a")
g3:addLink("b","out","a","a") -- cykl
ok, err = pcall(function()
  local s = g3:topologicalSort()
  for i,node in ipairs(s) do print(i,node.id) end
end)
print("error?", not ok, err)
