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

#include "centurion/common/sdl_string.hpp"

#include <gtest/gtest.h>

TEST(SDLString, Constructor)
{
  ASSERT_NO_THROW(cen::sdl_string {nullptr});

  const cen::sdl_string str {nullptr};
  ASSERT_FALSE(str);
}

TEST(SDLString, Get)
{
  SDL_SetClipboardText("foo");
  const cen::sdl_string str {SDL_GetClipboardText()};
  ASSERT_STREQ(str.get(), "foo");
}

TEST(SDLString, Copy)
{
  {  // Valid string
    SDL_SetClipboardText("bar");
    const cen::sdl_string str {SDL_GetClipboardText()};
    const auto copy = str.copy();
    ASSERT_EQ("bar", copy);
  }

  {  // Empty string
    SDL_SetClipboardText(nullptr);
    const cen::sdl_string empty {SDL_GetClipboardText()};
    ASSERT_TRUE(empty.copy().empty());
  }

  {  // Null string
    const cen::sdl_string str {nullptr};
    ASSERT_EQ("", str.copy());
  }
}
