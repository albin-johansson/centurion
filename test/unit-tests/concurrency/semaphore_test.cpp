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

#include "centurion/concurrency/semaphore.hpp"

#include <gtest/gtest.h>

#include "centurion/common/literals.hpp"

TEST(Semaphore, Acquire)
{
  cen::semaphore semaphore {1};

  ASSERT_TRUE(semaphore.acquire());
  ASSERT_EQ(semaphore.count(), 0u);

  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.count(), 1u);
}

TEST(Semaphore, AcquireMilliseconds)
{
  using namespace cen::literals::time_literals;

  cen::semaphore semaphore {0u};

  ASSERT_EQ(semaphore.acquire(1_ms), cen::lock_status::timed_out);
  ASSERT_TRUE(semaphore.release());

  ASSERT_EQ(semaphore.acquire(1_ms), cen::lock_status::success);
}

TEST(Semaphore, TryAcquire)
{
  cen::semaphore semaphore {0u};

  ASSERT_EQ(semaphore.try_acquire(), cen::lock_status::timed_out);
  ASSERT_TRUE(semaphore.release());

  ASSERT_EQ(semaphore.try_acquire(), cen::lock_status::success);
}

TEST(Semaphore, Release)
{
  cen::semaphore semaphore {0u};
  ASSERT_EQ(semaphore.count(), 0u);

  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.count(), 1u);
}

TEST(Semaphore, Count)
{
  constexpr Uint32 tokens = 32;

  cen::semaphore semaphore {tokens};
  ASSERT_EQ(semaphore.count(), tokens);
}
