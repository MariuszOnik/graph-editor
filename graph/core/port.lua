--[[
Port
----
Reprezentuje pojedyncze wejście lub wyjście węzła.

Odpowiedzialność:
- Opisuje punkt połączenia (link).
- Rozróżnia porty danych i exec.

Pola:
- name (string, np. "A" albo "ExecIn")
- kind (string: "data" | "exec")
- typeName (string: np. "number", "string", "vec2")
- node (Node właściciel, referencja wstecz)

Metody (stub):
- isCompatible(otherPort) -> bool
]]

-- graph/core/port.lua
-- Port (model) — prosty obiekt opisujący złącze węzła.

local class = require("middleclass")

local VALID_KIND = { data = true, exec = true }

local Port = class("Port")

--- ctor
-- @param name      string
-- @param kind      "data" | "exec"
-- @param typeName  string (np. "number","string","any")
-- @param node      Node (właściciel)
function Port:initialize(name, kind, typeName, node)
  if not VALID_KIND[kind] then
    error(("Invalid port kind '%s' (expected 'data' or 'exec')"):format(tostring(kind)))
  end
    self.name     = assert(name, "Port name required")
    self.kind     = kind
    self.typeName = typeName or "any"
    self.node     = assert(node, "Port requires owner node")
end

-- prosta zgodność typów: 'any' pasuje do wszystkiego, w innym razie nazwy muszą się zgadzać
local function typesCompatible(a, b)
    return a == "any" or b == "any" or a == b
end

--- Czy porty są kompatybilne do połączenia?
-- - ten port traktujemy jako "from" (wyjście), other jako "to" (wejście)
-- - musi zgadzać się kind oraz typy danych
function Port:isCompatible(other)
    if not other then return false end
    if self.kind ~= other.kind then return false end
    -- dla exec typ danych ignorujemy (brak danych), dla data sprawdzamy
    if self.kind == "data" then
      return typesCompatible(self.typeName, other.typeName)
    end
    return true
end

--- Minimalna serializacja (do odtworzenia nody, nie linku)
function Port:serialize()
    return { name = self.name, kind = self.kind, typeName = self.typeName }
end

--[[ TODO:
Port: wydziel typesCompatible do lokalnego modułu utils w core (przyda się też Graphowi).

]]


return Port

