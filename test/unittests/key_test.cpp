#include "key.hpp"

#include <SDL.h>

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("key()", "[key]")
{
  const ctn::key key;
  CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
  CHECK(key.keycode() == SDLK_UNKNOWN);
}

TEST_CASE("key(SDL_Scancode)", "[key]")
{
  const SDL_Scancode scancode = SDL_SCANCODE_B;
  const ctn::key key{scancode};
  CHECK(key.scancode() == scancode);
  CHECK(key.keycode() == SDL_GetKeyFromScancode(scancode));
}

TEST_CASE("key(SDL_Keycode)", "[key]")
{
  const SDL_Keycode keycode = SDLK_x;
  const ctn::key key{keycode};
  CHECK(key.keycode() == keycode);
  CHECK(key.scancode() == SDL_GetScancodeFromKey(keycode));
}

TEST_CASE("key constants", "[key]")
{
  const auto test_key = [](const ctn::key& keyConstant,
                           SDL_Scancode scancode) noexcept {
    const ctn::key key{scancode};
    CHECK(keyConstant == key);
  };

  SECTION("Unknown") { test_key(ctn::keys::unknown, SDL_SCANCODE_UNKNOWN); }

  SECTION("Alphabetical keys")
  {
    SECTION("a") { test_key(ctn::keys::a, SDL_SCANCODE_A); }

    SECTION("b") { test_key(ctn::keys::b, SDL_SCANCODE_B); }

    SECTION("c") { test_key(ctn::keys::c, SDL_SCANCODE_C); }

    SECTION("d") { test_key(ctn::keys::d, SDL_SCANCODE_D); }

    SECTION("e") { test_key(ctn::keys::e, SDL_SCANCODE_E); }

    SECTION("f") { test_key(ctn::keys::f, SDL_SCANCODE_F); }

    SECTION("g") { test_key(ctn::keys::g, SDL_SCANCODE_G); }

    SECTION("h") { test_key(ctn::keys::h, SDL_SCANCODE_H); }

    SECTION("i") { test_key(ctn::keys::i, SDL_SCANCODE_I); }

    SECTION("j") { test_key(ctn::keys::j, SDL_SCANCODE_J); }

    SECTION("k") { test_key(ctn::keys::k, SDL_SCANCODE_K); }

    SECTION("l") { test_key(ctn::keys::l, SDL_SCANCODE_L); }

    SECTION("m") { test_key(ctn::keys::m, SDL_SCANCODE_M); }

    SECTION("n") { test_key(ctn::keys::n, SDL_SCANCODE_N); }

    SECTION("o") { test_key(ctn::keys::o, SDL_SCANCODE_O); }

    SECTION("p") { test_key(ctn::keys::p, SDL_SCANCODE_P); }

    SECTION("q") { test_key(ctn::keys::q, SDL_SCANCODE_Q); }

    SECTION("r") { test_key(ctn::keys::r, SDL_SCANCODE_R); }

    SECTION("s") { test_key(ctn::keys::s, SDL_SCANCODE_S); }

    SECTION("t") { test_key(ctn::keys::t, SDL_SCANCODE_T); }

    SECTION("u") { test_key(ctn::keys::u, SDL_SCANCODE_U); }

    SECTION("v") { test_key(ctn::keys::v, SDL_SCANCODE_V); }

    SECTION("w") { test_key(ctn::keys::w, SDL_SCANCODE_W); }

    SECTION("x") { test_key(ctn::keys::x, SDL_SCANCODE_X); }

    SECTION("y") { test_key(ctn::keys::y, SDL_SCANCODE_Y); }

    SECTION("z") { test_key(ctn::keys::z, SDL_SCANCODE_Z); }
  }

  SECTION("Numerical keys")
  {
    SECTION("1") { test_key(ctn::keys::one, SDL_SCANCODE_1); }

    SECTION("2") { test_key(ctn::keys::two, SDL_SCANCODE_2); }

    SECTION("3") { test_key(ctn::keys::three, SDL_SCANCODE_3); }

    SECTION("4") { test_key(ctn::keys::four, SDL_SCANCODE_4); }

    SECTION("5") { test_key(ctn::keys::five, SDL_SCANCODE_5); }

    SECTION("6") { test_key(ctn::keys::six, SDL_SCANCODE_6); }

    SECTION("7") { test_key(ctn::keys::seven, SDL_SCANCODE_7); }

    SECTION("8") { test_key(ctn::keys::eight, SDL_SCANCODE_8); }

    SECTION("9") { test_key(ctn::keys::nine, SDL_SCANCODE_9); }

    SECTION("0") { test_key(ctn::keys::zero, SDL_SCANCODE_0); }
  }

  SECTION("Function keys")
  {
    SECTION("F1") { test_key(ctn::keys::f1, SDL_SCANCODE_F1); }

    SECTION("F2") { test_key(ctn::keys::f2, SDL_SCANCODE_F2); }

    SECTION("F3") { test_key(ctn::keys::f3, SDL_SCANCODE_F3); }

    SECTION("F4") { test_key(ctn::keys::f4, SDL_SCANCODE_F4); }

    SECTION("F5") { test_key(ctn::keys::f5, SDL_SCANCODE_F5); }

    SECTION("F6") { test_key(ctn::keys::f6, SDL_SCANCODE_F6); }

    SECTION("F7") { test_key(ctn::keys::f7, SDL_SCANCODE_F7); }

    SECTION("F8") { test_key(ctn::keys::f8, SDL_SCANCODE_F8); }

    SECTION("F9") { test_key(ctn::keys::f9, SDL_SCANCODE_F9); }

    SECTION("F10") { test_key(ctn::keys::f10, SDL_SCANCODE_F10); }

    SECTION("F11") { test_key(ctn::keys::f11, SDL_SCANCODE_F11); }

    SECTION("F12") { test_key(ctn::keys::f12, SDL_SCANCODE_F12); }
  }

  SECTION("Arrow keys")
  {
    SECTION("Left") { test_key(ctn::keys::left, SDL_SCANCODE_LEFT); }

    SECTION("Right") { test_key(ctn::keys::right, SDL_SCANCODE_RIGHT); }

    SECTION("Up") { test_key(ctn::keys::up, SDL_SCANCODE_UP); }

    SECTION("Down") { test_key(ctn::keys::down, SDL_SCANCODE_DOWN); }
  }

  SECTION("Special action keys")
  {
    SECTION("Space") { test_key(ctn::keys::space, SDL_SCANCODE_SPACE); }

    SECTION("Enter") { test_key(ctn::keys::enter, SDL_SCANCODE_RETURN); }

    SECTION("Escape") { test_key(ctn::keys::escape, SDL_SCANCODE_ESCAPE); }

    SECTION("Backspace")
    {
      test_key(ctn::keys::backspace, SDL_SCANCODE_BACKSPACE);
    }

    SECTION("Tab") { test_key(ctn::keys::tab, SDL_SCANCODE_TAB); }

    SECTION("Caps") { test_key(ctn::keys::caps_lock, SDL_SCANCODE_CAPSLOCK); }
  }

  SECTION("Modifiers")
  {
    SECTION("LSHIFT") { test_key(ctn::keys::left_shift, SDL_SCANCODE_LSHIFT); }

    SECTION("RSHIFT") { test_key(ctn::keys::right_shift, SDL_SCANCODE_RSHIFT); }

    SECTION("LCTRL") { test_key(ctn::keys::left_ctrl, SDL_SCANCODE_LCTRL); }

    SECTION("RCTRL") { test_key(ctn::keys::right_ctrl, SDL_SCANCODE_RCTRL); }

    SECTION("LALT") { test_key(ctn::keys::left_alt, SDL_SCANCODE_LALT); }

    SECTION("RALT") { test_key(ctn::keys::right_alt, SDL_SCANCODE_RALT); }

    SECTION("LGUI") { test_key(ctn::keys::left_gui, SDL_SCANCODE_LGUI); }

    SECTION("RGUI") { test_key(ctn::keys::right_gui, SDL_SCANCODE_RGUI); }
  }
}

TEST_CASE("key(CZString)", "[key]")
{
  SECTION("Null string")
  {
    ctn::key key{nullptr};
    CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
    CHECK(key.keycode() == SDLK_UNKNOWN);
  }
  SECTION("Bad name")
  {
    ctn::key key{"someunknownkey"};
    CHECK(key.scancode() == SDL_SCANCODE_UNKNOWN);
    CHECK(key.keycode() == SDLK_UNKNOWN);
  }
  SECTION("Good name")
  {
    ctn::key key{"A"};
    CHECK(key.scancode() == SDL_SCANCODE_A);
    CHECK(key.keycode() == SDLK_a);
  }
}

TEST_CASE("key::set(SDL_Scancode)", "[key]")
{
  ctn::key key;

  const auto scancode = SDL_SCANCODE_A;
  key.set(scancode);

  CHECK(key.scancode() == scancode);
}

TEST_CASE("key::set(SDL_Keycode)", "[key]")
{
  ctn::key key;

  const auto keycode = SDLK_y;
  key.set(keycode);

  CHECK(key.keycode() == keycode);
}

TEST_CASE("key::name", "[key]")
{
  SECTION("Known key")
  {
    ctn::key key{SDL_SCANCODE_ESCAPE};
    CHECK(key.name() == "Escape");
  }

  SECTION("Unknown key")
  {
    ctn::key key;
    CHECK(key.name().empty());
  }
}

TEST_CASE("key::unknown", "[key]")
{
  SECTION("Known key")
  {
    ctn::key key{SDL_SCANCODE_ESCAPE};
    CHECK(!key.unknown());
  }

  SECTION("Unknown key")
  {
    ctn::key key;
    CHECK(key.unknown());

    key.set(SDL_SCANCODE_UNKNOWN);
    CHECK(key.unknown());
  }
}

TEST_CASE("key::scancode", "[key]")
{
  const ctn::key key{SDL_SCANCODE_7};
  CHECK(key.scancode() == SDL_SCANCODE_7);
}

TEST_CASE("key::keycode", "[key]")
{
  const ctn::key key{SDLK_CAPSLOCK};
  CHECK(key.keycode() == SDLK_CAPSLOCK);
}

TEST_CASE("key to SDL_Scancode", "[key]")
{
  const auto scancode = SDL_SCANCODE_G;
  const ctn::key key{scancode};

  const auto copy = static_cast<SDL_Scancode>(key);

  CHECK(copy == scancode);
}

TEST_CASE("key to SDL_Keycode", "[key]")
{
  const auto keycode = SDLK_q;
  const ctn::key key{keycode};

  const auto copy = static_cast<SDL_Keycode>(key);

  CHECK(copy == keycode);
}

TEST_CASE("key::operator==", "[key]")
{
  SECTION("Equal")
  {
    const ctn::key first{SDLK_w};
    const ctn::key second{SDLK_w};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Not equal")
  {
    const ctn::key first{SDLK_v};
    const ctn::key second{SDLK_y};
    CHECK(!(first == second));
    CHECK(!(second == first));
  }

  SECTION("Reflexivity")
  {
    const ctn::key key{SDL_SCANCODE_I};
    CHECK(key == key);
  }
}

TEST_CASE("key::operator!=", "[key]")
{
  SECTION("Equal")
  {
    const ctn::key first{SDLK_n};
    const ctn::key second{SDLK_n};
    CHECK(!(first != second));
    CHECK(!(second != first));
  }

  SECTION("Not equal")
  {
    const ctn::key first{SDLK_l};
    const ctn::key second{SDLK_a};
    CHECK(first != second);
    CHECK(second != first);
  }
}
