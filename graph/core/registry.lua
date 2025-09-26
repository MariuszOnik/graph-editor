--[[
Registry
--------
Rejestr typów węzłów.

Odpowiedzialność:
- Pozwala rejestrować nowe typy węzłów.
- Tworzy instancje na podstawie typu (dla deserializacji).

Pola:
- types (mapa: typeName -> factoryFn)

Metody (stub):
- register(typeName, factoryFn, metadata)
- create(typeName, id) -> Node
- getMetadata(typeName) -> table
]]
