#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "log.hpp"
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

  const auto unknown = static_cast<SDL_KeyCode>(code);
  CHECK(unknown == SDLK_UNKNOWN);

  code = SDL_SCANCODE_H;
  const auto h = static_cast<SDL_KeyCode>(code);
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

TEST_CASE("operator!=(const scan_code&, const scan_code&)", "[scan_code]")
{
  SECTION("Default initialized scan codes")
  {
    const ctn::scan_code fst;
    const ctn::scan_code snd;
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Same assigned scan codes")
  {
    const ctn::scan_code fst{SDL_SCANCODE_U};
    const ctn::scan_code snd{fst};
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Not same")
  {
    const ctn::scan_code fst{SDL_SCANCODE_E};
    const ctn::scan_code snd{SDL_SCANCODE_G};
    CHECK(fst != snd);
    CHECK(snd != fst);
  }
}

TEST_CASE("scan_code constants", "[scan_code]")
{
  const auto test_key = [](const ctn::scan_code& constant,
                           SDL_Scancode scancode) noexcept {
    const ctn::scan_code code{scancode};
    CHECK(constant == code);
  };

  SECTION("Unknown")
  {
    test_key(ctn::scancodes::unknown, SDL_SCANCODE_UNKNOWN);
  }

  SECTION("Alphabetical keys")
  {
    SECTION("a") { test_key(ctn::scancodes::a, SDL_SCANCODE_A); }

    SECTION("b") { test_key(ctn::scancodes::b, SDL_SCANCODE_B); }

    SECTION("c") { test_key(ctn::scancodes::c, SDL_SCANCODE_C); }

    SECTION("d") { test_key(ctn::scancodes::d, SDL_SCANCODE_D); }

    SECTION("e") { test_key(ctn::scancodes::e, SDL_SCANCODE_E); }

    SECTION("f") { test_key(ctn::scancodes::f, SDL_SCANCODE_F); }

    SECTION("g") { test_key(ctn::scancodes::g, SDL_SCANCODE_G); }

    SECTION("h") { test_key(ctn::scancodes::h, SDL_SCANCODE_H); }

    SECTION("i") { test_key(ctn::scancodes::i, SDL_SCANCODE_I); }

    SECTION("j") { test_key(ctn::scancodes::j, SDL_SCANCODE_J); }

    SECTION("k") { test_key(ctn::scancodes::k, SDL_SCANCODE_K); }

    SECTION("l") { test_key(ctn::scancodes::l, SDL_SCANCODE_L); }

    SECTION("m") { test_key(ctn::scancodes::m, SDL_SCANCODE_M); }

    SECTION("n") { test_key(ctn::scancodes::n, SDL_SCANCODE_N); }

    SECTION("o") { test_key(ctn::scancodes::o, SDL_SCANCODE_O); }

    SECTION("p") { test_key(ctn::scancodes::p, SDL_SCANCODE_P); }

    SECTION("q") { test_key(ctn::scancodes::q, SDL_SCANCODE_Q); }

    SECTION("r") { test_key(ctn::scancodes::r, SDL_SCANCODE_R); }

    SECTION("s") { test_key(ctn::scancodes::s, SDL_SCANCODE_S); }

    SECTION("t") { test_key(ctn::scancodes::t, SDL_SCANCODE_T); }

    SECTION("u") { test_key(ctn::scancodes::u, SDL_SCANCODE_U); }

    SECTION("v") { test_key(ctn::scancodes::v, SDL_SCANCODE_V); }

    SECTION("w") { test_key(ctn::scancodes::w, SDL_SCANCODE_W); }

    SECTION("x") { test_key(ctn::scancodes::x, SDL_SCANCODE_X); }

    SECTION("y") { test_key(ctn::scancodes::y, SDL_SCANCODE_Y); }

    SECTION("z") { test_key(ctn::scancodes::z, SDL_SCANCODE_Z); }
  }

  SECTION("Numerical keys")
  {
    SECTION("1") { test_key(ctn::scancodes::one, SDL_SCANCODE_1); }

    SECTION("2") { test_key(ctn::scancodes::two, SDL_SCANCODE_2); }

    SECTION("3") { test_key(ctn::scancodes::three, SDL_SCANCODE_3); }

    SECTION("4") { test_key(ctn::scancodes::four, SDL_SCANCODE_4); }

    SECTION("5") { test_key(ctn::scancodes::five, SDL_SCANCODE_5); }

    SECTION("6") { test_key(ctn::scancodes::six, SDL_SCANCODE_6); }

    SECTION("7") { test_key(ctn::scancodes::seven, SDL_SCANCODE_7); }

    SECTION("8") { test_key(ctn::scancodes::eight, SDL_SCANCODE_8); }

    SECTION("9") { test_key(ctn::scancodes::nine, SDL_SCANCODE_9); }

    SECTION("0") { test_key(ctn::scancodes::zero, SDL_SCANCODE_0); }
  }

  SECTION("Function keys")
  {
    SECTION("F1") { test_key(ctn::scancodes::f1, SDL_SCANCODE_F1); }

    SECTION("F2") { test_key(ctn::scancodes::f2, SDL_SCANCODE_F2); }

    SECTION("F3") { test_key(ctn::scancodes::f3, SDL_SCANCODE_F3); }

    SECTION("F4") { test_key(ctn::scancodes::f4, SDL_SCANCODE_F4); }

    SECTION("F5") { test_key(ctn::scancodes::f5, SDL_SCANCODE_F5); }

    SECTION("F6") { test_key(ctn::scancodes::f6, SDL_SCANCODE_F6); }

    SECTION("F7") { test_key(ctn::scancodes::f7, SDL_SCANCODE_F7); }

    SECTION("F8") { test_key(ctn::scancodes::f8, SDL_SCANCODE_F8); }

    SECTION("F9") { test_key(ctn::scancodes::f9, SDL_SCANCODE_F9); }

    SECTION("F10") { test_key(ctn::scancodes::f10, SDL_SCANCODE_F10); }

    SECTION("F11") { test_key(ctn::scancodes::f11, SDL_SCANCODE_F11); }

    SECTION("F12") { test_key(ctn::scancodes::f12, SDL_SCANCODE_F12); }
  }

  SECTION("Arrow keys")
  {
    SECTION("Left") { test_key(ctn::scancodes::left, SDL_SCANCODE_LEFT); }

    SECTION("Right") { test_key(ctn::scancodes::right, SDL_SCANCODE_RIGHT); }

    SECTION("Up") { test_key(ctn::scancodes::up, SDL_SCANCODE_UP); }

    SECTION("Down") { test_key(ctn::scancodes::down, SDL_SCANCODE_DOWN); }
  }

  SECTION("Special action keys")
  {
    SECTION("Space") { test_key(ctn::scancodes::space, SDL_SCANCODE_SPACE); }

    SECTION("Enter") { test_key(ctn::scancodes::enter, SDL_SCANCODE_RETURN); }

    SECTION("Escape") { test_key(ctn::scancodes::escape, SDL_SCANCODE_ESCAPE); }

    SECTION("Backspace")
    {
      test_key(ctn::scancodes::backspace, SDL_SCANCODE_BACKSPACE);
    }

    SECTION("Tab") { test_key(ctn::scancodes::tab, SDL_SCANCODE_TAB); }

    SECTION("Caps")
    {
      test_key(ctn::scancodes::caps_lock, SDL_SCANCODE_CAPSLOCK);
    }
  }

  SECTION("Modifiers")
  {
    SECTION("LSHIFT")
    {
      test_key(ctn::scancodes::left_shift, SDL_SCANCODE_LSHIFT);
    }

    SECTION("RSHIFT")
    {
      test_key(ctn::scancodes::right_shift, SDL_SCANCODE_RSHIFT);
    }

    SECTION("LCTRL")
    {
      test_key(ctn::scancodes::left_ctrl, SDL_SCANCODE_LCTRL);
    }

    SECTION("RCTRL")
    {
      test_key(ctn::scancodes::right_ctrl, SDL_SCANCODE_RCTRL);
    }

    SECTION("LALT") { test_key(ctn::scancodes::left_alt, SDL_SCANCODE_LALT); }

    SECTION("RALT") { test_key(ctn::scancodes::right_alt, SDL_SCANCODE_RALT); }

    SECTION("LGUI") { test_key(ctn::scancodes::left_gui, SDL_SCANCODE_LGUI); }

    SECTION("RGUI") { test_key(ctn::scancodes::right_gui, SDL_SCANCODE_RGUI); }
  }
}

TEST_CASE("scan_code to_string", "[scan_code]")
{
  const ctn::scan_code sc{SDLK_r};
  ctn::log::put(ctn::log::category::test, ctn::to_string(sc));
}

TEST_CASE("scan_code stream operator", "[scan_code]")
{
  const ctn::scan_code sc{SDL_SCANCODE_P};
  std::cout << "COUT: " << sc << '\n';
}