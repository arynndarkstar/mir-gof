# MIR IO boiler — terminal + graphic surface

**Highest priority after pattern catalog.** Hammer this in before AI seat, sprites, sound.

## What “IO boiler” means

One **MainLoop** station is live at a time:

| Plugin DLL | Surface | Input |
|------------|---------|--------|
| `console_mainloop` | stdin/stdout text | keyboard line |
| `graphic_sdl2` | SDL2 window + PixelBuffer | mouse + keys |

Both export `mir_plugin_api()` → `create_mainloop()`.  
Mir loads **one** MainLoop plugin and runs `enter / tick / exit`.

## Layout

```
plugins/
  console_mainloop/     # text IO
  graphic_sdl2/         # window + software surface
lib_src/graphic/
  pixel_buffer.hpp      # draw / blit
  surface_facade.hpp    # Facade over buffer
  input.hpp             # InputSnapshot DTO
```

## Patterns in use

| Pattern | Where |
|---------|--------|
| **Strategy / plugin** | MainLoop chosen by which DLL is loaded |
| **Facade** | `SurfaceFacade` over PixelBuffer + bind |
| **DTO** | `InputSnapshot` (later → Observer / Command) |
| **Adapter** | SDL surface pixels bound into PixelBuffer |

## Build (graphic)

```bash
g++ -shared -fPIC -DMIR_HAS_SDL2 \
  -o graphic_sdl2.so plugins/graphic_sdl2/sdl2_mainloop.cpp \
  -I. -lSDL2
```

Without SDL2: software buffer only (no window).

## Explicitly deferred

- Sound (speaker down)
- AI seat Adapt/Facade
- Sprite contact sheets (Ultima 5 / Wizard’s Crown style)
- Full plugin discovery / settings file

## Rule

Do not rearrange GoF folders while IO boiler is being hardened.  
Small additive changes only until console **or** graphic path runs end-to-end on your machine.
