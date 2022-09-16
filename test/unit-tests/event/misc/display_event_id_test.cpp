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

#include "centurion/misc_events.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

using id = cen::display_event_id;

TEST(DisplayEventID, Values)
{
  ASSERT_EQ(SDL_DISPLAYEVENT_NONE, to_underlying(id::none));
  ASSERT_EQ(SDL_DISPLAYEVENT_ORIENTATION, to_underlying(id::orientation));
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, to_underlying(id::connected));
  ASSERT_EQ(SDL_DISPLAYEVENT_DISCONNECTED, to_underlying(id::disconnected));
}

TEST(DisplayEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<id>(4)), cen::exception);

  ASSERT_EQ("none", to_string(id::none));
  ASSERT_EQ("orientation", to_string(id::orientation));
  ASSERT_EQ("connected", to_string(id::connected));
  ASSERT_EQ("disconnected", to_string(id::disconnected));

  std::cout << "display_event_id::connected == " << id::connected << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)