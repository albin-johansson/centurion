#include "thread.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

#include "log.hpp"

namespace {

auto dummy = [](void*) noexcept -> int {
  using namespace cen::literals;
  cen::thread::sleep(10_ms);
  return 0;
};

}

static_assert(std::is_same_v<cen::thread::id, SDL_threadID>);
static_assert(std::is_same_v<cen::thread::task_type, SDL_ThreadFunction>);

TEST(Thread, Detach)
{
  cen::thread thread{dummy};
  thread.detach();

  EXPECT_FALSE(thread.joinable());
  EXPECT_FALSE(thread.was_joined());
  EXPECT_TRUE(thread.was_detached());

  EXPECT_NO_THROW(thread.detach());
}

TEST(Thread, Join)
{
  cen::thread thread{dummy};
  thread.join();

  EXPECT_FALSE(thread.joinable());
  EXPECT_TRUE(thread.was_joined());
  EXPECT_FALSE(thread.was_detached());

  EXPECT_EQ(thread.join(), 0);
}

TEST(Thread, Joinable)
{
  {  // Shouldn't be joinable after join
    cen::thread thread{dummy};
    EXPECT_TRUE(thread.joinable());

    thread.join();
    EXPECT_FALSE(thread.joinable());
  }

  {  // Shouldn't be joinable after detach
    cen::thread thread{dummy};
    EXPECT_TRUE(thread.joinable());

    thread.detach();
    EXPECT_FALSE(thread.joinable());
  }
}

TEST(Thread, WasJoined)
{
  cen::thread thread{dummy};
  EXPECT_FALSE(thread.was_joined());

  thread.join();
  EXPECT_TRUE(thread.was_joined());
}

TEST(Thread, WasDetached)
{
  cen::thread thread{dummy};
  EXPECT_FALSE(thread.was_detached());

  thread.detach();
  EXPECT_TRUE(thread.was_detached());
}

TEST(Thread, GetId)
{
  cen::thread thread{dummy};
  EXPECT_EQ(thread.get_id(), SDL_GetThreadID(thread.get()));
}

TEST(Thread, Name)
{
  {  // Custom name
    const auto name = "foobar";
    const cen::thread thread{dummy, name};
    EXPECT_EQ(thread.name(), name);
  }

  {  // Default name
    const cen::thread thread{dummy};
    EXPECT_EQ(thread.name(), "thread");
  }
}

TEST(Thread, Get)
{
  cen::thread thread{dummy};
  EXPECT_TRUE(thread.get());

  const auto& cThread = thread;
  EXPECT_TRUE(cThread.get());
}

TEST(Thread, Sleep)
{
  using ms = cen::milliseconds<cen::u32>;
  EXPECT_NO_THROW(cen::thread::sleep(ms{10}));
  EXPECT_NO_THROW(cen::thread::sleep(ms{0}));
}

TEST(Thread, SetPriority)
{
  EXPECT_TRUE(cen::thread::set_priority(cen::thread_priority::low));
}

TEST(Thread, CurrentId)
{
  EXPECT_EQ(cen::thread::current_id(), SDL_ThreadID());
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

TEST_CASE("thread stream operator", "[!mayfail][thread]")
{
  cen::thread thread{dummy, "myThread"};
  std::cout << "<< operator: " << thread << '\n';
}

TEST_CASE("thread_priority values", "[thread]")
{
  SECTION("==")
  {
    CHECK(cen::thread_priority::low == SDL_THREAD_PRIORITY_LOW);
    CHECK(cen::thread_priority::normal == SDL_THREAD_PRIORITY_NORMAL);
    CHECK(cen::thread_priority::high == SDL_THREAD_PRIORITY_HIGH);
    CHECK(cen::thread_priority::critical == SDL_THREAD_PRIORITY_TIME_CRITICAL);

    CHECK(SDL_THREAD_PRIORITY_LOW == cen::thread_priority::low);
    CHECK(SDL_THREAD_PRIORITY_NORMAL == cen::thread_priority::normal);
    CHECK(SDL_THREAD_PRIORITY_HIGH == cen::thread_priority::high);
    CHECK(SDL_THREAD_PRIORITY_TIME_CRITICAL == cen::thread_priority::critical);
  }

  SECTION("!=")
  {
    CHECK(cen::thread_priority::high != SDL_THREAD_PRIORITY_TIME_CRITICAL);
    CHECK(SDL_THREAD_PRIORITY_LOW != cen::thread_priority::normal);
  }
}