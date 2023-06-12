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

#include "centurion/events/window_events.hpp"

using id = cen::window_event_id;

TEST(WindowEventID, Values)
{
  ASSERT_EQ(SDL_WINDOWEVENT_NONE, to_underlying(id::none));
  ASSERT_EQ(SDL_WINDOWEVENT_SHOWN, to_underlying(id::shown));
  ASSERT_EQ(SDL_WINDOWEVENT_HIDDEN, to_underlying(id::hidden));
  ASSERT_EQ(SDL_WINDOWEVENT_EXPOSED, to_underlying(id::exposed));
  ASSERT_EQ(SDL_WINDOWEVENT_MOVED, to_underlying(id::moved));
  ASSERT_EQ(SDL_WINDOWEVENT_RESIZED, to_underlying(id::resized));
  ASSERT_EQ(SDL_WINDOWEVENT_SIZE_CHANGED, to_underlying(id::size_changed));
  ASSERT_EQ(SDL_WINDOWEVENT_MINIMIZED, to_underlying(id::minimized));
  ASSERT_EQ(SDL_WINDOWEVENT_MAXIMIZED, to_underlying(id::maximized));
  ASSERT_EQ(SDL_WINDOWEVENT_RESTORED, to_underlying(id::restored));
  ASSERT_EQ(SDL_WINDOWEVENT_ENTER, to_underlying(id::enter));
  ASSERT_EQ(SDL_WINDOWEVENT_LEAVE, to_underlying(id::leave));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_GAINED, to_underlying(id::focus_gained));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_LOST, to_underlying(id::focus_lost));
  ASSERT_EQ(SDL_WINDOWEVENT_CLOSE, to_underlying(id::close));
  ASSERT_EQ(SDL_WINDOWEVENT_TAKE_FOCUS, to_underlying(id::take_focus));
  ASSERT_EQ(SDL_WINDOWEVENT_HIT_TEST, to_underlying(id::hit_test));

#if SDL_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ(SDL_WINDOWEVENT_DISPLAY_CHANGED, to_underlying(id::display_changed));
  ASSERT_EQ(SDL_WINDOWEVENT_ICCPROF_CHANGED, to_underlying(id::icc_profile_changed));
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
}

TEST(WindowEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<id>(100)), cen::exception);

  ASSERT_EQ("none", to_string(id::none));
  ASSERT_EQ("shown", to_string(id::shown));
  ASSERT_EQ("hidden", to_string(id::hidden));
  ASSERT_EQ("exposed", to_string(id::exposed));
  ASSERT_EQ("moved", to_string(id::moved));
  ASSERT_EQ("resized", to_string(id::resized));
  ASSERT_EQ("size_changed", to_string(id::size_changed));
  ASSERT_EQ("minimized", to_string(id::minimized));
  ASSERT_EQ("maximized", to_string(id::maximized));
  ASSERT_EQ("restored", to_string(id::restored));
  ASSERT_EQ("enter", to_string(id::enter));
  ASSERT_EQ("leave", to_string(id::leave));
  ASSERT_EQ("focus_gained", to_string(id::focus_gained));
  ASSERT_EQ("focus_lost", to_string(id::focus_lost));
  ASSERT_EQ("close", to_string(id::close));
  ASSERT_EQ("take_focus", to_string(id::take_focus));
  ASSERT_EQ("hit_test", to_string(id::hit_test));

#if SDL_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ("display_changed", to_string(id::display_changed));
  ASSERT_EQ("icc_profile_changed", to_string(id::icc_profile_changed));
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  std::cout << "window_event_id::resized == " << id::resized << '\n';
}
