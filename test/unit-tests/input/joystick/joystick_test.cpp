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

#include "centurion/joystick.hpp"

#include <gtest/gtest.h>

TEST(Joystick, PointerConstructor)
{
  ASSERT_THROW(cen::joystick {nullptr}, cen::exception);
}

TEST(Joystick, IndexConstructor)
{
  ASSERT_THROW(cen::joystick {0}, cen::sdl_error);
}

TEST(Joystick, GetAxisMax)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MAX, cen::joystick::axis_max());
}

TEST(Joystick, GetAxisMin)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MIN, cen::joystick::axis_min());
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Joystick, VirtualAPI)
{
  const auto type = cen::joystick_type::game_controller;
  const auto nAxes = 2;
  const auto nButtons = 3;
  const auto nHats = 4;

  const auto index = cen::joystick::attach_virtual(type, nAxes, nButtons, nHats);
  ASSERT_TRUE(index);
  ASSERT_TRUE(cen::joystick::is_virtual(*index));

  cen::joystick joystick {*index};
  ASSERT_EQ(type, joystick.type());
  ASSERT_EQ(nAxes, joystick.axis_count());
  ASSERT_EQ(nButtons, joystick.button_count());
  ASSERT_EQ(nHats, joystick.hat_count());

  ASSERT_TRUE(joystick.set_virtual_axis(0, 123));
  ASSERT_TRUE(joystick.set_virtual_button(0, cen::button_state::pressed));
  ASSERT_TRUE(joystick.set_virtual_hat(0, cen::hat_state::centered));

  ASSERT_TRUE(cen::joystick::detach_virtual(*index));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 24, 0)

TEST(Joystick, AttachVirtualEx)
{
  const cen::virtual_joystick_desc desc;
  const auto index = cen::joystick::attach_virtual(desc);

  ASSERT_TRUE(index.has_value());
  ASSERT_TRUE(cen::joystick::is_virtual(*index));

  ASSERT_EQ(cen::success, cen::joystick::detach_virtual(*index));
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
