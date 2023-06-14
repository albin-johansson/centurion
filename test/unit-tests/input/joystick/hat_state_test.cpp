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

#include "centurion/input/joystick.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, to_underlying(cen::hat_state::centered));
  ASSERT_EQ(SDL_HAT_UP, to_underlying(cen::hat_state::up));
  ASSERT_EQ(SDL_HAT_RIGHT, to_underlying(cen::hat_state::right));
  ASSERT_EQ(SDL_HAT_DOWN, to_underlying(cen::hat_state::down));
  ASSERT_EQ(SDL_HAT_LEFT, to_underlying(cen::hat_state::left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, to_underlying(cen::hat_state::right_up));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, to_underlying(cen::hat_state::right_down));
  ASSERT_EQ(SDL_HAT_LEFTUP, to_underlying(cen::hat_state::left_up));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, to_underlying(cen::hat_state::left_down));
}

TEST(HatState, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::hat_state>(0x10)), cen::exception);

  ASSERT_EQ("centered", to_string(cen::hat_state::centered));
  ASSERT_EQ("up", to_string(cen::hat_state::up));
  ASSERT_EQ("right", to_string(cen::hat_state::right));
  ASSERT_EQ("down", to_string(cen::hat_state::down));
  ASSERT_EQ("left", to_string(cen::hat_state::left));
  ASSERT_EQ("right_up", to_string(cen::hat_state::right_up));
  ASSERT_EQ("right_down", to_string(cen::hat_state::right_down));
  ASSERT_EQ("left_up", to_string(cen::hat_state::left_up));
  ASSERT_EQ("left_down", to_string(cen::hat_state::left_down));

  std::cout << "hat_state::centered == " << cen::hat_state::centered << '\n';
}
