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

#include <gtest/gtest.h>

#include <centurion/video/color.hpp>

// clang-format off

// See https://en.wikipedia.org/wiki/Web_colors
TEST(Color, Constants)
{
  EXPECT_EQ(cen::colors::transparent, SDL_Color(0x00, 0x00, 0x00, 0x00));

  // Pink colors
  EXPECT_EQ(cen::colors::medium_violet_red, SDL_Color(0xC7, 0x15, 0x85, 0xFF));
  EXPECT_EQ(cen::colors::deep_pink,         SDL_Color(0xFF, 0x14, 0x93, 0xFF));
  EXPECT_EQ(cen::colors::pale_violet_red,   SDL_Color(0xDB, 0x70, 0x93, 0xFF));
  EXPECT_EQ(cen::colors::hot_pink,          SDL_Color(0xFF, 0x69, 0xB4, 0xFF));
  EXPECT_EQ(cen::colors::light_pink,        SDL_Color(0xFF, 0xB6, 0xC1, 0xFF));
  EXPECT_EQ(cen::colors::pink,              SDL_Color(0xFF, 0xC0, 0xCB, 0xFF));

  // Red colors
  EXPECT_EQ(cen::colors::dark_red,     SDL_Color(0x8B, 0x00, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::red,          SDL_Color(0xFF, 0x00, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::firebrick,    SDL_Color(0xB2, 0x22, 0x22, 0xFF));
  EXPECT_EQ(cen::colors::crimson,      SDL_Color(0xDC, 0x14, 0x3C, 0xFF));
  EXPECT_EQ(cen::colors::indian_red,   SDL_Color(0xCD, 0x5C, 0x5C, 0xFF));
  EXPECT_EQ(cen::colors::light_coral,  SDL_Color(0xF0, 0x80, 0x80, 0xFF));
  EXPECT_EQ(cen::colors::salmon,       SDL_Color(0xFA, 0x80, 0x72, 0xFF));
  EXPECT_EQ(cen::colors::dark_salmon,  SDL_Color(0xE9, 0x96, 0x7A, 0xFF));
  EXPECT_EQ(cen::colors::light_salmon, SDL_Color(0xFF, 0xA0, 0x7A, 0xFF));

  // Orange colors
  EXPECT_EQ(cen::colors::orange_red,  SDL_Color(0xFF, 0x45, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::tomato,      SDL_Color(0xFF, 0x63, 0x47, 0xFF));
  EXPECT_EQ(cen::colors::dark_orange, SDL_Color(0xFF, 0x8C, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::coral,       SDL_Color(0xFF, 0x7F, 0x50, 0xFF));
  EXPECT_EQ(cen::colors::orange,      SDL_Color(0xFF, 0xA5, 0x00, 0xFF));

  // Yellow colors
  EXPECT_EQ(cen::colors::dark_khaki,              SDL_Color(0xBD, 0xB7, 0x6B, 0xFF));
  EXPECT_EQ(cen::colors::gold,                    SDL_Color(0xFF, 0xD7, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::khaki,                   SDL_Color(0xF0, 0xE6, 0x8C, 0xFF));
  EXPECT_EQ(cen::colors::peach_puff,              SDL_Color(0xFF, 0xDA, 0xB9, 0xFF));
  EXPECT_EQ(cen::colors::yellow,                  SDL_Color(0xFF, 0xFF, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::pale_golden_rod,         SDL_Color(0xEE, 0xE8, 0xAA, 0xFF));
  EXPECT_EQ(cen::colors::moccasin,                SDL_Color(0xFF, 0xE4, 0xB5, 0xFF));
  EXPECT_EQ(cen::colors::papaya_whip,             SDL_Color(0xFF, 0xEF, 0xD5, 0xFF));
  EXPECT_EQ(cen::colors::light_golden_rod_yellow, SDL_Color(0xFA, 0xFA, 0xD2, 0xFF));
  EXPECT_EQ(cen::colors::lemon_chiffon,           SDL_Color(0xFF, 0xFA, 0xCD, 0xFF));
  EXPECT_EQ(cen::colors::light_yellow,            SDL_Color(0xFF, 0xFF, 0xE0, 0xFF));

  // Brown colors
  EXPECT_EQ(cen::colors::maroon,          SDL_Color(0x80, 0x00, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::brown,           SDL_Color(0xA5, 0x2A, 0x2A, 0xFF));
  EXPECT_EQ(cen::colors::saddle_brown,    SDL_Color(0x8B, 0x45, 0x13, 0xFF));
  EXPECT_EQ(cen::colors::sienna,          SDL_Color(0xA0, 0x52, 0x2D, 0xFF));
  EXPECT_EQ(cen::colors::chocolate,       SDL_Color(0xD2, 0x69, 0x1E, 0xFF));
  EXPECT_EQ(cen::colors::dark_golden_rod, SDL_Color(0xB8, 0x86, 0x0B, 0xFF));
  EXPECT_EQ(cen::colors::peru,            SDL_Color(0xCD, 0x85, 0x3F, 0xFF));
  EXPECT_EQ(cen::colors::rosy_brown,      SDL_Color(0xBC, 0x8F, 0x8F, 0xFF));
  EXPECT_EQ(cen::colors::golden_rod,      SDL_Color(0xDA, 0xA5, 0x20, 0xFF));
  EXPECT_EQ(cen::colors::sandy_brown,     SDL_Color(0xF4, 0xA4, 0x60, 0xFF));
  EXPECT_EQ(cen::colors::tan,             SDL_Color(0xD2, 0xB4, 0x8C, 0xFF));
  EXPECT_EQ(cen::colors::burly_wood,      SDL_Color(0xDE, 0xB8, 0x87, 0xFF));
  EXPECT_EQ(cen::colors::wheat,           SDL_Color(0xF5, 0xDE, 0xB3, 0xFF));
  EXPECT_EQ(cen::colors::navajo_white,    SDL_Color(0xFF, 0xDE, 0xAD, 0xFF));
  EXPECT_EQ(cen::colors::bisque,          SDL_Color(0xFF, 0xE4, 0xC4, 0xFF));
  EXPECT_EQ(cen::colors::blanched_almond, SDL_Color(0xFF, 0xEB, 0xCD, 0xFF));
  EXPECT_EQ(cen::colors::cornsilk,        SDL_Color(0xFF, 0xF8, 0xDC, 0xFF));

  // Purple, violet, and magenta colors
  EXPECT_EQ(cen::colors::indigo,            SDL_Color(0x4B, 0x00, 0x82, 0xFF));
  EXPECT_EQ(cen::colors::purple,            SDL_Color(0x80, 0x00, 0x80, 0xFF));
  EXPECT_EQ(cen::colors::dark_magenta,      SDL_Color(0x8B, 0x00, 0x8B, 0xFF));
  EXPECT_EQ(cen::colors::dark_violet,       SDL_Color(0x94, 0x00, 0xD3, 0xFF));
  EXPECT_EQ(cen::colors::dark_slate_blue,   SDL_Color(0x48, 0x3D, 0x8B, 0xFF));
  EXPECT_EQ(cen::colors::blue_violet,       SDL_Color(0x8A, 0x2B, 0xE2, 0xFF));
  EXPECT_EQ(cen::colors::dark_orchid,       SDL_Color(0x99, 0x32, 0xCC, 0xFF));
  EXPECT_EQ(cen::colors::fuchsia,           SDL_Color(0xFF, 0x00, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::magenta,           SDL_Color(0xFF, 0x00, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::slate_blue,        SDL_Color(0x6A, 0x5A, 0xCD, 0xFF));
  EXPECT_EQ(cen::colors::medium_slate_blue, SDL_Color(0x7B, 0x68, 0xEE, 0xFF));
  EXPECT_EQ(cen::colors::medium_orchid,     SDL_Color(0xBA, 0x55, 0xD3, 0xFF));
  EXPECT_EQ(cen::colors::medium_purple,     SDL_Color(0x93, 0x70, 0xDB, 0xFF));
  EXPECT_EQ(cen::colors::orchid,            SDL_Color(0xDA, 0x70, 0xD6, 0xFF));
  EXPECT_EQ(cen::colors::violet,            SDL_Color(0xEE, 0x82, 0xEE, 0xFF));
  EXPECT_EQ(cen::colors::plum,              SDL_Color(0xDD, 0xA0, 0xDD, 0xFF));
  EXPECT_EQ(cen::colors::thistle,           SDL_Color(0xD8, 0xBF, 0xD8, 0xFF));
  EXPECT_EQ(cen::colors::lavender,          SDL_Color(0xE6, 0xE6, 0xFA, 0xFF));
  EXPECT_EQ(cen::colors::rebecca_purple,    SDL_Color(0x66, 0x33, 0x99, 0xFF));

  // Blue colors
  EXPECT_EQ(cen::colors::midnight_blue,    SDL_Color(0x19, 0x19, 0x70, 0xFF));
  EXPECT_EQ(cen::colors::navy,             SDL_Color(0x00, 0x00, 0x80, 0xFF));
  EXPECT_EQ(cen::colors::dark_blue,        SDL_Color(0x00, 0x00, 0x8B, 0xFF));
  EXPECT_EQ(cen::colors::medium_blue,      SDL_Color(0x00, 0x00, 0xCD, 0xFF));
  EXPECT_EQ(cen::colors::blue,             SDL_Color(0x00, 0x00, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::royal_blue,       SDL_Color(0x41, 0x69, 0xE1, 0xFF));
  EXPECT_EQ(cen::colors::steel_blue,       SDL_Color(0x46, 0x82, 0xB4, 0xFF));
  EXPECT_EQ(cen::colors::dodger_blue,      SDL_Color(0x1E, 0x90, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::deep_sky_blue,    SDL_Color(0x00, 0xBF, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::cornflower_blue,  SDL_Color(0x64, 0x95, 0xED, 0xFF));
  EXPECT_EQ(cen::colors::sky_blue,         SDL_Color(0x87, 0xCE, 0xEB, 0xFF));
  EXPECT_EQ(cen::colors::light_sky_blue,   SDL_Color(0x87, 0xCE, 0xFA, 0xFF));
  EXPECT_EQ(cen::colors::light_steel_blue, SDL_Color(0xB0, 0xC4, 0xDE, 0xFF));
  EXPECT_EQ(cen::colors::light_blue,       SDL_Color(0xAD, 0xD8, 0xE6, 0xFF));
  EXPECT_EQ(cen::colors::powder_blue,      SDL_Color(0xB0, 0xE0, 0xE6, 0xFF));

  // Cyan colors
  EXPECT_EQ(cen::colors::teal,             SDL_Color(0x00, 0x80, 0x80, 0xFF));
  EXPECT_EQ(cen::colors::dark_cyan,        SDL_Color(0x00, 0x8B, 0x8B, 0xFF));
  EXPECT_EQ(cen::colors::light_sea_green,  SDL_Color(0x20, 0xB2, 0xAA, 0xFF));
  EXPECT_EQ(cen::colors::cadet_blue,       SDL_Color(0x5F, 0x9E, 0xA0, 0xFF));
  EXPECT_EQ(cen::colors::dark_turquoise,   SDL_Color(0x00, 0xCE, 0xD1, 0xFF));
  EXPECT_EQ(cen::colors::medium_turquoise, SDL_Color(0x48, 0xD1, 0xCC, 0xFF));
  EXPECT_EQ(cen::colors::turquoise,        SDL_Color(0x40, 0xE0, 0xD0, 0xFF));
  EXPECT_EQ(cen::colors::aqua,             SDL_Color(0x00, 0xFF, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::cyan,             SDL_Color(0x00, 0xFF, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::aquamarine,       SDL_Color(0x7F, 0xFF, 0xD4, 0xFF));
  EXPECT_EQ(cen::colors::pale_turquoise,   SDL_Color(0xAF, 0xEE, 0xEE, 0xFF));
  EXPECT_EQ(cen::colors::light_cyan,       SDL_Color(0xE0, 0xFF, 0xFF, 0xFF));

  // Green colors
  EXPECT_EQ(cen::colors::dark_green,          SDL_Color(0x00, 0x64, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::green,               SDL_Color(0x00, 0x80, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::dark_olive_green,    SDL_Color(0x55, 0x6B, 0x2F, 0xFF));
  EXPECT_EQ(cen::colors::forest_green,        SDL_Color(0x22, 0x8B, 0x22, 0xFF));
  EXPECT_EQ(cen::colors::sea_green,           SDL_Color(0x2E, 0x8B, 0x57, 0xFF));
  EXPECT_EQ(cen::colors::olive,               SDL_Color(0x80, 0x80, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::olive_drab,          SDL_Color(0x6B, 0x8E, 0x23, 0xFF));
  EXPECT_EQ(cen::colors::medium_sea_green,    SDL_Color(0x3C, 0xB3, 0x71, 0xFF));
  EXPECT_EQ(cen::colors::lime_green,          SDL_Color(0x32, 0xCD, 0x32, 0xFF));
  EXPECT_EQ(cen::colors::lime,                SDL_Color(0x00, 0xFF, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::spring_green,        SDL_Color(0x00, 0xFF, 0x7F, 0xFF));
  EXPECT_EQ(cen::colors::medium_spring_green, SDL_Color(0x00, 0xFA, 0x9A, 0xFF));
  EXPECT_EQ(cen::colors::dark_sea_green,      SDL_Color(0x8F, 0xBC, 0x8F, 0xFF));
  EXPECT_EQ(cen::colors::medium_aquamarine,   SDL_Color(0x66, 0xCD, 0xAA, 0xFF));
  EXPECT_EQ(cen::colors::yellow_green,        SDL_Color(0x9A, 0xCD, 0x32, 0xFF));
  EXPECT_EQ(cen::colors::lawn_green,          SDL_Color(0x7C, 0xFC, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::chartreuse,          SDL_Color(0x7F, 0xFF, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::light_green,         SDL_Color(0x90, 0xEE, 0x90, 0xFF));
  EXPECT_EQ(cen::colors::green_yellow,        SDL_Color(0xAD, 0xFF, 0x2F, 0xFF));
  EXPECT_EQ(cen::colors::pale_green,          SDL_Color(0x98, 0xFB, 0x98, 0xFF));

  // White colors
  EXPECT_EQ(cen::colors::misty_rose,     SDL_Color(0xFF, 0xE4, 0xE1, 0xFF));
  EXPECT_EQ(cen::colors::antique_white,  SDL_Color(0xFA, 0xEB, 0xD7, 0xFF));
  EXPECT_EQ(cen::colors::linen,          SDL_Color(0xFA, 0xF0, 0xE6, 0xFF));
  EXPECT_EQ(cen::colors::beige,          SDL_Color(0xF5, 0xF5, 0xDC, 0xFF));
  EXPECT_EQ(cen::colors::white_smoke,    SDL_Color(0xF5, 0xF5, 0xF5, 0xFF));
  EXPECT_EQ(cen::colors::lavender_blush, SDL_Color(0xFF, 0xF0, 0xF5, 0xFF));
  EXPECT_EQ(cen::colors::old_lace,       SDL_Color(0xFD, 0xF5, 0xE6, 0xFF));
  EXPECT_EQ(cen::colors::alice_blue,     SDL_Color(0xF0, 0xF8, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::seashell,       SDL_Color(0xFF, 0xF5, 0xEE, 0xFF));
  EXPECT_EQ(cen::colors::ghost_white,    SDL_Color(0xF8, 0xF8, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::honeydew,       SDL_Color(0xF0, 0xFF, 0xF0, 0xFF));
  EXPECT_EQ(cen::colors::floral_white,   SDL_Color(0xFF, 0xFA, 0xF0, 0xFF));
  EXPECT_EQ(cen::colors::azure,          SDL_Color(0xF0, 0xFF, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::mint_cream,     SDL_Color(0xF5, 0xFF, 0xFA, 0xFF));
  EXPECT_EQ(cen::colors::snow,           SDL_Color(0xFF, 0xFA, 0xFA, 0xFF));
  EXPECT_EQ(cen::colors::ivory,          SDL_Color(0xFF, 0xFF, 0xF0, 0xFF));
  EXPECT_EQ(cen::colors::white,          SDL_Color(0xFF, 0xFF, 0xFF, 0xFF));

  // Gray and black colors
  EXPECT_EQ(cen::colors::black,            SDL_Color(0x00, 0x00, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::dark_slate_gray,  SDL_Color(0x2F, 0x4F, 0x4F, 0xFF));
  EXPECT_EQ(cen::colors::dim_gray,         SDL_Color(0x69, 0x69, 0x69, 0xFF));
  EXPECT_EQ(cen::colors::slate_gray,       SDL_Color(0x70, 0x80, 0x90, 0xFF));
  EXPECT_EQ(cen::colors::gray,             SDL_Color(0x80, 0x80, 0x80, 0xFF));
  EXPECT_EQ(cen::colors::light_slate_gray, SDL_Color(0x77, 0x88, 0x99, 0xFF));
  EXPECT_EQ(cen::colors::dark_gray,        SDL_Color(0xA9, 0xA9, 0xA9, 0xFF));
  EXPECT_EQ(cen::colors::silver,           SDL_Color(0xC0, 0xC0, 0xC0, 0xFF));
  EXPECT_EQ(cen::colors::light_gray,       SDL_Color(0xD3, 0xD3, 0xD3, 0xFF));
  EXPECT_EQ(cen::colors::gainsboro,        SDL_Color(0xDC, 0xDC, 0xDC, 0xFF));
}

// clang-format on
