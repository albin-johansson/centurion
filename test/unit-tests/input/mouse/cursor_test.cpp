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

#include <type_traits>

#include "centurion/input/mouse.hpp"

static_assert(std::is_move_constructible_v<cen::cursor>);
static_assert(std::is_move_assignable_v<cen::cursor>);

static_assert(!std::is_copy_constructible_v<cen::cursor>);
static_assert(!std::is_copy_assignable_v<cen::cursor>);

static_assert(std::is_move_constructible_v<cen::cursor_handle>);
static_assert(std::is_move_assignable_v<cen::cursor_handle>);

static_assert(std::is_copy_constructible_v<cen::cursor_handle>);
static_assert(std::is_copy_assignable_v<cen::cursor_handle>);

TEST(Cursor, SystemCursorConstructor)
{
  ASSERT_NO_THROW(cen::cursor {cen::system_cursor::crosshair});

  const auto invalid = static_cast<cen::system_cursor>(83'948);
  ASSERT_THROW(cen::cursor {invalid}, cen::sdl_error);
}

TEST(Cursor, SurfaceConstructor)
{
  const cen::surface surface {"resources/panda.png"};
  const cen::ipoint hotspot {12, 14};
  ASSERT_NO_THROW(cen::cursor(surface, hotspot));

  const cen::ipoint outside {8341, 2342};
  ASSERT_THROW(cen::cursor(surface, outside), cen::sdl_error);
}

TEST(Cursor, Enable)
{
  {  // Normal usage
    cen::cursor cursor {cen::system_cursor::wait};

    cursor.enable();
    ASSERT_TRUE(cursor.is_enabled());
  }

  {  // Special case where two instances have the same type
    const auto id = cen::system_cursor::size_ne_sw;
    cen::cursor first {id};
    cen::cursor second {id};

    first.enable();
    ASSERT_TRUE(first.is_enabled());
    ASSERT_FALSE(second.is_enabled());

    second.enable();
    ASSERT_TRUE(second.is_enabled());
    ASSERT_FALSE(first.is_enabled());
  }
}

TEST(Cursor, ForceRedraw)
{
  cen::cursor cursor {cen::system_cursor::ibeam};
  cursor.enable();

  ASSERT_NO_THROW(cen::cursor::force_redraw());

  ASSERT_TRUE(cursor.is_enabled());  // ensure state of active cursor
}

TEST(Cursor, Reset)
{
  cen::cursor::reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor cursor {cen::system_cursor::crosshair};
  cursor.enable();
  ASSERT_NE(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor::reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());
}

TEST(Cursor, SetVisible)
{
  ASSERT_TRUE(cen::cursor::visible());

  cen::cursor::set_visible(false);
  ASSERT_FALSE(cen::cursor::visible());

  cen::cursor::set_visible(true);
  ASSERT_TRUE(cen::cursor::visible());
}
