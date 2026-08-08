# MIR + GoF Library — Living Executive Checklist
**Last updated:** 2026-08-08  
**Repo:** arynndarkstar/mir-gof  
**Goal:** Complete class-design system + IO ASAP while maximizing design density.

---

## A. GoF Pattern Catalog Status

### Creational
- [x] Factory Method (raw + spartan)
- [x] Abstract Factory (raw + spartan)
- [ ] Builder
- [ ] Prototype
- [ ] Singleton (low priority — prefer discovery)
- [ ] Object Pool

### Structural
- [ ] Adapter          ← high (pixel-buf / window / platform)
- [ ] Bridge
- [ ] Composite
- [ ] Decorator
- [ ] Facade           ← high (platform façade)
- [ ] Flyweight
- [ ] Proxy

### Behavioral
- [x] Strategy (raw + spartan + type-erased)
- [x] Observer (raw + spartan)
- [x] Command (raw + spartan)
- [ ] State            ← high (StateEngine station)
- [ ] Memento          ← high (Command undo)
- [ ] Null Object      ← high (missing plugins / optional stations)
- [ ] Chain of Responsibility
- [ ] Interpreter
- [ ] Iterator
- [ ] Mediator
- [ ] Template Method
- [ ] Visitor

### Advanced / Mergers
- [x] Type-Erased Strategy
- [ ] Command + Memento
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
- [ ] UML for State / Memento / Adapter / Facade
- [ ] SOLID mapping notes
- [ ] Refactor-in-place examples

---

## C. Immediate Execution Wave (next 2 h)

Priority order for maximum value + density:

1. [ ] **State** (raw + spartan)
2. [ ] **Memento** (raw + spartan)
3. [ ] **Command + Memento** advanced merger
4. [ ] **Null Object** (raw + spartan)
5. [ ] **Adapter** (raw + spartan) — platform / pixel-buffer oriented
6. [ ] **Facade** (raw + spartan)
7. [ ] **Builder** (raw)
8. [ ] Update README status tables
9. [ ] New UML sketches
10. [ ] Push all to git

---

## D. Later / Lower Priority
- Iterator, Template Method, Visitor
- Bridge, Composite, Decorator, Proxy, Flyweight
- Object Pool, Prototype, Singleton
- Full CMake / build system
- Windows dynlib
- Sound out abstraction

---

## Rules of Engagement
- Every new pattern = working header (raw preferred, spartan when meaningful)
- Header comment = problem → solution → MIR use-case
- Keep raw / spartan conceptual interface aligned
- Push early, push often
- Prefer patterns that unlock the graphic IO path or StateEngine
