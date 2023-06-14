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

#include "centurion/events/event_base.hpp"

#include <gtest/gtest.h>

#include "centurion/events/misc_events.hpp"

using sdl_event = SDL_QuitEvent;  // A simple SDL event type for testing
using common_event = cen::quit_event;

using namespace cen::literals::time_literals;

TEST(EventBase, SetTimestamp)
{
  common_event event;

  const auto time = 8'934_ms;
  event.set_timestamp(time);

  ASSERT_EQ(time, event.timestamp());
}

TEST(EventBase, SetType)
{
  common_event event;

  const auto type = cen::event_type::app_low_memory;
  event.set_type(type);

  ASSERT_EQ(type, event.type());
}

TEST(EventBase, Timestamp)
{
  const auto time = 8'321_ms;

  sdl_event sdl;
  sdl.timestamp = time.count();

  const common_event event {sdl};
  ASSERT_EQ(time, event.timestamp());
}

TEST(EventBase, Type)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event {sdl};
  ASSERT_EQ(cen::event_type::mouse_motion, event.type());
}

TEST(EventBase, Get)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event {sdl};
  const auto& internal = event.get();

  ASSERT_EQ(sdl.type, internal.type);
}
