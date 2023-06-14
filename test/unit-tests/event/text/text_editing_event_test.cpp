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

#include "centurion/events/misc_events.hpp"

TEST(TextEditingEvent, Defaults)
{
  cen::text_editing_event event;
  ASSERT_EQ(cen::event_type::text_editing, event.type());
}

TEST(TextEditingEvent, SetWindowId)
{
  cen::text_editing_event event;

  constexpr Uint32 id = 8;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(TextEditingEvent, SetStart)
{
  cen::text_editing_event event;

  constexpr auto start = 4;
  event.set_start(start);

  ASSERT_EQ(start, event.start());
}

TEST(TextEditingEvent, SetLength)
{
  cen::text_editing_event event;

  constexpr auto length = 9;
  event.set_length(length);

  ASSERT_EQ(length, event.length());

  event.set_length(-1);
  ASSERT_EQ(0, event.length());

  event.set_length(33);
  ASSERT_EQ(32, event.length());
}

TEST(TextEditingEvent, WindowId)
{
  SDL_TextEditingEvent sdl {};
  sdl.windowID = 7;

  const cen::text_editing_event event {sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(TextEditingEvent, Start)
{
  SDL_TextEditingEvent sdl {};
  sdl.start = 4;

  const cen::text_editing_event event {sdl};
  ASSERT_EQ(sdl.start, event.start());
}

TEST(TextEditingEvent, Length)
{
  {  // Good length
    SDL_TextEditingEvent sdl {};
    sdl.length = 4;

    const cen::text_editing_event event {sdl};
    ASSERT_EQ(sdl.length, event.length());
  }

  {  // Underflow length
    SDL_TextEditingEvent sdl {};
    sdl.length = -1;

    const cen::text_editing_event event {sdl};
    ASSERT_EQ(0, event.length());
  }

  {  // Overflow length
    SDL_TextEditingEvent sdl {};
    sdl.length = 33;

    const cen::text_editing_event event {sdl};
    ASSERT_EQ(32, event.length());
  }
}

TEST(TextEditingEvent, AsSDLEvent)
{
  const cen::text_editing_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.edit.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.edit.timestamp, event.timestamp().count());
}
