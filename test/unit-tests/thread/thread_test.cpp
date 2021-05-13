#include "thread/thread.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

#include "core/log.hpp"

namespace {

auto dummy = [](void*) noexcept -> int {
  using namespace cen::literals;
  cen::thread::sleep(2_ms);
  return 0;
};

}

static_assert(std::is_same_v<cen::thread::id, SDL_threadID>);
static_assert(std::is_same_v<cen::thread::task_type, SDL_ThreadFunction>);

static_assert(!std::is_copy_constructible_v<cen::thread>);
static_assert(!std::is_copy_assignable_v<cen::thread>);

TEST(Thread, Detach)
{
  cen::thread thread{dummy};
  thread.detach();

  ASSERT_FALSE(thread.joinable());
  ASSERT_FALSE(thread.was_joined());
  ASSERT_TRUE(thread.was_detached());

  ASSERT_NO_THROW(thread.detach());
}

TEST(Thread, Join)
{
  cen::thread thread{dummy};
  thread.join();

  ASSERT_FALSE(thread.joinable());
  ASSERT_TRUE(thread.was_joined());
  ASSERT_FALSE(thread.was_detached());

  ASSERT_EQ(thread.join(), 0);
}

TEST(Thread, Joinable)
{
  {  // Shouldn't be joinable after join
    cen::thread thread{dummy};
    ASSERT_TRUE(thread.joinable());

    thread.join();
    ASSERT_FALSE(thread.joinable());
  }

  {  // Shouldn't be joinable after detach
    cen::thread thread{dummy};
    ASSERT_TRUE(thread.joinable());

    thread.detach();
    ASSERT_FALSE(thread.joinable());
  }
}

TEST(Thread, WasJoined)
{
  cen::thread thread{dummy};
  ASSERT_FALSE(thread.was_joined());

  thread.join();
  ASSERT_TRUE(thread.was_joined());
}

TEST(Thread, WasDetached)
{
  cen::thread thread{dummy};
  ASSERT_FALSE(thread.was_detached());

  thread.detach();
  ASSERT_TRUE(thread.was_detached());
}

TEST(Thread, GetId)
{
  cen::thread thread{dummy};
  ASSERT_EQ(thread.get_id(), SDL_GetThreadID(thread.get()));
}

TEST(Thread, Name)
{
  {  // Custom name
    const auto name = "foobar";
    const cen::thread thread{dummy, name};
    ASSERT_EQ(thread.name(), name);
  }

  {  // Default name
    const cen::thread thread{dummy};
    ASSERT_EQ(thread.name(), "thread");
  }
}

TEST(Thread, Get)
{
  cen::thread thread{dummy};
  ASSERT_TRUE(thread.get());

  const auto& cThread = thread;
  ASSERT_TRUE(cThread.get());
}

TEST(Thread, Sleep)
{
  using ms = cen::milliseconds<cen::u32>;
  ASSERT_NO_THROW(cen::thread::sleep(ms{2}));
  ASSERT_NO_THROW(cen::thread::sleep(ms{0}));
}

TEST(Thread, SetPriority)
{
  ASSERT_TRUE(cen::thread::set_priority(cen::thread_priority::low));
}

TEST(Thread, CurrentId)
{
  ASSERT_EQ(cen::thread::current_id(), SDL_ThreadID());
}

TEST(Thread, ToString)
{
  cen::thread thread{dummy, "myThread"};
  cen::log::put(cen::to_string(thread));
}

TEST(Thread, StreamOperator)
{
  cen::thread thread{dummy, "myThread"};
  std::cout << "COUT: " << cen::to_string(thread) << '\n';
}

TEST(Thread, ThreadPriorityValues)
{
  ASSERT_EQ(cen::thread_priority::low, SDL_THREAD_PRIORITY_LOW);
  ASSERT_EQ(cen::thread_priority::normal, SDL_THREAD_PRIORITY_NORMAL);
  ASSERT_EQ(cen::thread_priority::high, SDL_THREAD_PRIORITY_HIGH);
  ASSERT_EQ(cen::thread_priority::critical, SDL_THREAD_PRIORITY_TIME_CRITICAL);

  ASSERT_EQ(SDL_THREAD_PRIORITY_LOW, cen::thread_priority::low);
  ASSERT_EQ(SDL_THREAD_PRIORITY_NORMAL, cen::thread_priority::normal);
  ASSERT_EQ(SDL_THREAD_PRIORITY_HIGH, cen::thread_priority::high);
  ASSERT_EQ(SDL_THREAD_PRIORITY_TIME_CRITICAL, cen::thread_priority::critical);

  ASSERT_NE(cen::thread_priority::high, SDL_THREAD_PRIORITY_TIME_CRITICAL);
  ASSERT_NE(SDL_THREAD_PRIORITY_LOW, cen::thread_priority::normal);
}
