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

TEST(KeyMod, Values)
{
  ASSERT_EQ(to_underlying(cen::key_mod::none), KMOD_NONE);

  ASSERT_EQ(KMOD_LSHIFT, to_underlying(cen::key_mod::lshift));
  ASSERT_EQ(KMOD_RSHIFT, to_underlying(cen::key_mod::rshift));
  ASSERT_EQ(KMOD_SHIFT, to_underlying(cen::key_mod::shift));

  ASSERT_EQ(KMOD_LCTRL, to_underlying(cen::key_mod::lctrl));
  ASSERT_EQ(KMOD_RCTRL, to_underlying(cen::key_mod::rctrl));
  ASSERT_EQ(KMOD_CTRL, to_underlying(cen::key_mod::ctrl));

  ASSERT_EQ(KMOD_LALT, to_underlying(cen::key_mod::lalt));
  ASSERT_EQ(KMOD_RALT, to_underlying(cen::key_mod::ralt));
  ASSERT_EQ(KMOD_ALT, to_underlying(cen::key_mod::alt));

  ASSERT_EQ(KMOD_LGUI, to_underlying(cen::key_mod::lgui));
  ASSERT_EQ(KMOD_RGUI, to_underlying(cen::key_mod::rgui));
  ASSERT_EQ(KMOD_GUI, to_underlying(cen::key_mod::gui));

  ASSERT_EQ(KMOD_NUM, to_underlying(cen::key_mod::num));
  ASSERT_EQ(KMOD_CAPS, to_underlying(cen::key_mod::caps));
  ASSERT_EQ(KMOD_MODE, to_underlying(cen::key_mod::mode));
}

TEST(KeyMod, SetModifiers)
{
  const auto previous = cen::get_modifiers();

  cen::set_modifiers(cen::key_mod::lshift | cen::key_mod::ralt);
  ASSERT_EQ(cen::key_mod::lshift | cen::key_mod::ralt, cen::get_modifiers());

  cen::set_modifiers(previous);
}

TEST(KeyMod, GetModifiers)
{
  ASSERT_EQ(SDL_GetModState(), to_underlying(cen::get_modifiers()));
}

TEST(KeyMod, IsActive)
{
  cen::set_modifiers(cen::key_mod::none);
  ASSERT_FALSE(cen::is_active(cen::key_mod::caps));

  cen::set_modifiers(cen::key_mod::caps);
  ASSERT_TRUE(cen::is_active(cen::key_mod::caps));
}

TEST(KeyMod, BitwiseNot)
{
  ASSERT_EQ(Uint16(~Uint16 {KMOD_SHIFT}), to_underlying(~cen::key_mod::shift));
}

TEST(KeyMod, BitwiseOR)
{
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::shift | cen::key_mod::shift);
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::lshift | cen::key_mod::rshift);
  ASSERT_EQ(KMOD_LCTRL | KMOD_RALT, to_underlying(cen::key_mod::lctrl | cen::key_mod::ralt));
}

TEST(KeyMod, BitwiseAND)
{
  ASSERT_EQ(cen::key_mod::shift, cen::key_mod::shift & cen::key_mod::shift);
  ASSERT_EQ(KMOD_LSHIFT & KMOD_RGUI, to_underlying(cen::key_mod::lshift & cen::key_mod::rgui));
}

TEST(KeyMod, ToString)
{
  {  // Singles
    ASSERT_EQ("none", to_string(cen::key_mod::none));
    ASSERT_EQ("lshift", to_string(cen::key_mod::lshift));
    ASSERT_EQ("rshift", to_string(cen::key_mod::rshift));
    ASSERT_EQ("lctrl", to_string(cen::key_mod::lctrl));
    ASSERT_EQ("rctrl", to_string(cen::key_mod::rctrl));
    ASSERT_EQ("lalt", to_string(cen::key_mod::lalt));
    ASSERT_EQ("ralt", to_string(cen::key_mod::ralt));
    ASSERT_EQ("lgui", to_string(cen::key_mod::lgui));
    ASSERT_EQ("rgui", to_string(cen::key_mod::rgui));
    ASSERT_EQ("num", to_string(cen::key_mod::num));
    ASSERT_EQ("caps", to_string(cen::key_mod::caps));
    ASSERT_EQ("mode", to_string(cen::key_mod::mode));
  }

  {  // Two modifiers
    const auto mods = cen::key_mod::lshift | cen::key_mod::caps;
    ASSERT_EQ("lshift,caps", to_string(mods));
  }

  {  // Three modifiers
    const auto mods = cen::key_mod::lctrl | cen::key_mod::ralt | cen::key_mod::num;
    ASSERT_EQ("lctrl,ralt,num", to_string(mods));
  }

  {  // Composite enumerator
    const auto mods = cen::key_mod::alt;
    ASSERT_EQ("lalt,ralt", to_string(mods));
  }

  {  // Everything
    const auto mods = static_cast<cen::key_mod>(0xFFFF);
    ASSERT_EQ("lshift,rshift,lctrl,rctrl,lalt,ralt,lgui,rgui,num,caps,mode", to_string(mods));
  }

  std::cout << "key_mod::lshift == " << cen::key_mod::lshift << '\n';
}
