# MIR Design-System Checklist
**Repo:** arynndarkstar/mir-gof  
**Last updated:** 2026-08-08

---

## MAIN TASK (now)
**Hammer basic terminal + graphic surface IO into the MIR boiler.**

Where we are:
- Pattern catalog largely done (no big-rearrange while IO hardens).
- Console MainLoop exists; graphic_sdl2 + PixelBuffer + mouse scaffolded.
- Sound = lowest (speaker broken). AI seat / sprites = future.
- You may be one response behind — small additive deltas only.

---

## CURRENT TODO

### After-Action — IO boiler focus
- [x] PixelBuffer blitters (rect, colorkey, blend)
- [x] Mouse in graphic_sdl2 + cursor + tile stamp
- [x] `lib_src/graphic/input.hpp` — InputSnapshot
- [x] `lib_src/graphic/surface_facade.hpp` — Facade
- [x] `docs/IO_BOILER.md` — single page for terminal/graphic path

**AAR:** Priority locked — console OR graphic MainLoop `enter/tick/exit` before AI/sprites/sound.

---

## NEXT TODO

1. **Run one path end-to-end** (console *or* graphic_sdl2 + SDL2).
2. Optional: InputSnapshot → Observer later (not blocking).
3. Keep GoF folders stable while IO settles.
4. Sprites / AI seat only after surface IO feels solid.

---

## SECONDARY (state)

| Task | State | Priority |
|------|--------|----------|
| Console MainLoop | done | IO boiler |
| graphic_sdl2 + PixelBuffer + mouse | scaffolded | IO boiler |
| SurfaceFacade + InputSnapshot | added | IO boiler |
| Mouse/key → Observer | open | after run works |
| Plugin discovery | open | mid |
| AI seat Adapt/Facade | future | low now |
| Sprite contact-sheet (U5/WC) | future | low now |
| Sound | deferred | least |

---

## FUTURE

- Sprite sheets (floor / icon / char)
- AI seat (Adapt / Facade)
- DLL test-bed
- Sound (when speaker lives)

---

## Rules

- Highest after patterns: **terminal + graphic surface IO**.
- Small additive changes; one step behind is OK.
- No big directory reshuffles until IO is hammered in.
- Sound last.
