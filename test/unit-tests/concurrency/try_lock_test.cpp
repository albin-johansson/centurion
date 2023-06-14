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

#include <type_traits>

#include "centurion/concurrency.hpp"

static_assert(!std::is_copy_constructible_v<cen::try_lock>);
static_assert(!std::is_copy_assignable_v<cen::try_lock>);

TEST(TryLock, BasicUsage)
{
  cen::mutex mutex;
  cen::try_lock lock {mutex};

  ASSERT_TRUE(lock.locked());
}

TEST(TryLock, GetStatus)
{
  cen::mutex mutex;
  cen::try_lock lock {mutex};

  ASSERT_EQ(cen::lock_status::success, lock.status());

  ASSERT_TRUE(lock.locked());
  ASSERT_FALSE(lock.timed_out());
  ASSERT_FALSE(lock.failed());
}

TEST(TryLock, BoolConversion)
{
  cen::mutex mutex;
  cen::try_lock lock {mutex};

  ASSERT_TRUE(lock);
}
