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

#include <centurion/video/color.hpp>
#include <gtest/gtest.h>

// See https://en.wikipedia.org/wiki/Web_colors
TEST(Color, Constants)
{
  auto make_color = [](Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF) {
    return SDL_Color {r, g, b, a};
  };

  // clang-format off
  EXPECT_EQ(cen::colors::transparent, make_color(0x00, 0x00, 0x00, 0x00));

  // Pink colors
  EXPECT_EQ(cen::colors::medium_violet_red, make_color(0xC7, 0x15, 0x85));
  EXPECT_EQ(cen::colors::deep_pink,         make_color(0xFF, 0x14, 0x93));
  EXPECT_EQ(cen::colors::pale_violet_red,   make_color(0xDB, 0x70, 0x93));
  EXPECT_EQ(cen::colors::hot_pink,          make_color(0xFF, 0x69, 0xB4));
  EXPECT_EQ(cen::colors::light_pink,        make_color(0xFF, 0xB6, 0xC1));
  EXPECT_EQ(cen::colors::pink,              make_color(0xFF, 0xC0, 0xCB));

  // Red colors
  EXPECT_EQ(cen::colors::dark_red,     make_color(0x8B, 0x00, 0x00));
  EXPECT_EQ(cen::colors::red,          make_color(0xFF, 0x00, 0x00));
  EXPECT_EQ(cen::colors::firebrick,    make_color(0xB2, 0x22, 0x22));
  EXPECT_EQ(cen::colors::crimson,      make_color(0xDC, 0x14, 0x3C));
  EXPECT_EQ(cen::colors::indian_red,   make_color(0xCD, 0x5C, 0x5C));
  EXPECT_EQ(cen::colors::light_coral,  make_color(0xF0, 0x80, 0x80));
  EXPECT_EQ(cen::colors::salmon,       make_color(0xFA, 0x80, 0x72));
  EXPECT_EQ(cen::colors::dark_salmon,  make_color(0xE9, 0x96, 0x7A));
  EXPECT_EQ(cen::colors::light_salmon, make_color(0xFF, 0xA0, 0x7A));

  // Orange colors
  EXPECT_EQ(cen::colors::orange_red,  make_color(0xFF, 0x45, 0x00));
  EXPECT_EQ(cen::colors::tomato,      make_color(0xFF, 0x63, 0x47));
  EXPECT_EQ(cen::colors::dark_orange, make_color(0xFF, 0x8C, 0x00));
  EXPECT_EQ(cen::colors::coral,       make_color(0xFF, 0x7F, 0x50));
  EXPECT_EQ(cen::colors::orange,      make_color(0xFF, 0xA5, 0x00));

  // Yellow colors
  EXPECT_EQ(cen::colors::dark_khaki,              make_color(0xBD, 0xB7, 0x6B));
  EXPECT_EQ(cen::colors::gold,                    make_color(0xFF, 0xD7, 0x00));
  EXPECT_EQ(cen::colors::khaki,                   make_color(0xF0, 0xE6, 0x8C));
  EXPECT_EQ(cen::colors::peach_puff,              make_color(0xFF, 0xDA, 0xB9));
  EXPECT_EQ(cen::colors::yellow,                  make_color(0xFF, 0xFF, 0x00));
  EXPECT_EQ(cen::colors::pale_golden_rod,         make_color(0xEE, 0xE8, 0xAA));
  EXPECT_EQ(cen::colors::moccasin,                make_color(0xFF, 0xE4, 0xB5));
  EXPECT_EQ(cen::colors::papaya_whip,             make_color(0xFF, 0xEF, 0xD5));
  EXPECT_EQ(cen::colors::light_golden_rod_yellow, make_color(0xFA, 0xFA, 0xD2));
  EXPECT_EQ(cen::colors::lemon_chiffon,           make_color(0xFF, 0xFA, 0xCD));
  EXPECT_EQ(cen::colors::light_yellow,            make_color(0xFF, 0xFF, 0xE0));

  // Brown colors
  EXPECT_EQ(cen::colors::maroon,          make_color(0x80, 0x00, 0x00));
  EXPECT_EQ(cen::colors::brown,           make_color(0xA5, 0x2A, 0x2A));
  EXPECT_EQ(cen::colors::saddle_brown,    make_color(0x8B, 0x45, 0x13));
  EXPECT_EQ(cen::colors::sienna,          make_color(0xA0, 0x52, 0x2D));
  EXPECT_EQ(cen::colors::chocolate,       make_color(0xD2, 0x69, 0x1E));
  EXPECT_EQ(cen::colors::dark_golden_rod, make_color(0xB8, 0x86, 0x0B));
  EXPECT_EQ(cen::colors::peru,            make_color(0xCD, 0x85, 0x3F));
  EXPECT_EQ(cen::colors::rosy_brown,      make_color(0xBC, 0x8F, 0x8F));
  EXPECT_EQ(cen::colors::golden_rod,      make_color(0xDA, 0xA5, 0x20));
  EXPECT_EQ(cen::colors::sandy_brown,     make_color(0xF4, 0xA4, 0x60));
  EXPECT_EQ(cen::colors::tan,             make_color(0xD2, 0xB4, 0x8C));
  EXPECT_EQ(cen::colors::burly_wood,      make_color(0xDE, 0xB8, 0x87));
  EXPECT_EQ(cen::colors::wheat,           make_color(0xF5, 0xDE, 0xB3));
  EXPECT_EQ(cen::colors::navajo_white,    make_color(0xFF, 0xDE, 0xAD));
  EXPECT_EQ(cen::colors::bisque,          make_color(0xFF, 0xE4, 0xC4));
  EXPECT_EQ(cen::colors::blanched_almond, make_color(0xFF, 0xEB, 0xCD));
  EXPECT_EQ(cen::colors::cornsilk,        make_color(0xFF, 0xF8, 0xDC));

  // Purple, violet, and magenta colors
  EXPECT_EQ(cen::colors::indigo,            make_color(0x4B, 0x00, 0x82));
  EXPECT_EQ(cen::colors::purple,            make_color(0x80, 0x00, 0x80));
  EXPECT_EQ(cen::colors::dark_magenta,      make_color(0x8B, 0x00, 0x8B));
  EXPECT_EQ(cen::colors::dark_violet,       make_color(0x94, 0x00, 0xD3));
  EXPECT_EQ(cen::colors::dark_slate_blue,   make_color(0x48, 0x3D, 0x8B));
  EXPECT_EQ(cen::colors::blue_violet,       make_color(0x8A, 0x2B, 0xE2));
  EXPECT_EQ(cen::colors::dark_orchid,       make_color(0x99, 0x32, 0xCC));
  EXPECT_EQ(cen::colors::fuchsia,           make_color(0xFF, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::magenta,           make_color(0xFF, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::slate_blue,        make_color(0x6A, 0x5A, 0xCD));
  EXPECT_EQ(cen::colors::medium_slate_blue, make_color(0x7B, 0x68, 0xEE));
  EXPECT_EQ(cen::colors::medium_orchid,     make_color(0xBA, 0x55, 0xD3));
  EXPECT_EQ(cen::colors::medium_purple,     make_color(0x93, 0x70, 0xDB));
  EXPECT_EQ(cen::colors::orchid,            make_color(0xDA, 0x70, 0xD6));
  EXPECT_EQ(cen::colors::violet,            make_color(0xEE, 0x82, 0xEE));
  EXPECT_EQ(cen::colors::plum,              make_color(0xDD, 0xA0, 0xDD));
  EXPECT_EQ(cen::colors::thistle,           make_color(0xD8, 0xBF, 0xD8));
  EXPECT_EQ(cen::colors::lavender,          make_color(0xE6, 0xE6, 0xFA));
  EXPECT_EQ(cen::colors::rebecca_purple,    make_color(0x66, 0x33, 0x99));

  // Blue colors
  EXPECT_EQ(cen::colors::midnight_blue,    make_color(0x19, 0x19, 0x70));
  EXPECT_EQ(cen::colors::navy,             make_color(0x00, 0x00, 0x80));
  EXPECT_EQ(cen::colors::dark_blue,        make_color(0x00, 0x00, 0x8B));
  EXPECT_EQ(cen::colors::medium_blue,      make_color(0x00, 0x00, 0xCD));
  EXPECT_EQ(cen::colors::blue,             make_color(0x00, 0x00, 0xFF));
  EXPECT_EQ(cen::colors::royal_blue,       make_color(0x41, 0x69, 0xE1));
  EXPECT_EQ(cen::colors::steel_blue,       make_color(0x46, 0x82, 0xB4));
  EXPECT_EQ(cen::colors::dodger_blue,      make_color(0x1E, 0x90, 0xFF));
  EXPECT_EQ(cen::colors::deep_sky_blue,    make_color(0x00, 0xBF, 0xFF));
  EXPECT_EQ(cen::colors::cornflower_blue,  make_color(0x64, 0x95, 0xED));
  EXPECT_EQ(cen::colors::sky_blue,         make_color(0x87, 0xCE, 0xEB));
  EXPECT_EQ(cen::colors::light_sky_blue,   make_color(0x87, 0xCE, 0xFA));
  EXPECT_EQ(cen::colors::light_steel_blue, make_color(0xB0, 0xC4, 0xDE));
  EXPECT_EQ(cen::colors::light_blue,       make_color(0xAD, 0xD8, 0xE6));
  EXPECT_EQ(cen::colors::powder_blue,      make_color(0xB0, 0xE0, 0xE6));

  // Cyan colors
  EXPECT_EQ(cen::colors::teal,             make_color(0x00, 0x80, 0x80));
  EXPECT_EQ(cen::colors::dark_cyan,        make_color(0x00, 0x8B, 0x8B));
  EXPECT_EQ(cen::colors::light_sea_green,  make_color(0x20, 0xB2, 0xAA));
  EXPECT_EQ(cen::colors::cadet_blue,       make_color(0x5F, 0x9E, 0xA0));
  EXPECT_EQ(cen::colors::dark_turquoise,   make_color(0x00, 0xCE, 0xD1));
  EXPECT_EQ(cen::colors::medium_turquoise, make_color(0x48, 0xD1, 0xCC));
  EXPECT_EQ(cen::colors::turquoise,        make_color(0x40, 0xE0, 0xD0));
  EXPECT_EQ(cen::colors::aqua,             make_color(0x00, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::cyan,             make_color(0x00, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::aquamarine,       make_color(0x7F, 0xFF, 0xD4));
  EXPECT_EQ(cen::colors::pale_turquoise,   make_color(0xAF, 0xEE, 0xEE));
  EXPECT_EQ(cen::colors::light_cyan,       make_color(0xE0, 0xFF, 0xFF));

  // Green colors
  EXPECT_EQ(cen::colors::dark_green,          make_color(0x00, 0x64, 0x00));
  EXPECT_EQ(cen::colors::green,               make_color(0x00, 0x80, 0x00));
  EXPECT_EQ(cen::colors::dark_olive_green,    make_color(0x55, 0x6B, 0x2F));
  EXPECT_EQ(cen::colors::forest_green,        make_color(0x22, 0x8B, 0x22));
  EXPECT_EQ(cen::colors::sea_green,           make_color(0x2E, 0x8B, 0x57));
  EXPECT_EQ(cen::colors::olive,               make_color(0x80, 0x80, 0x00));
  EXPECT_EQ(cen::colors::olive_drab,          make_color(0x6B, 0x8E, 0x23));
  EXPECT_EQ(cen::colors::medium_sea_green,    make_color(0x3C, 0xB3, 0x71));
  EXPECT_EQ(cen::colors::lime_green,          make_color(0x32, 0xCD, 0x32));
  EXPECT_EQ(cen::colors::lime,                make_color(0x00, 0xFF, 0x00));
  EXPECT_EQ(cen::colors::spring_green,        make_color(0x00, 0xFF, 0x7F));
  EXPECT_EQ(cen::colors::medium_spring_green, make_color(0x00, 0xFA, 0x9A));
  EXPECT_EQ(cen::colors::dark_sea_green,      make_color(0x8F, 0xBC, 0x8F));
  EXPECT_EQ(cen::colors::medium_aquamarine,   make_color(0x66, 0xCD, 0xAA));
  EXPECT_EQ(cen::colors::yellow_green,        make_color(0x9A, 0xCD, 0x32));
  EXPECT_EQ(cen::colors::lawn_green,          make_color(0x7C, 0xFC, 0x00));
  EXPECT_EQ(cen::colors::chartreuse,          make_color(0x7F, 0xFF, 0x00));
  EXPECT_EQ(cen::colors::light_green,         make_color(0x90, 0xEE, 0x90));
  EXPECT_EQ(cen::colors::green_yellow,        make_color(0xAD, 0xFF, 0x2F));
  EXPECT_EQ(cen::colors::pale_green,          make_color(0x98, 0xFB, 0x98));

  // White colors
  EXPECT_EQ(cen::colors::misty_rose,     make_color(0xFF, 0xE4, 0xE1));
  EXPECT_EQ(cen::colors::antique_white,  make_color(0xFA, 0xEB, 0xD7));
  EXPECT_EQ(cen::colors::linen,          make_color(0xFA, 0xF0, 0xE6));
  EXPECT_EQ(cen::colors::beige,          make_color(0xF5, 0xF5, 0xDC));
  EXPECT_EQ(cen::colors::white_smoke,    make_color(0xF5, 0xF5, 0xF5));
  EXPECT_EQ(cen::colors::lavender_blush, make_color(0xFF, 0xF0, 0xF5));
  EXPECT_EQ(cen::colors::old_lace,       make_color(0xFD, 0xF5, 0xE6));
  EXPECT_EQ(cen::colors::alice_blue,     make_color(0xF0, 0xF8, 0xFF));
  EXPECT_EQ(cen::colors::seashell,       make_color(0xFF, 0xF5, 0xEE));
  EXPECT_EQ(cen::colors::ghost_white,    make_color(0xF8, 0xF8, 0xFF));
  EXPECT_EQ(cen::colors::honeydew,       make_color(0xF0, 0xFF, 0xF0));
  EXPECT_EQ(cen::colors::floral_white,   make_color(0xFF, 0xFA, 0xF0));
  EXPECT_EQ(cen::colors::azure,          make_color(0xF0, 0xFF, 0xFF));
  EXPECT_EQ(cen::colors::mint_cream,     make_color(0xF5, 0xFF, 0xFA));
  EXPECT_EQ(cen::colors::snow,           make_color(0xFF, 0xFA, 0xFA));
  EXPECT_EQ(cen::colors::ivory,          make_color(0xFF, 0xFF, 0xF0));
  EXPECT_EQ(cen::colors::white,          make_color(0xFF, 0xFF, 0xFF));

  // Gray and black colors
  EXPECT_EQ(cen::colors::black,            make_color(0x00, 0x00, 0x00));
  EXPECT_EQ(cen::colors::dark_slate_gray,  make_color(0x2F, 0x4F, 0x4F));
  EXPECT_EQ(cen::colors::dim_gray,         make_color(0x69, 0x69, 0x69));
  EXPECT_EQ(cen::colors::slate_gray,       make_color(0x70, 0x80, 0x90));
  EXPECT_EQ(cen::colors::gray,             make_color(0x80, 0x80, 0x80));
  EXPECT_EQ(cen::colors::light_slate_gray, make_color(0x77, 0x88, 0x99));
  EXPECT_EQ(cen::colors::dark_gray,        make_color(0xA9, 0xA9, 0xA9));
  EXPECT_EQ(cen::colors::silver,           make_color(0xC0, 0xC0, 0xC0));
  EXPECT_EQ(cen::colors::light_gray,       make_color(0xD3, 0xD3, 0xD3));
  EXPECT_EQ(cen::colors::gainsboro,        make_color(0xDC, 0xDC, 0xDC));
}

// clang-format on
