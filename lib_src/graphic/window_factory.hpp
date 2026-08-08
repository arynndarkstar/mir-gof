#pragma once
// Window factory — staged software windows
// Stage 1: pixels + lines
// Stage 2: rectangles / panels + client buffer
// Stage 3: full chrome (title bar, icons, blit)

#include "pixel_buffer.hpp"
#include "icons8.hpp"
#include "widgets.hpp"
#include <string>

namespace mir {
namespace graphic {

enum class WindowStage {
    Stage1_PixelsLines = 1,
    Stage2_Rectangles  = 2,
    Stage3_FullChrome  = 3
};

struct WindowDesc {
    int x = 40, y = 40, w = 320, h = 200;
    std::string title;
    WindowStage stage = WindowStage::Stage3_FullChrome;
    bool closable = true, minimizable = true, maximizable = true;
};

struct SoftWindow {
    WindowDesc desc;
    TitleBar bar;
    Rect frame, client;
    PixelBuffer surface;
    bool closed = false;

    void layout() {
        frame = {desc.x, desc.y, desc.w, desc.h};
        const int bar_h = (desc.stage == WindowStage::Stage1_PixelsLines) ? 0 : 20;
        bar.layout(desc.x, desc.y, desc.w, bar_h > 0 ? bar_h : 1);
        bar.btn_close = desc.closable;
        bar.btn_min = desc.minimizable;
        bar.btn_max = desc.maximizable;
        client = {desc.x, desc.y + bar_h, desc.w, desc.h - bar_h};
        if (desc.stage >= WindowStage::Stage2_Rectangles) {
            if (surface.width() != client.w || surface.height() != client.h)
                surface.resize(client.w, client.h);
        }
    }

    void draw(PixelBuffer& host, const WidgetStyle& style = {}) const {
        if (desc.stage == WindowStage::Stage1_PixelsLines) {
            const int x0 = frame.x, y0 = frame.y;
            const int x1 = frame.x + frame.w - 1, y1 = frame.y + frame.h - 1;
            host.hline(x0, x1, y0, style.edge_light);
            host.hline(x0, x1, y1, style.edge_dark);
            host.vline(x0, y0, y1, style.edge_light);
            host.vline(x1, y0, y1, style.edge_dark);
            host.put(x0, y0, style.accent);
            host.put(x1, y0, style.accent);
            host.put(x0, y1, style.accent);
            host.put(x1, y1, style.accent);
            return;
        }
        if (desc.stage == WindowStage::Stage2_Rectangles) {
            draw_panel(host, frame, style, false);
            host.fill_rect(client.x + 2, client.y + 2,
                           std::max(0, client.w - 4), std::max(0, client.h - 4),
                           Color::rgb(20, 24, 32));
            if (surface.width() > 0) host.blit(surface, client.x, client.y);
            return;
        }
        // stage 3
        draw_panel(host, frame, style, false);
        bar.draw(host, style);
        if (surface.width() > 0) host.blit(surface, client.x, client.y);
        else host.fill_rect(client.x, client.y, client.w, client.h, Color::rgb(20, 24, 32));
    }

    void handle(const InputSnapshot& in) {
        if (desc.stage >= WindowStage::Stage3_FullChrome) {
            bar.handle(in);
            if (bar.hit_close) closed = true;
        }
    }
};

class WindowFactory {
public:
    static SoftWindow create(const WindowDesc& desc) {
        SoftWindow w;
        w.desc = desc;
        w.layout();
        if (desc.stage >= WindowStage::Stage2_Rectangles && w.surface.width() > 0)
            w.surface.clear(Color::rgb(20, 24, 32));
        return w;
    }
    static SoftWindow create_stage1(int x, int y, int w, int h) {
        WindowDesc d; d.x=x; d.y=y; d.w=w; d.h=h;
        d.stage = WindowStage::Stage1_PixelsLines;
        d.closable = d.minimizable = d.maximizable = false;
        return create(d);
    }
    static SoftWindow create_stage2(int x, int y, int w, int h) {
        WindowDesc d; d.x=x; d.y=y; d.w=w; d.h=h;
        d.stage = WindowStage::Stage2_Rectangles;
        return create(d);
    }
    static SoftWindow create_stage3(int x, int y, int w, int h, const std::string& title = {}) {
        WindowDesc d; d.x=x; d.y=y; d.w=w; d.h=h; d.title=title;
        d.stage = WindowStage::Stage3_FullChrome;
        return create(d);
    }
};

} // namespace graphic
} // namespace mir
