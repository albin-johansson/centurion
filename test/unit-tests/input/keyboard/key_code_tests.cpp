/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/keyboard.hpp"
#include "serialization_utils.hpp"

TEST(KeyCode, DefaultValue)
{
  cen::key_code code;
  ASSERT_EQ(SDLK_UNKNOWN, code.get());
}

TEST(KeyCode, SDLKeycodeContructor)
{
  const auto key = SDLK_x;
  const cen::key_code code {key};
  ASSERT_EQ(key, code.get());
}

TEST(KeyCode, SDLScancodeContructor)
{
  const auto scan = SDL_SCANCODE_Y;
  const cen::key_code code {scan};
  ASSERT_EQ(scan, code.to_scancode());
}

TEST(KeyCode, CStringConstructor)
{
  {  // Good name
    const cen::key_code code {"5"};
    ASSERT_EQ(SDLK_5, code.get());
    ASSERT_EQ(cen::keycodes::five, code);
    ASSERT_EQ("5", code.name());
  }

  {  // Bad name
    const cen::key_code code {"foobar"};
    ASSERT_EQ(SDLK_UNKNOWN, code.get());
    ASSERT_EQ(cen::keycodes::unknown, code);
    ASSERT_TRUE(code.name().empty());
    ASSERT_TRUE(code.unknown());
  }
}

TEST(KeyCode, StdStringConstructor)
{
  using namespace std::string_literals;

  {  // Good name
    const cen::key_code code {"5"s};
    ASSERT_EQ(SDLK_5, code.get());
    ASSERT_EQ(cen::keycodes::five, code);
    ASSERT_EQ("5", code.name());
  }

  {  // Bad name
    const cen::key_code code {"foobar"s};
    ASSERT_EQ(SDLK_UNKNOWN, code.get());
    ASSERT_EQ(cen::keycodes::unknown, code);
    ASSERT_TRUE(code.name().empty());
    ASSERT_TRUE(code.unknown());
  }
}

TEST(KeyCode, SDLKeycodeAssignmentOperator)
{
  cen::key_code code;
  code = SDLK_o;

  ASSERT_EQ(SDLK_o, code.get());
  ASSERT_EQ(cen::keycodes::o, code);
}

TEST(KeyCode, SDLScancodeAssignmentOperator)
{
  cen::key_code code;
  code = SDL_SCANCODE_U;

  ASSERT_EQ(SDL_GetKeyFromScancode(SDL_SCANCODE_U), code.get());
}

TEST(KeyCode, CZStringAssignmentOperator)
{
  {  // Good name
    cen::key_code code;
    code = "Tab";

    ASSERT_EQ(SDLK_TAB, code.get());
    ASSERT_EQ(cen::keycodes::tab, code);
    ASSERT_EQ("Tab", code.name());
  }

  {  // Bad name
    cen::key_code code;
    code = "qwerty";

    ASSERT_EQ(SDLK_UNKNOWN, code.get());
    ASSERT_EQ(cen::keycodes::unknown, code);
    ASSERT_TRUE(code.unknown());
  }
}

TEST(KeyCode, StrStringAssignmentOperator)
{
  using namespace std::string_literals;

  {  // Good name
    cen::key_code code;
    code = "Tab"s;

    ASSERT_EQ(SDLK_TAB, code.get());
    ASSERT_EQ(cen::keycodes::tab, code);
    ASSERT_EQ("Tab", code.name());
  }

  {  // Bad name
    cen::key_code code;
    code = "qwerty"s;

    ASSERT_EQ(SDLK_UNKNOWN, code.get());
    ASSERT_EQ(cen::keycodes::unknown, code);
    ASSERT_TRUE(code.unknown());
  }
}

TEST(KeyCode, Unknown)
{
  cen::key_code code;
  ASSERT_TRUE(code.unknown());

  code = cen::keycodes::w;
  ASSERT_FALSE(code.unknown());
}

TEST(KeyCode, Name)
{
  cen::key_code code;
  ASSERT_TRUE(code.name().empty());

  code = SDLK_z;
  ASSERT_EQ("Z", code.name());
}

TEST(KeyCode, Get)
{
  cen::key_code code;
  ASSERT_EQ(SDLK_UNKNOWN, code.get());

  code = SDLK_8;
  ASSERT_EQ(SDLK_8, code.get());
}

TEST(KeyCode, ToScanCode)
{
  const auto key = cen::keycodes::p;
  const auto scancode = key.to_scancode();
  ASSERT_EQ(SDL_GetScancodeFromKey(key.get()), scancode);
}

TEST(KeyCode, EqualityOperator)
{
  {
    const cen::key_code code;
    ASSERT_EQ(code, code);
  }

  {
    const cen::key_code fst {SDLK_i};
    const cen::key_code snd {fst};
    ASSERT_EQ(fst, snd);
    ASSERT_EQ(snd, fst);
  }

  {
    const cen::key_code fst {SDLK_e};
    const cen::key_code snd {SDLK_y};
    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(KeyCode, InequalityOperator)
{
  {
    const cen::key_code code;
    ASSERT_FALSE(code != code);
  }

  {
    const cen::key_code fst {SDLK_w};
    const cen::key_code snd {fst};
    ASSERT_FALSE(fst != snd);
    ASSERT_FALSE(snd != fst);
  }

  {
    const cen::key_code fst {SDLK_a};
    const cen::key_code snd {SDLK_5};
    ASSERT_NE(fst, snd);
    ASSERT_NE(snd, fst);
  }
}

TEST(KeyCode, StreamOperator)
{
  std::cout << cen::keycodes::a << '\n';
}

TEST(KeyCode, Constants)
{
  ASSERT_EQ(SDLK_UNKNOWN, cen::keycodes::unknown);

  // Alphabetical keys
  ASSERT_EQ(SDLK_a, cen::keycodes::a);
  ASSERT_EQ(SDLK_b, cen::keycodes::b);
  ASSERT_EQ(SDLK_c, cen::keycodes::c);
  ASSERT_EQ(SDLK_d, cen::keycodes::d);
  ASSERT_EQ(SDLK_e, cen::keycodes::e);
  ASSERT_EQ(SDLK_f, cen::keycodes::f);
  ASSERT_EQ(SDLK_g, cen::keycodes::g);
  ASSERT_EQ(SDLK_h, cen::keycodes::h);
  ASSERT_EQ(SDLK_i, cen::keycodes::i);
  ASSERT_EQ(SDLK_j, cen::keycodes::j);
  ASSERT_EQ(SDLK_k, cen::keycodes::k);
  ASSERT_EQ(SDLK_l, cen::keycodes::l);
  ASSERT_EQ(SDLK_m, cen::keycodes::m);
  ASSERT_EQ(SDLK_n, cen::keycodes::n);
  ASSERT_EQ(SDLK_o, cen::keycodes::o);
  ASSERT_EQ(SDLK_p, cen::keycodes::p);
  ASSERT_EQ(SDLK_q, cen::keycodes::q);
  ASSERT_EQ(SDLK_r, cen::keycodes::r);
  ASSERT_EQ(SDLK_s, cen::keycodes::s);
  ASSERT_EQ(SDLK_t, cen::keycodes::t);
  ASSERT_EQ(SDLK_u, cen::keycodes::u);
  ASSERT_EQ(SDLK_v, cen::keycodes::v);
  ASSERT_EQ(SDLK_w, cen::keycodes::w);
  ASSERT_EQ(SDLK_x, cen::keycodes::x);
  ASSERT_EQ(SDLK_y, cen::keycodes::y);
  ASSERT_EQ(SDLK_z, cen::keycodes::z);

  // Numerical keys
  ASSERT_EQ(SDLK_1, cen::keycodes::one);
  ASSERT_EQ(SDLK_2, cen::keycodes::two);
  ASSERT_EQ(SDLK_3, cen::keycodes::three);
  ASSERT_EQ(SDLK_4, cen::keycodes::four);
  ASSERT_EQ(SDLK_5, cen::keycodes::five);
  ASSERT_EQ(SDLK_6, cen::keycodes::six);
  ASSERT_EQ(SDLK_7, cen::keycodes::seven);
  ASSERT_EQ(SDLK_8, cen::keycodes::eight);
  ASSERT_EQ(SDLK_9, cen::keycodes::nine);
  ASSERT_EQ(SDLK_0, cen::keycodes::zero);

  // Function keys
  ASSERT_EQ(SDLK_F1, cen::keycodes::f1);
  ASSERT_EQ(SDLK_F2, cen::keycodes::f2);
  ASSERT_EQ(SDLK_F3, cen::keycodes::f3);
  ASSERT_EQ(SDLK_F4, cen::keycodes::f4);
  ASSERT_EQ(SDLK_F5, cen::keycodes::f5);
  ASSERT_EQ(SDLK_F6, cen::keycodes::f6);
  ASSERT_EQ(SDLK_F7, cen::keycodes::f7);
  ASSERT_EQ(SDLK_F8, cen::keycodes::f8);
  ASSERT_EQ(SDLK_F9, cen::keycodes::f9);
  ASSERT_EQ(SDLK_F10, cen::keycodes::f10);
  ASSERT_EQ(SDLK_F11, cen::keycodes::f11);
  ASSERT_EQ(SDLK_F12, cen::keycodes::f12);

  // Arrow keys
  ASSERT_EQ(SDLK_LEFT, cen::keycodes::left);
  ASSERT_EQ(SDLK_RIGHT, cen::keycodes::right);
  ASSERT_EQ(SDLK_UP, cen::keycodes::up);
  ASSERT_EQ(SDLK_DOWN, cen::keycodes::down);

  // Special keys
  ASSERT_EQ(SDLK_SPACE, cen::keycodes::space);
  ASSERT_EQ(SDLK_RETURN, cen::keycodes::enter);
  ASSERT_EQ(SDLK_ESCAPE, cen::keycodes::escape);
  ASSERT_EQ(SDLK_BACKSPACE, cen::keycodes::backspace);
  ASSERT_EQ(SDLK_TAB, cen::keycodes::tab);
  ASSERT_EQ(SDLK_CAPSLOCK, cen::keycodes::caps_lock);

  // Modifiers
  ASSERT_EQ(SDLK_LSHIFT, cen::keycodes::left_shift);
  ASSERT_EQ(SDLK_RSHIFT, cen::keycodes::right_shift);
  ASSERT_EQ(SDLK_LCTRL, cen::keycodes::left_ctrl);
  ASSERT_EQ(SDLK_RCTRL, cen::keycodes::right_ctrl);
  ASSERT_EQ(SDLK_LALT, cen::keycodes::left_alt);
  ASSERT_EQ(SDLK_RALT, cen::keycodes::right_alt);
  ASSERT_EQ(SDLK_LGUI, cen::keycodes::left_gui);
  ASSERT_EQ(SDLK_RGUI, cen::keycodes::right_gui);
}

TEST(KeyCode, Serialization)
{
  serialize_save("key_code.binary", cen::keycodes::enter);

  const auto other = serialize_create<cen::key_code>("key_code.binary");
  ASSERT_EQ(cen::keycodes::enter, other);
}
