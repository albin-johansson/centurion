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

#include "centurion/common/literals.hpp"
#include "centurion/concurrency.hpp"

TEST(Condition, Signal)
{
  cen::condition cond;
  ASSERT_TRUE(cond.signal());
}

TEST(Condition, Broadcast)
{
  cen::condition cond;
  ASSERT_TRUE(cond.broadcast());
}

TEST(Condition, Wait)
{
  cen::mutex mutex;
  cen::condition cond;

  ASSERT_TRUE(mutex.lock());

  cen::thread thread {[](void* data) {
                        auto* cond = reinterpret_cast<cen::condition*>(data);

                        using namespace cen::literals::time_literals;
                        cen::thread::sleep(50_ms);

                        cond->signal();

                        return 0;
                      },
                      "thread",
                      &cond};

  ASSERT_TRUE(cond.wait(mutex));
  ASSERT_TRUE(mutex.unlock());
}
