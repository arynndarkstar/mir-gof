# MIR GoF + C++ Idioms Library

Living catalog of Gang-of-Four patterns, advanced mergers, and C++ idioms
in two flavours:

- **raw**   — modern C++20/23, full standard library, expressive
- **spartan** — minimal, exception-free, no RTTI, embeddable / hardware friendly

## Layout

```
gof/
├── creational/     Factory, Abstract Factory, Builder, Prototype, Object Pool
├── structural/     Adapter, Bridge, Composite, Decorator, Facade, Proxy
├── behavioral/     Strategy, Observer, Command, State, Memento, Null Object,
│                   Chain of Responsibility, Iterator, Template Method
├── advanced/       Type-Erased Strategy, Command+Memento, Policy-Strategy
├── idioms/
│   ├── raw/        ScopeGuard, Pimpl
│   └── spartan/    ScopeGuard, Pimpl
└── common/         CRTP, Type Erasure helpers
```

## Current Status

| Pattern / Helper              | Raw | Spartan | Notes |
|-------------------------------|-----|---------|-------|
| Strategy                      | ✓   | ✓       | + type-erased + policy |
| Factory Method / Abstract F.  | ✓   | ✓       | |
| Builder                       | ✓   | –       | |
| Prototype                     | ✓   | –       | |
| Object Pool                   | ✓   | –       | |
| Observer                      | ✓   | ✓       | |
| Command                       | ✓   | ✓       | + Memento merger |
| State                         | ✓   | ✓       | |
| Memento                       | ✓   | ✓       | |
| Null Object                   | ✓   | ✓       | |
| Chain of Responsibility       | ✓   | –       | |
| Iterator                      | ✓   | –       | |
| Template Method               | ✓   | –       | |
| Adapter                       | ✓   | ✓       | |
| Bridge                        | ✓   | –       | |
| Composite                     | ✓   | –       | |
| Decorator                     | ✓   | –       | |
| Facade                        | ✓   | ✓       | |
| Proxy                         | ✓   | –       | |
| Pimpl                         | ✓   | ✓       | idioms/ |
| ScopeGuard                    | ✓   | ✓       | idioms/ |
| CRTP / Type Erasure           | ✓   | –       | common/ |
| Policy-based Strategy         | ✓   | –       | advanced/ |

## Still open
Flyweight, Interpreter, Mediator, Visitor, Singleton, CRTP State Machine, Type-Erased Observer

## Design Rules
1. Working header with problem → solution → MIR use-case.
2. MIR-used patterns get first-class treatment.
3. Advanced folder = mergers / evolved forms.
4. Raw / Spartan pairs stay conceptually aligned.
5. UML in `../docs/uml/`. Living checklist in `../docs/CHECKLIST.md`.

This library is the foundation for the “class design system” and
“refactoring in place” mentality of MIR.
