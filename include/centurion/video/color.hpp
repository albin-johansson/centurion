/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_VIDEO_COLOR_HPP_
#define CENTURION_VIDEO_COLOR_HPP_

#include <SDL3/SDL.h>

#include <centurion/common/primitives.hpp>

[[nodiscard]] constexpr auto operator==(const SDL_Color& c1, const SDL_Color& c2) noexcept
    -> bool
{
  return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

[[nodiscard]] constexpr auto operator!=(const SDL_Color& c1, const SDL_Color& c2) noexcept
    -> bool
{
  return !(c1 == c2);
}

namespace cen {

namespace colors {

inline constexpr SDL_Color transparent {0x00, 0x00, 0x00, 0x00};

// Pink colors
inline constexpr SDL_Color medium_violet_red {0xC7, 0x15, 0x85, 0xFF};
inline constexpr SDL_Color deep_pink {0xFF, 0x14, 0x93, 0xFF};
inline constexpr SDL_Color pale_violet_red {0xDB, 0x70, 0x93, 0xFF};
inline constexpr SDL_Color hot_pink {0xFF, 0x69, 0xB4, 0xFF};
inline constexpr SDL_Color light_pink {0xFF, 0xB6, 0xC1, 0xFF};
inline constexpr SDL_Color pink {0xFF, 0xC0, 0xCB, 0xFF};

// Red colors
inline constexpr SDL_Color dark_red {0x8B, 0, 0, 0xFF};
inline constexpr SDL_Color red {0xFF, 0, 0, 0xFF};
inline constexpr SDL_Color firebrick {0xB2, 0x22, 0x22, 0xFF};
inline constexpr SDL_Color crimson {0xDC, 0x14, 0x3C, 0xFF};
inline constexpr SDL_Color indian_red {0xCD, 0x5C, 0x5C, 0xFF};
inline constexpr SDL_Color light_coral {0xF0, 0x80, 0x80, 0xFF};
inline constexpr SDL_Color salmon {0xFA, 0x80, 0x72, 0xFF};
inline constexpr SDL_Color dark_salmon {0xE9, 0x96, 0x7A, 0xFF};
inline constexpr SDL_Color light_salmon {0xFF, 0xA0, 0x7A, 0xFF};

// Orange colors
inline constexpr SDL_Color orange_red {0xFF, 0x45, 0, 0xFF};
inline constexpr SDL_Color tomato {0xFF, 0x63, 0x47, 0xFF};
inline constexpr SDL_Color dark_orange {0xFF, 0x8C, 0, 0xFF};
inline constexpr SDL_Color coral {0xFF, 0x7F, 0x50, 0xFF};
inline constexpr SDL_Color orange {0xFF, 0xA5, 0, 0xFF};

// Yellow colors
inline constexpr SDL_Color dark_khaki {0xBD, 0xB7, 0x6B, 0xFF};
inline constexpr SDL_Color gold {0xFF, 0xD7, 0, 0xFF};
inline constexpr SDL_Color khaki {0xF0, 0xE6, 0x8C, 0xFF};
inline constexpr SDL_Color peach_puff {0xFF, 0xDA, 0xB9, 0xFF};
inline constexpr SDL_Color yellow {0xFF, 0xFF, 0, 0xFF};
inline constexpr SDL_Color pale_golden_rod {0xEE, 0xE8, 0xAA, 0xFF};
inline constexpr SDL_Color moccasin {0xFF, 0xE4, 0xB5, 0xFF};
inline constexpr SDL_Color papaya_whip {0xFF, 0xEF, 0xD5, 0xFF};
inline constexpr SDL_Color light_golden_rod_yellow {0xFA, 0xFA, 0xD2, 0xFF};
inline constexpr SDL_Color lemon_chiffon {0xFF, 0xFA, 0xCD, 0xFF};
inline constexpr SDL_Color light_yellow {0xFF, 0xFF, 0xE0, 0xFF};

// Brown colors
inline constexpr SDL_Color maroon {0x80, 0, 0, 0xFF};
inline constexpr SDL_Color brown {0xA5, 0x2A, 0x2A, 0xFF};
inline constexpr SDL_Color saddle_brown {0x8B, 0x45, 0x13, 0xFF};
inline constexpr SDL_Color sienna {0xA0, 0x52, 0x2D, 0xFF};
inline constexpr SDL_Color chocolate {0xD2, 0x69, 0x1E, 0xFF};
inline constexpr SDL_Color dark_golden_rod {0xB8, 0x86, 0x0B, 0xFF};
inline constexpr SDL_Color peru {0xCD, 0x85, 0x3F, 0xFF};
inline constexpr SDL_Color rosy_brown {0xBC, 0x8F, 0x8F, 0xFF};
inline constexpr SDL_Color golden_rod {0xDA, 0xA5, 0x20, 0xFF};
inline constexpr SDL_Color sandy_brown {0xF4, 0xA4, 0x60, 0xFF};
inline constexpr SDL_Color tan {0xD2, 0xB4, 0x8C, 0xFF};
inline constexpr SDL_Color burly_wood {0xDE, 0xB8, 0x87, 0xFF};
inline constexpr SDL_Color wheat {0xF5, 0xDE, 0xB3, 0xFF};
inline constexpr SDL_Color navajo_white {0xFF, 0xDE, 0xAD, 0xFF};
inline constexpr SDL_Color bisque {0xFF, 0xE4, 0xC4, 0xFF};
inline constexpr SDL_Color blanched_almond {0xFF, 0xEB, 0xCD, 0xFF};
inline constexpr SDL_Color cornsilk {0xFF, 0xF8, 0xDC, 0xFF};

// Purple, violet, and magenta colors
inline constexpr SDL_Color indigo {0x4B, 0, 0x82, 0xFF};
inline constexpr SDL_Color purple {0x80, 0, 0x80, 0xFF};
inline constexpr SDL_Color dark_magenta {0x8B, 0, 0x8B, 0xFF};
inline constexpr SDL_Color dark_violet {0x94, 0, 0xD3, 0xFF};
inline constexpr SDL_Color dark_slate_blue {0x48, 0x3D, 0x8B, 0xFF};
inline constexpr SDL_Color blue_violet {0x8A, 0x2B, 0xE2, 0xFF};
inline constexpr SDL_Color dark_orchid {0x99, 0x32, 0xCC, 0xFF};
inline constexpr SDL_Color fuchsia {0xFF, 0, 0xFF, 0xFF};
inline constexpr SDL_Color magenta {0xFF, 0, 0xFF, 0xFF};
inline constexpr SDL_Color slate_blue {0x6A, 0x5A, 0xCD, 0xFF};
inline constexpr SDL_Color medium_slate_blue {0x7B, 0x68, 0xEE, 0xFF};
inline constexpr SDL_Color medium_orchid {0xBA, 0x55, 0xD3, 0xFF};
inline constexpr SDL_Color medium_purple {0x93, 0x70, 0xDB, 0xFF};
inline constexpr SDL_Color orchid {0xDA, 0x70, 0xD6, 0xFF};
inline constexpr SDL_Color violet {0xEE, 0x82, 0xEE, 0xFF};
inline constexpr SDL_Color plum {0xDD, 0xA0, 0xDD, 0xFF};
inline constexpr SDL_Color thistle {0xD8, 0xBF, 0xD8, 0xFF};
inline constexpr SDL_Color lavender {0xE6, 0xE6, 0xFA, 0xFF};
inline constexpr SDL_Color rebecca_purple {0x66, 0x33, 0x99, 0xFF};

// Blue colors
inline constexpr SDL_Color midnight_blue {0x19, 0x19, 0x70, 0xFF};
inline constexpr SDL_Color navy {0, 0, 0x80, 0xFF};
inline constexpr SDL_Color dark_blue {0, 0, 0x8B, 0xFF};
inline constexpr SDL_Color medium_blue {0, 0, 0xCD, 0xFF};
inline constexpr SDL_Color blue {0, 0, 0xFF, 0xFF};
inline constexpr SDL_Color royal_blue {0x41, 0x69, 0xE1, 0xFF};
inline constexpr SDL_Color steel_blue {0x46, 0x82, 0xB4, 0xFF};
inline constexpr SDL_Color dodger_blue {0x1E, 0x90, 0xFF, 0xFF};
inline constexpr SDL_Color deep_sky_blue {0, 0xBF, 0xFF, 0xFF};
inline constexpr SDL_Color cornflower_blue {0x64, 0x95, 0xED, 0xFF};
inline constexpr SDL_Color sky_blue {0x87, 0xCE, 0xEB, 0xFF};
inline constexpr SDL_Color light_sky_blue {0x87, 0xCE, 0xFA, 0xFF};
inline constexpr SDL_Color light_steel_blue {0xB0, 0xC4, 0xDE, 0xFF};
inline constexpr SDL_Color light_blue {0xAD, 0xD8, 0xE6, 0xFF};
inline constexpr SDL_Color powder_blue {0xB0, 0xE0, 0xE6, 0xFF};

// Cyan colors
inline constexpr SDL_Color teal {0, 0x80, 0x80, 0xFF};
inline constexpr SDL_Color dark_cyan {0, 0x8B, 0x8B, 0xFF};
inline constexpr SDL_Color light_sea_green {0x20, 0xB2, 0xAA, 0xFF};
inline constexpr SDL_Color cadet_blue {0x5F, 0x9E, 0xA0, 0xFF};
inline constexpr SDL_Color dark_turquoise {0, 0xCE, 0xD1, 0xFF};
inline constexpr SDL_Color medium_turquoise {0x48, 0xD1, 0xCC, 0xFF};
inline constexpr SDL_Color turquoise {0x40, 0xE0, 0xD0, 0xFF};
inline constexpr SDL_Color aqua {0, 0xFF, 0xFF, 0xFF};
inline constexpr SDL_Color cyan {0, 0xFF, 0xFF, 0xFF};
inline constexpr SDL_Color aquamarine {0x7F, 0xFF, 0xD4, 0xFF};
inline constexpr SDL_Color pale_turquoise {0xAF, 0xEE, 0xEE, 0xFF};
inline constexpr SDL_Color light_cyan {0xE0, 0xFF, 0xFF, 0xFF};

// Green colors
inline constexpr SDL_Color dark_green {0, 0x64, 0, 0xFF};
inline constexpr SDL_Color green {0, 0x80, 0, 0xFF};
inline constexpr SDL_Color dark_olive_green {0x55, 0x6B, 0x2F, 0xFF};
inline constexpr SDL_Color forest_green {0x22, 0x8B, 0x22, 0xFF};
inline constexpr SDL_Color sea_green {0x2E, 0x8B, 0x57, 0xFF};
inline constexpr SDL_Color olive {0x80, 0x80, 0, 0xFF};
inline constexpr SDL_Color olive_drab {0x6B, 0x8E, 0x23, 0xFF};
inline constexpr SDL_Color medium_sea_green {0x3C, 0xB3, 0x71, 0xFF};
inline constexpr SDL_Color lime_green {0x32, 0xCD, 0x32, 0xFF};
inline constexpr SDL_Color lime {0, 0xFF, 0, 0xFF};
inline constexpr SDL_Color spring_green {0, 0xFF, 0x7F, 0xFF};
inline constexpr SDL_Color medium_spring_green {0, 0xFA, 0x9A, 0xFF};
inline constexpr SDL_Color dark_sea_green {0x8F, 0xBC, 0x8F, 0xFF};
inline constexpr SDL_Color medium_aquamarine {0x66, 0xCD, 0xAA, 0xFF};
inline constexpr SDL_Color yellow_green {0x9A, 0xCD, 0x32, 0xFF};
inline constexpr SDL_Color lawn_green {0x7C, 0xFC, 0, 0xFF};
inline constexpr SDL_Color chartreuse {0x7F, 0xFF, 0, 0xFF};
inline constexpr SDL_Color light_green {0x90, 0xEE, 0x90, 0xFF};
inline constexpr SDL_Color green_yellow {0xAD, 0xFF, 0x2F, 0xFF};
inline constexpr SDL_Color pale_green {0x98, 0xFB, 0x98, 0xFF};

// White colors
inline constexpr SDL_Color misty_rose {0xFF, 0xE4, 0xE1, 0xFF};
inline constexpr SDL_Color antique_white {0xFA, 0xEB, 0xD7, 0xFF};
inline constexpr SDL_Color linen {0xFA, 0xF0, 0xE6, 0xFF};
inline constexpr SDL_Color beige {0xF5, 0xF5, 0xDC, 0xFF};
inline constexpr SDL_Color white_smoke {0xF5, 0xF5, 0xF5, 0xFF};
inline constexpr SDL_Color lavender_blush {0xFF, 0xF0, 0xF5, 0xFF};
inline constexpr SDL_Color old_lace {0xFD, 0xF5, 0xE6, 0xFF};
inline constexpr SDL_Color alice_blue {0xF0, 0xF8, 0xFF, 0xFF};
inline constexpr SDL_Color seashell {0xFF, 0xF5, 0xEE, 0xFF};
inline constexpr SDL_Color ghost_white {0xF8, 0xF8, 0xFF, 0xFF};
inline constexpr SDL_Color honeydew {0xF0, 0xFF, 0xF0, 0xFF};
inline constexpr SDL_Color floral_white {0xFF, 0xFA, 0xF0, 0xFF};
inline constexpr SDL_Color azure {0xF0, 0xFF, 0xFF, 0xFF};
inline constexpr SDL_Color mint_cream {0xF5, 0xFF, 0xFA, 0xFF};
inline constexpr SDL_Color snow {0xFF, 0xFA, 0xFA, 0xFF};
inline constexpr SDL_Color ivory {0xFF, 0xFF, 0xF0, 0xFF};
inline constexpr SDL_Color white {0xFF, 0xFF, 0xFF, 0xFF};

// Gray and black colors
inline constexpr SDL_Color black {0x00, 0x00, 0x00, 0xFF};
inline constexpr SDL_Color dark_slate_gray {0x2F, 0x4F, 0x4F, 0xFF};
inline constexpr SDL_Color dim_gray {0x69, 0x69, 0x69, 0xFF};
inline constexpr SDL_Color slate_gray {0x70, 0x80, 0x90, 0xFF};
inline constexpr SDL_Color gray {0x80, 0x80, 0x80, 0xFF};
inline constexpr SDL_Color light_slate_gray {0x77, 0x88, 0x99, 0xFF};
inline constexpr SDL_Color dark_gray {0xA9, 0xA9, 0xA9, 0xFF};
inline constexpr SDL_Color silver {0xC0, 0xC0, 0xC0, 0xFF};
inline constexpr SDL_Color light_gray {0xD3, 0xD3, 0xD3, 0xFF};
inline constexpr SDL_Color gainsboro {0xDC, 0xDC, 0xDC, 0xFF};

}  // namespace colors
}  // namespace cen

#endif  // CENTURION_VIDEO_COLOR_HPP_
