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

#include "centurion/event.hpp"

TEST(TextInputEvent, Defaults)
{
  cen::text_input_event event;
  ASSERT_EQ(cen::event_type::text_input, event.type());
}

TEST(TextInputEvent, SetWindowId)
{
  cen::text_input_event event;

  constexpr Uint32 id = 23;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(TextInputEvent, WindowId)
{
  SDL_TextInputEvent sdl {};
  sdl.type = SDL_TEXTINPUT;
  sdl.windowID = 8;

  const cen::text_input_event event {sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(TextInputEvent, TextUtf8)
{
  const SDL_TextInputEvent sdl {SDL_TEXTINPUT, 1, 1, "hello"};
  const cen::text_input_event event {sdl};
  ASSERT_EQ("hello", event.text_utf8());
}

TEST(TextInputEvent, AsSDLEvent)
{
  const cen::text_input_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.text.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.text.timestamp, event.timestamp().count());
}
