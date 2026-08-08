#pragma once
// PixelBuffer — direct surface editing
// Software surface first (CPU). SDL2 (or other) can wrap/present it.

#include <cstdint>
#include <cstring>
#include <algorithm>
#include <cmath>

namespace mir {
namespace graphic {

struct Color {
    std::uint8_t r = 0, g = 0, b = 0, a = 255;
    static Color rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return {r, g, b, 255}; }
    static Color rgba(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) { return {r, g, b, a}; }
    static Color black() { return {0, 0, 0, 255}; }
    static Color white() { return {255, 255, 255, 255}; }
};

using Pixel32 = std::uint32_t;

inline Pixel32 pack(Color c) {
    return (Pixel32(c.a) << 24) | (Pixel32(c.r) << 16) | (Pixel32(c.g) << 8) | Pixel32(c.b);
}

class PixelBuffer {
    int width_ = 0, height_ = 0, stride_ = 0;
    std::uint8_t* data_ = nullptr;
    bool owns_ = false;
public:
    PixelBuffer() = default;
    PixelBuffer(int w, int h) { resize(w, h); }
    PixelBuffer(int w, int h, int stride_bytes, void* pixels)
        : width_(w), height_(h), stride_(stride_bytes),
          data_(static_cast<std::uint8_t*>(pixels)), owns_(false) {}
    ~PixelBuffer() { if (owns_) delete[] data_; }
    PixelBuffer(const PixelBuffer&) = delete;
    PixelBuffer& operator=(const PixelBuffer&) = delete;
    PixelBuffer(PixelBuffer&& o) noexcept
        : width_(o.width_), height_(o.height_), stride_(o.stride_), data_(o.data_), owns_(o.owns_) {
        o.data_ = nullptr; o.owns_ = false;
    }
    PixelBuffer& operator=(PixelBuffer&& o) noexcept {
        if (this != &o) {
            if (owns_) delete[] data_;
            width_ = o.width_; height_ = o.height_; stride_ = o.stride_;
            data_ = o.data_; owns_ = o.owns_;
            o.data_ = nullptr; o.owns_ = false;
        }
        return *this;
    }

    void resize(int w, int h) {
        if (owns_) delete[] data_;
        width_ = w; height_ = h; stride_ = w * 4;
        data_ = new std::uint8_t[static_cast<std::size_t>(stride_) * h]();
        owns_ = true;
    }
    void bind(int w, int h, int stride_bytes, void* pixels) {
        if (owns_) delete[] data_;
        width_ = w; height_ = h; stride_ = stride_bytes;
        data_ = static_cast<std::uint8_t*>(pixels); owns_ = false;
    }

    int width() const { return width_; }
    int height() const { return height_; }
    int stride() const { return stride_; }
    void* data() { return data_; }
    bool in_bounds(int x, int y) const {
        return x >= 0 && y >= 0 && x < width_ && y < height_;
    }

    void clear(Color c = Color::black()) {
        if (!data_) return;
        const Pixel32 p = pack(c);
        for (int y = 0; y < height_; ++y) {
            auto* row = reinterpret_cast<Pixel32*>(data_ + y * stride_);
            for (int x = 0; x < width_; ++x) row[x] = p;
        }
    }
    void put(int x, int y, Color c) {
        if (!in_bounds(x, y) || !data_) return;
        reinterpret_cast<Pixel32*>(data_ + y * stride_)[x] = pack(c);
    }
    void fill_rect(int x, int y, int w, int h, Color c) {
        if (!data_) return;
        const int x0 = std::max(0, x), y0 = std::max(0, y);
        const int x1 = std::min(width_, x + w), y1 = std::min(height_, y + h);
        const Pixel32 p = pack(c);
        for (int yy = y0; yy < y1; ++yy) {
            auto* row = reinterpret_cast<Pixel32*>(data_ + yy * stride_);
            for (int xx = x0; xx < x1; ++xx) row[xx] = p;
        }
    }
    void hline(int x0, int x1, int y, Color c) {
        if (!data_ || y < 0 || y >= height_) return;
        if (x0 > x1) std::swap(x0, x1);
        x0 = std::max(0, x0); x1 = std::min(width_ - 1, x1);
        auto* row = reinterpret_cast<Pixel32*>(data_ + y * stride_);
        const Pixel32 p = pack(c);
        for (int x = x0; x <= x1; ++x) row[x] = p;
    }
    void vline(int x, int y0, int y1, Color c) {
        if (!data_ || x < 0 || x >= width_) return;
        if (y0 > y1) std::swap(y0, y1);
        y0 = std::max(0, y0); y1 = std::min(height_ - 1, y1);
        const Pixel32 p = pack(c);
        for (int y = y0; y <= y1; ++y)
            reinterpret_cast<Pixel32*>(data_ + y * stride_)[x] = p;
    }
    void line(int x0, int y0, int x1, int y1, Color c) {
        const int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        const int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy;
        for (;;) {
            put(x0, y0, c);
            if (x0 == x1 && y0 == y1) break;
            const int e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    }
    void blit(const PixelBuffer& src, int dst_x, int dst_y) {
        if (!data_ || !src.data_) return;
        for (int sy = 0; sy < src.height_; ++sy) {
            const int dy = dst_y + sy;
            if (dy < 0 || dy >= height_) continue;
            auto* drow = reinterpret_cast<Pixel32*>(data_ + dy * stride_);
            auto* srow = reinterpret_cast<const Pixel32*>(src.data_ + sy * src.stride_);
            for (int sx = 0; sx < src.width_; ++sx) {
                const int dx = dst_x + sx;
                if (dx < 0 || dx >= width_) continue;
                drow[dx] = srow[sx];
            }
        }
    }
};

} // namespace graphic
} // namespace mir
