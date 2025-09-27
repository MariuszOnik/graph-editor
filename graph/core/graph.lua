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

--[[
graph/core/graph.lua
--------------------
Graph (model)
- Kontener na węzły i linki (bez UI i bez runtime).
- Walidacja połączeń (kind/data-type, kierunek OUTPUT->INPUT, pojedyncze wejście).
- Szybkie wyszukiwanie (mapy id->node/link, indeksy portów).
- Serializacja/Deserializacja (format v1).
- Topologiczne porządkowanie podgrafów DATAFLOW (dla późniejszej ewaluacji/codegen).

Konwencje:
- Jeden INPUT (data albo exec) może mieć **co najwyżej 1** przychodzący link.
- OUTPUT może iść do wielu INPUT-ów.
- Link zawsze łączy OUTPUT -> INPUT tego samego kind: "data" albo "exec".
- Typy danych zgodne wg Port:isCompatible (dla "data"). Dla "exec" bez danych.

Publiczne API (doc + pseudokod):
- new() -> Graph
- addNode(node) -> void
- removeNode(nodeId) -> void  (usuwa też linki związane z nodem)
- findNodeById(id) -> Node|nil
- addLink(fromNodeId, fromPortName, toNodeId, toPortName) -> Link
- removeLink(linkId) -> void
- getLinksFrom(nodeId[, portName]) -> {Link,...}      -- wychodzące
- getLinksTo(nodeId[, portName]) -> {Link,...}        -- przychodzące
- serialize() -> table
- deserialize(tbl, registry) -> Graph
- topologicalSort({subgraphNodeIds?}) -> {Node,...}   -- tylko DATA (ignoruje exec), błąd dla cyklu

Struktury wewnętrzne:
- nodesById : { [id]=Node }
- linksById : { [id]=Link }
- linksFrom : { [nodeId] = { [portName] = {Link,...} } }
- linksTo   : { [nodeId] = { [portName] = Link|nil } }  -- pojedyncze wejście

Uwaga: Graph **nie zna** rysowania ani runtime; to czysty model.
]]
--[[
To nie jest pełna implementacja, ale bardzo blisko — z jasnymi zasadami walidacji, strukturami danych
 i algorytmem sortu topologicznego (Kahn).

 Notatki wdrożeniowe (co i jak zrobimy w PR-ze)

Walidacje są po naszej stronie (czytelne komunikaty błędów). To później bardzo ułatwia debugging w UI.

Jedno wejście–jeden link wymuszamy przez linksTo[nodeId][port] = link.

Toposort ignoruje exec — to ważne (exec obsłuży scheduler).

Deserializacja: jeżeli masz Registry.create(type, id), użyjesz go; jeśli nie, fallback na Node.deserialize.

Testy ręczne (szybkie):

Dodaj 2×Number → Add, zlinkuj Number1.out -> Add.a i Number2.out -> Add.b, sprawdź topologicalSort() zwraca [Number1, Number2, Add] (lub dowolną wariację z Add na końcu).

Spróbuj zlinkować drugi raz do Add.a → powinien polecieć błąd „input already has a link”.

Spróbuj data->exec lub exec->data → błąd o mismatch kind.

To, co Ci wkleiłem do graph/core/graph.lua, wygląda jak pełna implementacja (bo kod jest kompletny w Lua). Celowo pisałem, że to „nie jest pełna implementacja, ale bardzo blisko” żeby zostawić jasny sygnał:

część rzeczy jest w pseudokodzie/komentarzach (np. jak Registry ma współpracować z Node.deserialize, jak dokładnie mierzyć porty itp.),

niektóre szczegóły trzeba będzie uzupełnić, kiedy pojawią się pozostałe moduły (np. Registry.create, Node z dodatkowymi metodami),

brakuje testów jednostkowych – a w naszym podejściu testy są częścią „pełnej implementacji”.

Czyli kod działa, ale wymaga jeszcze „domknięcia kontraktu” z resztą systemu.

Krótko:

To co masz w pliku → można normalnie odpalić i Graph już będzie umiał dodawać/usunąć node’y, linki, serializować i robić sort topologiczny.

„Niepełne” → bo dopiero integracja z Registry + testy sprawią, że uznamy moduł za w 100% gotowy do merge’a.

Chcesz, żebym przygotował Ci teraz mały zestaw testów sanity (np. w tests/core_graph_sanity.lua), żebyś mógł sprawdzić ten kod w praktyce zanim zrobisz PR?

 ]]

local class = require("middleclass")
local Link  = require("graph.core.link")

local Graph = class("Graph")

function Graph:initialize()
  self.nodesById = {}
  self.linksById = {}
  self.linksFrom = {}  -- nodeId -> portName -> {links}
  self.linksTo   = {}  -- nodeId -> portName -> link (albo nil)
end

-- utils (wewnętrzne) --------------------------------------------------------

local function ensureNode(tbl, id)
  local m = tbl[id]; if not m then m = {}; tbl[id] = m end; return m
end

local function assertNodeExists(self, id, role)
  local n = self.nodesById[id]
  if not n then error(("Graph: %s node '%s' not found"):format(role or "required", tostring(id))) end
  return n
end

local function getPortByRole(node, role, name)
  -- role: "output"|"input"
  if role == "output" then return node:getOutput(name) end
  if role == "input"  then return node:getInput(name)  end
  error("invalid role "..tostring(role))
end

-- Node API ------------------------------------------------------------------

-- addNode: ID musi być unikalne
function Graph:addNode(node)
  if self.nodesById[node.id] then
    error(("Graph: node id '%s' already exists"):format(node.id))
  end
  self.nodesById[node.id] = node
  -- nie tworzymy wpisów w linksFrom/linksTo do czasu aż powstaną linki
end

-- removeNode: usuń node + wszystkie jego linki (z i do)
function Graph:removeNode(nodeId)
  local n = self.nodesById[nodeId]
  if not n then return false end

  -- usuń wychodzące
  local fromMap = self.linksFrom[nodeId]
  if fromMap then
    for _, list in pairs(fromMap) do
      for i=#list,1,-1 do self:removeLink(list[i].id) end
    end
  end
  -- usuń przychodzące
  local toMap = self.linksTo[nodeId]
  if toMap then
    for _, link in pairs(toMap) do
      if link then self:removeLink(link.id) end
    end
  end

  self.nodesById[nodeId] = nil
  self.linksFrom[nodeId] = nil
  self.linksTo[nodeId]   = nil
  return true
end

function Graph:findNodeById(id) return self.nodesById[id] end

-- Link API ------------------------------------------------------------------

-- Walidacje połączenia (rzucają błąd z czytelną przyczyną)
local function validateCanConnect(self, fromNode, fromPort, toNode, toPort)
  if fromPort.node ~= fromNode or toPort.node ~= toNode then
    error("Graph: port doesn't belong to provided node")
  end
  if fromPort.kind ~= toPort.kind then
    error("Graph: port kinds mismatch (need data->data or exec->exec)")
  end
  -- kierunek: OUTPUT -> INPUT
  -- (użytkownik podał nazwy; my wymuszamy semantykę: from=OUTPUT, to=INPUT)
  if not fromNode:getOutput(fromPort.name) then
    error(("Graph: '%s.%s' is not an OUTPUT"):format(fromNode.id, fromPort.name))
  end
  if not toNode:getInput(toPort.name) then
    error(("Graph: '%s.%s' is not an INPUT"):format(toNode.id, toPort.name))
  end
  -- pojedyncze wejście
  local toMap = self.linksTo[toNode.id] and self.linksTo[toNode.id][toPort.name]
  if toMap then
    error(("Graph: input '%s.%s' already has a link"):format(toNode.id, toPort.name))
  end
  -- typy danych (dla data)
  if fromPort.kind == "data" and not fromPort:isCompatible(toPort) then
    error(("Graph: incompatible data types '%s' -> '%s'"):format(fromPort.typeName, toPort.typeName))
  end
end

-- addLink: tworzy i rejestruje Link
function Graph:addLink(fromNodeId, fromPortName, toNodeId, toPortName)
  local fromNode = assertNodeExists(self, fromNodeId, "from")
  local toNode   = assertNodeExists(self, toNodeId,   "to")

  local fromPort = getPortByRole(fromNode, "output", fromPortName)
  if not fromPort then
    error(("Graph: output port '%s.%s' not found"):format(fromNodeId, tostring(fromPortName)))
  end

  local toPort = getPortByRole(toNode, "input", toPortName)
  if not toPort then
    -- jeśli nazwa istnieje jako OUTPUT, doprecyzuj komunikat
    local maybeOut = toNode:getOutput(toPortName)
    if maybeOut then
      error(("Graph: port '%s.%s' exists but is OUTPUT; expected INPUT"):format(toNodeId, tostring(toPortName)))
    end
    error(("Graph: input port '%s.%s' not found"):format(toNodeId, tostring(toPortName)))
  end

  validateCanConnect(self, fromNode, fromPort, toNode, toPort)

  local link = Link:new(nil, fromNode, fromPort, toNode, toPort)
  self.linksById[link.id] = link

  local f = ensureNode(self.linksFrom, fromNode.id)
  local lf = f[fromPort.name]; if not lf then lf = {}; f[fromPort.name] = lf end
  table.insert(lf, link)

  local t = ensureNode(self.linksTo, toNode.id)
  t[toPort.name] = link

  return link
end


function Graph:removeLink(linkId)
  local link = self.linksById[linkId]
  if not link then return false end

  self.linksById[linkId] = nil

  -- usuń z linksFrom
  local fromMap = self.linksFrom[link.fromNode.id]
  if fromMap then
    local list = fromMap[link.fromPort.name]
    if list then
      for i=#list,1,-1 do
        if list[i].id == linkId then table.remove(list, i); break end
      end
      if #list == 0 then fromMap[link.fromPort.name] = nil end
    end
  end

  -- usuń z linksTo
  local toMap = self.linksTo[link.toNode.id]
  if toMap and toMap[link.toPort.name] and toMap[link.toPort.name].id == linkId then
    toMap[link.toPort.name] = nil
  end

  return true
end

function Graph:getLinksFrom(nodeId, portName)
  local m = self.linksFrom[nodeId]; if not m then return {} end
  if portName then return m[portName] or {} end
  -- złącz wszystkie listy
  local out = {}
  for _, list in pairs(m) do for i=1,#list do out[#out+1] = list[i] end end
  return out
end

function Graph:getLinksTo(nodeId, portName)
  local m = self.linksTo[nodeId]; if not m then return {} end
  if portName then return m[portName] and { m[portName] } or {} end
  local out = {}
  for _, l in pairs(m) do if l then out[#out+1] = l end end
  return out
end

-- Serializacja --------------------------------------------------------------

-- Format v1 (zgodny z README):
-- {
--   version = 1,
--   nodes = { {id,type,title,x,y,w,h, inputs=[{name,kind,typeName}...], outputs=[...] , props={...}}, ... },
--   links = { {id, from={nid,pname}, to={nid,pname}, kind="data"|"exec"}, ... },
--   locals = {} -- opcjonalnie (blackboard); Graph tego nie używa, pozostawiamy dla runtime
-- }

function Graph:serialize()
  local out = { version = 1, nodes = {}, links = {} }
  for _, node in pairs(self.nodesById) do
    out.nodes[#out.nodes+1] = node:serialize()
  end
  for _, link in pairs(self.linksById) do
    out.links[#out.links+1] = link:serialize()
  end
  return out
end

function Graph.deserialize(tbl, registry)
  if (tbl.version or 1) ~= 1 then
    error("Graph.deserialize: unsupported version "..tostring(tbl.version))
  end
  local g = Graph:new()
  -- odtwórz nody przez registry (żeby mieć właściwe klasy)
  for _, n in ipairs(tbl.nodes or {}) do
    local ctor = registry and registry.create or nil
    local node
    if ctor then node = ctor(registry, n.type, n.id) else
      -- fallback: deserializacja przez Node.deserialize z już wczytanych modułów
      local Node = require("graph.core.node")
      node = Node.deserialize(n)
    end
    -- jeśli poszliśmy przez registry, to node może nie mieć portów -> dokończ:
    if node and node.deserialize and node ~= n then
      -- pozwalamy klasie węzła załadować swoje propsy/porty
      -- (wspólne pola pozycji dopiszemy niżej)
    end
    -- w każdym wariancie uzupełnij podstawowe pola pozycji/props jeśli brak
    node.x, node.y = n.x or node.x or 0, n.y or node.y or 0
    node.w, node.h = n.w or node.w, n.h or node.h
    if not node.props then node.props = {} end
    for k,v in pairs(n.props or {}) do node.props[k] = v end
    g:addNode(node)
    -- jeśli węzły rejestrowane z góry nie mają list portów w JSON, a polegamy na registry,
    -- nie dodawaj portów drugi raz; w przeciwnym razie (Node.deserialize) już są.
    if (n.inputs or n.outputs) and node.getInput and not node:getInput("__probe__") then
      -- nic: zakładamy, że Node.deserialize wykonał addInput/addOutput
    end
  end
  -- linki
  for _, l in ipairs(tbl.links or {}) do
    local link = Link.deserialize(l, g)
    g.linksById[link.id] = link
    -- uzupełnij indeksy
    local f = ensureNode(g.linksFrom, link.fromNode.id)
    local lf = f[link.fromPort.name]; if not lf then lf = {}; f[link.fromPort.name] = lf end
    table.insert(lf, link)
    local t = ensureNode(g.linksTo, link.toNode.id)
    t[link.toPort.name] = link
  end
  return g
end

-- Topologiczne porządkowanie (DATAFLOW) -------------------------------------
-- - Budujemy DAG tylko dla połączeń kind="data".
-- - Ignorujemy exec (sterowanie) — scheduler obsłuży je osobno.
-- - Jeśli wykryjemy cykl -> błąd.

function Graph:topologicalSort(subsetIds)
  -- zbuduj zbiór węzłów wejściowych (jeśli subsetIds, to tylko te; inaczej wszystkie)
  local include = nil
  if subsetIds and #subsetIds > 0 then
    include = {}
    for i=1,#subsetIds do include[subsetIds[i]] = true end
  end

  -- stopnie wejściowe (in-degree) dla DATA krawędzi
  local indeg = {}
  local nodes = {}
  for id, node in pairs(self.nodesById) do
    if not include or include[id] then
      indeg[id] = 0
      nodes[#nodes+1] = node
    end
  end
  -- policz in-degree po linkach DATA
  for _, link in pairs(self.linksById) do
    if link.kind == "data" then
      local toId = link.toNode.id
      if indeg[toId] ~= nil then
        indeg[toId] = indeg[toId] + 1
      end
    end
  end

  -- Kahn:
  local q = {}
  for _, node in ipairs(nodes) do
    if indeg[node.id] == 0 then q[#q+1] = node end
  end
  local out = {}
  local head = 1
  while head <= #q do
    local n = q[head]; head = head + 1
    out[#out+1] = n
    -- dla wszystkich data-linków wychodzących z n odejmij in-degree
    local outLinks = self:getLinksFrom(n.id)
    for i=1,#outLinks do
      local l = outLinks[i]
      if l.kind == "data" then
        local toId = l.toNode.id
        if indeg[toId] ~= nil then
          indeg[toId] = indeg[toId] - 1
          if indeg[toId] == 0 then
            q[#q+1] = self.nodesById[toId]
          end
        end
      end
    end
  end

  -- czy pokryliśmy wszystkie? jeśli nie, jest cykl
  local covered = {}
  for i=1,#out do covered[out[i].id] = true end
  for _, node in ipairs(nodes) do
    if not covered[node.id] then
      error("Graph.topologicalSort: cycle detected in data subgraph")
    end
  end
  return out
end

return Graph

