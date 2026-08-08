#pragma once
// SurfaceFacade — Facade over PixelBuffer (+ bind for SDL)

#include "pixel_buffer.hpp"

namespace mir {
namespace graphic {

class SurfaceFacade {
    PixelBuffer buf_;
public:
    SurfaceFacade() = default;
    explicit SurfaceFacade(int w, int h) : buf_(w, h) {}

    void resize(int w, int h) { buf_.resize(w, h); }
    void bind(int w, int h, int stride, void* pixels) {
        buf_.bind(w, h, stride, pixels);
    }

    PixelBuffer&       buffer()       { return buf_; }
    const PixelBuffer& buffer() const { return buf_; }
    int width()  const { return buf_.width(); }
    int height() const { return buf_.height(); }

    void clear(Color c = Color::black()) { buf_.clear(c); }
    void put(int x, int y, Color c) { buf_.put(x, y, c); }
    void line(int x0, int y0, int x1, int y1, Color c) { buf_.line(x0, y0, x1, y1, c); }
    void fill_rect(int x, int y, int w, int h, Color c) { buf_.fill_rect(x, y, w, h, c); }
    void blit_colorkey(const PixelBuffer& src, int dx, int dy, Color key) {
        buf_.blit_colorkey(src, dx, dy, key);
    }
};

} // namespace graphic
} // namespace mir
