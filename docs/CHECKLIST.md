# MIR + GoF Library — Living Executive Checklist
**Last updated:** 2026-08-08 (wave 3 — bulk missing patterns)  
**Repo:** arynndarkstar/mir-gof  
**Goal:** Complete class-design system + IO ASAP while maximizing design density.

---

## A. GoF Pattern Catalog Status

### Creational
- [x] Factory Method (raw + spartan)
- [x] Abstract Factory (raw + spartan)
- [x] Builder
- [x] Prototype
- [ ] Singleton (low priority — prefer discovery)
- [x] Object Pool

### Structural
- [x] Adapter
- [x] Bridge
- [x] Composite
- [x] Decorator
- [x] Facade
- [ ] Flyweight
- [x] Proxy

### Behavioral
- [x] Strategy (raw + spartan + type-erased)
- [x] Observer (raw + spartan)
- [x] Command (raw + spartan)
- [x] State (raw + spartan)
- [x] Memento (raw + spartan)
- [x] Null Object (raw + spartan)
- [x] Chain of Responsibility
- [ ] Interpreter
- [x] Iterator
- [ ] Mediator
- [x] Template Method
- [ ] Visitor

### Advanced / Mergers
- [x] Type-Erased Strategy
- [x] Command + Memento
- [x] Policy-based Strategy
- [ ] CRTP State Machine
- [ ] Type-Erased Observer

### Idioms & Common
- [x] ScopeGuard (raw + spartan)
- [x] CRTP
- [x] Type Erasure helpers
- [x] Pimpl (raw + spartan)
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
- [x] UML for wave-2 patterns
- [ ] SOLID mapping notes
- [ ] Refactor-in-place examples

---

## C. Waves Completed

**Wave 1** — Strategy, Factory, Observer, Command, Type Erasure, ScopeGuard  
**Wave 2** — State, Memento, Null Object, Adapter, Facade, Builder, Command+Memento  
**Wave 3** — Pimpl, Prototype, Object Pool, Bridge, Composite, Decorator, Proxy, Iterator, Template Method, Chain of Responsibility, Policy-Strategy  

---

## D. Still Open (lower priority / next)

- Flyweight, Interpreter, Mediator, Visitor, Singleton
- CRTP State Machine, Type-Erased Observer
- Non-copyable helpers
- Graphic window + pixel buffer station
- Mouse / key input
- SOLID notes + refactor examples
- CMake / build system

---

## Rules of Engagement
- Every new pattern = working header (problem → solution → MIR use-case)
- Keep raw / spartan conceptual interface aligned
- Push early, push often
- Prefer patterns that unlock the graphic IO path or StateEngine
