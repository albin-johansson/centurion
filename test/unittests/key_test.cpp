#include "key.hpp"

#include <SDL.h>

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Key()", "[Key]")
{
  const Key key;
  CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
  CHECK(key.keycode() == SDLK_UNKNOWN);
}

TEST_CASE("Key(SDL_Scancode)", "[Key]")
{
  const SDL_Scancode scancode = SDL_SCANCODE_B;
  const Key key{scancode};
  CHECK(key.scancode() == scancode);
  CHECK(key.keycode() == SDL_GetKeyFromScancode(scancode));
}

TEST_CASE("Key(SDL_Keycode)", "[Key]")
{
  const SDL_Keycode keycode = SDLK_x;
  const Key key{keycode};
  CHECK(key.keycode() == keycode);
  CHECK(key.scancode() == SDL_GetScancodeFromKey(keycode));
}

TEST_CASE("Key(CZString)", "[Key]")
{
  SECTION("Null string")
  {
    Key key{nullptr};
    CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
    CHECK(key.keycode() == SDLK_UNKNOWN);
  }
  SECTION("Bad name")
  {
    Key key{"someunknownkey"};
    CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
    CHECK(key.keycode() == SDLK_UNKNOWN);
  }
  SECTION("Good name")
  {
    Key key{"A"};
    CHECK(key.scancode() == SDL_SCANCODE_A);
    CHECK(key.keycode() == SDLK_a);
  }
}

TEST_CASE("Key::set(SDL_Scancode)", "[Key]")
{
  Key key;

  const auto scancode = SDL_SCANCODE_A;
  key.set(scancode);

  CHECK(key.scancode() == scancode);
}

TEST_CASE("Key::set(SDL_Keycode)", "[Key]")
{
  Key key;

  const auto keycode = SDLK_y;
  key.set(keycode);

  CHECK(key.keycode() == keycode);
}

TEST_CASE("Key::name", "[Key]")
{
  SECTION("Known key")
  {
    Key key{SDL_SCANCODE_ESCAPE};
    CHECK(key.name() == "Escape");
  }

  SECTION("Unknown key")
  {
    Key key;
    CHECK(key.name().empty());
  }
}

TEST_CASE("Key::unknown", "[Key]")
{
  SECTION("Known key")
  {
    Key key{SDL_SCANCODE_ESCAPE};
    CHECK(!key.unknown());
  }

  SECTION("Unknown key")
  {
    Key key;
    CHECK(key.unknown());

    key.set(SDL_SCANCODE_UNKNOWN);
    CHECK(key.unknown());
  }
}

TEST_CASE("Key::scancode", "[Key]")
{
  const Key key{SDL_SCANCODE_7};
  CHECK(key.scancode() == SDL_SCANCODE_7);
}

TEST_CASE("Key::keycode", "[Key]")
{
  const Key key{SDLK_CAPSLOCK};
  CHECK(key.keycode() == SDLK_CAPSLOCK);
}

TEST_CASE("Key to SDL_Scancode", "[Key]")
{
  const auto scancode = SDL_SCANCODE_G;
  const Key key{scancode};

  const SDL_Scancode copy = key;

  CHECK(copy == scancode);
}

TEST_CASE("Key to SDL_Keycode", "[Key]")
{
  const auto keycode = SDLK_q;
  const Key key{keycode};

  const SDL_Keycode copy = key;

  CHECK(copy == keycode);
}

TEST_CASE("Key::operator==", "[Key]")
{
  SECTION("Equal")
  {
    const Key first{SDLK_w};
    const Key second{SDLK_w};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Not equal")
  {
    const Key first{SDLK_v};
    const Key second{SDLK_y};
    CHECK(!(first == second));
    CHECK(!(second == first));
  }

  SECTION("Reflexivity")
  {
    const Key key{SDL_SCANCODE_I};
    CHECK(key == key);
  }
}

TEST_CASE("Key::operator!=", "[Key]")
{
  SECTION("Equal")
  {
    const Key first{SDLK_n};
    const Key second{SDLK_n};
    CHECK(!(first != second));
    CHECK(!(second != first));
  }

  SECTION("Not equal")
  {
    const Key first{SDLK_l};
    const Key second{SDLK_a};
    CHECK(first != second);
    CHECK(second != first);
  }
}
