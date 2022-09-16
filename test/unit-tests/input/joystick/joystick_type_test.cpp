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

#include "centurion/joystick.hpp"

TEST(JoystickType, Values)
{
  ASSERT_EQ(SDL_JOYSTICK_TYPE_UNKNOWN, to_underlying(cen::joystick_type::unknown));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GAMECONTROLLER,
            to_underlying(cen::joystick_type::game_controller));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_WHEEL, to_underlying(cen::joystick_type::wheel));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_STICK, to_underlying(cen::joystick_type::arcade_stick));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_FLIGHT_STICK, to_underlying(cen::joystick_type::flight_stick));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DANCE_PAD, to_underlying(cen::joystick_type::dance_pad));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GUITAR, to_underlying(cen::joystick_type::guitar));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DRUM_KIT, to_underlying(cen::joystick_type::drum_kit));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_PAD, to_underlying(cen::joystick_type::arcade_pad));
  ASSERT_EQ(SDL_JOYSTICK_TYPE_THROTTLE, to_underlying(cen::joystick_type::throttle));
}

TEST(JoystickType, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::joystick_type>(11)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::joystick_type::unknown));
  ASSERT_EQ("game_controller", to_string(cen::joystick_type::game_controller));
  ASSERT_EQ("wheel", to_string(cen::joystick_type::wheel));
  ASSERT_EQ("arcade_stick", to_string(cen::joystick_type::arcade_stick));
  ASSERT_EQ("flight_stick", to_string(cen::joystick_type::flight_stick));
  ASSERT_EQ("dance_pad", to_string(cen::joystick_type::dance_pad));
  ASSERT_EQ("guitar", to_string(cen::joystick_type::guitar));
  ASSERT_EQ("drum_kit", to_string(cen::joystick_type::drum_kit));
  ASSERT_EQ("arcade_pad", to_string(cen::joystick_type::arcade_pad));
  ASSERT_EQ("throttle", to_string(cen::joystick_type::throttle));

  std::cout << "joystick_type::guitar == " << cen::joystick_type::guitar << '\n';
}
