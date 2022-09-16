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

#include "centurion/keyboard.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // ...

static_assert(std::is_final_v<cen::keyboard>);

static_assert(std::is_default_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_destructible_v<cen::keyboard>);

static_assert(std::is_nothrow_move_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_move_assignable_v<cen::keyboard>);

static_assert(std::is_nothrow_copy_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_copy_assignable_v<cen::keyboard>);

TEST(Keyboard, Refresh)
{
  cen::keyboard keyboard;
  ASSERT_NO_THROW(keyboard.refresh());
}

TEST(Keyboard, IsPressed)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.is_pressed(SDL_SCANCODE_A));
  ASSERT_FALSE(keyboard.is_pressed(SDLK_a));

  ASSERT_FALSE(keyboard.is_pressed(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.is_pressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.is_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsHeld)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.is_held(SDL_SCANCODE_X));
  ASSERT_FALSE(keyboard.is_held(SDLK_x));

  ASSERT_FALSE(keyboard.is_held(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.is_held(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.is_held(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustPressed)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.just_pressed(SDL_SCANCODE_V));
  ASSERT_FALSE(keyboard.just_pressed(SDLK_v));

  ASSERT_FALSE(keyboard.just_pressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.just_pressed(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.just_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustReleased)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.just_released(SDL_SCANCODE_U));
  ASSERT_FALSE(keyboard.just_released(SDLK_u));

  ASSERT_FALSE(keyboard.just_released(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES}));
  ASSERT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, Size)
{
  cen::keyboard keyboard;
  ASSERT_EQ(cen::scan_code::count(), keyboard.size());
}

TEST(Keyboard, ToString)
{
  cen::keyboard keyboard;

  ASSERT_EQ("keyboard(size: " + std::to_string(keyboard.size()) + ")",
            cen::to_string(keyboard));

  std::cout << keyboard << '\n';
}
