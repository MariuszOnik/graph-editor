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
