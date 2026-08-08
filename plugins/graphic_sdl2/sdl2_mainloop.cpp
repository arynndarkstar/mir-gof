// Graphic MainLoop plugin — SDL2 window + pixel buffer present
// MIR-exclusive option module (DLL).

#include "../../core/stations.hpp"
#include "../../lib_src/graphic/pixel_buffer.hpp"

#include <cstdio>
#include <memory>
#include <string>

#if defined(MIR_HAS_SDL2) || defined(__has_include)
#  if defined(MIR_HAS_SDL2) || __has_include(<SDL2/SDL.h>)
#    include <SDL2/SDL.h>
#    define MIR_SDL2_OK 1
#  endif
#endif

#ifndef MIR_SDL2_OK
#  define MIR_SDL2_OK 0
#endif

namespace mir {
namespace plugins {

class Sdl2MainLoop : public MainLoop {
#if MIR_SDL2_OK
    SDL_Window*   window_  = nullptr;
    SDL_Surface*  surface_ = nullptr;
#endif
    graphic::PixelBuffer buf_;
    bool running_ = false;
    int  width_   = 640;
    int  height_  = 400;
    const char* title_ = "MIR graphic (SDL2)";

public:
    void enter() override {
        running_ = true;
#if MIR_SDL2_OK
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::fprintf(stderr, "[sdl2] SDL_Init: %s\n", SDL_GetError());
            running_ = false;
            return;
        }
        window_ = SDL_CreateWindow(title_,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width_, height_, SDL_WINDOW_SHOWN);
        if (!window_) {
            std::fprintf(stderr, "[sdl2] CreateWindow: %s\n", SDL_GetError());
            running_ = false;
            return;
        }
        surface_ = SDL_GetWindowSurface(window_);
        if (surface_)
            buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
        std::printf("[sdl2] window %dx%d ready. Close window or ESC to quit.\n", width_, height_);
#else
        buf_.resize(width_, height_);
        std::printf("[sdl2] built WITHOUT SDL2 — software buffer only.\n");
#endif
        demo_frame();
        present();
    }

    bool tick(Tick& t) override {
        t.dt = 0.016;
        if (!running_) return false;
#if MIR_SDL2_OK
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) { running_ = false; return false; }
            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE) {
                running_ = false; return false;
            }
        }
        if (surface_)
            buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
#endif
        present();
        return running_;
    }

    void exit() override {
        running_ = false;
#if MIR_SDL2_OK
        if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; surface_ = nullptr; }
        SDL_Quit();
#endif
        std::printf("[sdl2] MainLoop exit.\n");
    }

    graphic::PixelBuffer& buffer() { return buf_; }

private:
    void demo_frame() {
        using namespace graphic;
        buf_.clear(Color::rgb(16, 24, 48));
        buf_.fill_rect(40, 40, 200, 120, Color::rgb(48, 96, 160));
        buf_.line(0, 0, width_ - 1, height_ - 1, Color::rgb(255, 200, 64));
        buf_.hline(20, width_ - 20, height_ / 2, Color::rgb(200, 200, 200));
        buf_.vline(width_ / 2, 20, height_ - 20, Color::rgb(200, 200, 200));
    }
    void present() {
#if MIR_SDL2_OK
        if (window_) SDL_UpdateWindowSurface(window_);
#endif
    }
};

} // namespace plugins
} // namespace mir

extern "C" mir::PluginApi* mir_plugin_api() {
    static mir::PluginApi api = {
        "graphic_sdl2",
        "0.1.0",
        []() -> mir::MainLoop* { return new mir::plugins::Sdl2MainLoop(); },
        nullptr,
        nullptr
    };
    return &api;
}
