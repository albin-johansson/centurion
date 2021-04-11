#include <gtest/gtest.h>

#include <iostream>

#include "input/scan_code.hpp"
#include "misc/log.hpp"
#include "serialization_utils.hpp"

TEST(ScanCode, DefaultValue)
{
  const cen::scan_code code;
  EXPECT_EQ(cen::scancodes::unknown, code);
  EXPECT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
}

TEST(ScanCode, ScancodeConstructor)
{
  const cen::scan_code code{SDL_SCANCODE_W};
  EXPECT_EQ(SDL_SCANCODE_W, code.get());
}

TEST(ScanCode, KeycodeConstructor)
{
  const cen::scan_code code{SDLK_LSHIFT};
  EXPECT_EQ(SDL_GetScancodeFromKey(SDLK_LSHIFT), code.get());
}

TEST(ScanCode, StringConstructor)
{
  using namespace std::string_literals;

  {  // Good name
    const auto name = "Escape"s;
    const cen::scan_code code{name};

    EXPECT_EQ(cen::scancodes::escape, code);
    EXPECT_EQ(SDL_SCANCODE_ESCAPE, code.get());
    EXPECT_EQ(name, code.name());
  }

  {  // Bad name
    const cen::scan_code code{"foobar"};
    EXPECT_EQ(cen::scancodes::unknown, code);
    EXPECT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
    EXPECT_TRUE(code.name().empty());
  }
}

TEST(ScanCode, SDLScancodeAssignmentOperator)
{
  cen::scan_code code;
  code = SDL_SCANCODE_B;

  EXPECT_EQ(cen::scancodes::b, code);
  EXPECT_EQ(SDL_SCANCODE_B, code.get());
}

TEST(ScanCode, SDLKeycodeAssignmentOperator)
{
  cen::scan_code code;
  code = SDLK_q;

  EXPECT_EQ(SDL_GetScancodeFromKey(SDLK_q), code.get());
}

TEST(ScanCode, StringAssignmentOperator)
{
  using namespace std::string_literals;

  {  // Good name
    const auto name = "A"s;
    cen::scan_code code;
    code = name;

    EXPECT_EQ(cen::scancodes::a, code);
    EXPECT_EQ(SDL_SCANCODE_A, code.get());
    EXPECT_EQ(name, code.name());
  }

  {  // Bad name
    cen::scan_code code;
    code = "qwerty";

    EXPECT_EQ(cen::scancodes::unknown, code);
    EXPECT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
    EXPECT_TRUE(code.name().empty());
  }
}

TEST(ScanCode, Count)
{
  EXPECT_EQ(static_cast<int>(SDL_NUM_SCANCODES), cen::scan_code::count());
}

TEST(ScanCode, Unknown)
{
  cen::scan_code code;
  EXPECT_TRUE(code.unknown());

  code = SDL_SCANCODE_O;
  EXPECT_FALSE(code.unknown());
}

TEST(ScanCode, Name)
{
  cen::scan_code code;
  EXPECT_TRUE(code.name().empty());

  code = SDL_SCANCODE_L;
  EXPECT_EQ("L", code.name());
}

TEST(ScanCode, Get)
{
  cen::scan_code code;
  EXPECT_EQ(SDL_SCANCODE_UNKNOWN, code.get());

  code = SDL_SCANCODE_Z;
  EXPECT_EQ(SDL_SCANCODE_Z, code.get());
}

TEST(KeyCode, ToKeyCode)
{
  const auto code = cen::scancodes::y;
  const auto keycode = code.to_key_code();
  EXPECT_EQ(SDL_GetKeyFromScancode(code.get()), keycode);
}

TEST(ScanCode, SDLScancodeConversion)
{
  cen::scan_code code;

  const auto unknown = static_cast<SDL_Scancode>(code);
  EXPECT_EQ(unknown, code.get());

  code = SDL_SCANCODE_Z;

  const auto z = static_cast<SDL_Scancode>(code);
  EXPECT_EQ(z, code.get());
}

TEST(ScanCode, SDLKeycodeConversion)
{
  cen::scan_code code;

  const auto unknown = static_cast<SDL_KeyCode>(code);
  EXPECT_EQ(SDLK_UNKNOWN, unknown);

  code = SDL_SCANCODE_H;

  const auto h = static_cast<SDL_KeyCode>(code);
  EXPECT_EQ(SDLK_h, h);
}

TEST(ScanCode, EqualityOperator)
{
  {
    const cen::scan_code code;
    EXPECT_EQ(code, code);
  }

  {
    const cen::scan_code fst{SDL_SCANCODE_W};
    const cen::scan_code snd{fst};
    EXPECT_EQ(fst, snd);
    EXPECT_EQ(snd, fst);
  }

  {
    const cen::scan_code fst{SDL_SCANCODE_P};
    const cen::scan_code snd{SDL_SCANCODE_X};
    EXPECT_FALSE(fst == snd);
    EXPECT_FALSE(snd == fst);
  }
}

TEST(ScanCode, InequalityOperator)
{
  {
    const cen::scan_code code;
    EXPECT_FALSE(code != code);
  }

  {
    const cen::scan_code fst{SDL_SCANCODE_W};
    const cen::scan_code snd{fst};
    EXPECT_FALSE(fst != snd);
    EXPECT_FALSE(snd != fst);
  }

  {
    const cen::scan_code fst{SDL_SCANCODE_P};
    const cen::scan_code snd{SDL_SCANCODE_X};
    EXPECT_NE(fst, snd);
    EXPECT_NE(snd, fst);
  }
}

TEST(ScanCode, ToString)
{
  cen::log::put(cen::to_string(cen::scancodes::x));
}

TEST(ScanCode, StreamOperator)
{
  std::cout << "COUT: " << cen::scancodes::x << '\n';
}

TEST(ScanCode, Constants)
{
  EXPECT_EQ(SDL_SCANCODE_UNKNOWN, cen::scancodes::unknown);

  // Alphabetical keys
  EXPECT_EQ(SDL_SCANCODE_A, cen::scancodes::a);
  EXPECT_EQ(SDL_SCANCODE_B, cen::scancodes::b);
  EXPECT_EQ(SDL_SCANCODE_C, cen::scancodes::c);
  EXPECT_EQ(SDL_SCANCODE_D, cen::scancodes::d);
  EXPECT_EQ(SDL_SCANCODE_E, cen::scancodes::e);
  EXPECT_EQ(SDL_SCANCODE_F, cen::scancodes::f);
  EXPECT_EQ(SDL_SCANCODE_G, cen::scancodes::g);
  EXPECT_EQ(SDL_SCANCODE_H, cen::scancodes::h);
  EXPECT_EQ(SDL_SCANCODE_I, cen::scancodes::i);
  EXPECT_EQ(SDL_SCANCODE_J, cen::scancodes::j);
  EXPECT_EQ(SDL_SCANCODE_K, cen::scancodes::k);
  EXPECT_EQ(SDL_SCANCODE_L, cen::scancodes::l);
  EXPECT_EQ(SDL_SCANCODE_M, cen::scancodes::m);
  EXPECT_EQ(SDL_SCANCODE_N, cen::scancodes::n);
  EXPECT_EQ(SDL_SCANCODE_O, cen::scancodes::o);
  EXPECT_EQ(SDL_SCANCODE_P, cen::scancodes::p);
  EXPECT_EQ(SDL_SCANCODE_Q, cen::scancodes::q);
  EXPECT_EQ(SDL_SCANCODE_R, cen::scancodes::r);
  EXPECT_EQ(SDL_SCANCODE_S, cen::scancodes::s);
  EXPECT_EQ(SDL_SCANCODE_T, cen::scancodes::t);
  EXPECT_EQ(SDL_SCANCODE_U, cen::scancodes::u);
  EXPECT_EQ(SDL_SCANCODE_V, cen::scancodes::v);
  EXPECT_EQ(SDL_SCANCODE_W, cen::scancodes::w);
  EXPECT_EQ(SDL_SCANCODE_X, cen::scancodes::x);
  EXPECT_EQ(SDL_SCANCODE_Y, cen::scancodes::y);
  EXPECT_EQ(SDL_SCANCODE_Z, cen::scancodes::z);

  // Numerical keys
  EXPECT_EQ(SDL_SCANCODE_1, cen::scancodes::one);
  EXPECT_EQ(SDL_SCANCODE_2, cen::scancodes::two);
  EXPECT_EQ(SDL_SCANCODE_3, cen::scancodes::three);
  EXPECT_EQ(SDL_SCANCODE_4, cen::scancodes::four);
  EXPECT_EQ(SDL_SCANCODE_5, cen::scancodes::five);
  EXPECT_EQ(SDL_SCANCODE_6, cen::scancodes::six);
  EXPECT_EQ(SDL_SCANCODE_7, cen::scancodes::seven);
  EXPECT_EQ(SDL_SCANCODE_8, cen::scancodes::eight);
  EXPECT_EQ(SDL_SCANCODE_9, cen::scancodes::nine);
  EXPECT_EQ(SDL_SCANCODE_0, cen::scancodes::zero);

  // Function keys
  EXPECT_EQ(SDL_SCANCODE_F1, cen::scancodes::f1);
  EXPECT_EQ(SDL_SCANCODE_F2, cen::scancodes::f2);
  EXPECT_EQ(SDL_SCANCODE_F3, cen::scancodes::f3);
  EXPECT_EQ(SDL_SCANCODE_F4, cen::scancodes::f4);
  EXPECT_EQ(SDL_SCANCODE_F5, cen::scancodes::f5);
  EXPECT_EQ(SDL_SCANCODE_F6, cen::scancodes::f6);
  EXPECT_EQ(SDL_SCANCODE_F7, cen::scancodes::f7);
  EXPECT_EQ(SDL_SCANCODE_F8, cen::scancodes::f8);
  EXPECT_EQ(SDL_SCANCODE_F9, cen::scancodes::f9);
  EXPECT_EQ(SDL_SCANCODE_F10, cen::scancodes::f10);
  EXPECT_EQ(SDL_SCANCODE_F11, cen::scancodes::f11);
  EXPECT_EQ(SDL_SCANCODE_F12, cen::scancodes::f12);

  // Arrow keys
  EXPECT_EQ(SDL_SCANCODE_LEFT, cen::scancodes::left);
  EXPECT_EQ(SDL_SCANCODE_RIGHT, cen::scancodes::right);
  EXPECT_EQ(SDL_SCANCODE_UP, cen::scancodes::up);
  EXPECT_EQ(SDL_SCANCODE_DOWN, cen::scancodes::down);

  // Special keys
  EXPECT_EQ(SDL_SCANCODE_SPACE, cen::scancodes::space);
  EXPECT_EQ(SDL_SCANCODE_RETURN, cen::scancodes::enter);
  EXPECT_EQ(SDL_SCANCODE_ESCAPE, cen::scancodes::escape);
  EXPECT_EQ(SDL_SCANCODE_BACKSPACE, cen::scancodes::backspace);
  EXPECT_EQ(SDL_SCANCODE_TAB, cen::scancodes::tab);
  EXPECT_EQ(SDL_SCANCODE_CAPSLOCK, cen::scancodes::caps_lock);

  // Modifiers
  EXPECT_EQ(SDL_SCANCODE_LSHIFT, cen::scancodes::left_shift);
  EXPECT_EQ(SDL_SCANCODE_RSHIFT, cen::scancodes::right_shift);
  EXPECT_EQ(SDL_SCANCODE_LCTRL, cen::scancodes::left_ctrl);
  EXPECT_EQ(SDL_SCANCODE_RCTRL, cen::scancodes::right_ctrl);
  EXPECT_EQ(SDL_SCANCODE_LALT, cen::scancodes::left_alt);
  EXPECT_EQ(SDL_SCANCODE_RALT, cen::scancodes::right_alt);
  EXPECT_EQ(SDL_SCANCODE_LGUI, cen::scancodes::left_gui);
  EXPECT_EQ(SDL_SCANCODE_RGUI, cen::scancodes::right_gui);
}

TEST(ScanCode, Serialization)
{
  serialize_to("scan_code.binary", cen::scancodes::u);

  const auto code = serialize_from<cen::scan_code>("scan_code.binary");
  EXPECT_EQ(cen::scancodes::u, code);
}