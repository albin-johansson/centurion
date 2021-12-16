#include <gtest/gtest.h>

#include <iostream>

#include "core/logging.hpp"
#include "keyboard.hpp"
#include "serialization_utils.hpp"

TEST(ScanCode, DefaultValue)
{
  const cen::ScanCode code;
  ASSERT_EQ(cen::scancodes::unknown, code);
  ASSERT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
}

TEST(ScanCode, ScancodeConstructor)
{
  const cen::ScanCode code{SDL_SCANCODE_W};
  ASSERT_EQ(SDL_SCANCODE_W, code.get());
}

TEST(ScanCode, KeycodeConstructor)
{
  const cen::ScanCode code{SDLK_LSHIFT};
  ASSERT_EQ(SDL_GetScancodeFromKey(SDLK_LSHIFT), code.get());
}

TEST(ScanCode, StringConstructor)
{
  using namespace std::string_literals;

  {  // Good name
    const auto name = "Escape"s;
    const cen::ScanCode code{name};

    ASSERT_EQ(cen::scancodes::escape, code);
    ASSERT_EQ(SDL_SCANCODE_ESCAPE, code.get());
    ASSERT_EQ(name, code.GetName());
  }

  {  // Bad name
    const cen::ScanCode code{"foobar"};
    ASSERT_EQ(cen::scancodes::unknown, code);
    ASSERT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
    ASSERT_TRUE(code.GetName().empty());
  }
}

TEST(ScanCode, SDLScancodeAssignmentOperator)
{
  cen::ScanCode code;
  code = SDL_SCANCODE_B;

  ASSERT_EQ(cen::scancodes::b, code);
  ASSERT_EQ(SDL_SCANCODE_B, code.get());
}

TEST(ScanCode, SDLKeycodeAssignmentOperator)
{
  cen::ScanCode code;
  code = SDLK_q;

  ASSERT_EQ(SDL_GetScancodeFromKey(SDLK_q), code.get());
}

TEST(ScanCode, StringAssignmentOperator)
{
  using namespace std::string_literals;

  {  // Good name
    const auto name = "A"s;
    cen::ScanCode code;
    code = name;

    ASSERT_EQ(cen::scancodes::a, code);
    ASSERT_EQ(SDL_SCANCODE_A, code.get());
    ASSERT_EQ(name, code.GetName());
  }

  {  // Bad name
    cen::ScanCode code;
    code = "qwerty";

    ASSERT_EQ(cen::scancodes::unknown, code);
    ASSERT_EQ(SDL_SCANCODE_UNKNOWN, code.get());
    ASSERT_TRUE(code.GetName().empty());
  }
}

TEST(ScanCode, GetAmount)
{
  ASSERT_EQ(SDL_NUM_SCANCODES, cen::ScanCode::GetAmount());
}

TEST(ScanCode, IsUnknown)
{
  cen::ScanCode code;
  ASSERT_TRUE(code.IsUnknown());

  code = SDL_SCANCODE_O;
  ASSERT_FALSE(code.IsUnknown());
}

TEST(ScanCode, Name)
{
  cen::ScanCode code;
  ASSERT_TRUE(code.GetName().empty());

  code = SDL_SCANCODE_L;
  ASSERT_EQ("L", code.GetName());
}

TEST(ScanCode, Get)
{
  cen::ScanCode code;
  ASSERT_EQ(SDL_SCANCODE_UNKNOWN, code.get());

  code = SDL_SCANCODE_Z;
  ASSERT_EQ(SDL_SCANCODE_Z, code.get());
}

TEST(KeyCode, ToKeyCode)
{
  const auto code = cen::scancodes::y;
  const auto keycode = code.ToKeyCode();
  ASSERT_EQ(SDL_GetKeyFromScancode(code.get()), keycode);
}

TEST(ScanCode, EqualityOperator)
{
  {
    const cen::ScanCode code;
    ASSERT_EQ(code, code);
  }

  {
    const cen::ScanCode fst{SDL_SCANCODE_W};
    const cen::ScanCode snd{fst};
    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {
    const cen::ScanCode fst{SDL_SCANCODE_P};
    const cen::ScanCode snd{SDL_SCANCODE_X};
    ASSERT_FALSE(fst == snd);
    ASSERT_FALSE(snd == fst);
  }
}

TEST(ScanCode, InequalityOperator)
{
  {
    const cen::ScanCode code;
    ASSERT_FALSE(code != code);
  }

  {
    const cen::ScanCode fst{SDL_SCANCODE_W};
    const cen::ScanCode snd{fst};
    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {
    const cen::ScanCode fst{SDL_SCANCODE_P};
    const cen::ScanCode snd{SDL_SCANCODE_X};
    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(ScanCode, ToString)
{
  cen::log_info_raw(cen::to_string(cen::scancodes::x));
}

TEST(ScanCode, StreamOperator)
{
  std::clog << cen::scancodes::x << '\n';
}

TEST(ScanCode, Constants)
{
  ASSERT_EQ(SDL_SCANCODE_UNKNOWN, cen::scancodes::unknown);

  // Alphabetical keys
  ASSERT_EQ(SDL_SCANCODE_A, cen::scancodes::a);
  ASSERT_EQ(SDL_SCANCODE_B, cen::scancodes::b);
  ASSERT_EQ(SDL_SCANCODE_C, cen::scancodes::c);
  ASSERT_EQ(SDL_SCANCODE_D, cen::scancodes::d);
  ASSERT_EQ(SDL_SCANCODE_E, cen::scancodes::e);
  ASSERT_EQ(SDL_SCANCODE_F, cen::scancodes::f);
  ASSERT_EQ(SDL_SCANCODE_G, cen::scancodes::g);
  ASSERT_EQ(SDL_SCANCODE_H, cen::scancodes::h);
  ASSERT_EQ(SDL_SCANCODE_I, cen::scancodes::i);
  ASSERT_EQ(SDL_SCANCODE_J, cen::scancodes::j);
  ASSERT_EQ(SDL_SCANCODE_K, cen::scancodes::k);
  ASSERT_EQ(SDL_SCANCODE_L, cen::scancodes::l);
  ASSERT_EQ(SDL_SCANCODE_M, cen::scancodes::m);
  ASSERT_EQ(SDL_SCANCODE_N, cen::scancodes::n);
  ASSERT_EQ(SDL_SCANCODE_O, cen::scancodes::o);
  ASSERT_EQ(SDL_SCANCODE_P, cen::scancodes::p);
  ASSERT_EQ(SDL_SCANCODE_Q, cen::scancodes::q);
  ASSERT_EQ(SDL_SCANCODE_R, cen::scancodes::r);
  ASSERT_EQ(SDL_SCANCODE_S, cen::scancodes::s);
  ASSERT_EQ(SDL_SCANCODE_T, cen::scancodes::t);
  ASSERT_EQ(SDL_SCANCODE_U, cen::scancodes::u);
  ASSERT_EQ(SDL_SCANCODE_V, cen::scancodes::v);
  ASSERT_EQ(SDL_SCANCODE_W, cen::scancodes::w);
  ASSERT_EQ(SDL_SCANCODE_X, cen::scancodes::x);
  ASSERT_EQ(SDL_SCANCODE_Y, cen::scancodes::y);
  ASSERT_EQ(SDL_SCANCODE_Z, cen::scancodes::z);

  // Numerical keys
  ASSERT_EQ(SDL_SCANCODE_1, cen::scancodes::one);
  ASSERT_EQ(SDL_SCANCODE_2, cen::scancodes::two);
  ASSERT_EQ(SDL_SCANCODE_3, cen::scancodes::three);
  ASSERT_EQ(SDL_SCANCODE_4, cen::scancodes::four);
  ASSERT_EQ(SDL_SCANCODE_5, cen::scancodes::five);
  ASSERT_EQ(SDL_SCANCODE_6, cen::scancodes::six);
  ASSERT_EQ(SDL_SCANCODE_7, cen::scancodes::seven);
  ASSERT_EQ(SDL_SCANCODE_8, cen::scancodes::eight);
  ASSERT_EQ(SDL_SCANCODE_9, cen::scancodes::nine);
  ASSERT_EQ(SDL_SCANCODE_0, cen::scancodes::zero);

  // Function keys
  ASSERT_EQ(SDL_SCANCODE_F1, cen::scancodes::f1);
  ASSERT_EQ(SDL_SCANCODE_F2, cen::scancodes::f2);
  ASSERT_EQ(SDL_SCANCODE_F3, cen::scancodes::f3);
  ASSERT_EQ(SDL_SCANCODE_F4, cen::scancodes::f4);
  ASSERT_EQ(SDL_SCANCODE_F5, cen::scancodes::f5);
  ASSERT_EQ(SDL_SCANCODE_F6, cen::scancodes::f6);
  ASSERT_EQ(SDL_SCANCODE_F7, cen::scancodes::f7);
  ASSERT_EQ(SDL_SCANCODE_F8, cen::scancodes::f8);
  ASSERT_EQ(SDL_SCANCODE_F9, cen::scancodes::f9);
  ASSERT_EQ(SDL_SCANCODE_F10, cen::scancodes::f10);
  ASSERT_EQ(SDL_SCANCODE_F11, cen::scancodes::f11);
  ASSERT_EQ(SDL_SCANCODE_F12, cen::scancodes::f12);

  // Arrow keys
  ASSERT_EQ(SDL_SCANCODE_LEFT, cen::scancodes::left);
  ASSERT_EQ(SDL_SCANCODE_RIGHT, cen::scancodes::right);
  ASSERT_EQ(SDL_SCANCODE_UP, cen::scancodes::up);
  ASSERT_EQ(SDL_SCANCODE_DOWN, cen::scancodes::down);

  // Special keys
  ASSERT_EQ(SDL_SCANCODE_SPACE, cen::scancodes::space);
  ASSERT_EQ(SDL_SCANCODE_RETURN, cen::scancodes::enter);
  ASSERT_EQ(SDL_SCANCODE_ESCAPE, cen::scancodes::escape);
  ASSERT_EQ(SDL_SCANCODE_BACKSPACE, cen::scancodes::backspace);
  ASSERT_EQ(SDL_SCANCODE_TAB, cen::scancodes::tab);
  ASSERT_EQ(SDL_SCANCODE_CAPSLOCK, cen::scancodes::caps_lock);

  // Modifiers
  ASSERT_EQ(SDL_SCANCODE_LSHIFT, cen::scancodes::left_shift);
  ASSERT_EQ(SDL_SCANCODE_RSHIFT, cen::scancodes::right_shift);
  ASSERT_EQ(SDL_SCANCODE_LCTRL, cen::scancodes::left_ctrl);
  ASSERT_EQ(SDL_SCANCODE_RCTRL, cen::scancodes::right_ctrl);
  ASSERT_EQ(SDL_SCANCODE_LALT, cen::scancodes::left_alt);
  ASSERT_EQ(SDL_SCANCODE_RALT, cen::scancodes::right_alt);
  ASSERT_EQ(SDL_SCANCODE_LGUI, cen::scancodes::left_gui);
  ASSERT_EQ(SDL_SCANCODE_RGUI, cen::scancodes::right_gui);
}

TEST(ScanCode, Serialization)
{
  serialize_save("scan_code.binary", cen::scancodes::u);

  const auto code = serialize_create<cen::ScanCode>("scan_code.binary");
  ASSERT_EQ(cen::scancodes::u, code);
}