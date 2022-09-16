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

#include "centurion/mouse.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // ...

static_assert(std::is_final_v<cen::mouse>);

static_assert(std::is_nothrow_move_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_move_assignable_v<cen::mouse>);

static_assert(std::is_nothrow_copy_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_copy_assignable_v<cen::mouse>);

TEST(Mouse, Defaults)
{
  const cen::mouse mouse;

  ASSERT_EQ(0, mouse.x());
  ASSERT_EQ(0, mouse.y());

  ASSERT_FALSE(mouse.is_left_pressed());
  ASSERT_FALSE(mouse.is_middle_pressed());
  ASSERT_FALSE(mouse.is_right_pressed());

  ASSERT_FALSE(mouse.was_left_released());
  ASSERT_FALSE(mouse.was_middle_released());
  ASSERT_FALSE(mouse.was_right_released());

  ASSERT_FALSE(mouse.was_moved());
}

TEST(Mouse, Update)
{
  cen::mouse mouse;
  ASSERT_NO_THROW(mouse.update());
}

TEST(Mouse, ToString)
{
  const cen::mouse mouse;
  ASSERT_EQ("mouse(x: 0, y: 0)", cen::to_string(mouse));

  std::cout << mouse << '\n';
}