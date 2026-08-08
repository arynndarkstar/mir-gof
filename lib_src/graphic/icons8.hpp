#pragma once
// 8x8 B/W icons as uint64_t bitvectors (MSB = top-left, row-major).

#include "pixel_buffer.hpp"
#include <cstdint>

namespace mir {
namespace graphic {

using Icon8 = std::uint64_t;

inline bool icon8_bit(Icon8 bits, int r, int c) {
    if (r < 0 || r > 7 || c < 0 || c > 7) return false;
    return (bits >> (63 - (r * 8 + c))) & 1ull;
}

inline void draw_icon8(PixelBuffer& buf, int x, int y, Icon8 bits,
                       Color fg, Color bg, bool opaque_bg = false) {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c) {
            if (icon8_bit(bits, r, c))
                buf.put(x + c, y + r, fg);
            else if (opaque_bg)
                buf.put(x + c, y + r, bg);
        }
}

constexpr Icon8 ICN_CLOSE =
    0b10000001'01000010'00100100'00011000'00011000'00100100'01000010'10000001ull;
constexpr Icon8 ICN_MINIMIZE =
    0b00000000'00000000'00000000'00000000'00000000'00000000'01111110'01111110ull;
constexpr Icon8 ICN_SQUARE =
    0b11111111'10000001'10000001'10000001'10000001'10000001'10000001'11111111ull;
constexpr Icon8 ICN_MAXIMIZE =
    0b11111111'11111111'10000001'10000001'10000001'10000001'10000001'11111111ull;
constexpr Icon8 ICN_FILLED =
    0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11111111ull;
constexpr Icon8 ICN_CHECK =
    0b00000000'00000001'00000010'00000100'10001000'01010000'00100000'00000000ull;
constexpr Icon8 ICN_MENU =
    0b00000000'01111110'01111110'00000000'01111110'01111110'00000000'01111110ull;

constexpr Icon8 ICN_CHECKBOX =
    0b11111111'10000001'10000001'10000001'10000001'10000001'10000001'11111111ull;
constexpr Icon8 ICN_CHECKBOX_ON =
    0b11111111'10000001'10000011'10000101'10101001'11010001'10000001'11111111ull;

constexpr Icon8 ICN_RADIO =
    0b00111100'01000010'10000001'10000001'10000001'10000001'01000010'00111100ull;
constexpr Icon8 ICN_RADIO_ON =
    0b00111100'01000010'10011001'10111101'10111101'10011001'01000010'00111100ull;

} // namespace graphic
} // namespace mir
