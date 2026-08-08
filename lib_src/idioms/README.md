# MIR Idioms (`lib_src/idioms`)

Secondary to the GoF catalog. Only idioms that patterns or MIR stations actually need.

## Present

| Idiom | Raw | Spartan | Notes |
|-------|-----|---------|-------|
| ScopeGuard | ✓ | ✓ | RAII arbitrary cleanup |
| Pimpl | ✓ | ✓ | Compilation firewall |
| NonCopyable / MoveOnly | ✓ | ✓ | Ownership discipline |
| Copy-and-swap | ✓ | – | Strong exception guarantee pattern |
| EBO helper | ✓ | – | Empty-base / policy compression |
| Traits skeleton | ✓ | – | Type-dependent properties |

CRTP + Type Erasure live under `gof/common/` (they serve patterns directly).

## Stance

- Not a dump of Wikibooks “More C++ Idioms”.
- Expand only when a concrete MIR need appears.
- Preferred deeper references: Alexandrescu *Modern C++ Design*, modern CRTP / type-erasure / policy material, ISO C++ core guidelines.

## Layout

```
idioms/
├── raw/
└── spartan/
```
