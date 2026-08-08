# `lib_src/graphic` — surface tools (not the window)

## Split (hard rule)

| Piece | Role | Depends on graphic plugin? |
|-------|------|----------------------------|
| **PixelBuffer** (+ blitters, Color) | Surface edit toolbox — any 2D pixel surface | **No** |
| **SurfaceFacade** | Thin Facade over PixelBuffer | **No** |
| **InputSnapshot** | Shared input DTO | **No** |
| **`plugins/graphic_sdl2`** | MainLoop: SDL window + present | **Yes** (optional) |

**PixelBuffer is used even when MIR graphic is off / not loaded**  
(console-only, offline tile baking, tests, contact-sheet generators, etc.).

**SDL = main graphics**  
Window, events, present. May *bind* a PixelBuffer to the window surface; does not own pixel-editing APIs.

```
lib_src/graphic/          ← always available tools
  pixel_buffer.hpp
  surface_facade.hpp
  input.hpp

plugins/graphic_sdl2/     ← optional MainLoop DLL
  sdl2_mainloop.cpp       ← uses PixelBuffer when presenting
```
