#pragma once
// Minimal software widgets for graphic test-bed (PixelBuffer only).

#include "pixel_buffer.hpp"
#include "icons8.hpp"
#include "input.hpp"
#include <string>

namespace mir {
namespace graphic {

struct Rect {
    int x = 0, y = 0, w = 0, h = 0;
    bool contains(int px, int py) const {
        return px >= x && py >= y && px < x + w && py < y + h;
    }
};

struct WidgetStyle {
    Color face       = Color::rgb(48, 56, 72);
    Color face_hot   = Color::rgb(64, 80, 112);
    Color face_down  = Color::rgb(32, 40, 56);
    Color edge_light = Color::rgb(96, 112, 140);
    Color edge_dark  = Color::rgb(16, 20, 28);
    Color text       = Color::rgb(220, 220, 230);
    Color accent     = Color::rgb(80, 140, 220);
};

inline void draw_panel(PixelBuffer& buf, Rect r, const WidgetStyle& s, bool inset = false) {
    const Color tl = inset ? s.edge_dark : s.edge_light;
    const Color br = inset ? s.edge_light : s.edge_dark;
    buf.fill_rect(r.x, r.y, r.w, r.h, s.face);
    buf.hline(r.x, r.x + r.w - 1, r.y, tl);
    buf.vline(r.x, r.y, r.y + r.h - 1, tl);
    buf.hline(r.x, r.x + r.w - 1, r.y + r.h - 1, br);
    buf.vline(r.x + r.w - 1, r.y, r.y + r.h - 1, br);
}

struct TitleBar {
    Rect rect;
    bool btn_min = true, btn_max = true, btn_close = true;
    bool hit_min = false, hit_max = false, hit_close = false;

    void layout(int x, int y, int w, int h = 20) { rect = {x, y, w, h}; }

    Rect icon_slot(int index_from_right) const {
        const int slot = 12;
        const int ix = rect.x + rect.w - 4 - slot * (index_from_right + 1);
        const int iy = rect.y + (rect.h - 8) / 2;
        return {ix, iy, 8, 8};
    }

    void draw(PixelBuffer& buf, const WidgetStyle& s) const {
        buf.fill_rect(rect.x, rect.y, rect.w, rect.h, s.accent);
        buf.hline(rect.x, rect.x + rect.w - 1, rect.y + rect.h - 1, s.edge_dark);
        buf.fill_rect(rect.x + 6, rect.y + 6, 40, 6, s.text);
        int idx = 0;
        if (btn_close) { auto r = icon_slot(idx++); draw_icon8(buf, r.x, r.y, ICN_CLOSE, s.text, s.accent, false); }
        if (btn_max)   { auto r = icon_slot(idx++); draw_icon8(buf, r.x, r.y, ICN_MAXIMIZE, s.text, s.accent, false); }
        if (btn_min)   { auto r = icon_slot(idx++); draw_icon8(buf, r.x, r.y, ICN_MINIMIZE, s.text, s.accent, false); }
    }

    void handle(const InputSnapshot& in) {
        hit_min = hit_max = hit_close = false;
        if (!in.mouse_l) return;
        int idx = 0;
        if (btn_close && icon_slot(idx++).contains(in.mouse_x, in.mouse_y)) hit_close = true;
        if (btn_max   && icon_slot(idx++).contains(in.mouse_x, in.mouse_y)) hit_max = true;
        if (btn_min   && icon_slot(idx++).contains(in.mouse_x, in.mouse_y)) hit_min = true;
    }
};

struct Button {
    Rect rect;
    Icon8 icon = ICN_FILLED;
    bool has_icon = false;
    bool hot = false, down = false, clicked = false;

    void draw(PixelBuffer& buf, const WidgetStyle& s) const {
        WidgetStyle local = s;
        if (down) local.face = s.face_down;
        else if (hot) local.face = s.face_hot;
        draw_panel(buf, rect, local, down);
        if (has_icon) {
            const int ix = rect.x + (rect.w - 8) / 2;
            const int iy = rect.y + (rect.h - 8) / 2;
            draw_icon8(buf, ix, iy, icon, s.text, local.face, false);
        }
    }

    void handle(const InputSnapshot& in) {
        hot = rect.contains(in.mouse_x, in.mouse_y);
        clicked = false;
        if (hot && in.mouse_l) down = true;
        else { if (down && hot) clicked = true; down = false; }
    }
};

struct TestBedFrame {
    TitleBar bar;
    Rect client;
    WidgetStyle style;
    Button btn_line, btn_circle, btn_sprite, btn_clear;
    int demo_mode = 0;

    void layout(int w, int h) {
        bar.layout(0, 0, w, 22);
        client = {0, 22, w, h - 22};
        const int bw = 56, bh = 24, gap = 6, y = client.y + 8;
        int x = client.x + 8;
        auto place = [&](Button& b) { b.rect = {x, y, bw, bh}; x += bw + gap; };
        btn_sprite.has_icon = true; btn_sprite.icon = ICN_SQUARE;
        btn_clear.has_icon = true; btn_clear.icon = ICN_CLOSE;
        place(btn_line); place(btn_circle); place(btn_sprite); place(btn_clear);
    }

    void handle(const InputSnapshot& in) {
        bar.handle(in);
        btn_line.handle(in); btn_circle.handle(in);
        btn_sprite.handle(in); btn_clear.handle(in);
        if (btn_line.clicked) demo_mode = 0;
        if (btn_circle.clicked) demo_mode = 1;
        if (btn_sprite.clicked) demo_mode = 2;
        if (btn_clear.clicked) demo_mode = 3;
    }

    void draw_chrome(PixelBuffer& buf) const {
        buf.fill_rect(0, 0, buf.width(), buf.height(), Color::rgb(24, 28, 36));
        bar.draw(buf, style);
        draw_panel(buf, client, style, true);
        btn_line.draw(buf, style); btn_circle.draw(buf, style);
        btn_sprite.draw(buf, style); btn_clear.draw(buf, style);
        const int mark_y = btn_line.rect.y + btn_line.rect.h + 2;
        auto mark = [&](const Button& b, bool on) {
            if (on) buf.fill_rect(b.rect.x, mark_y, b.rect.w, 3, style.accent);
        };
        mark(btn_line, demo_mode == 0);
        mark(btn_circle, demo_mode == 1);
        mark(btn_sprite, demo_mode == 2);
        mark(btn_clear, demo_mode == 3);
    }
};

} // namespace graphic
} // namespace mir
