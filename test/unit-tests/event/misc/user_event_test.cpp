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

#include "centurion/events/misc_events.hpp"

TEST(UserEvent, Defaults)
{
  const cen::user_event event;

  ASSERT_EQ(0, event.code());
  ASSERT_EQ(0u, event.window_id());

  ASSERT_EQ(nullptr, event.data1());
  ASSERT_EQ(nullptr, event.data2());
}

TEST(UserEvent, SetWindowID)
{
  cen::user_event event;

  const cen::uint32 id = 123;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(UserEvent, SetCode)
{
  cen::user_event event;

  const cen::int32 code = 13;
  event.set_code(code);

  ASSERT_EQ(code, event.code());
}

TEST(UserEvent, SetData1)
{
  cen::user_event event;
  const auto& ref = event;

  int i = 42;
  event.set_data1(&i);

  ASSERT_EQ(&i, event.data1());
  ASSERT_EQ(&i, ref.data1());
  ASSERT_EQ(nullptr, event.data2());
}

TEST(UserEvent, SetData2)
{
  cen::user_event event;
  const auto& ref = event;

  int i = 42;
  event.set_data2(&i);

  ASSERT_EQ(&i, event.data2());
  ASSERT_EQ(&i, ref.data2());
  ASSERT_EQ(nullptr, event.data1());
}

TEST(UserEvent, AsSDLEvent)
{
  const cen::user_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.user.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.user.timestamp, event.timestamp().count());
  ASSERT_EQ(underlying.user.code, event.code());
  ASSERT_EQ(underlying.user.windowID, event.window_id());
  ASSERT_EQ(underlying.user.data1, event.data1());
  ASSERT_EQ(underlying.user.data2, event.data2());
}
