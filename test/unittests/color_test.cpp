#include "color.hpp"

#include <catch.hpp>
#include <iostream>
#include <utility>

#include "centurion_as_ctn.hpp"
#include "colors.hpp"
#include "log.hpp"

TEST_CASE("color()", "[color]")
{
  ctn::color c;
  CHECK(0 == c.red());
  CHECK(0 == c.red());
  CHECK(0 == c.red());
  CHECK(0xFF == c.alpha());
}

TEST_CASE("color(color&&)", "[color]")
{
  const auto r = 0xAE;
  const auto g = 0xDD;
  const auto b = 0xC5;
  const auto a = 0x38;
  ctn::color color{r, g, b, a};
  ctn::color other{std::move(color)};
  CHECK(r == other.red());
  CHECK(g == other.green());
  CHECK(b == other.blue());
  CHECK(a == other.alpha());
}

TEST_CASE("color(u8, u8, u8, u8)", "[color]")
{
  const auto r = 0xA5;
  const auto g = 0xB3;
  const auto b = 0x29;
  const auto a = 0xCC;

  SECTION("Full ctor")
  {
    const ctn::color c{r, g, b, a};

    CHECK(r == c.red());
    CHECK(g == c.green());
    CHECK(b == c.blue());
    CHECK(a == c.alpha());
  }

  SECTION("Defaulted alpha value")
  {
    const ctn::color c{r, g, b};

    CHECK(r == c.red());
    CHECK(g == c.green());
    CHECK(b == c.blue());
    CHECK(c.alpha() == ctn::color::max());
  }
}

TEST_CASE("color::operator=(color&)", "[color]")
{
  ctn::color color{0xFE, 0x13, 0xA8, 0xCA};
  const ctn::color other{0xBE, 0x44, 0xAC, 0xFD};

  REQUIRE(color != other);

  color = other;

  CHECK(color == other);
}

TEST_CASE("color::operator=(color&&)", "[color]")
{
  ctn::color color{0xFE, 0x13, 0xA8, 0xCA};
  const auto r = 0xCC;
  const auto g = 0xCE;
  const auto b = 0x71;
  const auto a = 0x99;

  color = ctn::color{r, g, b, a};

  CHECK(r == color.red());
  CHECK(g == color.green());
  CHECK(b == color.blue());
  CHECK(a == color.alpha());
}

TEST_CASE("color from SDL_Color", "[color]")
{
  const auto sc = SDL_Color{0x3F, 0x9A, 0xCC, 0x17};

  SECTION("Copy constructor")
  {
    const ctn::color c{sc};
    CHECK(c == sc);
    CHECK(c.red() == sc.r);
    CHECK(c.green() == sc.g);
    CHECK(c.blue() == sc.b);
    CHECK(c.alpha() == sc.a);
  }

  SECTION("Move constructor")
  {
    const ctn::color c{SDL_Color{sc.r, sc.g, sc.b, sc.a}};
    CHECK(c == sc);
    CHECK(c.red() == sc.r);
    CHECK(c.green() == sc.g);
    CHECK(c.blue() == sc.b);
    CHECK(c.alpha() == sc.a);
  }
}

TEST_CASE("color from SDL_MessageBoxColor", "[color]")
{
  const SDL_MessageBoxColor sc{0xDA, 0x5E, 0x81};

  SECTION("Copy constructor")
  {
    const auto c = ctn::color{sc};
    CHECK(c == sc);
    CHECK(c.red() == sc.r);
    CHECK(c.green() == sc.g);
    CHECK(c.blue() == sc.b);
  }

  SECTION("Move constructor")
  {
    const ctn::color c{SDL_MessageBoxColor{sc.r, sc.g, sc.b}};
    CHECK(c == sc);
    CHECK(c.red() == sc.r);
    CHECK(c.green() == sc.g);
    CHECK(c.blue() == sc.b);
  }
}

TEST_CASE("Equality operators", "[color]")
{
  SECTION("Reflexivity")
  {
    const ctn::color color{10, 20, 30, 40};
    CHECK(color == color);
    CHECK(!(color != color));
  }

  SECTION("Equal colors")
  {
    const auto r = 0x43;
    const auto g = 0x8A;
    const auto b = 0x14;
    const auto a = 0x86;

    const SDL_Color sdlColor{r, g, b, a};
    const SDL_MessageBoxColor msgColor{r, g, b};
    const ctn::color color{r, g, b, a};

    CHECK(color == sdlColor);
    CHECK(sdlColor == color);

    CHECK(color == msgColor);
    CHECK(msgColor == color);
  }

  SECTION("Non-equal colors")
  {
    const ctn::color color{0x34, 0xD2, 0xCA, 0xDE};
    const SDL_Color sdlColor{0x84, 0x45, 0x11, 0xFA};
    const SDL_MessageBoxColor msgColor{0xAA, 0x57, 0x99};

    CHECK(color != sdlColor);
    CHECK(sdlColor != color);

    CHECK(color != msgColor);
    CHECK(msgColor != color);
  }
}

TEST_CASE("color setters", "[color]")
{
  ctn::color c;
  SECTION("Red")
  {
    const auto r = 0x3C;
    c.set_red(r);
    CHECK(r == c.red());
  }

  SECTION("Green")
  {
    const auto g = 0x79;
    c.set_green(g);
    CHECK(g == c.green());
  }

  SECTION("Blue")
  {
    const auto b = 0xEE;
    c.set_blue(b);
    CHECK(b == c.blue());
  }

  SECTION("Alpha")
  {
    const auto a = 0x28;
    c.set_alpha(a);
    CHECK(a == c.alpha());
  }
}

TEST_CASE("color conversions", "[color]")
{
  SECTION("Convert to SDL_Color")
  {
    const auto& color = ctn::colors::dark_orchid;
    const auto sdlColor = static_cast<SDL_Color>(color);

    CHECK(color == sdlColor);
    CHECK(sdlColor == color);

    CHECK(color.red() == sdlColor.r);
    CHECK(color.green() == sdlColor.g);
    CHECK(color.blue() == sdlColor.b);
    CHECK(color.alpha() == sdlColor.a);
  }

  SECTION("Convert to SDL_MessageBoxColor")
  {
    const auto& color = ctn::colors::dark_orchid;
    const auto msgColor = static_cast<SDL_MessageBoxColor>(color);

    CHECK(color == msgColor);
    CHECK(msgColor == color);

    CHECK(color.red() == msgColor.r);
    CHECK(color.green() == msgColor.g);
    CHECK(color.blue() == msgColor.b);
  }

  SECTION("Reinterpret to SDL_Color*")
  {
    const ctn::color color = ctn::colors::bisque;
    const auto* sdlColor = static_cast<const SDL_Color*>(color);

    const void* adr = &color;
    const void* sdlAdr = sdlColor;
    CHECK(adr == sdlAdr);

    CHECK(color.red() == sdlColor->r);
    CHECK(color.green() == sdlColor->g);
    CHECK(color.blue() == sdlColor->b);
    CHECK(color.alpha() == sdlColor->a);
  }
}

TEST_CASE("color to_string", "[color]")
{
  const ctn::color color{0x12, 0xFA, 0xCC, 0xAD};
  ctn::log::put(ctn::log::category::test, ctn::to_string(color));
}

TEST_CASE("color stream operator", "[color]")
{
  const ctn::color color{0xAA, 0xBB, 0xCC, 0xDD};
  std::cout << "COUT: " << color << '\n';
}