// MIR widget test-bed MainLoop
// g++ -shared -fPIC -DMIR_HAS_SDL2 -o graphic_testbed.so testbed_widgets.cpp -I../.. -lSDL2

#include "../../core/stations.hpp"
#include "../../lib_src/graphic/pixel_buffer.hpp"
#include "../../lib_src/graphic/draw_extras.hpp"
#include "../../lib_src/graphic/icons8.hpp"
#include "../../lib_src/graphic/widgets.hpp"
#include "../../lib_src/graphic/window_factory.hpp"
#include "../../lib_src/graphic/input.hpp"
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

class WidgetTestBed : public MainLoop {
#if MIR_SDL2_OK
    SDL_Window* window_ = nullptr;
    SDL_Surface* surface_ = nullptr;
#endif
    graphic::PixelBuffer buf_, sprite_;
    graphic::TestBedFrame ui_;
    graphic::SoftWindow demo_win_;
    graphic::InputSnapshot input_;
    bool running_ = false;
    bool mouse_was_down_ = false;
    int width_ = 720, height_ = 440;

public:
    void enter() override {
        running_ = true;
#if MIR_SDL2_OK
        if (SDL_Init(SDL_INIT_VIDEO) != 0) { running_ = false; return; }
        window_ = SDL_CreateWindow("MIR widget test-bed",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width_, height_, SDL_WINDOW_SHOWN);
        if (!window_) { running_ = false; return; }
        surface_ = SDL_GetWindowSurface(window_);
        if (surface_) buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
#else
        buf_.resize(width_, height_);
#endif
        ui_.layout(width_, height_);
        demo_win_ = graphic::WindowFactory::create_stage3(200, 120, 280, 160, "demo");
        sprite_.resize(16, 16);
        sprite_.clear(graphic::Color::rgb(255, 0, 255));
        graphic::circle_fill(sprite_, 8, 8, 6, graphic::Color::rgb(200, 80, 60));
        std::printf("[testbed] line|circle|icons|clear. Title X=quit.\n");
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
            if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP) {
                input_.mouse_l = (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT);
                input_.mouse_x = ev.button.x; input_.mouse_y = ev.button.y;
            }
            if (ev.type == SDL_MOUSEMOTION) {
                input_.mouse_x = ev.motion.x; input_.mouse_y = ev.motion.y;
                input_.mouse_l = (ev.motion.state & SDL_BUTTON_LMASK) != 0;
            }
        }
        if (surface_) buf_.bind(surface_->w, surface_->h, surface_->pitch, surface_->pixels);
#endif
        graphic::InputSnapshot edge = input_;
        if (!input_.mouse_l) mouse_was_down_ = false;
        if (input_.mouse_l && !mouse_was_down_) mouse_was_down_ = true;
        else if (input_.mouse_l) edge.mouse_l = false;

        ui_.handle(edge);
        demo_win_.handle(edge);
        if (ui_.bar.hit_close) { running_ = false; return false; }
        draw_frame();
#if MIR_SDL2_OK
        if (window_) SDL_UpdateWindowSurface(window_);
#endif
        return running_;
    }

    void exit() override {
        running_ = false;
#if MIR_SDL2_OK
        if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; }
        SDL_Quit();
#endif
    }

private:
    void draw_frame() {
        using namespace graphic;
        ui_.draw_chrome(buf_);
        const int dx = ui_.client.x + 8, dy = ui_.client.y + 48;
        const int dw = ui_.client.w - 16, dh = ui_.client.h - 56;
        buf_.fill_rect(dx, dy, dw, dh, Color::rgb(20, 24, 32));
        buf_.rect_outline(dx, dy, dw, dh, Color::rgb(60, 70, 90));
        const int cx = dx + dw / 2, cy = dy + dh / 2;
        const Color fg = Color::white(), bg = Color::rgb(20, 24, 32);

        switch (ui_.demo_mode) {
        case 0:
            buf_.line(dx+8, dy+8, dx+dw-8, dy+dh-8, Color::rgb(255, 200, 64));
            buf_.line(dx+dw-8, dy+8, dx+8, dy+dh-8, Color::rgb(80, 180, 255));
            buf_.hline(dx+8, dx+dw-8, cy, Color::rgb(180, 180, 180));
            buf_.put(cx, cy, Color::rgb(255, 80, 80));
            break;
        case 1:
            buf_.fill_rect(cx-50, cy-30, 100, 60, Color::rgb(48, 64, 96));
            buf_.rect_outline(cx-50, cy-30, 100, 60, Color::rgb(120, 140, 180));
            circle(buf_, cx, cy, 50, Color::rgb(100, 200, 120));
            circle_fill(buf_, cx-40, cy-20, 16, Color::rgb(200, 100, 80));
            break;
        case 2: {
            for (int i = 0; i < 5; ++i)
                sprite_drop(buf_, sprite_, dx+16+i*28, dy+16, Color::rgb(255, 0, 255));
            int ix = dx + 16, iy = dy + 50;
            auto ic = [&](Icon8 b) { draw_icon8(buf_, ix, iy, b, fg, bg, true); ix += 14; };
            ic(ICN_CLOSE); ic(ICN_MINIMIZE); ic(ICN_MAXIMIZE); ic(ICN_SQUARE);
            ic(ICN_CHECKBOX); ic(ICN_CHECKBOX_ON); ic(ICN_RADIO); ic(ICN_RADIO_ON);
            ic(ICN_CHECK); ic(ICN_MENU);
            demo_win_.draw(buf_);
            break;
        }
        default: break;
        }
    }
};

} // namespace plugins
} // namespace mir

extern "C" mir::PluginApi* mir_plugin_api() {
    static mir::PluginApi api = {
        "graphic_testbed", "0.2.0",
        []() -> mir::MainLoop* { return new mir::plugins::WidgetTestBed(); },
        nullptr, nullptr
    };
    return &api;
}
