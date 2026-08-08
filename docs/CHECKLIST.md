# MIR Design-System Checklist
**Repo:** arynndarkstar/mir-gof  
**Last updated:** 2026-08-08

---

## MAIN TASK (now)
**Bootstrap MIR class-design system + IO ASAP — graphic path scaffolded.**

Where we are:
- Classic GoF complete (raw + spartan where useful).
- Graphic option-module DLLs under `plugins/`; PixelBuffer in `lib_src/graphic/`.
- Console MainLoop exists; graphic_sdl2 skeleton ready for SDL2 tutor/build.

---

## CURRENT TODO (in progress / just finished)

### After-Action — Graphic plugin scaffold + PixelBuffer
- [x] `lib_src/graphic/pixel_buffer.hpp` — clear, put, line, h/v line, fill_rect, blit, bind
- [x] `plugins/graphic_sdl2/` — SDL2 MainLoop DLL skeleton (window + present + demo frame)
- [x] `plugins/pixel_buffer/` — notes (impl in lib_src)
- [x] UML graphic path
- [x] Idioms README → GoF-style “what is what” groups

**AAR notes**
- Graphics = MIR-exclusive option-module DLLs under `plugins/`.
- PixelBuffer = pure CPU surface; SDL2 binds + presents.
- Build: `-DMIR_HAS_SDL2 -lSDL2` for window; without = software-only fallback.
- Tutor for SDL2 later (you).
- Dopamine: first window + draw-line path is scaffolded.

---

## NEXT TODO (immediate)

1. **Build / run graphic_sdl2** with SDL2 on your machine.
2. **Expand blitters / clip / alpha** on PixelBuffer as needed.
3. **Mouse / key → Observer** from SDL2 events.
4. **DLL test-bed + AI seat** when ready.
5. Keep pure GoF pristine; mergers only under `advanced/`.

---

## SECONDARY TASKS (state)

| Task | State | Notes |
|------|--------|------|
| Classic GoF | **done** | |
| Spartan pairs | **mostly done** | |
| Advanced / mergers | **complete for now** | |
| Idioms | **what-is-what map** | ownership / static-poly / typing / assignment |
| Graphic + PixelBuffer | **scaffolded** | graphic_sdl2 + lib_src/graphic |
| Mouse / key | queued | |
| Plugin discovery | open | |
| DLL test-bed | future | |
| AI seat | future | Adapt / Facade |
| Sprite contact-sheet | future | Ultima 5 / Wizard’s Crown style |

---

## FUTURE / LONG-TERM

- SDL2 tutor (you), richer blitters, sound-out
- DLL test-bed for MIR hot-swap stations
- AI seat Adapt/Facade boundary
- Sprite contact-sheet generator (tile icons)
- SOLID mapping notes

---

## Rules

- Pure GoF = pristine classic only.
- Mergers under `advanced/` only.
- Graphics as option-module DLLs under `plugins/`.
- Checklist = Main → Current/AAR → Next → Secondary → Future.
