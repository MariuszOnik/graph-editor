# grapheditor2

SOLID-owy edytor grafów (Lua + Raylib bindings). Czysty podział na **Core**, **Runtime** i **UI**. Bez spagetti. 💪

## Cele
- Minimalne sprzężenia, testowalny core w czystym Lua.
- Wykonywanie w trybie **Exec + coroutines** (na start), opcjonalnie **Dataflow** i **Codegen (Lua)**.
- Edytor UI oparty o `rcore`, `rshapes`, `rtext`, `rtextures`.

## Architektura (high level)
- **graph.core** – model domenowy: `Node`, `Port`, `Link`, `Graph`, `Registry`, `Serializer`.
- **graph.runtime** – wykonywanie: `Scheduler (coroutines)`, `Context (services)`, API: `start/tick/stop`.
- **graph.ui** – edytor: `Renderer`, `Controller`, `Hit`, `Gestures`, `Theme`, `Layout`.

### Kontrakty (skrót)
- `Graph.addNode/removeNode/addLink/serialize/deserialize`
- Runtime Exec: `start(eventName, payload)`, `tick(dt)`, `getInput/setOutput`, `yield({sleep|wait})`
- UI: `Renderer.draw(graph, selection, theme)`, `Controller.update(dt) -> Actions`

## Format serializacji (v1)
```json
{
  "version": 1,
  "nodes": [{ "id": "n1", "type": "Number", "x":100, "y":100, "w":120, "h":40, "props": { "value": 3 } }],
  "links": [{ "from": ["n1","out"], "to": ["n2","a"], "kind": "data" }],
  "locals": []
}


Tylko dane niezbędne do uruchomienia. Bez stanu UI (zaznaczenia itp.).

Migracje przy zmianie wersji.

Roadmap

Faza 0 – Skeleton

 Struktura katalogów: graph/core, graph/runtime, graph/ui

 Rejestr węzłów (pluginy)

 Minimalne węzły: Number, Add, Display (data) + Start, Delay, Branch (exec)

Faza 1 – Runtime Exec

 Scheduler (coroutines) z sleep/waitUntil

 Event bridge: Start, Timer, KeyDown

 Serializacja v1 (roundtrip test)

Faza 2 – Edytor UI

 Renderer: grid, nody, porty (kółko=data, prostokąt=exec), linki Bezier

 Hit-test, tworzenie/edytowanie linków, multi-select/drag

 Inspektor właściwości

 Undo/Redo (command stack)

Faza 3 – Integracje

 Services: Input, Audio, Scene, Time

 Pakiety węzłów audio/scene

Faza 4 – Dataflow / Codegen (opcjonalnie)

 Dirty flags/memoizacja

 Kompilacja czystych subgrafów do Lua

Zasady współpracy

Gałęzie feature → PR do dev, main tylko release.

Commity: Conventional Commits.

CI: lint/format/test (TODO).