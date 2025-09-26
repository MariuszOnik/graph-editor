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
