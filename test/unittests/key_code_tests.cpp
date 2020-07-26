#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "key_code.hpp"
#include "log.hpp"

TEST_CASE("key_code default value", "[key_code]")
{
  ctn::key_code code;
  CHECK(code.get() == SDLK_UNKNOWN);
}

TEST_CASE("key_code::key_code(SDL_Keycode)", "[key_code]")
{
  const auto expected = SDL_SCANCODE_BACKSPACE;
  const ctn::key_code code{expected};
  CHECK(code.get() == SDL_GetKeyFromScancode(expected));
}

TEST_CASE("key_code::key_code(SDL_Scancode)", "[key_code]")
{
  const auto expected = SDL_SCANCODE_C;
  const ctn::key_code code{expected};
  CHECK(code.get() == SDLK_c);
}

TEST_CASE("key_code::key_code(czstring)", "[key_code]")
{
  SECTION("Good name")
  {
    ctn::czstring name = "5";
    const ctn::key_code code{name};
    CHECK(code.get() == SDLK_5);
    CHECK(code.name() == name);
  }
  SECTION("Bad name")
  {
    ctn::czstring bad = "foobar";
    const ctn::key_code code{bad};
    CHECK(code.get() == SDLK_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("key_code::operator=(SDL_Keycode)", "[key_code]")
{
  ctn::key_code code;

  const auto expected = SDLK_n;
  code = expected;

  CHECK(code.get() == expected);
}

TEST_CASE("key_code::operator=(SDL_Scancode)", "[key_code]")
{
  ctn::key_code code;

  const auto expected = SDL_SCANCODE_T;
  code = expected;

  CHECK(code.get() == SDLK_t);
}

TEST_CASE("key_code::operator=(czstring)", "[key_code]")
{
  SECTION("Good name")
  {
    ctn::key_code code;

    const auto name = "Tab";
    code = name;

    CHECK(code.get() == SDLK_TAB);
    CHECK(code.name() == "Tab");
  }

  SECTION("Bad name")
  {
    ctn::key_code code;

    const auto name = "qwerty";
    code = name;

    CHECK(code.get() == SDLK_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("key_code::unknown", "[key_code]")
{
  ctn::key_code code;
  CHECK(code.unknown());

  code = SDLK_l;
  CHECK(!code.unknown());
}

TEST_CASE("key_code::name", "[key_code]")
{
  ctn::key_code code;
  CHECK(code.name().empty());

  code = SDLK_z;
  CHECK(code.name() == "Z");
}

TEST_CASE("key_code::get", "[key_code]")
{
  ctn::key_code code;
  CHECK(code.get() == SDLK_UNKNOWN);

  code = SDLK_8;
  CHECK(code.get() == SDLK_8);
}

TEST_CASE("key_code::operator SDL_Keycode", "[key_code]")
{
  ctn::key_code code;

  const auto unknown = static_cast<SDL_Keycode>(code);
  CHECK(unknown == SDLK_UNKNOWN);

  code = SDLK_f;

  const auto f = static_cast<SDL_Keycode>(code);
  CHECK(f == SDLK_f);
}

TEST_CASE("key_code::operator SDL_Scancode", "[key_code]")
{
  ctn::key_code code;

  const auto unknown = static_cast<SDL_Scancode>(code);
  CHECK(unknown == SDL_SCANCODE_UNKNOWN);

  code = SDLK_RSHIFT;

  const auto rshift = static_cast<SDL_Scancode>(code);
  CHECK(rshift == SDL_SCANCODE_RSHIFT);
}

TEST_CASE("operator==(const key_code&, const key_code&)", "[key_code]")
{
  SECTION("Default initialized scan codes")
  {
    const ctn::key_code fst;
    const ctn::key_code snd;
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Same assigned scan codes")
  {
    const ctn::key_code fst{SDLK_i};
    const ctn::key_code snd{fst};
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Not same")
  {
    const ctn::key_code fst{SDLK_e};
    const ctn::key_code snd{SDLK_y};
    CHECK_FALSE(fst == snd);
    CHECK_FALSE(snd == fst);
  }
}

TEST_CASE("operator!=(const key_code&, const key_code&)", "[key_code]")
{
  SECTION("Default initialized scan codes")
  {
    const ctn::key_code fst;
    const ctn::key_code snd;
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Same assigned scan codes")
  {
    const ctn::key_code fst{SDLK_w};
    const ctn::key_code snd{fst};
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Not same")
  {
    const ctn::key_code fst{SDLK_a};
    const ctn::key_code snd{SDLK_5};
    CHECK(fst != snd);
    CHECK(snd != fst);
  }
}

TEST_CASE("key_code constants", "[key_code]")
{
  const auto test_key = [](const ctn::key_code& constant,
                           SDL_KeyCode keycode) noexcept {
    const ctn::key_code code{keycode};
    CHECK(constant == code);
  };

  SECTION("Unknown") { test_key(ctn::keycodes::unknown, SDLK_UNKNOWN); }

  SECTION("Alphabetical keys")
  {
    SECTION("a") { test_key(ctn::keycodes::a, SDLK_a); }

    SECTION("b") { test_key(ctn::keycodes::b, SDLK_b); }

    SECTION("c") { test_key(ctn::keycodes::c, SDLK_c); }

    SECTION("d") { test_key(ctn::keycodes::d, SDLK_d); }

    SECTION("e") { test_key(ctn::keycodes::e, SDLK_e); }

    SECTION("f") { test_key(ctn::keycodes::f, SDLK_f); }

    SECTION("g") { test_key(ctn::keycodes::g, SDLK_g); }

    SECTION("h") { test_key(ctn::keycodes::h, SDLK_h); }

    SECTION("i") { test_key(ctn::keycodes::i, SDLK_i); }

    SECTION("j") { test_key(ctn::keycodes::j, SDLK_j); }

    SECTION("k") { test_key(ctn::keycodes::k, SDLK_k); }

    SECTION("l") { test_key(ctn::keycodes::l, SDLK_l); }

    SECTION("m") { test_key(ctn::keycodes::m, SDLK_m); }

    SECTION("n") { test_key(ctn::keycodes::n, SDLK_n); }

    SECTION("o") { test_key(ctn::keycodes::o, SDLK_o); }

    SECTION("p") { test_key(ctn::keycodes::p, SDLK_p); }

    SECTION("q") { test_key(ctn::keycodes::q, SDLK_q); }

    SECTION("r") { test_key(ctn::keycodes::r, SDLK_r); }

    SECTION("s") { test_key(ctn::keycodes::s, SDLK_s); }

    SECTION("t") { test_key(ctn::keycodes::t, SDLK_t); }

    SECTION("u") { test_key(ctn::keycodes::u, SDLK_u); }

    SECTION("v") { test_key(ctn::keycodes::v, SDLK_v); }

    SECTION("w") { test_key(ctn::keycodes::w, SDLK_w); }

    SECTION("x") { test_key(ctn::keycodes::x, SDLK_x); }

    SECTION("y") { test_key(ctn::keycodes::y, SDLK_y); }

    SECTION("z") { test_key(ctn::keycodes::z, SDLK_z); }
  }

  SECTION("Numerical keys")
  {
    SECTION("1") { test_key(ctn::keycodes::one, SDLK_1); }

    SECTION("2") { test_key(ctn::keycodes::two, SDLK_2); }

    SECTION("3") { test_key(ctn::keycodes::three, SDLK_3); }

    SECTION("4") { test_key(ctn::keycodes::four, SDLK_4); }

    SECTION("5") { test_key(ctn::keycodes::five, SDLK_5); }

    SECTION("6") { test_key(ctn::keycodes::six, SDLK_6); }

    SECTION("7") { test_key(ctn::keycodes::seven, SDLK_7); }

    SECTION("8") { test_key(ctn::keycodes::eight, SDLK_8); }

    SECTION("9") { test_key(ctn::keycodes::nine, SDLK_9); }

    SECTION("0") { test_key(ctn::keycodes::zero, SDLK_0); }
  }

  SECTION("Function keys")
  {
    SECTION("F1") { test_key(ctn::keycodes::f1, SDLK_F1); }

    SECTION("F2") { test_key(ctn::keycodes::f2, SDLK_F2); }

    SECTION("F3") { test_key(ctn::keycodes::f3, SDLK_F3); }

    SECTION("F4") { test_key(ctn::keycodes::f4, SDLK_F4); }

    SECTION("F5") { test_key(ctn::keycodes::f5, SDLK_F5); }

    SECTION("F6") { test_key(ctn::keycodes::f6, SDLK_F6); }

    SECTION("F7") { test_key(ctn::keycodes::f7, SDLK_F7); }

    SECTION("F8") { test_key(ctn::keycodes::f8, SDLK_F8); }

    SECTION("F9") { test_key(ctn::keycodes::f9, SDLK_F9); }

    SECTION("F10") { test_key(ctn::keycodes::f10, SDLK_F10); }

    SECTION("F11") { test_key(ctn::keycodes::f11, SDLK_F11); }

    SECTION("F12") { test_key(ctn::keycodes::f12, SDLK_F12); }
  }

  SECTION("Arrow keys")
  {
    SECTION("Left") { test_key(ctn::keycodes::left, SDLK_LEFT); }

    SECTION("Right") { test_key(ctn::keycodes::right, SDLK_RIGHT); }

    SECTION("Up") { test_key(ctn::keycodes::up, SDLK_UP); }

    SECTION("Down") { test_key(ctn::keycodes::down, SDLK_DOWN); }
  }

  SECTION("Special action keys")
  {
    SECTION("Space") { test_key(ctn::keycodes::space, SDLK_SPACE); }

    SECTION("Enter") { test_key(ctn::keycodes::enter, SDLK_RETURN); }

    SECTION("Escape") { test_key(ctn::keycodes::escape, SDLK_ESCAPE); }

    SECTION("Backspace") { test_key(ctn::keycodes::backspace, SDLK_BACKSPACE); }

    SECTION("Tab") { test_key(ctn::keycodes::tab, SDLK_TAB); }

    SECTION("Caps") { test_key(ctn::keycodes::caps_lock, SDLK_CAPSLOCK); }
  }

  SECTION("Modifiers")
  {
    SECTION("LSHIFT") { test_key(ctn::keycodes::left_shift, SDLK_LSHIFT); }

    SECTION("RSHIFT") { test_key(ctn::keycodes::right_shift, SDLK_RSHIFT); }

    SECTION("LCTRL") { test_key(ctn::keycodes::left_ctrl, SDLK_LCTRL); }

    SECTION("RCTRL") { test_key(ctn::keycodes::right_ctrl, SDLK_RCTRL); }

    SECTION("LALT") { test_key(ctn::keycodes::left_alt, SDLK_LALT); }

    SECTION("RALT") { test_key(ctn::keycodes::right_alt, SDLK_RALT); }

    SECTION("LGUI") { test_key(ctn::keycodes::left_gui, SDLK_LGUI); }

    SECTION("RGUI") { test_key(ctn::keycodes::right_gui, SDLK_RGUI); }
  }
}

TEST_CASE("key_code to_string", "[key_code]")
{
  const ctn::key_code kc{SDLK_r};
  ctn::log::put(ctn::log::category::test, ctn::to_string(kc));
}

TEST_CASE("key_code stream operator", "[key_code]")
{
  const ctn::key_code kc{SDLK_q};
  std::cout << "COUT: " << kc << '\n';
}