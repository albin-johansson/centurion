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

#include "centurion/common/errors.hpp"

static_assert(std::has_virtual_destructor_v<cen::exception>);
static_assert(std::is_default_constructible_v<cen::exception>);
static_assert(std::is_nothrow_move_constructible_v<cen::exception>);
static_assert(std::is_nothrow_destructible_v<cen::exception>);

TEST(Exception, NoArgsConstructor)
{
  const cen::exception exception;
  ASSERT_STREQ("?", exception.what());
}

TEST(Exception, StringConstructor)
{
  const char* normal_msg = "Hello, world!";

  // Limit is 128 characters, with last character reserved for null-terminator.
  const char* max_msg =
      ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"  // 32
      "--------------------------------"  // 64
      "................................"  // 96
      "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";  // 127

  const char* overflow_msg =
      ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"   // 32
      "--------------------------------"   // 64
      "................................"   // 96
      "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!X";  // 128

  {
    const cen::exception exception {normal_msg};
    ASSERT_STREQ(normal_msg, exception.what());
  }

  {
    const cen::exception exception {max_msg};
    ASSERT_STREQ(max_msg, exception.what());
  }

  {
    const cen::exception exception {overflow_msg};
    ASSERT_STREQ(max_msg, exception.what());
  }
}
