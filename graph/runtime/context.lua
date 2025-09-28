--[[
Context
-------
Odpowiedzialność:
- Przenosi stan wykonania (blackboard) i usługi (services) między węzłami.
- Nie zna UI; to czysty runtime-owy obiekt.

Pola:
- blackboard : table    -- współdzielony stan gry/sceny (np. {player={x=..}})
- services   : table    -- wstrzyknięte serwisy (Input, Audio, Scene, Time, UIBus...)

Publiczne API (stub):
- new(opts) -> Context
  -- opts.blackboard? : table
  -- opts.services?   : table
- get(name)          -> any      -- skrót do blackboard[name]
- set(name, value)   -> void
- service(name)      -> any      -- zwróć services[name] lub błąd jeśli brak
]]

-- graph/runtime/context.lua
-- Context przechowuje stan wykonania i serwisy dla runtime

local class = require("lib.middleclass")

local Context = class("Context")

--- Constructor
-- @param opts table {blackboard?, services?}
function Context:initialize(opts)
  opts = opts or {}
  self.blackboard = opts.blackboard or {}
  self.services = opts.services or {}
end

--- Get value from blackboard
-- @param name string
-- @return any
function Context:get(name)
  return self.blackboard[name]
end

--- Set value in blackboard
-- @param name string
-- @param value any
function Context:set(name, value)
  self.blackboard[name] = value
end

--- Get service by name
-- @param name string
-- @return any
function Context:service(name)
  local service = self.services[name]
  if not service then
    error("Service '" .. name .. "' not found")
  end
  return service
end

--- Check if service exists
-- @param name string
-- @return boolean
function Context:hasService(name)
  return self.services[name] ~= nil
end

--- Register a service
-- @param name string
-- @param service any
function Context:registerService(name, service)
  self.services[name] = service
end

--- Get copy of blackboard for debugging
-- @return table
function Context:getBlackboard()
  local copy = {}
  for k, v in pairs(self.blackboard) do
    copy[k] = v
  end
  return copy
end

--- Get list of service names
-- @return array of string
function Context:getServiceNames()
  local names = {}
  for name, _ in pairs(self.services) do
    table.insert(names, name)
  end
  return names
end

--- Clear blackboard
function Context:clearBlackboard()
  self.blackboard = {}
end

return Context
