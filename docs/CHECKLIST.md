# MIR + GoF Library — Living Executive Checklist
**Last updated:** 2026-08-08 (lib_src reorg + remaining classic GoF)  
**Repo:** arynndarkstar/mir-gof  
**Canonical source:** `lib_src/gof/` + `lib_src/idioms/`

---

## A. Directory layout (new)

```
mir/
├── core/
├── plugins/
├── lib_src/
│   ├── gof/
│   │   ├── creational/
│   │   ├── structural/
│   │   ├── behavioral/
│   │   ├── advanced/
│   │   └── common/
│   └── idioms/
│       ├── raw/
│       └── spartan/
└── docs/
    ├── uml/
    ├── tutor/markdown/     ← how_to_uml_in_md.md
    └── CHECKLIST.md
```

Old `gof/` at repo root is legacy mirror; prefer `lib_src/`.

---

## B. GoF Pattern Catalog

### Creational
- [x] Factory Method (raw + spartan)
- [x] Abstract Factory (raw + spartan)
- [x] Builder
- [x] Prototype
- [x] Object Pool
- [x] Singleton (provided; low priority for MIR)

### Structural
- [x] Adapter (raw + spartan)
- [x] Bridge
- [x] Composite
- [x] Decorator
- [x] Facade (raw + spartan)
- [x] Flyweight
- [x] Proxy

### Behavioral
- [x] Strategy (raw + spartan + type-erased + policy)
- [x] Observer (raw + spartan)
- [x] Command (raw + spartan)
- [x] State (raw + spartan)
- [x] Memento (raw + spartan)
- [x] Null Object (raw + spartan)
- [x] Chain of Responsibility
- [x] Iterator
- [x] Template Method
- [x] Mediator
- [x] Visitor
- [x] Interpreter

### Advanced / Mergers
- [x] Type-Erased Strategy
- [x] Command + Memento
- [x] Policy-based Strategy
- [ ] CRTP State Machine
- [ ] Type-Erased Observer

### Idioms (minimal — not primary focus yet)
- [x] ScopeGuard (raw + spartan)
- [x] Pimpl (raw + spartan)
- [x] CRTP / Type Erasure (in gof/common)
- [ ] Further idioms deferred (see lib_src/README.md for better sources)

---

## C. MIR Core / IO Bootstrap

- [x] Core stations interfaces
- [x] Console MainLoop plugin
- [ ] Graphic window + pixel buffer abstraction
- [ ] Mouse / key secondary input
- [ ] Plugin discovery / settings-driven loading
- [ ] SOLID mapping notes
- [ ] Refactor-in-place examples

---

## D. Docs

- [x] UML core stations
- [x] UML core GoF patterns
- [x] UML wave-2 patterns
- [x] How to UML in Markdown (`docs/tutor/markdown/how_to_uml_in_md.md`)
- [ ] More UML for remaining patterns

---

## E. Still open / next

1. Graphic window + pixel buffer station (highest IO value)
2. CRTP State Machine / Type-Erased Observer (advanced polish)
3. SOLID notes + refactor-in-place examples
4. Expand idioms only when a concrete need appears
