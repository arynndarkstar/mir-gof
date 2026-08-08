# MIR GoF + C++ Idioms Library

Living catalog of Gang-of-Four patterns, advanced mergers, and C++ idioms
in two flavours:

- **raw**   — modern C++20/23, full standard library, expressive
- **spartan** — minimal, exception-free, no RTTI, embeddable / hardware friendly

## Layout

```
gof/
├── creational/     Factory Method, Abstract Factory, (Builder/Prototype/Singleton later)
├── structural/     Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Proxy
├── behavioral/     Strategy, Observer, Command, (State, Memento, Visitor …)
├── advanced/       Pattern mergers & evolved forms
│                   (Type-Erased Strategy, Policy-Strategy, CRTP State Machine …)
├── idioms/
│   ├── raw/        Full modern idioms (ScopeGuard, Pimpl, Type Erasure …)
│   └── spartan/    Same concepts stripped for constrained environments
└── common/         Shared CRTP bases, type-erasure helpers, policy tags
```

## Current Status (bootstrap)

| Pattern / Helper              | Raw | Spartan | Notes |
|-------------------------------|-----|---------|-------|
| Strategy                      | ✓   | ✓       | AI providers, render backends |
| Factory Method / Abstract F.  | ✓   | ✓       | Plugin station creation |
| Observer                      | ✓   | ✓       | Input events, state deltas |
| Command                       | ✓   | ✓       | Operator actions (+ undo hook) |
| CRTP                          | ✓   | ✓       | common/ |
| Type Erasure helpers          | ✓   | –       | common/type_erasure.hpp |
| Type-Erased Strategy (adv)    | ✓   | –       | advanced/ |
| ScopeGuard                    | ✓   | ✓       | idioms/ |

## Design Rules

1. Every pattern is a *working* header (+ minimal conceptual example in comments).
2. Patterns that MIR itself uses get first-class treatment.
3. Advanced folder holds *merged* or *evolved* forms.
4. Raw vs Spartan pairs share the same conceptual interface where possible so
   a design can switch density without rewriting call sites.
5. UML sketches live in `../docs/uml/`.

## Immediate next targets

- State + Memento (pair with Command for undo)
- Adapter / Facade for platform pixel-buffer & sound out
- Policy-based Strategy merger
- Pimpl idiom (raw + spartan)

This library is the foundation for the “class design system” and
“refactoring in place” mentality of MIR.
