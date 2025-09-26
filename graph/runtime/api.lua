--[[
Runtime API (fasada)
--------------------
Odpowiedzialność:
- Udostępnia proste wejście do runtime dla reszty aplikacji (gra/edytor).
- Składa w całość: Scheduler + Context.
- Nie zawiera logiki „węzłów”.

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
- entryFn ma sygnaturę function(ctx, payload) i POWINIEN być „exec-chain” (może yielduać).
- Węzły używają helperów (np. runtime.yieldSleep/ms) – do rozważenia jako delegacja do scheduler’a.
]]
