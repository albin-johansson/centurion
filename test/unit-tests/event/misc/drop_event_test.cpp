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

#include "centurion/misc_events.hpp"

TEST(DropEvent, Defaults)
{
  const cen::drop_event event;
  ASSERT_EQ(cen::event_type::drop_file, event.type());

  ASSERT_EQ(nullptr, event.file());
  ASSERT_EQ(0u, event.window_id());
  ASSERT_FALSE(event.will_free_file());
}

TEST(DropEvent, SetWillFreeFile)
{
  cen::drop_event event;

  event.set_will_free_file(true);
  ASSERT_TRUE(event.will_free_file());

  event.set_will_free_file(false);
  ASSERT_FALSE(event.will_free_file());
}

TEST(DropEvent, SetFile)
{
  cen::drop_event event;
  ASSERT_NO_THROW(event.set_file(nullptr));

  event.set_will_free_file(true);
  ASSERT_TRUE(event.will_free_file());

  /* This is the only time in the tests that a drop event should free the file,
     check the code coverage reports in order to see if it's freed. */
  event.set_file(static_cast<char*>(SDL_malloc(sizeof(char))));
}

TEST(DropEvent, SetWindowID)
{
  cen::drop_event event;

  event.set_window_id(84);
  ASSERT_EQ(84u, event.window_id());
}

TEST(DropEvent, AsSDLEvent)
{
  const cen::drop_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.drop.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.drop.timestamp, event.timestamp().count());
}
