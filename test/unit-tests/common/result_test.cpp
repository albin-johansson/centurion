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

#include "centurion/common.hpp"

TEST(Result, Values)
{
  ASSERT_EQ(cen::result {true}, cen::success);
  ASSERT_EQ(cen::result {false}, cen::failure);

  ASSERT_NE(cen::result {false}, cen::success);
  ASSERT_NE(cen::result {true}, cen::failure);

  ASSERT_NE(cen::success, cen::failure);

  ASSERT_TRUE(cen::success);
  ASSERT_FALSE(cen::failure);
}

TEST(Result, ToString)
{
  std::cout << "result (success): '" << cen::success << "'\n";
  std::cout << "result (failure): '" << cen::failure << "'\n";
}
