#include <gtest/gtest.h>

#include <iostream>

#include "input/key_code.hpp"
#include "misc/log.hpp"
#include "serialization_utils.hpp"

TEST(KeyCode, DefaultValue)
{
  cen::key_code code;
  EXPECT_EQ(SDLK_UNKNOWN, code.get());
}

TEST(KeyCode, SDLKeycodeContructor)
{
  const auto key = SDLK_x;
  const cen::key_code code{key};
  EXPECT_EQ(key, code.get());
}

TEST(KeyCode, SDLScancodeContructor)
{
  const auto scan = SDL_SCANCODE_Y;
  const cen::key_code code{scan};
  EXPECT_EQ(scan, code.operator SDL_Scancode());
}

TEST(KeyCode, CZStringConstructor)
{
  {  // Good name
    const cen::key_code code{"5"};
    EXPECT_EQ(SDLK_5, code.get());
    EXPECT_EQ(cen::keycodes::five, code);
    EXPECT_EQ("5", code.name());
  }

  {  // Bad name
    const cen::key_code code{"foobar"};
    EXPECT_EQ(SDLK_UNKNOWN, code.get());
    EXPECT_EQ(cen::keycodes::unknown, code);
    EXPECT_TRUE(code.name().empty());
    EXPECT_TRUE(code.unknown());
  }
}

TEST(KeyCode, StdStringConstructor)
{
  using namespace std::string_literals;

  {  // Good name
    const cen::key_code code{"5"s};
    EXPECT_EQ(SDLK_5, code.get());
    EXPECT_EQ(cen::keycodes::five, code);
    EXPECT_EQ("5", code.name());
  }

  {  // Bad name
    const cen::key_code code{"foobar"s};
    EXPECT_EQ(SDLK_UNKNOWN, code.get());
    EXPECT_EQ(cen::keycodes::unknown, code);
    EXPECT_TRUE(code.name().empty());
    EXPECT_TRUE(code.unknown());
  }
}

TEST(KeyCode, SDLKeycodeAssignmentOperator)
{
  cen::key_code code;
  code = SDLK_o;

  EXPECT_EQ(SDLK_o, code.get());
  EXPECT_EQ(cen::keycodes::o, code);
}

TEST(KeyCode, SDLScancodeAssignmentOperator)
{
  cen::key_code code;
  code = SDL_SCANCODE_U;

  EXPECT_EQ(SDL_GetKeyFromScancode(SDL_SCANCODE_U), code.get());
}

TEST(KeyCode, CZStringAssignmentOperator)
{
  {  // Good name
    cen::key_code code;
    code = "Tab";

    EXPECT_EQ(SDLK_TAB, code.get());
    EXPECT_EQ(cen::keycodes::tab, code);
    EXPECT_EQ("Tab", code.name());
  }

  {  // Bad name
    cen::key_code code;
    code = "qwerty";

    EXPECT_EQ(SDLK_UNKNOWN, code.get());
    EXPECT_EQ(cen::keycodes::unknown, code);
    EXPECT_TRUE(code.unknown());
  }
}

TEST(KeyCode, StrStringAssignmentOperator)
{
  using namespace std::string_literals;

  {  // Good name
    cen::key_code code;
    code = "Tab"s;

    EXPECT_EQ(SDLK_TAB, code.get());
    EXPECT_EQ(cen::keycodes::tab, code);
    EXPECT_EQ("Tab", code.name());
  }

  {  // Bad name
    cen::key_code code;
    code = "qwerty"s;

    EXPECT_EQ(SDLK_UNKNOWN, code.get());
    EXPECT_EQ(cen::keycodes::unknown, code);
    EXPECT_TRUE(code.unknown());
  }
}

TEST(KeyCode, Unknown)
{
  cen::key_code code;
  EXPECT_TRUE(code.unknown());

  code = cen::keycodes::w;
  EXPECT_FALSE(code.unknown());
}

TEST(KeyCode, Name)
{
  cen::key_code code;
  EXPECT_TRUE(code.name().empty());

  code = SDLK_z;
  EXPECT_EQ("Z", code.name());
}

TEST(KeyCode, Get)
{
  cen::key_code code;
  EXPECT_EQ(SDLK_UNKNOWN, code.get());

  code = SDLK_8;
  EXPECT_EQ(SDLK_8, code.get());
}

TEST(KeyCode, ToScanCode)
{
  const auto key = cen::keycodes::p;
  const auto scancode = key.to_scan_code();
  EXPECT_EQ(SDL_GetScancodeFromKey(key.get()), scancode);
}

TEST(KeyCode, SDLKeycodeConversion)
{
  cen::key_code code;

  const auto unknown = static_cast<SDL_Keycode>(code);
  EXPECT_EQ(SDLK_UNKNOWN, unknown);

  code = SDLK_f;

  const auto f = static_cast<SDL_Keycode>(code);
  EXPECT_EQ(SDLK_f, f);
}

TEST(KeyCode, SDLScancodeConversion)
{
  cen::key_code code;

  const auto unknown = static_cast<SDL_Scancode>(code);
  EXPECT_EQ(SDL_SCANCODE_UNKNOWN, unknown);

  code = SDLK_RSHIFT;

  const auto rshift = static_cast<SDL_Scancode>(code);
  EXPECT_EQ(SDL_SCANCODE_RSHIFT, rshift);
}

TEST(KeyCode, EqualityOperator)
{
  {
    const cen::key_code code;
    EXPECT_EQ(code, code);
  }

  {
    const cen::key_code fst{SDLK_i};
    const cen::key_code snd{fst};
    EXPECT_EQ(fst, snd);
    EXPECT_EQ(snd, fst);
  }

  {
    const cen::key_code fst{SDLK_e};
    const cen::key_code snd{SDLK_y};
    EXPECT_NE(fst, snd);
    EXPECT_NE(snd, fst);
  }
}

TEST(KeyCode, InequalityOperator)
{
  {
    const cen::key_code code;
    EXPECT_FALSE(code != code);
  }

  {
    const cen::key_code fst{SDLK_w};
    const cen::key_code snd{fst};
    EXPECT_FALSE(fst != snd);
    EXPECT_FALSE(snd != fst);
  }

  {
    const cen::key_code fst{SDLK_a};
    const cen::key_code snd{SDLK_5};
    EXPECT_NE(fst, snd);
    EXPECT_NE(snd, fst);
  }
}

TEST(KeyCode, ToString)
{
  cen::log::put(cen::to_string(cen::keycodes::a));
}

TEST(KeyCode, StreamOperator)
{
  std::cout << "COUT: " << cen::keycodes::a << '\n';
}

TEST(KeyCode, Constants)
{
  EXPECT_EQ(SDLK_UNKNOWN, cen::keycodes::unknown);

  // Alphabetical keys
  EXPECT_EQ(SDLK_a, cen::keycodes::a);
  EXPECT_EQ(SDLK_b, cen::keycodes::b);
  EXPECT_EQ(SDLK_c, cen::keycodes::c);
  EXPECT_EQ(SDLK_d, cen::keycodes::d);
  EXPECT_EQ(SDLK_e, cen::keycodes::e);
  EXPECT_EQ(SDLK_f, cen::keycodes::f);
  EXPECT_EQ(SDLK_g, cen::keycodes::g);
  EXPECT_EQ(SDLK_h, cen::keycodes::h);
  EXPECT_EQ(SDLK_i, cen::keycodes::i);
  EXPECT_EQ(SDLK_j, cen::keycodes::j);
  EXPECT_EQ(SDLK_k, cen::keycodes::k);
  EXPECT_EQ(SDLK_l, cen::keycodes::l);
  EXPECT_EQ(SDLK_m, cen::keycodes::m);
  EXPECT_EQ(SDLK_n, cen::keycodes::n);
  EXPECT_EQ(SDLK_o, cen::keycodes::o);
  EXPECT_EQ(SDLK_p, cen::keycodes::p);
  EXPECT_EQ(SDLK_q, cen::keycodes::q);
  EXPECT_EQ(SDLK_r, cen::keycodes::r);
  EXPECT_EQ(SDLK_s, cen::keycodes::s);
  EXPECT_EQ(SDLK_t, cen::keycodes::t);
  EXPECT_EQ(SDLK_u, cen::keycodes::u);
  EXPECT_EQ(SDLK_v, cen::keycodes::v);
  EXPECT_EQ(SDLK_w, cen::keycodes::w);
  EXPECT_EQ(SDLK_x, cen::keycodes::x);
  EXPECT_EQ(SDLK_y, cen::keycodes::y);
  EXPECT_EQ(SDLK_z, cen::keycodes::z);

  // Numerical keys
  EXPECT_EQ(SDLK_1, cen::keycodes::one);
  EXPECT_EQ(SDLK_2, cen::keycodes::two);
  EXPECT_EQ(SDLK_3, cen::keycodes::three);
  EXPECT_EQ(SDLK_4, cen::keycodes::four);
  EXPECT_EQ(SDLK_5, cen::keycodes::five);
  EXPECT_EQ(SDLK_6, cen::keycodes::six);
  EXPECT_EQ(SDLK_7, cen::keycodes::seven);
  EXPECT_EQ(SDLK_8, cen::keycodes::eight);
  EXPECT_EQ(SDLK_9, cen::keycodes::nine);
  EXPECT_EQ(SDLK_0, cen::keycodes::zero);

  // Function keys
  EXPECT_EQ(SDLK_F1, cen::keycodes::f1);
  EXPECT_EQ(SDLK_F2, cen::keycodes::f2);
  EXPECT_EQ(SDLK_F3, cen::keycodes::f3);
  EXPECT_EQ(SDLK_F4, cen::keycodes::f4);
  EXPECT_EQ(SDLK_F5, cen::keycodes::f5);
  EXPECT_EQ(SDLK_F6, cen::keycodes::f6);
  EXPECT_EQ(SDLK_F7, cen::keycodes::f7);
  EXPECT_EQ(SDLK_F8, cen::keycodes::f8);
  EXPECT_EQ(SDLK_F9, cen::keycodes::f9);
  EXPECT_EQ(SDLK_F10, cen::keycodes::f10);
  EXPECT_EQ(SDLK_F11, cen::keycodes::f11);
  EXPECT_EQ(SDLK_F12, cen::keycodes::f12);

  // Arrow keys
  EXPECT_EQ(SDLK_LEFT, cen::keycodes::left);
  EXPECT_EQ(SDLK_RIGHT, cen::keycodes::right);
  EXPECT_EQ(SDLK_UP, cen::keycodes::up);
  EXPECT_EQ(SDLK_DOWN, cen::keycodes::down);

  // Special keys
  EXPECT_EQ(SDLK_SPACE, cen::keycodes::space);
  EXPECT_EQ(SDLK_RETURN, cen::keycodes::enter);
  EXPECT_EQ(SDLK_ESCAPE, cen::keycodes::escape);
  EXPECT_EQ(SDLK_BACKSPACE, cen::keycodes::backspace);
  EXPECT_EQ(SDLK_TAB, cen::keycodes::tab);
  EXPECT_EQ(SDLK_CAPSLOCK, cen::keycodes::caps_lock);

  // Modifiers
  EXPECT_EQ(SDLK_LSHIFT, cen::keycodes::left_shift);
  EXPECT_EQ(SDLK_RSHIFT, cen::keycodes::right_shift);
  EXPECT_EQ(SDLK_LCTRL, cen::keycodes::left_ctrl);
  EXPECT_EQ(SDLK_RCTRL, cen::keycodes::right_ctrl);
  EXPECT_EQ(SDLK_LALT, cen::keycodes::left_alt);
  EXPECT_EQ(SDLK_RALT, cen::keycodes::right_alt);
  EXPECT_EQ(SDLK_LGUI, cen::keycodes::left_gui);
  EXPECT_EQ(SDLK_RGUI, cen::keycodes::right_gui);
}

TEST(KeyCode, Serialization)
{
  serialize_to("key_code.binary", cen::keycodes::enter);

  const auto other = serialize_from<cen::key_code>("key_code.binary");
  EXPECT_EQ(cen::keycodes::enter, other);
}
