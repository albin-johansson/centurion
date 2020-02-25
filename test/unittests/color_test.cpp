#include "color.h"

#include <utility>

#include "catch.hpp"
#include "colors.h"
#include "log.h"

using namespace centurion;
using namespace centurion::video;

TEST_CASE("Color()", "[Color]")
{
  Color c;
  CHECK(0 == c.get_red());
  CHECK(0 == c.get_red());
  CHECK(0 == c.get_red());
  CHECK(0xFF == c.get_alpha());
}

TEST_CASE("Color(Color&&)", "[Color]")
{
  const auto r = 0xAE;
  const auto g = 0xDD;
  const auto b = 0xC5;
  const auto a = 0x38;
  Color color{r, g, b, a};
  Color other{std::move(color)};
  CHECK(r == other.get_red());
  CHECK(g == other.get_green());
  CHECK(b == other.get_blue());
  CHECK(a == other.get_alpha());
}

TEST_CASE("Color(uint8_t, uint8_t, uint8_t, uint8_t)", "[Color]")
{
  const auto r = 0xA5;
  const auto g = 0xB3;
  const auto b = 0x29;
  const auto a = 0xCC;

  SECTION("Full ctor")
  {
    const Color c{r, g, b, a};

    CHECK(r == c.get_red());
    CHECK(g == c.get_green());
    CHECK(b == c.get_blue());
    CHECK(a == c.get_alpha());
  }

  SECTION("Defaulted alpha value")
  {
    const Color c{r, g, b};

    CHECK(r == c.get_red());
    CHECK(g == c.get_green());
    CHECK(b == c.get_blue());
    CHECK(c.get_alpha() == Color::max);
  }
}

TEST_CASE("Color::operator=(Color&)", "[Color]")
{
  Color color{0xFE, 0x13, 0xA8, 0xCA};
  const Color other{0xBE, 0x44, 0xAC, 0xFD};

  REQUIRE(color != other);

  color = other;

  CHECK(color == other);
}

TEST_CASE("Color::operator=(Color&&)", "[Color]")
{
  Color color{0xFE, 0x13, 0xA8, 0xCA};
  const auto r = 0xCC;
  const auto g = 0xCE;
  const auto b = 0x71;
  const auto a = 0x99;

  color = Color{r, g, b, a};

  CHECK(r == color.get_red());
  CHECK(g == color.get_green());
  CHECK(b == color.get_blue());
  CHECK(a == color.get_alpha());
}

TEST_CASE("Color from SDL_Color", "[Color]")
{
  const auto sc = SDL_Color{0x3F, 0x9A, 0xCC, 0x17};

  SECTION("Copy constructor")
  {
    const auto c = Color{sc};
    CHECK(c == sc);
    CHECK(c.get_red() == sc.r);
    CHECK(c.get_green() == sc.g);
    CHECK(c.get_blue() == sc.b);
    CHECK(c.get_alpha() == sc.a);
  }

  SECTION("Move constructor")
  {
    const auto c = Color{SDL_Color{sc.r, sc.g, sc.b, sc.a}};
    CHECK(c == sc);
    CHECK(c.get_red() == sc.r);
    CHECK(c.get_green() == sc.g);
    CHECK(c.get_blue() == sc.b);
    CHECK(c.get_alpha() == sc.a);
  }
}

TEST_CASE("Color from SDL_MessageBoxColor", "[Color]")
{
  const auto sc = SDL_MessageBoxColor{0xDA, 0x5E, 0x81};

  SECTION("Copy constructor")
  {
    const auto c = Color{sc};
    CHECK(c == sc);
    CHECK(c.get_red() == sc.r);
    CHECK(c.get_green() == sc.g);
    CHECK(c.get_blue() == sc.b);
  }

  SECTION("Move constructor")
  {
    const auto c = Color{SDL_MessageBoxColor{sc.r, sc.g, sc.b}};
    CHECK(c == sc);
    CHECK(c.get_red() == sc.r);
    CHECK(c.get_green() == sc.g);
    CHECK(c.get_blue() == sc.b);
  }
}

TEST_CASE("Equality operators", "[Color]")
{
  SECTION("Reflexivity")
  {
    const auto color = Color{10, 20, 30, 40};
    CHECK(color == color);
    CHECK(!(color != color));
  }

  SECTION("Equal colors")
  {
    const auto r = 0x43;
    const auto g = 0x8A;
    const auto b = 0x14;
    const auto a = 0x86;

    const auto sdlColor = SDL_Color{r, g, b, a};
    const auto msgColor = SDL_MessageBoxColor{r, g, b};
    const auto color = Color{r, g, b, a};

    CHECK(color == sdlColor);
    CHECK(sdlColor == color);

    CHECK(color == msgColor);
    CHECK(msgColor == color);
  }

  SECTION("Non-equal colors")
  {
    const auto color = Color{0x34, 0xD2, 0xCA, 0xDE};
    const auto sdlColor = SDL_Color{0x84, 0x45, 0x11, 0xFA};
    const auto msgColor = SDL_MessageBoxColor{0xAA, 0x57, 0x99};

    CHECK(color != sdlColor);
    CHECK(sdlColor != color);

    CHECK(color != msgColor);
    CHECK(msgColor != color);
  }
}

TEST_CASE("Color setters", "[Color]")
{
  Color c;
  SECTION("Red")
  {
    const auto r = 0x3C;
    c.set_red(r);
    CHECK(r == c.get_red());
  }

  SECTION("Green")
  {
    const auto g = 0x79;
    c.set_green(g);
    CHECK(g == c.get_green());
  }

  SECTION("Blue")
  {
    const auto b = 0xEE;
    c.set_blue(b);
    CHECK(b == c.get_blue());
  }

  SECTION("Alpha")
  {
    const auto a = 0x28;
    c.set_alpha(a);
    CHECK(a == c.get_alpha());
  }
}

TEST_CASE("Color conversions", "[Color]")
{
  const auto& color = dark_orchid;
  SECTION("Convert to SDL_Color")
  {
    SDL_Color sdlColor = color;

    CHECK(color == sdlColor);
    CHECK(sdlColor == color);

    CHECK(color.get_red() == sdlColor.r);
    CHECK(color.get_green() == sdlColor.g);
    CHECK(color.get_blue() == sdlColor.b);
    CHECK(color.get_alpha() == sdlColor.a);
  }

  SECTION("Convert to SDL_MessageBoxColor")
  {
    SDL_MessageBoxColor msgColor = color;

    CHECK(color == msgColor);
    CHECK(msgColor == color);

    CHECK(color.get_red() == msgColor.r);
    CHECK(color.get_green() == msgColor.g);
    CHECK(color.get_blue() == msgColor.b);
  }

  SECTION("Reinterpret to SDL_Color*") {
    const Color color = bisque;
    const auto* sdlColor = static_cast<const SDL_Color*>(color);

    const void* adr = &color;
    const void* sdlAdr = sdlColor;
    CHECK(adr == sdlAdr);

    CHECK(color.get_red() == sdlColor->r);
    CHECK(color.get_green() == sdlColor->g);
    CHECK(color.get_blue() == sdlColor->b);
    CHECK(color.get_alpha() == sdlColor->a);
  }
}

TEST_CASE("Color::to_string", "[Color]")
{
  const auto color = Color{0x12, 0xFA, 0xCC, 0xAD};
  Log::msgf(Category::Test, "%s", color.to_string().c_str());
}