# MIR GoF + C++ Idioms Library

Living catalog of Gang-of-Four patterns, advanced mergers, and C++ idioms
in two flavours:

- **raw**   — modern C++20/23, full standard library, expressive
- **spartan** — minimal, exception-free, no RTTI, embeddable / hardware friendly

## Layout

```
gof/
├── creational/     Factory Method, Abstract Factory, Builder, …
├── structural/     Adapter, Facade, Bridge, Composite, Decorator, …
├── behavioral/     Strategy, Observer, Command, State, Memento, Null Object, …
├── advanced/       Type-Erased Strategy, Command+Memento, …
├── idioms/
│   ├── raw/        ScopeGuard, Pimpl, …
│   └── spartan/    Same concepts stripped
└── common/         CRTP, Type Erasure helpers
```

## Current Status

| Pattern / Helper              | Raw | Spartan | Notes |
|-------------------------------|-----|---------|-------|
| Strategy                      | ✓   | ✓       | AI providers, render backends |
| Factory Method / Abstract F.  | ✓   | ✓       | Plugin station creation |
| Builder                       | ✓   | –       | Settings / bootstrap objects |
| Observer                      | ✓   | ✓       | Input events, state deltas |
| Command                       | ✓   | ✓       | Operator actions |
| State                         | ✓   | ✓       | StateEngine, modal modes |
| Memento                       | ✓   | ✓       | Snapshots / undo |
| Null Object                   | ✓   | ✓       | Missing plugins / optional collabs |
| Adapter                       | ✓   | ✓       | Pixel-buf / window / platform |
| Facade                        | ✓   | ✓       | Subsystem entry points |
| CRTP                          | ✓   | ✓       | common/ |
| Type Erasure helpers          | ✓   | –       | common/type_erasure.hpp |
| Type-Erased Strategy (adv)    | ✓   | –       | advanced/ |
| Command + Memento (adv)       | ✓   | –       | advanced/ |
| ScopeGuard                    | ✓   | ✓       | idioms/ |

## Design Rules

1. Every pattern is a *working* header (problem → solution → MIR use-case).
2. Patterns that MIR itself uses get first-class treatment.
3. Advanced folder holds *merged* or *evolved* forms.
4. Raw vs Spartan pairs share the same conceptual interface where possible.
5. UML sketches live in `../docs/uml/`.
6. Living checklist: `../docs/CHECKLIST.md`.

## Next targets

- Policy-based Strategy merger
- Pimpl idiom (raw + spartan)
- Type-Erased Observer
- Bridge / Composite / Decorator (as needed for graphic hierarchy)
- Object Pool

This library is the foundation for the “class design system” and
“refactoring in place” mentality of MIR.
