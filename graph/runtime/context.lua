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
