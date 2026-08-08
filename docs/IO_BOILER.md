# MIR IO boiler — terminal + graphic surface

**Highest priority after pattern catalog.** Hammer this in before AI seat, sprites, sound.

## Hard split: SDL vs PixelBuffer

| | SDL (`graphic_sdl2`) | PixelBuffer (`lib_src/graphic`) |
|--|----------------------|----------------------------------|
| Role | **Main graphics** — window, events, present | **Tools** for all surface-edit requests |
| Required? | Optional plugin DLL | Always available library |
| When graphic off | Not loaded | Still used (tests, offline draw, baking) |

PixelBuffer is **not** part of the graphic plugin. SDL may bind/present a buffer; editing APIs live in `lib_src/graphic/` forever.

## What “IO boiler” means

One **MainLoop** station is live at a time:

| Plugin DLL | Surface | Input |
|------------|---------|--------|
| `console_mainloop` | stdin/stdout text | keyboard line |
| `graphic_sdl2` | SDL2 window (binds PixelBuffer to present) | mouse + keys |

Both export `mir_plugin_api()` → `create_mainloop()`.  
Mir loads **one** MainLoop plugin and runs `enter / tick / exit`.

## Layout

```
plugins/
  console_mainloop/     # text IO
  graphic_sdl2/         # main graphics (optional)
lib_src/graphic/        # surface tools (always)
  pixel_buffer.hpp
  surface_facade.hpp
  input.hpp
```

## Patterns

| Pattern | Where |
|---------|--------|
| Strategy / plugin | MainLoop DLL choice |
| Facade | SurfaceFacade over PixelBuffer |
| Adapter | SDL surface pixels → PixelBuffer::bind |

## Build (main graphics)

```bash
g++ -shared -fPIC -DMIR_HAS_SDL2 \
  -o graphic_sdl2.so plugins/graphic_sdl2/sdl2_mainloop.cpp \
  -I. -lSDL2
```

## Deferred

Sound, AI seat, sprite sheets, full plugin discovery.
