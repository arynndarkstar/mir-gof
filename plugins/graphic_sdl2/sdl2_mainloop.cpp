// Graphic MainLoop — SDL2 + PixelBuffer + mouse
// g++ -shared -fPIC -DMIR_HAS_SDL2 -o graphic_sdl2.so sdl2_mainloop.cpp -I../.. -lSDL2

#include "../../core/stations.hpp"
#include "../../lib_src/graphic/pixel_buffer.hpp"
#include <cstdio>

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

struct InputState {
    int mouse_x = 0, mouse_y = 0;
    bool mouse_l = false, mouse_r = false, mouse_m = false;
    bool quit = false;
};

class Sdl2MainLoop : public MainLoop {
#if MIR_SDL2_OK
    SDL_Window* window_ = nullptr;
    SDL_Surface* surface_ = nullptr;
#endif
    graphic::PixelBuffer buf_, tile_;
    InputState input_;
    bool running_ = false;
    int width_ = 640, height_ = 400;

public:
    void enter() override {
        running_ = true;
#if MIR_SDL2_OK
        if (SDL_Init(SDL_INIT_VIDEO) != 0) { running_ = false; return; }
        window_ = SDL_CreateWindow("MIR graphic — mouse",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width_, height_, SDL_WINDOW_SHOWN);
        if (!window_) { running_ = false; return; }
        surface_ = SDL_GetWindowSurface(window_);
        if (surface_) buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
        SDL_ShowCursor(SDL_DISABLE);
        std::printf("[sdl2] LMB stamps tile; ESC quit.\n");
#else
        buf_.resize(width_, height_);
#endif
        make_demo_tile(); redraw(); present();
    }

    bool tick(Tick& t) override {
        t.dt = 0.016;
        if (!running_) return false;
#if MIR_SDL2_OK
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) handle_event(ev);
        if (input_.quit) { running_ = false; return false; }
        SDL_GetMouseState(&input_.mouse_x, &input_.mouse_y);
        if (surface_) buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
#endif
        redraw(); present();
        return running_;
    }

    void exit() override {
        running_ = false;
#if MIR_SDL2_OK
        SDL_ShowCursor(SDL_ENABLE);
        if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; }
        SDL_Quit();
#endif
    }

private:
#if MIR_SDL2_OK
    void handle_event(const SDL_Event& ev) {
        switch (ev.type) {
        case SDL_QUIT: input_.quit = true; break;
        case SDL_KEYDOWN:
            if (ev.key.keysym.sym == SDLK_ESCAPE) input_.quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            const bool down = (ev.type == SDL_MOUSEBUTTONDOWN);
            if (ev.button.button == SDL_BUTTON_LEFT) input_.mouse_l = down;
            if (ev.button.button == SDL_BUTTON_RIGHT) input_.mouse_r = down;
            input_.mouse_x = ev.button.x; input_.mouse_y = ev.button.y;
            break;
        }
        case SDL_MOUSEMOTION:
            input_.mouse_x = ev.motion.x; input_.mouse_y = ev.motion.y;
            break;
        default: break;
        }
    }
#endif
    void make_demo_tile() {
        using namespace graphic;
        tile_.resize(16, 16);
        const Color key = Color::rgb(255, 0, 255);
        const Color dirt = Color::rgb(96, 72, 48);
        const Color edge = Color::rgb(64, 48, 32);
        tile_.clear(key);
        tile_.fill_rect(1, 1, 14, 14, dirt);
        tile_.rect_outline(1, 1, 14, 14, edge);
        tile_.put(4, 5, edge); tile_.put(11, 9, edge); tile_.put(7, 12, edge);
    }
    void redraw() {
        using namespace graphic;
        buf_.clear(Color::rgb(16, 24, 48));
        for (int i = 0; i < 8; ++i)
            buf_.blit_colorkey(tile_, 32 + i * 16, 32, Color::rgb(255, 0, 255));
        if (input_.mouse_l)
            buf_.blit_colorkey(tile_, input_.mouse_x - 8, input_.mouse_y - 8, Color::rgb(255, 0, 255));
        const Color c = input_.mouse_l ? Color::rgb(255, 220, 80) : Color::rgb(220, 220, 220);
        const int x = input_.mouse_x, y = input_.mouse_y;
        buf_.hline(x - 6, x - 2, y, c); buf_.hline(x + 2, x + 6, y, c);
        buf_.vline(x, y - 6, y - 2, c); buf_.vline(x, y + 2, y + 6, c);
        buf_.put(x, y, c);
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
        "graphic_sdl2", "0.2.0",
        []() -> mir::MainLoop* { return new mir::plugins::Sdl2MainLoop(); },
        nullptr, nullptr
    };
    return &api;
}
