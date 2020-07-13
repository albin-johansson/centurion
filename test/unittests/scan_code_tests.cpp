#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "scan_code.hpp"

TEST_CASE("scan_code default value", "[scan_code]")
{
  ctn::scan_code code;
  CHECK(code.get() == SDL_SCANCODE_UNKNOWN);
}

TEST_CASE("scan_code::scan_code(SDL_Scancode)", "[scan_code]")
{
  const auto expected = SDL_SCANCODE_W;
  const ctn::scan_code code{expected};
  CHECK(code.get() == expected);
}

TEST_CASE("scan_code::scan_code(SDL_Keycode)", "[scan_code]")
{
  const auto expected = SDLK_LSHIFT;
  const ctn::scan_code code{expected};
  CHECK(code.get() == SDL_GetScancodeFromKey(expected));
}

TEST_CASE("scan_code::scan_code(czstring)", "[scan_code]")
{
  SECTION("Good name")
  {
    ctn::czstring name = "Escape";
    const ctn::scan_code code{name};
    CHECK(code.get() == SDL_SCANCODE_ESCAPE);
    CHECK(code.name() == name);
  }
  SECTION("Bad name")
  {
    ctn::czstring bad = "foobar";
    const ctn::scan_code code{bad};
    CHECK(code.get() == SDL_SCANCODE_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("scan_code::operator=(SDL_Scancode)", "[scan_code]")
{
  ctn::scan_code code;

  const auto expected = SDL_SCANCODE_B;
  code = expected;

  CHECK(code.get() == expected);
}

TEST_CASE("scan_code::operator=(SDL_Keycode)", "[scan_code]")
{
  ctn::scan_code code;

  const auto expected = SDLK_CAPSLOCK;
  code = expected;

  CHECK(code.get() == SDL_SCANCODE_CAPSLOCK);
}

TEST_CASE("scan_code::operator=(czstring)", "[scan_code]")
{
  SECTION("Good name")
  {
    ctn::scan_code code;

    const auto name = "A";
    code = name;

    CHECK(code.get() == SDL_SCANCODE_A);
    CHECK(code.name() == "A");
  }

  SECTION("Bad name")
  {
    ctn::scan_code code;

    const auto name = "qwerty";
    code = name;

    CHECK(code.get() == SDL_SCANCODE_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("scan_code::unknown", "[scan_code]")
{
  ctn::scan_code code;
  CHECK(code.unknown());

  code = SDL_SCANCODE_O;
  CHECK(!code.unknown());
}

TEST_CASE("scan_code::name", "[scan_code]")
{
  ctn::scan_code code;
  CHECK(code.name().empty());

  code = SDL_SCANCODE_O;
  CHECK(code.name() == "O");
}

TEST_CASE("scan_code::get", "[scan_code]")
{
  ctn::scan_code code;
  CHECK(code.get() == SDL_SCANCODE_UNKNOWN);

  code = SDL_SCANCODE_Z;
  CHECK(code.get() == SDL_SCANCODE_Z);
}

TEST_CASE("scan_code::operator SDL_Scancode", "[scan_code]")
{
  ctn::scan_code code;

  const auto unknown = static_cast<SDL_Scancode>(code);
  CHECK(code.get() == unknown);

  code = SDL_SCANCODE_Z;
  const auto z = static_cast<SDL_Scancode>(code);
  CHECK(code.get() == z);
}

TEST_CASE("scan_code::operator SDL_Keycode", "[scan_code]")
{
  ctn::scan_code code;

  const auto unknown = static_cast<SDL_Keycode>(code);
  CHECK(unknown == SDLK_UNKNOWN);

  code = SDL_SCANCODE_H;
  const auto h = static_cast<SDL_Keycode>(code);
  CHECK(h == SDLK_h);
}

TEST_CASE("operator==(const scan_code&, const scan_code&)", "[scan_code]")
{
  SECTION("Default initialized scan codes")
  {
    const ctn::scan_code fst;
    const ctn::scan_code snd;
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Same assigned scan codes")
  {
    const ctn::scan_code fst{SDL_SCANCODE_V};
    const ctn::scan_code snd{fst};
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Not same")
  {
    const ctn::scan_code fst{SDL_SCANCODE_Q};
    const ctn::scan_code snd{SDL_SCANCODE_P};
    CHECK_FALSE(fst == snd);
    CHECK_FALSE(snd == fst);
  }
}