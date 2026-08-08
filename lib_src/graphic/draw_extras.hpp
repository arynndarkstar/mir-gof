#pragma once
// Extra software-renderer ops (Game Programming Gems / LaMothe-style)
// Free functions over PixelBuffer — surface tools, graphic plugin not required.

#include "pixel_buffer.hpp"
#include <cmath>
#include <utility>

namespace mir {
namespace graphic {

inline void circle(PixelBuffer& buf, int cx, int cy, int r, Color c) {
    if (r < 0) return;
    int x = r, y = 0, err = 0;
    while (x >= y) {
        buf.put(cx + x, cy + y, c); buf.put(cx + y, cy + x, c);
        buf.put(cx - y, cy + x, c); buf.put(cx - x, cy + y, c);
        buf.put(cx - x, cy - y, c); buf.put(cx - y, cy - x, c);
        buf.put(cx + y, cy - x, c); buf.put(cx + x, cy - y, c);
        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) { x -= 1; err += 1 - 2 * x; }
    }
}

inline void circle_fill(PixelBuffer& buf, int cx, int cy, int r, Color c) {
    if (r < 0) return;
    for (int dy = -r; dy <= r; ++dy) {
        const int dx = static_cast<int>(std::sqrt(static_cast<double>(r * r - dy * dy)));
        buf.hline(cx - dx, cx + dx, cy + dy, c);
    }
}

inline void sprite_drop(PixelBuffer& dst, const PixelBuffer& spr,
                        int x, int y, Color key) {
    dst.blit_colorkey(spr, x, y, key);
}

inline void sprite_drop_opaque(PixelBuffer& dst, const PixelBuffer& spr, int x, int y) {
    dst.blit(spr, x, y);
}

inline PixelBuffer rotate90_cw(const PixelBuffer& src) {
    PixelBuffer out(src.height(), src.width());
    const auto* sbase = static_cast<const std::uint8_t*>(src.data());
    auto* dbase = static_cast<std::uint8_t*>(out.data());
    for (int y = 0; y < src.height(); ++y) {
        auto* srow = reinterpret_cast<const Pixel32*>(sbase + y * src.stride());
        for (int x = 0; x < src.width(); ++x) {
            const int dx = src.height() - 1 - y;
            const int dy = x;
            reinterpret_cast<Pixel32*>(dbase + dy * out.stride())[dx] = srow[x];
        }
    }
    return out;
}

inline PixelBuffer rotate180(const PixelBuffer& src) {
    PixelBuffer out(src.width(), src.height());
    const auto* sbase = static_cast<const std::uint8_t*>(src.data());
    auto* dbase = static_cast<std::uint8_t*>(out.data());
    for (int y = 0; y < src.height(); ++y) {
        auto* srow = reinterpret_cast<const Pixel32*>(sbase + y * src.stride());
        for (int x = 0; x < src.width(); ++x) {
            const int dx = src.width() - 1 - x;
            const int dy = src.height() - 1 - y;
            reinterpret_cast<Pixel32*>(dbase + dy * out.stride())[dx] = srow[x];
        }
    }
    return out;
}

// Slow arbitrary rotate (degrees), nearest-neighbor — small sprites only
inline PixelBuffer rotate(const PixelBuffer& src, float degrees) {
    const float rad = degrees * 0.01745329251f;
    const float cs = std::cos(rad), sn = std::sin(rad);
    const int sw = src.width(), sh = src.height();
    const float cx = (sw - 1) * 0.5f, cy = (sh - 1) * 0.5f;
    auto map = [&](float x, float y) {
        float dx = x - cx, dy = y - cy;
        return std::pair<float,float>{cx + dx * cs - dy * sn, cy + dx * sn + dy * cs};
    };
    float minx = 1e9f, miny = 1e9f, maxx = -1e9f, maxy = -1e9f;
    for (int y = 0; y < sh; y += (sh > 1 ? sh - 1 : 1))
        for (int x = 0; x < sw; x += (sw > 1 ? sw - 1 : 1)) {
            auto [nx, ny] = map(static_cast<float>(x), static_cast<float>(y));
            minx = std::min(minx, nx); maxx = std::max(maxx, nx);
            miny = std::min(miny, ny); maxy = std::max(maxy, ny);
        }
    const int ow = std::max(1, static_cast<int>(maxx - minx) + 1);
    const int oh = std::max(1, static_cast<int>(maxy - miny) + 1);
    PixelBuffer out(ow, oh);
    out.clear(Color::rgba(0, 0, 0, 0));
    const float inv_cs = cs, inv_sn = -sn;
    const auto* sbase = static_cast<const std::uint8_t*>(src.data());
    auto* dbase = static_cast<std::uint8_t*>(out.data());
    for (int dy = 0; dy < oh; ++dy) {
        for (int dx = 0; dx < ow; ++dx) {
            float wx = dx + minx - cx, wy = dy + miny - cy;
            float sx = cx + wx * inv_cs - wy * inv_sn;
            float sy = cy + wx * inv_sn + wy * inv_cs;
            int ix = static_cast<int>(sx + 0.5f);
            int iy = static_cast<int>(sy + 0.5f);
            if (ix >= 0 && iy >= 0 && ix < sw && iy < sh) {
                auto* srow = reinterpret_cast<const Pixel32*>(sbase + iy * src.stride());
                reinterpret_cast<Pixel32*>(dbase + dy * out.stride())[dx] = srow[ix];
            }
        }
    }
    return out;
}

} // namespace graphic
} // namespace mir
