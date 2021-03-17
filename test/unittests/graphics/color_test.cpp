#include "color.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // is_nothrow_X...
#include <utility>      // move

#include "colors.hpp"
#include "log.hpp"
#include "serialization_utils.hpp"

static_assert(std::is_final_v<cen::color>);

static_assert(std::is_default_constructible_v<cen::color>);

static_assert(std::is_nothrow_copy_constructible_v<cen::color>);
static_assert(std::is_nothrow_copy_assignable_v<cen::color>);

static_assert(std::is_nothrow_move_constructible_v<cen::color>);
static_assert(std::is_nothrow_move_assignable_v<cen::color>);

TEST(Color, DefaultConstruction)
{
  constexpr cen::color color;
  EXPECT_EQ(color.red(), 0);
  EXPECT_EQ(color.red(), 0);
  EXPECT_EQ(color.red(), 0);
  EXPECT_EQ(color.alpha(), cen::color::max());
}

TEST(Color, ValueConstruction)
{
  constexpr auto red = 0xA5;
  constexpr auto green = 0xB3;
  constexpr auto blue = 0x29;
  constexpr auto alpha = 0xCC;

  constexpr cen::color color{red, green, blue, alpha};

  EXPECT_EQ(color.red(), red);
  EXPECT_EQ(color.green(), green);
  EXPECT_EQ(color.blue(), blue);
  EXPECT_EQ(color.alpha(), alpha);
}

TEST(Color, ValueConstructionDefaultedAlpha)
{
  constexpr auto red = 0x2C;
  constexpr auto green = 0xE2;
  constexpr auto blue = 0x08;

  constexpr cen::color color{red, green, blue};

  EXPECT_EQ(red, color.red());
  EXPECT_EQ(green, color.green());
  EXPECT_EQ(blue, color.blue());
  EXPECT_EQ(color.alpha(), cen::color::max());
}

TEST(Color, FromSDLColor)
{
  constexpr SDL_Color sdlColor{0x3F, 0x9A, 0xCC, 0x17};
  constexpr cen::color color{sdlColor};

  EXPECT_EQ(color.red(), sdlColor.r);
  EXPECT_EQ(color.green(), sdlColor.g);
  EXPECT_EQ(color.blue(), sdlColor.b);
  EXPECT_EQ(color.alpha(), sdlColor.a);
}

TEST(Color, FromSDLMessageBoxColor)
{
  constexpr SDL_MessageBoxColor msgColor{0xDA, 0x5E, 0x81};
  constexpr cen::color color{msgColor};

  EXPECT_EQ(color.red(), msgColor.r);
  EXPECT_EQ(color.green(), msgColor.g);
  EXPECT_EQ(color.blue(), msgColor.b);

  // SDL_MessageBoxColor has no alpha component
  EXPECT_EQ(color.alpha(), cen::color::max());
}

TEST(Color, FromHSV)
{
  EXPECT_EQ(cen::colors::black, cen::color::from_hsv(0, 0, 0));
  EXPECT_EQ(cen::colors::black, cen::color::from_hsv(359, 0, 0));
  EXPECT_EQ(cen::colors::black, cen::color::from_hsv(0, 100, 0));
  EXPECT_EQ(cen::colors::white, cen::color::from_hsv(0, 0, 100));

  EXPECT_EQ(cen::colors::red, cen::color::from_hsv(0, 100, 100));
  EXPECT_EQ(cen::colors::lime, cen::color::from_hsv(120, 100, 100));
  EXPECT_EQ(cen::colors::blue, cen::color::from_hsv(240, 100, 100));

  // Random colors
  EXPECT_EQ(cen::colors::dark_orchid, cen::color::from_hsv(280, 75.5, 80));
  EXPECT_EQ(cen::colors::turquoise, cen::color::from_hsv(174, 71.4, 87.8));
  EXPECT_EQ(cen::colors::crimson, cen::color::from_hsv(348, 90.9, 86.3));
  EXPECT_EQ(cen::colors::light_pink, cen::color::from_hsv(351, 28.6, 100));
  EXPECT_EQ(cen::colors::thistle, cen::color::from_hsv(300, 11.6, 84.7));

  {  // Maxed out
    const auto color = cen::color::from_hsv(359, 100, 100);
    EXPECT_EQ(255, color.red());
    EXPECT_EQ(0, color.green());
    EXPECT_EQ(4, color.blue());
    EXPECT_EQ(255, color.alpha());
  }
}

TEST(Color, FromHSL)
{
  EXPECT_EQ(cen::colors::black, cen::color::from_hsl(0, 0, 0));
  EXPECT_EQ(cen::colors::black, cen::color::from_hsl(359, 0, 0));
  EXPECT_EQ(cen::colors::black, cen::color::from_hsl(0, 100, 0));
  EXPECT_EQ(cen::colors::white, cen::color::from_hsl(0, 0, 100));

  EXPECT_EQ(cen::colors::red, cen::color::from_hsl(0, 100, 50));
  EXPECT_EQ(cen::colors::lime, cen::color::from_hsl(120, 100, 50));
  EXPECT_EQ(cen::colors::blue, cen::color::from_hsl(240, 100, 50));

  // Random colors
  EXPECT_EQ(cen::colors::dark_orchid, cen::color::from_hsl(280, 60.6, 49.8));
  EXPECT_EQ(cen::colors::turquoise, cen::color::from_hsl(174, 72.1, 56.5));
  EXPECT_EQ(cen::colors::crimson, cen::color::from_hsl(348, 83.3, 47.1));
  EXPECT_EQ(cen::colors::light_pink, cen::color::from_hsl(351, 100, 85.7));
  EXPECT_EQ(cen::colors::thistle, cen::color::from_hsl(300, 24.3, 79.8));

  // Maxed out
  EXPECT_EQ(cen::colors::white, cen::color::from_hsl(359, 100, 100));
}

TEST(Color, EqualityOperatorReflexivity)
{
  const cen::color color{10, 20, 30, 40};
  EXPECT_EQ(color, color);
  EXPECT_FALSE(color != color);
}

TEST(Color, EqualityOperatorComparison)
{
  const auto red = 0x43;
  const auto green = 0x8A;
  const auto blue = 0x14;
  const auto alpha = 0x86;

  constexpr SDL_Color sdlColor{red, green, blue, alpha};
  constexpr SDL_MessageBoxColor msgColor{red, green, blue};
  constexpr cen::color color{red, green, blue, alpha};

  EXPECT_EQ(color, sdlColor);
  EXPECT_EQ(sdlColor, color);

  EXPECT_EQ(color, msgColor);
  EXPECT_EQ(msgColor, color);
}

TEST(Color, EqualityOperatorComparisonWithDifferentColors)
{
  const cen::color color{0x34, 0xD2, 0xCA, 0xDE};
  const SDL_Color sdlColor{0x84, 0x45, 0x11, 0xFA};
  const SDL_MessageBoxColor msgColor{0xAA, 0x57, 0x99};

  EXPECT_NE(color, sdlColor);
  EXPECT_NE(sdlColor, color);

  EXPECT_NE(color, msgColor);
  EXPECT_NE(msgColor, color);
}

TEST(Color, SetRed)
{
  cen::color color;

  constexpr auto red = 0x3C;
  color.set_red(red);

  EXPECT_EQ(color.red(), red);
}

TEST(Color, SetGreen)
{
  cen::color color;

  constexpr auto green = 0x79;
  color.set_green(green);

  EXPECT_EQ(color.green(), green);
}

TEST(Color, SetBlue)
{
  cen::color color;

  constexpr auto blue = 0xEE;
  color.set_blue(blue);

  EXPECT_EQ(color.blue(), blue);
}

TEST(Color, SetAlpha)
{
  cen::color color;

  constexpr auto alpha = 0x28;
  color.set_alpha(alpha);

  EXPECT_EQ(color.alpha(), alpha);
}

TEST(Color, WithAlpha)
{
  constexpr auto other = cen::colors::maroon;
  constexpr auto color = other.with_alpha(0x12);

  EXPECT_EQ(color.red(), other.red());
  EXPECT_EQ(color.green(), other.green());
  EXPECT_EQ(color.blue(), other.blue());
  EXPECT_EQ(color.alpha(), 0x12);
}

TEST(Color, ConversionToSDLColor)
{
  constexpr auto color = cen::colors::dark_orchid;
  constexpr auto sdlColor = static_cast<SDL_Color>(color);

  EXPECT_EQ(color, sdlColor);
  EXPECT_EQ(sdlColor, color);

  EXPECT_EQ(color.red(), sdlColor.r);
  EXPECT_EQ(color.green(), sdlColor.g);
  EXPECT_EQ(color.blue(), sdlColor.b);
  EXPECT_EQ(color.alpha(), sdlColor.a);
}

TEST(Color, ConversionToSDLMessageBoxColor)
{
  constexpr auto color = cen::colors::dark_orchid;
  constexpr auto msgColor = static_cast<SDL_MessageBoxColor>(color);

  EXPECT_EQ(color, msgColor);
  EXPECT_EQ(msgColor, color);

  EXPECT_EQ(color.red(), msgColor.r);
  EXPECT_EQ(color.green(), msgColor.g);
  EXPECT_EQ(color.blue(), msgColor.b);
}

TEST(Color, ConversionToSDLColorPointer)
{
  const cen::color color = cen::colors::bisque;
  const auto* sdlColor = static_cast<const SDL_Color*>(color);

  const void* colorAdr = &color;
  EXPECT_EQ(sdlColor, colorAdr);

  EXPECT_EQ(color.red(), sdlColor->r);
  EXPECT_EQ(color.green(), sdlColor->g);
  EXPECT_EQ(color.blue(), sdlColor->b);
  EXPECT_EQ(color.alpha(), sdlColor->a);
}

TEST(Color, ToString)
{
  constexpr cen::color color{0x12, 0xFA, 0xCC, 0xAD};
  cen::log::put(cen::to_string(color));
}

TEST(Color, StreamOperator)
{
  constexpr cen::color color{0xAA, 0xBB, 0xCC, 0xDD};
  std::cout << "COUT: " << color << '\n';
}

TEST(Color, Serialization)
{
  const auto red = 0xAB;
  const auto green = 0xDE;
  const auto blue = 0xC3;
  const auto alpha = 0x8F;
  serialize_to("color.binary", cen::color{red, green, blue, alpha});

  const auto color = serialize_from<cen::color>("color.binary");
  EXPECT_EQ(red, color.red());
  EXPECT_EQ(green, color.green());
  EXPECT_EQ(blue, color.blue());
  EXPECT_EQ(alpha, color.alpha());
}