--[[
Runtime API (fasada)
--------------------
Odpowiedzialność:
- Udostępnia proste wejście do runtime dla reszty aplikacji (gra/edytor).
- Składa w całość: Scheduler + Context.
- Nie zawiera logiki „węzłów".

Pola:
- scheduler : Scheduler
- context   : Context

Publiczne API (stub):
- new(opts) -> Runtime
  -- opts.scheduler? : Scheduler (dla testów można wstrzyknąć mock)
  -- opts.context?   : Context
- on(eventName, entryFn)           -- alias do scheduler.on
- emit(eventName, payload)         -- start handlerów z domyślnym contextem
- tick(dt_ms)                      -- alias do scheduler.tick
- stopAll()
- setContext(ctx) / getContext()

Uwagi:
- entryFn ma sygnaturę function(ctx, payload) i POWINIEN być „exec-chain" (może yielduać).
- Węzły używają helperów (np. runtime.yieldSleep/ms) – do rozważenia jako delegacja do scheduler'a.
]]

-- graph/runtime/api.lua
-- Runtime API facade łącząca Scheduler i Context

local class = require("lib.middleclass")
local Scheduler = require("graph.runtime.scheduler")
local Context = require("graph.runtime.context")

local Runtime = class("Runtime")

--- Constructor
-- @param opts table {scheduler?, context?}
function Runtime:initialize(opts)
  opts = opts or {}
  self.scheduler = opts.scheduler or Scheduler:new()
  self.context = opts.context or Context:new()
end

--- Register event handler (delegates to scheduler)
-- @param eventName string
-- @param entryFn function(ctx, payload)
function Runtime:on(eventName, entryFn)
  self.scheduler:on(eventName, entryFn)
end

--- Emit event with current context (start coroutines)
-- @param eventName string  
-- @param payload any
function Runtime:emit(eventName, payload)
  self.scheduler:start(eventName, payload, self.context)
end

--- Update runtime (tick scheduler)
-- @param dt_ms number delta time in milliseconds
function Runtime:tick(dt_ms)
  self.scheduler:tick(dt_ms)
end

--- Stop all running coroutines
function Runtime:stopAll()
  self.scheduler:stopAll()
end

--- Set context
-- @param ctx Context
function Runtime:setContext(ctx)
  self.context = ctx
end

--- Get current context
-- @return Context
function Runtime:getContext()
  return self.context
end

--- Get number of active coroutines
-- @return number
function Runtime:getActiveCount()
  return self.scheduler:getActiveCount()
end

--- Helper to register a simple handler that prints
-- @param eventName string
-- @param message string
function Runtime:onDebug(eventName, message)
  self:on(eventName, function(ctx, payload)
    print("DEBUG [" .. eventName .. "]: " .. (message or "triggered"))
    if payload then
      print("  Payload:", payload)
    end
  end)
end

--- Helper to register a delay handler
-- @param eventName string
-- @param delayMs number
-- @param callback function(ctx, payload)
function Runtime:onDelay(eventName, delayMs, callback)
  self:on(eventName, function(ctx, payload)
    yieldSleep(delayMs)
    if callback then
      callback(ctx, payload)
    end
  end)
end

return Runtime