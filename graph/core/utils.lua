
--
local Utils = {}

-- Prosta zgodność typów: 'any' pasuje do wszystkiego, w innym razie nazwy muszą się zgadzać
function Utils.typesCompatible(a, b)
    return a == "any" or b == "any" or a == b
end

return Utils