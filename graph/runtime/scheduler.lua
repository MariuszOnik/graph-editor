--[[
Scheduler (Exec + Coroutines)
-----------------------------
Odpowiedzialność:
- Uruchamianie ścieżek „exec” jako korutyn.
- Harmonogram „sleep” (czas) i „waitUntil” (warunek).
- Pętla odświeżania: tick(dt).
- Rejestrowanie handlerów zdarzeń (Start, Timer, KeyDown itp.).

Pola (wewnętrzne):
- coroutines : { { co=thread, wake=number_ms, cond=function|nil, ctx=table } }
- nowMs()    : function zwracająca czas w ms (wstrzykiwana / zamienialna dla testów)
- events     : mapa: eventName -> lista funkcji entry(ctx,payload) (wygenerowane/zbindowane)

Publiczne API (stub):
- new(opts) -> Scheduler
  -- opts.nowMs? : function
- on(eventName, entryFn)            -- zarejestruj handler „entryFn(ctx, payload)”
- start(eventName, payload, ctx)    -- odpal łańcuch exec jako korutynę
- tick(dt_ms)                        -- odmraża korutyny, wznawia je; wołane co klatkę
- stopAll()                          -- zabija wszystkie aktywne korutyny

API dla węzłów (wywoływane Z WEWNĄTRZ korutyny):
- yieldSleep(ms)         -- coroutine.yield({ type="sleep", t=ms })
- yieldWaitUntil(fn)     -- coroutine.yield({ type="waitUntil", cond=fn })
]]
