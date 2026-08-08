# MIR Design-System Checklist
**Repo:** arynndarkstar/mir-gof  
**Canonical source (current):** `lib_src/gof/` + `lib_src/idioms/`  
**Last updated:** 2026-08-08

---

## MAIN TASK (now)
**Bootstrap the MIR class-design system + get IO live ASAP.**

Where we are:
- Classic GoF catalog is essentially complete (raw + spartan where it matters).
- Layout is under `lib_src/`; pure GoF stays pristine; mergers live separately.
- Console MainLoop exists. Graphic / pixel-buffer / SDL path is **next major IO thread** (not this one).
- Idioms are secondary; only the minimal set that patterns need is present.

---

## CURRENT TODO (in progress / just finished)

### After-Action — Spartan pass + Idioms expansion
- [x] Spartan pairs added: Bridge, Decorator, Proxy, Composite, Chain of Responsibility, Template Method, Iterator, Prototype, Mediator
- [x] Idioms expanded: NonCopyable/MoveOnly (raw+spartan), Copy-and-swap, EBO helper, Traits skeleton
- [x] `lib_src/idioms/README.md` stance documented

**AAR notes**
- Pure GoF remains pristine; spartan forms sit beside raw in the same classic folders.
- Mergers stay out of pure GoF trees.
- Idioms still secondary — only high-value, need-driven additions.
- User rearranges after account reset; this tree is the working surface until then.

---

## NEXT TODO (immediate)

1. **Keep GoF surface pristine** — any new pure pattern goes into the correct classic folder; no mergers mixed in.
2. **Capture future ideation** in this checklist (see FUTURE section) so AARs and upcoming work can be commented strongly.
3. **Stand by for pixel-buffer / SDL / SDL2 thread** — user will open that separately.
4. **DLL test-bed + AI seat** — sketch Adapt / Facade responsibilities when that thread opens.

---

## SECONDARY TASKS (state)

| Task | State | Notes |
|------|--------|------|
| Classic GoF catalog | **done** | All 23 + practical extras (Null Object, Object Pool) |
| Spartan pairs | **mostly done** | Core + structural/behavioral pairs added this pass |
| Advanced / mergers dir | open | Type-Erased Strategy, Command+Memento, Policy-Strategy already exist; keep them away from pure GoF |
| Idioms expansion | **expanded** | + NonCopyable/MoveOnly, Copy-and-swap, EBO, Traits; still secondary |
| Graphic window + pixel buffer | **next major** | Other thread |
| Mouse / key secondary input | queued | After pixel-buffer |
| Plugin discovery / settings load | open | |
| DLL test-bed for MIR | future | |
| AI seat (Adapt / Facade / ?) | future | |
| SOLID mapping notes | open | See note below |
| Refactor-in-place examples | open | |
| Sprite contact-sheet generator | future | Ultima 5 / SSI Wizard’s Crown style tiles |

---

## FUTURE / LONG-TERM

### Design system
- CRTP State Machine, Type-Erased Observer (advanced polish)
- Expand idioms only when a concrete MIR need appears  
  Better sources than Wikibooks: **Alexandrescu — Modern C++ Design**, modern CRTP/type-erasure/policy material
- SOLID + refactor-in-place notes (short mapping of each principle to the patterns we actually use)

### IO / runtime
- Graphic window + pixel-buffer abstraction (SDL / SDL2 path)
- Mouse / key secondary input
- Sound-out abstraction
- Full plugin discovery + settings-driven loading
- DLL test-bed for MIR (load / unload / hot-swap stations)

### AI seat
- Adapt / Facade (and possibly Strategy / Proxy) responsibilities for the AI provider station
- Clear boundary: Mir stays PEBCAK operator; AI seat is a replaceable station

### Creative / tooling
- **Generate image contact sheet for sprite characters**  
  Style reference: Ultima 5 / SSI Wizard’s Crown tiles — simple character, UI, and map-tile icons  
  Use case: rapid visual inventory of sprite sets for graphic station / tests

### Process
- Checklist stays the single rapid-fire surface: Main → Current/AAR → Next → Secondary → Future
- Strong commentary welcome on upcoming work, AARs, and ideation (drop notes under the relevant section)

---

## SOLID (quick answer)

**SOLID is a thing**, not just a word.  
Five design principles that patterns often serve:

| Letter | Principle | Rough meaning |
|--------|-----------|----------------|
| **S** | Single Responsibility | One reason to change |
| **O** | Open/Closed | Open for extension, closed for modification |
| **L** | Liskov Substitution | Subtypes must be usable where the base is |
| **I** | Interface Segregation | Many small interfaces > one fat one |
| **D** | Dependency Inversion | Depend on abstractions, not concretions |

We will add a short “which MIR patterns support which letter” note later; not blocking IO.

---

## Rules of engagement (rapid-fire)

- Pure GoF folders = pristine classic patterns (raw / spartan only).
- Mergers live elsewhere.
- Idioms stay secondary until needed.
- Checklist is the living AAR + todo surface — comment freely on upcoming, after-action, and future ideation.
- Pixel-buffer / SDL work happens in its own thread when you open it.
