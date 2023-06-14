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

TEST(JoystickPower, Values)
{
  ASSERT_EQ(SDL_JOYSTICK_POWER_UNKNOWN, to_underlying(cen::joystick_power::unknown));
  ASSERT_EQ(SDL_JOYSTICK_POWER_EMPTY, to_underlying(cen::joystick_power::empty));
  ASSERT_EQ(SDL_JOYSTICK_POWER_LOW, to_underlying(cen::joystick_power::low));
  ASSERT_EQ(SDL_JOYSTICK_POWER_MEDIUM, to_underlying(cen::joystick_power::medium));
  ASSERT_EQ(SDL_JOYSTICK_POWER_FULL, to_underlying(cen::joystick_power::full));
  ASSERT_EQ(SDL_JOYSTICK_POWER_WIRED, to_underlying(cen::joystick_power::wired));
  ASSERT_EQ(SDL_JOYSTICK_POWER_MAX, to_underlying(cen::joystick_power::max));
}

TEST(JoystickPower, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::joystick_power>(SDL_JOYSTICK_POWER_MAX + 1)),
               cen::exception);

  ASSERT_EQ("unknown", to_string(cen::joystick_power::unknown));
  ASSERT_EQ("empty", to_string(cen::joystick_power::empty));
  ASSERT_EQ("low", to_string(cen::joystick_power::low));
  ASSERT_EQ("medium", to_string(cen::joystick_power::medium));
  ASSERT_EQ("full", to_string(cen::joystick_power::full));
  ASSERT_EQ("wired", to_string(cen::joystick_power::wired));
  ASSERT_EQ("max", to_string(cen::joystick_power::max));

  std::cout << "joystick_power::wired == " << cen::joystick_power::wired << '\n';
}
