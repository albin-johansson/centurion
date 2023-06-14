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

#include "centurion/concurrency/locks.hpp"

TEST(LockStatus, Values)
{
  ASSERT_EQ(0, to_underlying(cen::lock_status::success));
  ASSERT_EQ(SDL_MUTEX_TIMEDOUT, to_underlying(cen::lock_status::timed_out));
  ASSERT_EQ(-1, to_underlying(cen::lock_status::error));
}

TEST(LockStatus, to_string)
{
  ASSERT_THROW(to_string(static_cast<cen::lock_status>(2)), cen::exception);

  ASSERT_EQ("success", to_string(cen::lock_status::success));
  ASSERT_EQ("timed_out", to_string(cen::lock_status::timed_out));
  ASSERT_EQ("error", to_string(cen::lock_status::error));

  std::cout << "lock_status::timed_out == " << cen::lock_status::timed_out << '\n';
}
