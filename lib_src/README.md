# MIR `lib_src` — class-design system source

Canonical layout for the living design-system library.

```
lib_src/
├── gof/                    # Gang-of-Four + advanced mergers
│   ├── creational/
│   ├── structural/
│   ├── behavioral/
│   ├── advanced/           # mergers (Type-Erased Strategy, Command+Memento, Policy…)
│   └── common/             # CRTP, type-erasure helpers
└── idioms/                 # C++ idioms (raw + spartan)
    ├── raw/
    └── spartan/
```

## Why this layout

- `gof/` is the primary design vocabulary (patterns).
- `idioms/` is intentionally **secondary** for now.
  Classic GoF book + pattern catalogs come first.
  Idioms (Pimpl, ScopeGuard, Policy-based design, …) support the patterns
  but are not the main catalog.
- Nothing else should sit at the `lib_src/` root except this README.
  Future libraries (pixel-buffer helpers, math, …) get their own sibling folders
  under `lib_src/` when needed.

## Namespace

All headers live under `mir::gof` (or `mir::gof::spartan` / `mir::gof::advanced` /
`mir::gof::idiom`).

## Idioms stance

The old Wikibooks “More C++ Idioms” is incomplete (Policy-based Design is still TODO,
many modern C++20/23 techniques are missing).

Better primary sources for when we expand idioms:

1. **Andrei Alexandrescu — Modern C++ Design** (the canonical policy-based / Loki material)
2. **Modern C++ Design Patterns** repos that show CRTP, type erasure, policy, Pimpl together
3. ISO C++ core guidelines + current standard library practice

Existing idioms already present (minimal set that patterns need):

- ScopeGuard (RAII cleanup)
- Pimpl (compilation firewall)
- CRTP + Type Erasure (in `gof/common/`)

Further idioms will be added only when a concrete MIR need appears.
