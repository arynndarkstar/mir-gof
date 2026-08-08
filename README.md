# MIR

**Mir** — the PEBCAK human operator shell.

Only one hard-coded binary: `core/mir.cpp`.  
Everything else (MainLoop, AI provider, StateEngine) is discovered at runtime via plugins or refused.

## Bootstrap Goals (current)

1. **IO ASAP**
   - [x] Console MainLoop plugin (cmd terminal)
   - [ ] Graphic window + pixel buffer abstraction
   - [ ] Mouse / key secondary input

2. **Class Design System**
   - Living GoF + C++ idioms library (`gof/`) — Strategy, Factory, Observer, Command, Type Erasure, ScopeGuard (raw + spartan)
   - Advanced mergers started (Type-Erased Strategy)
   - UML sketches in `docs/uml/`
   - Foundation for “refactoring in place”

3. **Grok IO path**
   - Structure ready → Grok can start impacting source
   - Git repo as the shared surface

## Layout

```
mir/
├── core/                 # the only hard-coded binary + stations
│   ├── mir.cpp / mir.hpp
│   ├── stations.hpp
│   ├── types.hpp
│   └── platform/
├── plugins/
│   └── console_mainloop/ # first IO station
├── gof/                  # Gang-of-Four + idioms library
│   ├── creational/
│   ├── structural/
│   ├── behavioral/
│   ├── advanced/
│   ├── idioms/{raw,spartan}/
│   └── common/
└── docs/
    ├── uml/
    ├── design-notes/
    └── whiteboard/
```

## Quick start (dev)

```bash
# build core + console plugin (posix)
# (CMake / Makefile coming next)
```

## Design Principles

- No hard-coded plugin names inside Mir.
- Settings / discovery only.
- Stations are pure interfaces.
- Plugins export a single `mir_plugin_api()` symbol.
- Human (Mir) remains the PEBCAK operator in the loop.

See `gof/README.md` for the pattern library rules.
