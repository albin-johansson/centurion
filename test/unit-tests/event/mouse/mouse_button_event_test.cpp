/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include "centurion/events/mouse_events.hpp"

TEST(MouseButtonEvent, Defaults)
{
  const cen::mouse_button_event event;
  ASSERT_EQ(cen::event_type::mouse_button_down, event.type());
}

TEST(MouseButtonEvent, SetWindowID)
{
  cen::mouse_button_event event;

  const cen::uint32 id = 64;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseButtonEvent, SetWhich)
{
  cen::mouse_button_event event;

  const cen::uint32 which = 17;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseButtonEvent, SetButton)
{
  cen::mouse_button_event event;

  event.set_button(cen::mouse_button::right);
  ASSERT_EQ(cen::mouse_button::right, event.button());
}

TEST(MouseButtonEvent, SetState)
{
  cen::mouse_button_event event;

  event.set_state(cen::button_state::pressed);

  ASSERT_EQ(cen::button_state::pressed, event.state());
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());

  event.set_state(cen::button_state::released);

  ASSERT_EQ(cen::button_state::released, event.state());
  ASSERT_TRUE(event.released());
  ASSERT_FALSE(event.pressed());
}

TEST(MouseButtonEvent, SetClicks)
{
  cen::mouse_button_event event;

  const cen::uint8 clicks = 2;
  event.set_clicks(clicks);

  ASSERT_EQ(clicks, event.clicks());
}

TEST(MouseButtonEvent, SetX)
{
  cen::mouse_button_event event;

  const cen::int32 x = 645;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseButtonEvent, SetY)
{
  cen::mouse_button_event event;

  const cen::int32 y = 177;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(MouseButtonEvent, AsSDLEvent)
{
  const cen::mouse_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.button.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.button.timestamp, event.timestamp().count());
}
