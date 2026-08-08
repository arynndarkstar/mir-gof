# MIR GoF Library (`lib_src/gof`)

Living Gang-of-Four catalog + advanced mergers.

## Status (classic set complete)

| Category     | Present |
|--------------|--------|
| Creational   | Factory Method, Abstract Factory, Builder, Prototype, Object Pool, Singleton* |
| Structural   | Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Proxy |
| Behavioral   | Strategy, Observer, Command, State, Memento, Null Object, Chain of Responsibility, Iterator, Template Method, Mediator, Visitor, Interpreter |
| Advanced     | Type-Erased Strategy, Command+Memento, Policy-based Strategy |
| Common       | CRTP, Type Erasure helpers |

\* Singleton provided for completeness; MIR prefers discovery over classic Singleton.

## Layout

```
gof/
├── creational/
├── structural/
├── behavioral/
├── advanced/
└── common/
```

## Design rules

1. Working header: problem → solution → MIR use-case.
2. Raw (modern) preferred; spartan pair when the pattern is used in constrained paths.
3. Advanced = mergers / evolved forms.
4. UML sketches in `../../docs/uml/`.
5. Living checklist in `../../docs/CHECKLIST.md`.
