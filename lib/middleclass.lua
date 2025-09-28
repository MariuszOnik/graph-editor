-- middleclass.lua (minimal implementation for the graph editor)
-- Simplified class system for Lua

local class = {}

function class(name)
  local cls = {}
  cls.__index = cls
  cls.name = name
  cls.super = nil
  
  function cls:new(...)
    local instance = setmetatable({}, cls)
    if instance.initialize then
      instance:initialize(...)
    end
    return instance
  end
  
  function cls:extend(name)
    local child = class(name)
    child.super = cls
    return child
  end
  
  return cls
end

return class