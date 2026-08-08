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
- Idioms are secondary; only high-value need-driven set is present.

---

## CURRENT TODO (in progress / just finished)

### After-Action — Spartan continue + Advanced/mergers complete
- [x] Additional Spartan: Builder, Object Pool (fixed capacity)
- [x] Advanced complete: Type-Erased Observer, CRTP State Machine, Policy-Strategy documented + multi-policy host
- [x] `advanced/README.md` — lineage (GoF, Alexandrescu/Loki, CRTP/Coplien, type erasure, Wikibooks status)
- [x] Skipped Spartan for Flyweight / Visitor / Interpreter (low value as minimalist forms)

**AAR notes**
- Pure GoF stays pristine; spartan beside raw.
- Mergers live only under `advanced/`.
- Knowledge sources are established literature, not invention (see advanced/README).
- “More C++ Idioms” = first community idiom *group/catalog*; incomplete (Policy-based still TODO).
- User rearranges after account reset.

---

## NEXT TODO (immediate)

1. **Keep GoF surface pristine** — any new pure pattern goes into the correct classic folder; no mergers mixed in.
2. **Capture future ideation** in this checklist so AARs and upcoming work can be commented strongly.
3. **Stand by for pixel-buffer / SDL / SDL2 thread** — user will open that separately.
4. **DLL test-bed + AI seat** — sketch Adapt / Facade responsibilities when that thread opens.

---

## SECONDARY TASKS (state)

| Task | State | Notes |
|------|--------|------|
| Classic GoF catalog | **done** | All 23 + practical extras |
| Spartan pairs | **mostly done** | Builder + Object Pool added; Flyweight/Visitor/Interpreter skipped |
| Advanced / mergers dir | **complete for now** | Type-Erased Strategy/Observer, Command+Memento, Policy-Strategy, CRTP State Machine |
| Idioms expansion | **expanded** | ScopeGuard, Pimpl, NonCopyable, Copy-and-swap, EBO, Traits |
| Graphic window + pixel buffer | **next major** | Other thread |
| Mouse / key secondary input | queued | After pixel-buffer |
| Plugin discovery / settings load | open | |
| DLL test-bed for MIR | future | |
| AI seat (Adapt / Facade / ?) | future | |
| SOLID mapping notes | open | |
| Refactor-in-place examples | open | |
| Sprite contact-sheet generator | future | Ultima 5 / SSI Wizard’s Crown style |

---

## FUTURE / LONG-TERM

### Design system
- Expand idioms only when a concrete MIR need appears  
  Better sources: **Alexandrescu — Modern C++ Design**, modern CRTP/type-erasure/policy material
- SOLID + refactor-in-place notes

### IO / runtime
- Graphic window + pixel-buffer abstraction (SDL / SDL2 path)
- Mouse / key secondary input
- Sound-out abstraction
- Full plugin discovery + settings-driven loading
- DLL test-bed for MIR

### AI seat
- Adapt / Facade (and possibly Strategy / Proxy) for the AI provider station
- Mir stays PEBCAK operator; AI seat is a replaceable station

### Creative / tooling
- Generate image contact sheet for sprite characters (Ultima 5 / SSI Wizard’s Crown style tiles)

### Process
- Checklist = Main → Current/AAR → Next → Secondary → Future
- Strong commentary welcome on upcoming, AAR, and ideation

---

## SOLID (quick answer)

**SOLID is a thing** — five principles (SRP, OCP, LSP, ISP, DIP). Short mapping later; not blocking IO.

---

## Rules of engagement

- Pure GoF folders = pristine classic (raw / spartan only).
- Mergers only under `advanced/`.
- Idioms secondary until needed.
- Checklist is the living AAR + todo surface.
- Pixel-buffer / SDL = other thread when you open it.
