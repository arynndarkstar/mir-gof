# Advanced / Mergers (`lib_src/gof/advanced`)

**Not pure GoF.** Evolved or merged forms. Keep out of pristine classic folders.

## Present

| Merger | Idea | Primary lineage |
|--------|------|-----------------|
| Type-Erased Strategy | Value-semantic Strategy, any callable | GoF Strategy + type erasure |
| Type-Erased Observer | Heterogeneous listeners without common base | GoF Observer + type erasure |
| Command + Memento | Undo via snapshot | GoF Command + Memento |
| Policy-based Strategy | Compile-time Strategy (zero overhead) | GoF Strategy + Alexandrescu policies / Loki |
| CRTP State Machine | Static / low-overhead state dispatch | GoF State + CRTP (Coplien) |

## Where the ideas come from

Not invented from scratch — drawn from established C++ design knowledge:

1. **GoF (1994)** — Strategy, Observer, Command, State, Memento as runtime patterns
2. **Andrei Alexandrescu — *Modern C++ Design* (2001) + Loki** — policy-based design as compile-time Strategy
3. **CRTP** — named by Jim Coplien (1995); static polymorphism
4. **Type erasure** — external polymorphism; common in modern C++ (and `std::function`)
5. **More C++ Idioms (Wikibooks)** — community idiom catalog; **incomplete** (Policy-based Design still TODO). Useful index, not authoritative for policies
6. **Contemporary** — e.g. oopscenities “Strategy vs Policy-Based Design” (runtime virtual vs template policies)

**“More C++ Idioms” was a first group** — a parallel catalog of *idioms* the way GoF catalogued *patterns*. It never fully finished.

## MIR rule

- Pure GoF folders = classic only (raw / spartan)
- `advanced/` = mergers and compile-time evolutions
- Policy / CRTP when the behaviour set is closed at compile time
- Classic or type-erased forms when plugins / runtime swap are required
