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

#include "centurion/io/file_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(FileMode, ToString)
{
  ASSERT_EQ("r", to_string(cen::file_mode::r));
  ASSERT_EQ("rb", to_string(cen::file_mode::rb));

  ASSERT_EQ("w", to_string(cen::file_mode::w));
  ASSERT_EQ("wb", to_string(cen::file_mode::wb));

  ASSERT_EQ("a", to_string(cen::file_mode::a));
  ASSERT_EQ("ab", to_string(cen::file_mode::ab));

  ASSERT_EQ("rx", to_string(cen::file_mode::rx));
  ASSERT_EQ("rbx", to_string(cen::file_mode::rbx));

  ASSERT_EQ("wx", to_string(cen::file_mode::wx));
  ASSERT_EQ("wbx", to_string(cen::file_mode::wbx));

  ASSERT_EQ("ax", to_string(cen::file_mode::ax));
  ASSERT_EQ("abx", to_string(cen::file_mode::abx));

  std::cout << "file_mode::rb == " << cen::file_mode::rb << '\n';
}