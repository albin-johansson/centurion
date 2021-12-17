#include "color.hpp"

#include <gtest/gtest.h>

#include <iostream>     // clog
#include <type_traits>  // is_nothrow_X...
#include <utility>      // move

#include "color.hpp"
#include "core/logging.hpp"
#include "serialization_utils.hpp"

static_assert(std::is_final_v<cen::Color>);

static_assert(std::is_default_constructible_v<cen::Color>);

static_assert(std::is_nothrow_copy_constructible_v<cen::Color>);
static_assert(std::is_nothrow_copy_assignable_v<cen::Color>);

static_assert(std::is_nothrow_move_constructible_v<cen::Color>);
static_assert(std::is_nothrow_move_assignable_v<cen::Color>);

TEST(Color, DefaultConstruction)
{
  const cen::Color color;
  ASSERT_EQ(0, color.GetRed());
  ASSERT_EQ(0, color.GetGreen());
  ASSERT_EQ(0, color.GetBlue());
  ASSERT_EQ(0xFF, color.GetAlpha());

  ASSERT_EQ(0, color.GetRedNorm());
  ASSERT_EQ(0, color.GetGreenNorm());
  ASSERT_EQ(0, color.GetBlueNorm());
  ASSERT_EQ(1, color.GetAlphaNorm());
}

TEST(Color, ValueConstruction)
{
  constexpr auto red = 0xA5;
  constexpr auto green = 0xB3;
  constexpr auto blue = 0x29;
  constexpr auto alpha = 0xCC;

  constexpr cen::Color color{red, green, blue, alpha};

  ASSERT_EQ(color.GetRed(), red);
  ASSERT_EQ(color.GetGreen(), green);
  ASSERT_EQ(color.GetBlue(), blue);
  ASSERT_EQ(color.GetAlpha(), alpha);
}

TEST(Color, ValueConstructionDefaultedAlpha)
{
  constexpr auto red = 0x2C;
  constexpr auto green = 0xE2;
  constexpr auto blue = 0x08;

  constexpr cen::Color color{red, green, blue};

  ASSERT_EQ(red, color.GetRed());
  ASSERT_EQ(green, color.GetGreen());
  ASSERT_EQ(blue, color.GetBlue());
  ASSERT_EQ(color.GetAlpha(), 0xFF);
}

TEST(Color, FromSDLColor)
{
  constexpr SDL_Color sdlColor{0x3F, 0x9A, 0xCC, 0x17};
  constexpr cen::Color color{sdlColor};

  ASSERT_EQ(color.GetRed(), sdlColor.r);
  ASSERT_EQ(color.GetGreen(), sdlColor.g);
  ASSERT_EQ(color.GetBlue(), sdlColor.b);
  ASSERT_EQ(color.GetAlpha(), sdlColor.a);
}

TEST(Color, FromSDLMessageBoxColor)
{
  constexpr SDL_MessageBoxColor msgColor{0xDA, 0x5E, 0x81};
  constexpr cen::Color color{msgColor};

  ASSERT_EQ(color.GetRed(), msgColor.r);
  ASSERT_EQ(color.GetGreen(), msgColor.g);
  ASSERT_EQ(color.GetBlue(), msgColor.b);

  // SDL_MessageBoxColor has no alpha component
  ASSERT_EQ(color.GetAlpha(), 0xFF);
}

TEST(Color, FromHSV)
{
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSV(0, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSV(359, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSV(0, 100, 0));
  ASSERT_EQ(cen::colors::white, cen::Color::FromHSV(0, 0, 100));

  ASSERT_EQ(cen::colors::red, cen::Color::FromHSV(0, 100, 100));
  ASSERT_EQ(cen::colors::lime, cen::Color::FromHSV(120, 100, 100));
  ASSERT_EQ(cen::colors::blue, cen::Color::FromHSV(240, 100, 100));

  // Random colors
  ASSERT_EQ(cen::colors::dark_orchid, cen::Color::FromHSV(280, 75.5f, 80));
  ASSERT_EQ(cen::colors::turquoise, cen::Color::FromHSV(174, 71.4f, 87.8f));
  ASSERT_EQ(cen::colors::crimson, cen::Color::FromHSV(348, 90.9f, 86.3f));
  ASSERT_EQ(cen::colors::light_pink, cen::Color::FromHSV(351, 28.6f, 100));
  ASSERT_EQ(cen::colors::thistle, cen::Color::FromHSV(300, 11.6f, 84.7f));

  {  // Maxed out
    const auto color = cen::Color::FromHSV(359, 100, 100);
    ASSERT_EQ(255, color.GetRed());
    ASSERT_EQ(0, color.GetGreen());
    ASSERT_EQ(4, color.GetBlue());
    ASSERT_EQ(255, color.GetAlpha());
  }
}

TEST(Color, FromHSL)
{
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSL(0, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSL(359, 0, 0));
  ASSERT_EQ(cen::colors::black, cen::Color::FromHSL(0, 100, 0));
  ASSERT_EQ(cen::colors::white, cen::Color::FromHSL(0, 0, 100));

  ASSERT_EQ(cen::colors::red, cen::Color::FromHSL(0, 100, 50));
  ASSERT_EQ(cen::colors::lime, cen::Color::FromHSL(120, 100, 50));
  ASSERT_EQ(cen::colors::blue, cen::Color::FromHSL(240, 100, 50));

  // Random colors
  ASSERT_EQ(cen::colors::dark_orchid, cen::Color::FromHSL(280, 60.6f, 49.8f));
  ASSERT_EQ(cen::colors::turquoise, cen::Color::FromHSL(174, 72.1f, 56.5f));
  ASSERT_EQ(cen::colors::crimson, cen::Color::FromHSL(348, 83.3f, 47.1f));
  ASSERT_EQ(cen::colors::light_pink, cen::Color::FromHSL(351, 100, 85.7f));
  ASSERT_EQ(cen::colors::thistle, cen::Color::FromHSL(300, 24.3f, 79.8f));

  // Maxed out
  ASSERT_EQ(cen::colors::white, cen::Color::FromHSL(359, 100, 100));
}

TEST(Color, FromRGB)
{
  ASSERT_FALSE(cen::Color::FromRGB("112233"));

  ASSERT_FALSE(cen::Color::FromRGB("#1122333"));
  ASSERT_FALSE(cen::Color::FromRGB("#11223"));

  ASSERT_FALSE(cen::Color::FromRGB("#XY0000"));

  const auto color = cen::Color::FromRGB("#2AEB9C");
  ASSERT_TRUE(color);
  ASSERT_EQ(0x2A, color->GetRed());
  ASSERT_EQ(0xEB, color->GetGreen());
  ASSERT_EQ(0x9C, color->GetBlue());
  ASSERT_EQ(0xFF, color->GetAlpha());
}

TEST(Color, FromRGBA)
{
  ASSERT_FALSE(cen::Color::FromRGBA("11223344"));

  ASSERT_FALSE(cen::Color::FromRGBA("#112233444"));
  ASSERT_FALSE(cen::Color::FromRGBA("#112233"));

  ASSERT_FALSE(cen::Color::FromRGB("#11X23344"));

  const auto color = cen::Color::FromRGBA("#7BCF39EA");
  ASSERT_TRUE(color);
  ASSERT_EQ(0x7B, color->GetRed());
  ASSERT_EQ(0xCF, color->GetGreen());
  ASSERT_EQ(0x39, color->GetBlue());
  ASSERT_EQ(0xEA, color->GetAlpha());
}

TEST(Color, FromARGB)
{
  ASSERT_FALSE(cen::Color::FromARGB("11223344"));

  ASSERT_FALSE(cen::Color::FromARGB("#112233444"));
  ASSERT_FALSE(cen::Color::FromARGB("#112233"));

  ASSERT_FALSE(cen::Color::FromRGB("#112233N4"));

  const auto color = cen::Color::FromARGB("#B281CDA7");
  ASSERT_TRUE(color);
  ASSERT_EQ(0xB2, color->GetAlpha());
  ASSERT_EQ(0x81, color->GetRed());
  ASSERT_EQ(0xCD, color->GetGreen());
  ASSERT_EQ(0xA7, color->GetBlue());
}

TEST(Color, FromNorm)
{
  {
    const auto negative = cen::Color::FromNorm(-0.3f, -5, -0.4f, -234);
    ASSERT_EQ(0, negative.GetRedNorm());
    ASSERT_EQ(0, negative.GetGreenNorm());
    ASSERT_EQ(0, negative.GetBlueNorm());
    ASSERT_EQ(0, negative.GetAlphaNorm());
  }

  {
    const auto overflow = cen::Color::FromNorm(1.1f, 6.5, 53, 394);
    ASSERT_EQ(1, overflow.GetRedNorm());
    ASSERT_EQ(1, overflow.GetGreenNorm());
    ASSERT_EQ(1, overflow.GetBlueNorm());
    ASSERT_EQ(1, overflow.GetAlphaNorm());
  }

  {
    const auto red = 0.2f;
    const auto green = 0.6f;
    const auto blue = 1.0f;
    const auto alpha = 0.8f;

    const auto color = cen::Color::FromNorm(red, green, blue, alpha);
    ASSERT_FLOAT_EQ(red, color.GetRedNorm());
    ASSERT_FLOAT_EQ(green, color.GetGreenNorm());
    ASSERT_FLOAT_EQ(blue, color.GetBlueNorm());
    ASSERT_FLOAT_EQ(alpha, color.GetAlphaNorm());
  }
}

TEST(Color, EqualityOperatorReflexivity)
{
  const cen::Color color{10, 20, 30, 40};
  ASSERT_EQ(color, color);
  ASSERT_FALSE(color != color);
}

TEST(Color, EqualityOperatorComparisonWithDifferentColors)
{
  const cen::Color a{0x34, 0xD2, 0xCA, 0xDE};
  const cen::Color b{0x84, 0x45, 0x11, 0xFA};
  ASSERT_NE(a, b);
  ASSERT_NE(b, a);
}

TEST(Color, SetRed)
{
  cen::Color color;

  constexpr auto red = 0x3C;
  color.SetRed(red);

  ASSERT_EQ(color.GetRed(), red);
}

TEST(Color, SetGreen)
{
  cen::Color color;

  constexpr auto green = 0x79;
  color.SetGreen(green);

  ASSERT_EQ(color.GetGreen(), green);
}

TEST(Color, SetBlue)
{
  cen::Color color;

  constexpr auto blue = 0xEE;
  color.SetBlue(blue);

  ASSERT_EQ(color.GetBlue(), blue);
}

TEST(Color, SetAlpha)
{
  cen::Color color;

  constexpr auto alpha = 0x28;
  color.SetAlpha(alpha);

  ASSERT_EQ(color.GetAlpha(), alpha);
}

TEST(Color, NormalizedColorGetters)
{
  const auto red = 154;
  const auto green = 82;
  const auto blue = 232;
  const auto alpha = 34;

  const cen::Color color{red, green, blue, alpha};

  ASSERT_EQ(red / 255.0f, color.GetRedNorm());
  ASSERT_EQ(green / 255.0f, color.GetGreenNorm());
  ASSERT_EQ(blue / 255.0f, color.GetBlueNorm());
  ASSERT_EQ(alpha / 255.0f, color.GetAlphaNorm());
}

TEST(Color, WithAlpha)
{
  constexpr auto other = cen::colors::maroon;
  constexpr auto color = other.WithAlpha(0x12);

  ASSERT_EQ(color.GetRed(), other.GetRed());
  ASSERT_EQ(color.GetGreen(), other.GetGreen());
  ASSERT_EQ(color.GetBlue(), other.GetBlue());
  ASSERT_EQ(color.GetAlpha(), 0x12);
}

TEST(Color, Blend)
{
  ASSERT_EQ(cen::colors::gray, cen::Blend(cen::colors::white, cen::colors::black));
  ASSERT_EQ(cen::colors::white, cen::Blend(cen::colors::white, cen::colors::black, 0.0f));
  ASSERT_EQ(cen::colors::black, cen::Blend(cen::colors::white, cen::colors::black, 1.0f));

  // light pink: #FFB6C1, crimson:  #DC143C
  const auto c = cen::Blend(cen::colors::light_pink, cen::colors::crimson, 0.4f);
  ASSERT_EQ(0xF1, c.GetRed());
  ASSERT_EQ(0x75, c.GetGreen());
  ASSERT_EQ(0x8C, c.GetBlue());
  ASSERT_EQ(0xFF, c.GetAlpha());
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
  ASSERT_EQ("#000000", cen::colors::black.AsRGB());
  ASSERT_EQ("#FF0000", cen::colors::red.AsRGB());
  ASSERT_EQ("#00FF00", cen::colors::lime.AsRGB());
  ASSERT_EQ("#0000FF", cen::colors::blue.AsRGB());

  const cen::Color color{0x5B, 0xE1, 0x84};
  ASSERT_EQ("#5BE184", color.AsRGB());
}

TEST(Color, AsRGBA)
{
  ASSERT_EQ("#000000FF", cen::colors::black.AsRGBA());
  ASSERT_EQ("#FF0000FF", cen::colors::red.AsRGBA());
  ASSERT_EQ("#00FF00FF", cen::colors::lime.AsRGBA());
  ASSERT_EQ("#0000FFFF", cen::colors::blue.AsRGBA());

  const cen::Color color{0x36, 0xCA, 0x9F, 0xDA};
  ASSERT_EQ("#36CA9FDA", color.AsRGBA());
}

TEST(Color, AsARGB)
{
  ASSERT_EQ("#FF000000", cen::colors::black.AsARGB());
  ASSERT_EQ("#FFFF0000", cen::colors::red.AsARGB());
  ASSERT_EQ("#FF00FF00", cen::colors::lime.AsARGB());
  ASSERT_EQ("#FF0000FF", cen::colors::blue.AsARGB());

  const cen::Color color{0xF1, 0x85, 0xB3, 0xCE};
  ASSERT_EQ("#CEF185B3", color.AsARGB());
}

TEST(Color, ToString)
{
  constexpr cen::Color color{0x12, 0xFA, 0xCC, 0xAD};
  cen::log_info_raw(cen::to_string(color));
}

TEST(Color, StreamOperator)
{
  constexpr cen::Color color{0xAA, 0xBB, 0xCC, 0xDD};
  std::clog << color << '\n';
}

TEST(Color, Serialization)
{
  const auto red = 0xAB;
  const auto green = 0xDE;
  const auto blue = 0xC3;
  const auto alpha = 0x8F;
  serialize_save("color.binary", cen::Color{red, green, blue, alpha});

  const auto color = serialize_create<cen::Color>("color.binary");
  ASSERT_EQ(red, color.GetRed());
  ASSERT_EQ(green, color.GetGreen());
  ASSERT_EQ(blue, color.GetBlue());
  ASSERT_EQ(alpha, color.GetAlpha());
}