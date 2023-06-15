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

#include "centurion/io/seek_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/common/utils.hpp"

TEST(SeekMode, Values)
{
  ASSERT_EQ(RW_SEEK_SET, to_underlying(cen::seek_mode::from_beginning));
  ASSERT_EQ(RW_SEEK_CUR, to_underlying(cen::seek_mode::relative_to_current));
  ASSERT_EQ(RW_SEEK_END, to_underlying(cen::seek_mode::relative_to_end));
}

TEST(SeekMode, ToString)
{
  ASSERT_EQ("from_beginning", to_string(cen::seek_mode::from_beginning));
  ASSERT_EQ("relative_to_current", to_string(cen::seek_mode::relative_to_current));
  ASSERT_EQ("relative_to_end", to_string(cen::seek_mode::relative_to_end));

  std::cout << "seek_mode::from_beginning == " << cen::seek_mode::from_beginning << '\n';
}
