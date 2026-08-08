# graphic_sdl2 — MIR option-module DLL

**Role:** MainLoop station that opens an SDL2 window and presents a software `PixelBuffer`.

## Layout

```
plugins/
├── console_mainloop/     # cmd terminal
├── graphic_sdl2/         # THIS — window + present
└── pixel_buffer/         # notes (impl in lib_src/graphic)
```

MIR-exclusive: discovered via `mir_plugin_api()`.

## Build sketch

```bash
g++ -shared -fPIC -DMIR_HAS_SDL2 -o graphic_sdl2.so sdl2_mainloop.cpp -I../.. -lSDL2
# without SDL2:
g++ -shared -fPIC -o graphic_sdl2.so sdl2_mainloop.cpp -I../..
```

## Status
- [x] Skeleton MainLoop + plugin export
- [x] PixelBuffer bind + demo draw
- [ ] Resize, mouse/key → Observer, tutor
