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

#include "centurion/input/controller.hpp"

using axis = cen::controller_axis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_AXIS_INVALID, to_underlying(axis::invalid));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTX, to_underlying(axis::left_x));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTY, to_underlying(axis::left_y));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, to_underlying(axis::right_x));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, to_underlying(axis::right_y));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, to_underlying(axis::trigger_left));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, to_underlying(axis::trigger_right));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_MAX, to_underlying(axis::max));
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(to_string(static_cast<axis>(SDL_CONTROLLER_AXIS_MAX + 1)), cen::exception);

  ASSERT_EQ("invalid", to_string(axis::invalid));

  ASSERT_EQ("left_x", to_string(axis::left_x));
  ASSERT_EQ("left_y", to_string(axis::left_y));

  ASSERT_EQ("right_x", to_string(axis::right_x));
  ASSERT_EQ("right_y", to_string(axis::right_y));

  ASSERT_EQ("trigger_left", to_string(axis::trigger_left));
  ASSERT_EQ("trigger_right", to_string(axis::trigger_right));

  ASSERT_EQ("max", to_string(axis::max));

  std::cout << "controller_axis::right_x == " << axis::right_x << '\n';
}
