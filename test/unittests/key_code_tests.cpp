#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "key_code.hpp"
#include "log.hpp"

TEST_CASE("key_code default value", "[key_code]")
{
  cen::key_code code;
  CHECK(code.get() == SDLK_UNKNOWN);
}

TEST_CASE("key_code::key_code(SDL_Keycode)", "[key_code]")
{
  const auto expected = SDL_SCANCODE_BACKSPACE;
  const cen::key_code code{expected};
  CHECK(code.get() == SDL_GetKeyFromScancode(expected));
}

TEST_CASE("key_code::key_code(SDL_Scancode)", "[key_code]")
{
  const auto expected = SDL_SCANCODE_C;
  const cen::key_code code{expected};
  CHECK(code.get() == SDLK_c);
}

TEST_CASE("key_code::key_code(czstring)", "[key_code]")
{
  SECTION("Good name")
  {
    cen::czstring name = "5";
    const cen::key_code code{name};
    CHECK(code.get() == SDLK_5);
    CHECK(code.name() == name);
  }
  SECTION("Bad name")
  {
    cen::czstring bad = "foobar";
    const cen::key_code code{bad};
    CHECK(code.get() == SDLK_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("key_code::operator=(SDL_Keycode)", "[key_code]")
{
  cen::key_code code;

  const auto expected = SDLK_n;
  code = expected;

  CHECK(code.get() == expected);
}

TEST_CASE("key_code::operator=(SDL_Scancode)", "[key_code]")
{
  cen::key_code code;

  const auto expected = SDL_SCANCODE_T;
  code = expected;

  CHECK(code.get() == SDLK_t);
}

TEST_CASE("key_code::operator=(czstring)", "[key_code]")
{
  SECTION("Good name")
  {
    cen::key_code code;

    const auto name = "Tab";
    code = name;

    CHECK(code.get() == SDLK_TAB);
    CHECK(code.name() == "Tab");
  }

  SECTION("Bad name")
  {
    cen::key_code code;

    const auto name = "qwerty";
    code = name;

    CHECK(code.get() == SDLK_UNKNOWN);
    CHECK(code.unknown());
  }
}

TEST_CASE("key_code::unknown", "[key_code]")
{
  cen::key_code code;
  CHECK(code.unknown());

  code = SDLK_l;
  CHECK(!code.unknown());
}

TEST_CASE("key_code::name", "[key_code]")
{
  cen::key_code code;
  CHECK(code.name().empty());

  code = SDLK_z;
  CHECK(code.name() == "Z");
}

TEST_CASE("key_code::get", "[key_code]")
{
  cen::key_code code;
  CHECK(code.get() == SDLK_UNKNOWN);

  code = SDLK_8;
  CHECK(code.get() == SDLK_8);
}

TEST_CASE("key_code::operator SDL_Keycode", "[key_code]")
{
  cen::key_code code;

  const auto unknown = static_cast<SDL_Keycode>(code);
  CHECK(unknown == SDLK_UNKNOWN);

  code = SDLK_f;

  const auto f = static_cast<SDL_Keycode>(code);
  CHECK(f == SDLK_f);
}

TEST_CASE("key_code::operator SDL_Scancode", "[key_code]")
{
  cen::key_code code;

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
    const cen::key_code fst;
    const cen::key_code snd;
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Same assigned scan codes")
  {
    const cen::key_code fst{SDLK_i};
    const cen::key_code snd{fst};
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Not same")
  {
    const cen::key_code fst{SDLK_e};
    const cen::key_code snd{SDLK_y};
    CHECK_FALSE(fst == snd);
    CHECK_FALSE(snd == fst);
  }
}

TEST_CASE("operator!=(const key_code&, const key_code&)", "[key_code]")
{
  SECTION("Default initialized scan codes")
  {
    const cen::key_code fst;
    const cen::key_code snd;
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Same assigned scan codes")
  {
    const cen::key_code fst{SDLK_w};
    const cen::key_code snd{fst};
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Not same")
  {
    const cen::key_code fst{SDLK_a};
    const cen::key_code snd{SDLK_5};
    CHECK(fst != snd);
    CHECK(snd != fst);
  }
}

TEST_CASE("key_code constants", "[key_code]")
{
  const auto test_key = [](const cen::key_code& constant,
                           SDL_KeyCode keycode) noexcept {
    const cen::key_code code{keycode};
    CHECK(constant == code);
  };

  SECTION("Unknown") { test_key(cen::keycodes::unknown, SDLK_UNKNOWN); }

  SECTION("Alphabetical keys")
  {
    SECTION("a") { test_key(cen::keycodes::a, SDLK_a); }

    SECTION("b") { test_key(cen::keycodes::b, SDLK_b); }

    SECTION("c") { test_key(cen::keycodes::c, SDLK_c); }

    SECTION("d") { test_key(cen::keycodes::d, SDLK_d); }

    SECTION("e") { test_key(cen::keycodes::e, SDLK_e); }

    SECTION("f") { test_key(cen::keycodes::f, SDLK_f); }

    SECTION("g") { test_key(cen::keycodes::g, SDLK_g); }

    SECTION("h") { test_key(cen::keycodes::h, SDLK_h); }

    SECTION("i") { test_key(cen::keycodes::i, SDLK_i); }

    SECTION("j") { test_key(cen::keycodes::j, SDLK_j); }

    SECTION("k") { test_key(cen::keycodes::k, SDLK_k); }

    SECTION("l") { test_key(cen::keycodes::l, SDLK_l); }

    SECTION("m") { test_key(cen::keycodes::m, SDLK_m); }

    SECTION("n") { test_key(cen::keycodes::n, SDLK_n); }

    SECTION("o") { test_key(cen::keycodes::o, SDLK_o); }

    SECTION("p") { test_key(cen::keycodes::p, SDLK_p); }

    SECTION("q") { test_key(cen::keycodes::q, SDLK_q); }

    SECTION("r") { test_key(cen::keycodes::r, SDLK_r); }

    SECTION("s") { test_key(cen::keycodes::s, SDLK_s); }

    SECTION("t") { test_key(cen::keycodes::t, SDLK_t); }

    SECTION("u") { test_key(cen::keycodes::u, SDLK_u); }

    SECTION("v") { test_key(cen::keycodes::v, SDLK_v); }

    SECTION("w") { test_key(cen::keycodes::w, SDLK_w); }

    SECTION("x") { test_key(cen::keycodes::x, SDLK_x); }

    SECTION("y") { test_key(cen::keycodes::y, SDLK_y); }

    SECTION("z") { test_key(cen::keycodes::z, SDLK_z); }
  }

  SECTION("Numerical keys")
  {
    SECTION("1") { test_key(cen::keycodes::one, SDLK_1); }

    SECTION("2") { test_key(cen::keycodes::two, SDLK_2); }

    SECTION("3") { test_key(cen::keycodes::three, SDLK_3); }

    SECTION("4") { test_key(cen::keycodes::four, SDLK_4); }

    SECTION("5") { test_key(cen::keycodes::five, SDLK_5); }

    SECTION("6") { test_key(cen::keycodes::six, SDLK_6); }

    SECTION("7") { test_key(cen::keycodes::seven, SDLK_7); }

    SECTION("8") { test_key(cen::keycodes::eight, SDLK_8); }

    SECTION("9") { test_key(cen::keycodes::nine, SDLK_9); }

    SECTION("0") { test_key(cen::keycodes::zero, SDLK_0); }
  }

  SECTION("Function keys")
  {
    SECTION("F1") { test_key(cen::keycodes::f1, SDLK_F1); }

    SECTION("F2") { test_key(cen::keycodes::f2, SDLK_F2); }

    SECTION("F3") { test_key(cen::keycodes::f3, SDLK_F3); }

    SECTION("F4") { test_key(cen::keycodes::f4, SDLK_F4); }

    SECTION("F5") { test_key(cen::keycodes::f5, SDLK_F5); }

    SECTION("F6") { test_key(cen::keycodes::f6, SDLK_F6); }

    SECTION("F7") { test_key(cen::keycodes::f7, SDLK_F7); }

    SECTION("F8") { test_key(cen::keycodes::f8, SDLK_F8); }

    SECTION("F9") { test_key(cen::keycodes::f9, SDLK_F9); }

    SECTION("F10") { test_key(cen::keycodes::f10, SDLK_F10); }

    SECTION("F11") { test_key(cen::keycodes::f11, SDLK_F11); }

    SECTION("F12") { test_key(cen::keycodes::f12, SDLK_F12); }
  }

  SECTION("Arrow keys")
  {
    SECTION("Left") { test_key(cen::keycodes::left, SDLK_LEFT); }

    SECTION("Right") { test_key(cen::keycodes::right, SDLK_RIGHT); }

    SECTION("Up") { test_key(cen::keycodes::up, SDLK_UP); }

    SECTION("Down") { test_key(cen::keycodes::down, SDLK_DOWN); }
  }

  SECTION("Special action keys")
  {
    SECTION("Space") { test_key(cen::keycodes::space, SDLK_SPACE); }

    SECTION("Enter") { test_key(cen::keycodes::enter, SDLK_RETURN); }

    SECTION("Escape") { test_key(cen::keycodes::escape, SDLK_ESCAPE); }

    SECTION("Backspace") { test_key(cen::keycodes::backspace, SDLK_BACKSPACE); }

    SECTION("Tab") { test_key(cen::keycodes::tab, SDLK_TAB); }

    SECTION("Caps") { test_key(cen::keycodes::caps_lock, SDLK_CAPSLOCK); }
  }

  SECTION("Modifiers")
  {
    SECTION("LSHIFT") { test_key(cen::keycodes::left_shift, SDLK_LSHIFT); }

    SECTION("RSHIFT") { test_key(cen::keycodes::right_shift, SDLK_RSHIFT); }

    SECTION("LCTRL") { test_key(cen::keycodes::left_ctrl, SDLK_LCTRL); }

    SECTION("RCTRL") { test_key(cen::keycodes::right_ctrl, SDLK_RCTRL); }

    SECTION("LALT") { test_key(cen::keycodes::left_alt, SDLK_LALT); }

    SECTION("RALT") { test_key(cen::keycodes::right_alt, SDLK_RALT); }

    SECTION("LGUI") { test_key(cen::keycodes::left_gui, SDLK_LGUI); }

    SECTION("RGUI") { test_key(cen::keycodes::right_gui, SDLK_RGUI); }
  }
}

TEST_CASE("key_code to_string", "[key_code]")
{
  const cen::key_code kc{SDLK_r};
  cen::log::put(cen::to_string(kc));
}

TEST_CASE("key_code stream operator", "[key_code]")
{
  const cen::key_code kc{SDLK_q};
  std::cout << "COUT: " << kc << '\n';
}