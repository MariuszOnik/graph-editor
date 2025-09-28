--[[
Scheduler (Exec + Coroutines)
-----------------------------
Odpowiedzialność:
- Uruchamianie ścieżek „exec" jako korutyn.
- Harmonogram „sleep" (czas) i „waitUntil" (warunek).
- Pętla odświeżania: tick(dt).
- Rejestrowanie handlerów zdarzeń (Start, Timer, KeyDown itp.).

Pola (wewnętrzne):
- coroutines : { { co=thread, wake=number_ms, cond=function|nil, ctx=table } }
- nowMs()    : function zwracająca czas w ms (wstrzykiwana / zamienialna dla testów)
- events     : mapa: eventName -> lista funkcji entry(ctx,payload) (wygenerowane/zbindowane)

Publiczne API (stub):
- new(opts) -> Scheduler
  -- opts.nowMs? : function
- on(eventName, entryFn)            -- zarejestruj handler „entryFn(ctx, payload)"
- start(eventName, payload, ctx)    -- odpal łańcuch exec jako korutynę
- tick(dt_ms)                        -- odmraża korutyny, wznawia je; wołane co klatkę
- stopAll()                          -- zabija wszystkie aktywne korutyny

API dla węzłów (wywoływane Z WEWNĄTRZ korutyny):
- yieldSleep(ms)         -- coroutine.yield({ type="sleep", t=ms })
- yieldWaitUntil(fn)     -- coroutine.yield({ type="waitUntil", cond=fn })
]]

-- graph/runtime/scheduler.lua  
-- Scheduler zarządza wykonywaniem korutyn z harmonogramem

local class = require("lib.middleclass")

local Scheduler = class("Scheduler")

--- Constructor
-- @param opts table {nowMs?}
function Scheduler:initialize(opts)
  opts = opts or {}
  self.coroutines = {}  -- active coroutines
  self.events = {}      -- eventName -> array of handler functions
  
  -- Time function (injectable for testing)
  self.nowMs = opts.nowMs or function()
    return os.clock() * 1000  -- convert seconds to milliseconds
  end
end

--- Register event handler
-- @param eventName string
-- @param entryFn function(ctx, payload)
function Scheduler:on(eventName, entryFn)
  assert(eventName, "Event name required")
  assert(entryFn, "Entry function required")
  
  if not self.events[eventName] then
    self.events[eventName] = {}
  end
  
  table.insert(self.events[eventName], entryFn)
end

--- Start execution chain as coroutine
-- @param eventName string
-- @param payload any
-- @param ctx Context
function Scheduler:start(eventName, payload, ctx)
  local handlers = self.events[eventName]
  if not handlers then
    return -- No handlers for this event
  end
  
  local currentTime = self.nowMs()
  
  for _, entryFn in ipairs(handlers) do
    local co = coroutine.create(function()
      entryFn(ctx, payload)
    end)
    
    table.insert(self.coroutines, {
      co = co,
      wake = currentTime, -- Wake immediately
      cond = nil,
      ctx = ctx,
      eventName = eventName
    })
  end
end

--- Update scheduler - resume coroutines that are ready
-- @param dt_ms number delta time in milliseconds
function Scheduler:tick(dt_ms)
  local currentTime = self.nowMs()
  local activeCoroutines = {}
  
  for _, corState in ipairs(self.coroutines) do
    local shouldResume = false
    
    -- Check if coroutine should wake up
    if corState.cond then
      -- Wait until condition
      if corState.cond() then
        shouldResume = true
      end
    elseif currentTime >= corState.wake then
      -- Time-based wake up
      shouldResume = true
    end
    
    if shouldResume then
      local status = coroutine.status(corState.co)
      
      if status == "suspended" then
        local success, result = coroutine.resume(corState.co)
        
        if success then
          if result then
            -- Coroutine yielded with instruction
            if result.type == "sleep" then
              corState.wake = currentTime + result.t
              corState.cond = nil
              table.insert(activeCoroutines, corState)
            elseif result.type == "waitUntil" then
              corState.wake = 0
              corState.cond = result.cond
              table.insert(activeCoroutines, corState)
            end
          else
            -- Coroutine finished normally
            -- Don't add to activeCoroutines
          end
        else
          -- Coroutine error
          print("Coroutine error:", result)
        end
      end
    else
      -- Keep waiting
      table.insert(activeCoroutines, corState)
    end
  end
  
  self.coroutines = activeCoroutines
end

--- Stop all active coroutines
function Scheduler:stopAll()
  self.coroutines = {}
end

--- Get number of active coroutines  
-- @return number
function Scheduler:getActiveCount()
  return #self.coroutines
end

--- Yield with sleep instruction (called from within coroutine)
-- @param ms number milliseconds to sleep
function yieldSleep(ms)
  return coroutine.yield({ type = "sleep", t = ms })
end

--- Yield with wait until instruction (called from within coroutine)  
-- @param fn function condition to wait for
function yieldWaitUntil(fn)
  return coroutine.yield({ type = "waitUntil", cond = fn })
end

-- Export helper functions globally for use in node execution
_G.yieldSleep = yieldSleep
_G.yieldWaitUntil = yieldWaitUntil

return Scheduler