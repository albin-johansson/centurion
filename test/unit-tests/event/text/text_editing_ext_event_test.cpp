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

#if SDL_VERSION_ATLEAST(2, 0, 22)

TEST(TextEditingExtEvent, Defaults)
{
  cen::text_editing_ext_event event;
  ASSERT_EQ(cen::event_type::text_editing_ext, event.type());
}

TEST(TextEditingEvent, SetStart)
{
  cen::text_editing_event event;

  event.set_start(42);
  ASSERT_EQ(42, event.start());
}

TEST(TextEditingEvent, SetLength)
{
  cen::text_editing_event event;

  event.set_length(18);
  ASSERT_EQ(18, event.length());
}

TEST(TextEditingEvent, SetWindowId)
{
  cen::text_editing_event event;

  const Uint32 id = 2;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(TextEditingExtEvent, AsSDLEvent)
{
  const cen::text_editing_ext_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.edit.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.edit.timestamp, event.timestamp().count());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
