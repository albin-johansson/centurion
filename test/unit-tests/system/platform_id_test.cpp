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

#include <iostream>  // cout

#include "centurion/system.hpp"

TEST(PlatformID, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::platform_id>(100)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::platform_id::unknown));
  ASSERT_EQ("windows", to_string(cen::platform_id::windows));
  ASSERT_EQ("macos", to_string(cen::platform_id::macos));
  ASSERT_EQ("linux_os", to_string(cen::platform_id::linux_os));
  ASSERT_EQ("ios", to_string(cen::platform_id::ios));
  ASSERT_EQ("android", to_string(cen::platform_id::android));

  std::cout << "platform_id::windows == " << cen::platform_id::windows << '\n';
}