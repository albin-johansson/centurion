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

#include "centurion/controller.hpp"

using button = cen::controller_button;

TEST(ControllerButton, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_INVALID, to_underlying(button::invalid));

  ASSERT_EQ(SDL_CONTROLLER_BUTTON_A, to_underlying(button::a));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_B, to_underlying(button::b));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_X, to_underlying(button::x));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_Y, to_underlying(button::y));

  ASSERT_EQ(SDL_CONTROLLER_BUTTON_BACK, to_underlying(button::back));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_GUIDE, to_underlying(button::guide));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_START, to_underlying(button::start));

  ASSERT_EQ(SDL_CONTROLLER_BUTTON_LEFTSTICK, to_underlying(button::left_stick));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_RIGHTSTICK, to_underlying(button::right_stick));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, to_underlying(button::left_shoulder));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, to_underlying(button::right_shoulder));

  ASSERT_EQ(SDL_CONTROLLER_BUTTON_DPAD_UP, to_underlying(button::dpad_up));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_DPAD_DOWN, to_underlying(button::dpad_down));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, to_underlying(button::dpad_right));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_DPAD_LEFT, to_underlying(button::dpad_left));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_MAX, to_underlying(button::max));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_MISC1, to_underlying(button::misc1));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_PADDLE1, to_underlying(button::paddle1));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_PADDLE2, to_underlying(button::paddle2));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_PADDLE3, to_underlying(button::paddle3));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_PADDLE4, to_underlying(button::paddle4));
  ASSERT_EQ(SDL_CONTROLLER_BUTTON_TOUCHPAD, to_underlying(button::touchpad));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(ControllerButton, ToString)
{
  ASSERT_THROW(to_string(static_cast<button>(SDL_CONTROLLER_BUTTON_MAX + 1)), cen::exception);

  ASSERT_EQ("invalid", to_string(button::invalid));

  ASSERT_EQ("a", to_string(button::a));
  ASSERT_EQ("b", to_string(button::b));
  ASSERT_EQ("x", to_string(button::x));
  ASSERT_EQ("y", to_string(button::y));

  ASSERT_EQ("back", to_string(button::back));
  ASSERT_EQ("guide", to_string(button::guide));
  ASSERT_EQ("start", to_string(button::start));

  ASSERT_EQ("left_stick", to_string(button::left_stick));
  ASSERT_EQ("right_stick", to_string(button::right_stick));

  ASSERT_EQ("left_shoulder", to_string(button::left_shoulder));
  ASSERT_EQ("right_shoulder", to_string(button::right_shoulder));

  ASSERT_EQ("dpad_up", to_string(button::dpad_up));
  ASSERT_EQ("dpad_down", to_string(button::dpad_down));
  ASSERT_EQ("dpad_left", to_string(button::dpad_left));
  ASSERT_EQ("dpad_right", to_string(button::dpad_right));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("misc1", to_string(button::misc1));

  ASSERT_EQ("paddle1", to_string(button::paddle1));
  ASSERT_EQ("paddle2", to_string(button::paddle2));
  ASSERT_EQ("paddle3", to_string(button::paddle3));
  ASSERT_EQ("paddle4", to_string(button::paddle4));

  ASSERT_EQ("touchpad", to_string(button::touchpad));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("max", to_string(button::max));

  std::cout << "controller_button::x == " << button::x << '\n';
}
