# MIR GoF + C++ Idioms Library

Living catalog of Gang-of-Four patterns, advanced mergers, and C++ idioms
in two flavours:

- **raw**   — modern C++20/23, full standard library, expressive
- **spartan** — minimal, exception-free, no RTTI, embeddable / hardware friendly

## Layout

```
gof/
├── creational/     Factory, Abstract Factory, Builder, Prototype, Singleton
├── structural/     Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Proxy
├── behavioral/     Chain, Command, Interpreter, Iterator, Mediator, Memento,
│                   Observer, State, Strategy, Template Method, Visitor
├── advanced/       Pattern mergers, policy-based design, type-erasure hybrids,
│                   CRTP + Strategy, Command + Memento, etc.
├── idioms/
│   ├── raw/        Full modern idioms (Pimpl, ScopeGuard, Type Erasure, CRTP…)
│   └── spartan/    Same concepts stripped for constrained environments
└── common/         Shared CRTP bases, type-erasure helpers, policy tags
```

## Design Rules for this library

1. Every pattern is a *working* header + minimal example.
2. Patterns that MIR itself uses (Strategy for AI providers, Factory for plugins,
   Observer for event buses, Command for operator actions) get first-class treatment.
3. Advanced folder holds *merged* or *evolved* forms (e.g. “Policy Strategy”,
   “Type-Erased Observer”, “CRTP State Machine”).
4. Raw vs Spartan pairs share the same conceptual interface where possible so
   a design can switch density without rewriting call sites.
5. UML sketches live in `../docs/uml/`.

## Immediate targets (bootstrap)

- Strategy (AI providers, render backends)
- Factory Method + Abstract Factory (plugin creation)
- Command (operator decisions, undo later via Memento)
- Observer (input events, state deltas)
- CRTP + Type Erasure (common/)
- ScopeGuard / RAII (idioms)

This library is the foundation for the “class design system” and
“refactoring in place” mentality of MIR.
