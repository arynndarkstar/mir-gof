# MIR + GoF Library — Living Executive Checklist
**Last updated:** 2026-08-08 (wave 2 complete)  
**Repo:** arynndarkstar/mir-gof  
**Goal:** Complete class-design system + IO ASAP while maximizing design density.

---

## A. GoF Pattern Catalog Status

### Creational
- [x] Factory Method (raw + spartan)
- [x] Abstract Factory (raw + spartan)
- [x] Builder
- [ ] Prototype
- [ ] Singleton (low priority — prefer discovery)
- [ ] Object Pool

### Structural
- [x] Adapter          ← high (pixel-buf / window / platform)
- [ ] Bridge
- [ ] Composite
- [ ] Decorator
- [x] Facade           ← high (platform façade)
- [ ] Flyweight
- [ ] Proxy

### Behavioral
- [x] Strategy (raw + spartan + type-erased)
- [x] Observer (raw + spartan)
- [x] Command (raw + spartan)
- [x] State            ← high (StateEngine station)
- [x] Memento          ← high (Command undo)
- [x] Null Object      ← high (missing plugins / optional stations)
- [ ] Chain of Responsibility
- [ ] Interpreter
- [ ] Iterator
- [ ] Mediator
- [ ] Template Method
- [ ] Visitor

### Advanced / Mergers
- [x] Type-Erased Strategy
- [x] Command + Memento
- [ ] Policy-based Strategy
- [ ] CRTP State Machine
- [ ] Type-Erased Observer

### Idioms & Common
- [x] ScopeGuard (raw + spartan)
- [x] CRTP
- [x] Type Erasure helpers
- [ ] Pimpl (raw + spartan)
- [ ] Non-copyable / Move-only helpers

---

## B. MIR Core / IO Bootstrap

### Stations & Plugins
- [x] Core stations interfaces (MainLoop / AiStation / StateEngine)
- [x] Console MainLoop plugin (cmd terminal)
- [ ] Graphic window + pixel buffer abstraction
- [ ] Mouse / key secondary input
- [ ] Platform dynlib complete (posix done, win32 later)
- [ ] Plugin discovery / settings-driven loading

### Design System
- [x] gof/ living catalog structure
- [x] UML for core stations
- [x] UML for core GoF patterns
- [x] UML for State / Memento / Adapter / Facade / Builder / Null Object
- [ ] SOLID mapping notes
- [ ] Refactor-in-place examples

---

## C. Immediate Execution Wave (wave 2 — DONE)

1. [x] **State** (raw + spartan)
2. [x] **Memento** (raw + spartan)
3. [x] **Command + Memento** advanced merger
4. [x] **Null Object** (raw + spartan)
5. [x] **Adapter** (raw + spartan)
6. [x] **Facade** (raw + spartan)
7. [x] **Builder** (raw)
8. [x] Update README status tables
9. [x] New UML sketches
10. [x] Push all to git

---

## D. Later / Lower Priority
- Iterator, Template Method, Visitor
- Bridge, Composite, Decorator, Proxy, Flyweight
- Object Pool, Prototype, Singleton
- Full CMake / build system
- Windows dynlib
- Sound out abstraction
- Graphic window + pixel buffer station

---

## Rules of Engagement
- Every new pattern = working header (raw preferred, spartan when meaningful)
- Header comment = problem → solution → MIR use-case
- Keep raw / spartan conceptual interface aligned
- Push early, push often
- Prefer patterns that unlock the graphic IO path or StateEngine
