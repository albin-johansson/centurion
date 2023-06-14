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

#include <iostream>
#include <type_traits>

#include "centurion/concurrency.hpp"
#include "centurion/logging.hpp"

namespace {

auto dummy = [](void*) noexcept -> int {
  using namespace cen::literals;
  cen::thread::sleep(2_ms);
  return 0;
};

}  // namespace

static_assert(std::is_same_v<cen::thread_id, SDL_threadID>);

static_assert(!std::is_copy_constructible_v<cen::thread>);
static_assert(!std::is_copy_assignable_v<cen::thread>);

TEST(Thread, Detach)
{
  cen::thread thread {dummy};
  thread.detach();

  ASSERT_FALSE(thread.joinable());
  ASSERT_FALSE(thread.joined());
  ASSERT_TRUE(thread.detached());

  ASSERT_NO_THROW(thread.detach());
}

TEST(Thread, Join)
{
  cen::thread thread {dummy};
  thread.join();

  ASSERT_FALSE(thread.joinable());
  ASSERT_TRUE(thread.joined());
  ASSERT_FALSE(thread.detached());

  ASSERT_EQ(thread.join(), 0);
}

TEST(Thread, Joinable)
{
  {  // Shouldn't be joinable after join
    cen::thread thread {dummy};
    ASSERT_TRUE(thread.joinable());

    thread.join();
    ASSERT_FALSE(thread.joinable());
  }

  {  // Shouldn't be joinable after detach
    cen::thread thread {dummy};
    ASSERT_TRUE(thread.joinable());

    thread.detach();
    ASSERT_FALSE(thread.joinable());
  }
}

TEST(Thread, Joined)
{
  cen::thread thread {dummy};
  ASSERT_FALSE(thread.joined());

  thread.join();
  ASSERT_TRUE(thread.joined());
}

TEST(Thread, Detached)
{
  cen::thread thread {dummy};
  ASSERT_FALSE(thread.detached());

  thread.detach();
  ASSERT_TRUE(thread.detached());
}

TEST(Thread, ID)
{
  cen::thread thread {dummy};
  ASSERT_EQ(thread.id(), SDL_GetThreadID(thread.data()));
}

TEST(Thread, Name)
{
  {  // Custom name
    const cen::thread thread {dummy, "foobar"};
    ASSERT_EQ(thread.name(), "foobar");
  }

  {  // Default name
    const cen::thread thread {dummy};
    ASSERT_EQ(thread.name(), "thread");
  }
}

TEST(Thread, Data)
{
  cen::thread thread {dummy};
  ASSERT_TRUE(thread.data());

  const auto& ref = thread;
  ASSERT_TRUE(ref.data());
}

TEST(Thread, Sleep)
{
  using namespace cen::literals::time_literals;
  ASSERT_NO_THROW(cen::thread::sleep(2_ms));
  ASSERT_NO_THROW(cen::thread::sleep(0_ms));
}

TEST(Thread, SetPriority)
{
  ASSERT_TRUE(cen::thread::set_priority(cen::thread_priority::low));
}

TEST(Thread, CurrentId)
{
  ASSERT_EQ(cen::thread::current_id(), SDL_ThreadID());
}

TEST(Thread, StreamOperator)
{
  cen::thread thread {dummy, "cen-thread"};
  std::cout << thread << '\n';
}

#if CENTURION_HAS_FEATURE_CONCEPTS

TEST(Thread, Init)
{
  {  // No arguments
    auto thread = cen::thread::init([] {});
    ASSERT_TRUE(thread.joinable());
    ASSERT_EQ(0, thread.join());
  }

  {  // No arguments but returns integer
    auto thread = cen::thread::init([] { return 42; });
    ASSERT_TRUE(thread.joinable());
    ASSERT_EQ(42, thread.join());
  }

  {  // With user data
    int i = 123;
    auto thread = cen::thread::init([](int* data) { return *data; }, &i);
    ASSERT_TRUE(thread.joinable());
    ASSERT_EQ(123, thread.join());
  }
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS
