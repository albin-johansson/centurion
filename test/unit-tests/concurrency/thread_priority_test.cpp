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

#include "centurion/concurrency/thread.hpp"

TEST(ThreadPriority, Values)
{
  ASSERT_EQ(SDL_THREAD_PRIORITY_LOW, to_underlying(cen::thread_priority::low));
  ASSERT_EQ(SDL_THREAD_PRIORITY_NORMAL, to_underlying(cen::thread_priority::normal));
  ASSERT_EQ(SDL_THREAD_PRIORITY_HIGH, to_underlying(cen::thread_priority::high));
  ASSERT_EQ(SDL_THREAD_PRIORITY_TIME_CRITICAL, to_underlying(cen::thread_priority::critical));
}

TEST(ThreadPriority, to_string)
{
  ASSERT_THROW(to_string(static_cast<cen::thread_priority>(5)), cen::exception);

  ASSERT_EQ("low", to_string(cen::thread_priority::low));
  ASSERT_EQ("normal", to_string(cen::thread_priority::normal));
  ASSERT_EQ("high", to_string(cen::thread_priority::high));
  ASSERT_EQ("critical", to_string(cen::thread_priority::critical));

  std::cout << "thread_priority::high == " << cen::thread_priority::high << '\n';
}
