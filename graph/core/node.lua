--[[
Node
-----
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
-- Node (model) — bez zależności od UI/runtime.
-- Odpowiedzialność:
-- - Definicja węzła: id, type, title, pozycja (x,y) i opcjonalny rozmiar (w,h)
-- - Porty: inputs/outputs (listy) + szybkie mapy po nazwie
-- - Prosta serializacja/deserializacja (bez stanu UI)


--[[
uwagi krótkie:

Port:new musi istnieć i mieć sygnaturę (name, kind, typeName, ownerNode).

Walidację „typów danych” (zgodność typeName) trzymamy w Port/Link/Graph — Node tylko kolekcjonuje.

Pozycja/rozmiar w modelu są celowe — UI/layout tego potrzebują i zapisujemy to w pliku grafu.

]]

local class = require("middleclass")
local Port  = require("graph.core.port")

-- Bezpieczne ID: próbujemy utila, inaczej lokalny inkrement.
local function make_id()
  local ok, gen = pcall(require, "graph.utils.uuid")
  if ok and type(gen) == "function" then return gen() end
  make_id._c = (make_id._c or 0) + 1
  return ("n%06d"):format(make_id._c)
end

local VALID_KIND = { data = true, exec = true }

local Node = class("Node")

--- ctor
-- @param id?        string
-- @param typeName?  string
-- @param title?     string
function Node:initialize(id, typeName, title)
  self.id      = id or make_id()
  self.type    = typeName or "Generic"
  self.title   = title or self.type

  -- Modelowa pozycja/rozmiar w world-space (w,h opcjonalne — layout może policzyć)
  self.x, self.y = 0, 0
  self.w, self.h = nil, nil

  -- Porty
  self.inputs,  self.outputs   = {}, {}
  self.inputsByName, self.outputsByName = {}, {}

  -- Właściwości (konfig nody)
  self.props = {}
end

-- -- -- Porty ---------------------------------------------------------------

local function assertKind(kind)
  if not VALID_KIND[kind] then
    error(("Invalid port kind '%s' (expected 'data' or 'exec')"):format(tostring(kind)))
  end
end

--- Dodaj port wejściowy.
function Node:addInput(name, kind, typeName)
  assertKind(kind)
  if self.inputsByName[name] then
    error(("Input port '%s' already exists on node %s"):format(name, self.id))
  end
  local p = Port:new(name, kind, typeName, self)
  table.insert(self.inputs, p)
  self.inputsByName[name] = p
  return p
end

--- Dodaj port wyjściowy.
function Node:addOutput(name, kind, typeName)
  assertKind(kind)
  if self.outputsByName[name] then
    error(("Output port '%s' already exists on node %s"):format(name, self.id))
  end
  local p = Port:new(name, kind, typeName, self)
  table.insert(self.outputs, p)
  self.outputsByName[name] = p
  return p
end

--- Usuń port wejściowy po nazwie.
function Node:removeInput(name)
  if not self.inputsByName[name] then return false end
  self.inputsByName[name] = nil
  for i = #self.inputs, 1, -1 do
    if self.inputs[i].name == name then table.remove(self.inputs, i); break end
  end
  return true
end

--- Usuń port wyjściowy po nazwie.
function Node:removeOutput(name)
  if not self.outputsByName[name] then return false end
  self.outputsByName[name] = nil
  for i = #self.outputs, 1, -1 do
    if self.outputs[i].name == name then table.remove(self.outputs, i); break end
  end
  return true
end

--- O(1) dostęp do portów po nazwie.
function Node:getInput(name)  return self.inputsByName[name]  end
function Node:getOutput(name) return self.outputsByName[name] end

-- -- -- Props / convenience ------------------------------------------------

function Node:setPos(x, y) self.x, self.y = x, y end
function Node:setSize(w, h) self.w, self.h = w, h end

-- -- -- Serializacja -------------------------------------------------------

--- Zapisz do tabeli JSON-friendly (format v1).
function Node:serialize()
  local inputs, outputs = {}, {}
  for i = 1, #self.inputs do
    local p = self.inputs[i]
    inputs[i] = { name = p.name, kind = p.kind, typeName = p.typeName }
  end
  for i = 1, #self.outputs do
    local p = self.outputs[i]
    outputs[i] = { name = p.name, kind = p.kind, typeName = p.typeName }
  end
  local props = {}
  for k, v in pairs(self.props) do props[k] = v end

  return {
    id     = self.id,
    type   = self.type,
    title  = self.title,
    x      = self.x, y = self.y,
    w      = self.w, h = self.h,
    inputs = inputs,
    outputs= outputs,
    props  = props,
  }
end

--- Odtwórz z tabeli (wspiera brakujące pola).
function Node.deserialize(t)
  local node = Node:new(t.id, t.type, t.title)
  node.x, node.y = t.x or 0, t.y or 0
  node.w, node.h = t.w, t.h

  if t.inputs then
    for _, p in ipairs(t.inputs) do node:addInput (p.name, p.kind, p.typeName) end
  end
  if t.outputs then
    for _, p in ipairs(t.outputs) do node:addOutput(p.name, p.kind, p.typeName) end
  end

  node.props = {}
  for k, v in pairs(t.props or {}) do node.props[k] = v end
  return node
end

return Node
