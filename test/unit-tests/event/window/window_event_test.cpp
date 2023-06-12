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

#include "centurion/events/window_events.hpp"

TEST(window_event, Defaults)
{
  const cen::window_event event;
  ASSERT_EQ(cen::event_type::window, event.type());
  ASSERT_EQ(cen::window_event_id::none, event.event_id());
}

TEST(WindowEvent, SetEventID)
{
  cen::window_event event;

  event.set_event_id(cen::window_event_id::focus_gained);
  ASSERT_EQ(cen::window_event_id::focus_gained, event.event_id());
}

TEST(WindowEvent, SetData1)
{
  cen::window_event event;
  event.set_event_id(cen::window_event_id::resized);

  const cen::int32 data = 75;
  event.set_data1(data);

  ASSERT_EQ(cen::window_event_id::resized, event.event_id());
  ASSERT_EQ(data, event.data1());
  ASSERT_EQ(0, event.data2());
}

TEST(WindowEvent, SetData2)
{
  cen::window_event event;
  event.set_event_id(cen::window_event_id::resized);

  const cen::int32 data = 54;
  event.set_data2(data);

  ASSERT_EQ(cen::window_event_id::resized, event.event_id());
  ASSERT_EQ(0, event.data1());
  ASSERT_EQ(data, event.data2());
}

TEST(WindowEvent, AsSDLEvent)
{
  const cen::window_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.window.type, to_underlying(event.type()));
  ASSERT_EQ(underlying.window.timestamp, event.timestamp().count());
}
