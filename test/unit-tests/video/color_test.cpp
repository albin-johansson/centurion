/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#include "centurion/color.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // is_nothrow_X...
#include <utility>      // move

#include "serialization_utils.hpp"

static_assert(std::is_final_v<cen::color>);

static_assert(std::is_default_constructible_v<cen::color>);

static_assert(std::is_nothrow_copy_constructible_v<cen::color>);
static_assert(std::is_nothrow_copy_assignable_v<cen::color>);

static_assert(std::is_nothrow_move_constructible_v<cen::color>);
static_assert(std::is_nothrow_move_assignable_v<cen::color>);

TEST(Color, DefaultConstruction)
{
  const cen::color color;
  ASSERT_EQ(0, color.red());
  ASSERT_EQ(0, color.green());
  ASSERT_EQ(0, color.blue());
  ASSERT_EQ(0xFF, color.alpha());

  ASSERT_EQ(0, color.norm_red());
  ASSERT_EQ(0, color.norm_green());
  ASSERT_EQ(0, color.norm_blue());
  ASSERT_EQ(1, color.norm_alpha());
}

TEST(Color, ValueConstruction)
{
  constexpr auto red = 0xA5;
  constexpr auto green = 0xB3;
  constexpr auto blue = 0x29;
  constexpr auto alpha = 0xCC;

  constexpr cen::color color{red, green, blue, alpha};

  ASSERT_EQ(color.red(), red);
  ASSERT_EQ(color.green(), green);
  ASSERT_EQ(color.blue(), blue);
  ASSERT_EQ(color.alpha(), alpha);
}

TEST(Color, ValueConstructionDefaultedAlpha)
{
  constexpr auto red = 0x2C;
  constexpr auto green = 0xE2;
  constexpr auto blue = 0x08;

  constexpr cen::color color{red, green, blue};

  ASSERT_EQ(red, color.red());
  ASSERT_EQ(green, color.green());
  ASSERT_EQ(blue, color.blue());
  ASSERT_EQ(color.alpha(), 0xFF);
}

TEST(Color, FromSDLColor)
{
  constexpr SDL_Color sdlColor{0x3F, 0x9A, 0xCC, 0x17};
  constexpr cen::color color{sdlColor};

  ASSERT_EQ(color.red(), sdlColor.r);
  ASSERT_EQ(color.green(), sdlColor.g);
  ASSERT_EQ(color.blue(), sdlColor.b);
  ASSERT_EQ(color.alpha(), sdlColor.a);
}

TEST(Color, FromSDLMessageBoxColor)
{
  constexpr SDL_MessageBoxColor msgColor{0xDA, 0x5E, 0x81};
  constexpr cen::color color{msgColor};

  ASSERT_EQ(color.red(), msgColor.r);
  ASSERT_EQ(color.green(), msgColor.g);
  ASSERT_EQ(color.blue(), msgColor.b);

  // SDL_MessageBoxColor has no alpha component
  ASSERT_EQ(color.alpha(), 0xFF);
}

TEST(Color, FromHSV)
{
  ASSERT_EQ(cen::colors::black, cen::color::from_hsv(0, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::color::from_hsv(359, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::color::from_hsv(0, 100, 0));
  ASSERT_EQ(cen::colors::white, cen::color::from_hsv(0, 0, 100));

  ASSERT_EQ(cen::colors::red, cen::color::from_hsv(0, 100, 100));
  ASSERT_EQ(cen::colors::lime, cen::color::from_hsv(120, 100, 100));
  ASSERT_EQ(cen::colors::blue, cen::color::from_hsv(240, 100, 100));

  // Random colors
  ASSERT_EQ(cen::colors::dark_orchid, cen::color::from_hsv(280, 75.5f, 80));
  ASSERT_EQ(cen::colors::turquoise, cen::color::from_hsv(174, 71.4f, 87.8f));
  ASSERT_EQ(cen::colors::crimson, cen::color::from_hsv(348, 90.9f, 86.3f));
  ASSERT_EQ(cen::colors::light_pink, cen::color::from_hsv(351, 28.6f, 100));
  ASSERT_EQ(cen::colors::thistle, cen::color::from_hsv(300, 11.6f, 84.7f));

  {  // Maxed out
    const auto color = cen::color::from_hsv(359, 100, 100);
    ASSERT_EQ(255, color.red());
    ASSERT_EQ(0, color.green());
    ASSERT_EQ(4, color.blue());
    ASSERT_EQ(255, color.alpha());
  }
}

TEST(Color, FromHSL)
{
  ASSERT_EQ(cen::colors::black, cen::color::from_hsl(0, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::color::from_hsl(359, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::color::from_hsl(0, 100, 0));
  ASSERT_EQ(cen::colors::white, cen::color::from_hsl(0, 0, 100));

  ASSERT_EQ(cen::colors::red, cen::color::from_hsl(0, 100, 50));
  ASSERT_EQ(cen::colors::lime, cen::color::from_hsl(120, 100, 50));
  ASSERT_EQ(cen::colors::blue, cen::color::from_hsl(240, 100, 50));

  // Random colors
  ASSERT_EQ(cen::colors::dark_orchid, cen::color::from_hsl(280, 60.6f, 49.8f));
  ASSERT_EQ(cen::colors::turquoise, cen::color::from_hsl(174, 72.1f, 56.5f));
  ASSERT_EQ(cen::colors::crimson, cen::color::from_hsl(348, 83.3f, 47.1f));
  ASSERT_EQ(cen::colors::light_pink, cen::color::from_hsl(351, 100, 85.7f));
  ASSERT_EQ(cen::colors::thistle, cen::color::from_hsl(300, 24.3f, 79.8f));

  // Maxed out
  ASSERT_EQ(cen::colors::white, cen::color::from_hsl(359, 100, 100));
}

TEST(Color, FromRGB)
{
  ASSERT_FALSE(cen::color::from_rgb("112233"));

  ASSERT_FALSE(cen::color::from_rgb("#1122333"));
  ASSERT_FALSE(cen::color::from_rgb("#11223"));

  ASSERT_FALSE(cen::color::from_rgb("#XY0000"));

  const auto color = cen::color::from_rgb("#2AEB9C");
  ASSERT_TRUE(color);
  ASSERT_EQ(0x2A, color->red());
  ASSERT_EQ(0xEB, color->green());
  ASSERT_EQ(0x9C, color->blue());
  ASSERT_EQ(0xFF, color->alpha());

  ASSERT_EQ("#108D0E", cen::color::from_rgb("#108D0E").value().as_rgb());
}

TEST(Color, FromRGBA)
{
  ASSERT_FALSE(cen::color::from_rgba("11223344"));

  ASSERT_FALSE(cen::color::from_rgba("#112233444"));
  ASSERT_FALSE(cen::color::from_rgba("#112233"));

  ASSERT_FALSE(cen::color::from_rgb("#11X23344"));

  const auto color = cen::color::from_rgba("#7BCF39EA");
  ASSERT_TRUE(color);
  ASSERT_EQ(0x7B, color->red());
  ASSERT_EQ(0xCF, color->green());
  ASSERT_EQ(0x39, color->blue());
  ASSERT_EQ(0xEA, color->alpha());

  ASSERT_EQ("#0710F3C0", cen::color::from_rgba("#0710F3C0").value().as_rgba());
}

TEST(Color, FromARGB)
{
  ASSERT_FALSE(cen::color::from_argb("11223344"));

  ASSERT_FALSE(cen::color::from_argb("#112233444"));
  ASSERT_FALSE(cen::color::from_argb("#112233"));

  ASSERT_FALSE(cen::color::from_rgb("#112233N4"));

  const auto color = cen::color::from_argb("#B281CDA7");
  ASSERT_TRUE(color);
  ASSERT_EQ(0xB2, color->alpha());
  ASSERT_EQ(0x81, color->red());
  ASSERT_EQ(0xCD, color->green());
  ASSERT_EQ(0xA7, color->blue());

  ASSERT_EQ("#890FE1CA", cen::color::from_argb("#890FE1CA").value().as_argb());
}

TEST(Color, FromNorm)
{
  {
    const auto negative = cen::color::from_norm(-0.3f, -5, -0.4f, -234);
    ASSERT_EQ(0, negative.norm_red());
    ASSERT_EQ(0, negative.norm_green());
    ASSERT_EQ(0, negative.norm_blue());
    ASSERT_EQ(0, negative.norm_alpha());
  }

  {
    const auto overflow = cen::color::from_norm(1.1f, 6.5, 53, 394);
    ASSERT_EQ(1, overflow.norm_red());
    ASSERT_EQ(1, overflow.norm_green());
    ASSERT_EQ(1, overflow.norm_blue());
    ASSERT_EQ(1, overflow.norm_alpha());
  }

  {
    const auto red = 0.2f;
    const auto green = 0.6f;
    const auto blue = 1.0f;
    const auto alpha = 0.8f;

    const auto color = cen::color::from_norm(red, green, blue, alpha);
    ASSERT_FLOAT_EQ(red, color.norm_red());
    ASSERT_FLOAT_EQ(green, color.norm_green());
    ASSERT_FLOAT_EQ(blue, color.norm_blue());
    ASSERT_FLOAT_EQ(alpha, color.norm_alpha());
  }
}

TEST(Color, EqualityOperatorReflexivity)
{
  const cen::color color{10, 20, 30, 40};
  ASSERT_EQ(color, color);
  ASSERT_FALSE(color != color);
}

TEST(Color, EqualityOperatorComparisonWithDifferentColors)
{
  const cen::color a{0x34, 0xD2, 0xCA, 0xDE};
  const cen::color b{0x84, 0x45, 0x11, 0xFA};
  ASSERT_NE(a, b);
  ASSERT_NE(b, a);
}

TEST(Color, SetRed)
{
  cen::color color;

  constexpr auto red = 0x3C;
  color.set_red(red);

  ASSERT_EQ(color.red(), red);
}

TEST(Color, SetGreen)
{
  cen::color color;

  constexpr auto green = 0x79;
  color.set_green(green);

  ASSERT_EQ(color.green(), green);
}

TEST(Color, SetBlue)
{
  cen::color color;

  constexpr auto blue = 0xEE;
  color.set_blue(blue);

  ASSERT_EQ(color.blue(), blue);
}

TEST(Color, SetAlpha)
{
  cen::color color;

  constexpr auto alpha = 0x28;
  color.set_alpha(alpha);

  ASSERT_EQ(color.alpha(), alpha);
}

TEST(Color, NormalizedColorGetters)
{
  const auto red = 154;
  const auto green = 82;
  const auto blue = 232;
  const auto alpha = 34;

  const cen::color color{red, green, blue, alpha};

  ASSERT_EQ(red / 255.0f, color.norm_red());
  ASSERT_EQ(green / 255.0f, color.norm_green());
  ASSERT_EQ(blue / 255.0f, color.norm_blue());
  ASSERT_EQ(alpha / 255.0f, color.norm_alpha());
}

TEST(Color, WithAlpha)
{
  constexpr auto other = cen::colors::maroon;
  constexpr auto color = other.with_alpha(0x12);

  ASSERT_EQ(color.red(), other.red());
  ASSERT_EQ(color.green(), other.green());
  ASSERT_EQ(color.blue(), other.blue());
  ASSERT_EQ(color.alpha(), 0x12);
}

TEST(Color, blend)
{
  ASSERT_EQ(cen::colors::gray, cen::blend(cen::colors::white, cen::colors::black));
  ASSERT_EQ(cen::colors::white, cen::blend(cen::colors::white, cen::colors::black, 0.0f));
  ASSERT_EQ(cen::colors::black, cen::blend(cen::colors::white, cen::colors::black, 1.0f));

  // light pink: #FFB6C1, crimson:  #DC143C
  const auto c = cen::blend(cen::colors::light_pink, cen::colors::crimson, 0.4f);
  ASSERT_EQ(0xF1, c.red());
  ASSERT_EQ(0x75, c.green());
  ASSERT_EQ(0x8C, c.blue());
  ASSERT_EQ(0xFF, c.alpha());
}

TEST(Color, Data)
{
  auto white = cen::colors::white;
  const auto black = cen::colors::black;

  ASSERT_TRUE(white.data());
  ASSERT_TRUE(black.data());
}

TEST(Color, AsRGB)
{
  ASSERT_EQ("#000000", cen::colors::black.as_rgb());
  ASSERT_EQ("#FF0000", cen::colors::red.as_rgb());
  ASSERT_EQ("#00FF00", cen::colors::lime.as_rgb());
  ASSERT_EQ("#0000FF", cen::colors::blue.as_rgb());

  const cen::color color{0x5B, 0xE1, 0x84};
  ASSERT_EQ("#5BE184", color.as_rgb());
}

TEST(Color, AsRGBA)
{
  ASSERT_EQ("#000000FF", cen::colors::black.as_rgba());
  ASSERT_EQ("#FF0000FF", cen::colors::red.as_rgba());
  ASSERT_EQ("#00FF00FF", cen::colors::lime.as_rgba());
  ASSERT_EQ("#0000FFFF", cen::colors::blue.as_rgba());

  const cen::color color{0x36, 0xCA, 0x9F, 0xDA};
  ASSERT_EQ("#36CA9FDA", color.as_rgba());
}

TEST(Color, AsARGB)
{
  ASSERT_EQ("#FF000000", cen::colors::black.as_argb());
  ASSERT_EQ("#FFFF0000", cen::colors::red.as_argb());
  ASSERT_EQ("#FF00FF00", cen::colors::lime.as_argb());
  ASSERT_EQ("#FF0000FF", cen::colors::blue.as_argb());

  const cen::color color{0xF1, 0x85, 0xB3, 0xCE};
  ASSERT_EQ("#CEF185B3", color.as_argb());
}

TEST(Color, StreamOperator)
{
  std::cout << cen::color{0xAA, 0xBB, 0xCC, 0xDD} << '\n';
}

TEST(Color, Serialization)
{
  const auto red = 0xAB;
  const auto green = 0xDE;
  const auto blue = 0xC3;
  const auto alpha = 0x8F;
  serialize_save("color.binary", cen::color{red, green, blue, alpha});

  const auto color = serialize_create<cen::color>("color.binary");
  ASSERT_EQ(red, color.red());
  ASSERT_EQ(green, color.green());
  ASSERT_EQ(blue, color.blue());
  ASSERT_EQ(alpha, color.alpha());
}