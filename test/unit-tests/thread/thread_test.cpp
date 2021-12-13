#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

#include "concurrency.hpp"
#include "core/logging.hpp"

namespace {

auto dummy = [](void*) noexcept -> int {
  using namespace cen::literals;
  cen::Thread::Sleep(2_ms);
  return 0;
};

}  // namespace

static_assert(std::is_same_v<cen::ThreadID, SDL_threadID>);

static_assert(!std::is_copy_constructible_v<cen::Thread>);
static_assert(!std::is_copy_assignable_v<cen::Thread>);

TEST(Thread, Detach)
{
  cen::Thread thread{dummy};
  thread.Detach();

  ASSERT_FALSE(thread.IsJoinable());
  ASSERT_FALSE(thread.IsJoined());
  ASSERT_TRUE(thread.IsDetached());

  ASSERT_NO_THROW(thread.Detach());
}

TEST(Thread, Join)
{
  cen::Thread thread{dummy};
  thread.Join();

  ASSERT_FALSE(thread.IsJoinable());
  ASSERT_TRUE(thread.IsJoined());
  ASSERT_FALSE(thread.IsDetached());

  ASSERT_EQ(thread.Join(), 0);
}

TEST(Thread, IsJoinable)
{
  {  // Shouldn't be IsJoinable after join
    cen::Thread thread{dummy};
    ASSERT_TRUE(thread.IsJoinable());

    thread.Join();
    ASSERT_FALSE(thread.IsJoinable());
  }

  {  // Shouldn't be IsJoinable after detach
    cen::Thread thread{dummy};
    ASSERT_TRUE(thread.IsJoinable());

    thread.Detach();
    ASSERT_FALSE(thread.IsJoinable());
  }
}

TEST(Thread, IsJoined)
{
  cen::Thread thread{dummy};
  ASSERT_FALSE(thread.IsJoined());

  thread.Join();
  ASSERT_TRUE(thread.IsJoined());
}

TEST(Thread, IsDetached)
{
  cen::Thread thread{dummy};
  ASSERT_FALSE(thread.IsDetached());

  thread.Detach();
  ASSERT_TRUE(thread.IsDetached());
}

TEST(Thread, GetId)
{
  cen::Thread thread{dummy};
  ASSERT_EQ(thread.GetID(), SDL_GetThreadID(thread.get()));
}

TEST(Thread, GetName)
{
  {  // Custom name
    const cen::Thread thread{dummy, "foobar"};
    ASSERT_EQ(thread.GetName(), "foobar");
  }

  {  // Default name
    const cen::Thread thread{dummy};
    ASSERT_EQ(thread.GetName(), "thread");
  }
}

TEST(Thread, Get)
{
  cen::Thread thread{dummy};
  ASSERT_TRUE(thread.get());

  const auto& cThread = thread;
  ASSERT_TRUE(cThread.get());
}

TEST(Thread, Sleep)
{
  using ms = cen::milliseconds<Uint32>;
  ASSERT_NO_THROW(cen::Thread::Sleep(ms{2}));
  ASSERT_NO_THROW(cen::Thread::Sleep(ms{0}));
}

TEST(Thread, SetPriority)
{
  ASSERT_TRUE(cen::Thread::SetPriority(cen::ThreadPriority::Low));
}

TEST(Thread, CurrentId)
{
  ASSERT_EQ(cen::Thread::GetCurrentID(), SDL_ThreadID());
}

TEST(Thread, ToString)
{
  cen::Thread thread{dummy, "myThread"};
  cen::log_info_raw(cen::to_string(thread));
}

TEST(Thread, StreamOperator)
{
  cen::Thread thread{dummy, "myThread"};
  std::clog << cen::to_string(thread) << '\n';
}

#if CENTURION_HAS_FEATURE_CONCEPTS

TEST(Thread, Init)
{
  {  // No arguments
    auto thread = cen::Thread::Init([] {});
    ASSERT_TRUE(thread.IsJoinable());
    ASSERT_EQ(0, thread.Join());
  }

  {  // No arguments but returns integer
    auto thread = cen::Thread::Init([] { return 42; });
    ASSERT_TRUE(thread.IsJoinable());
    ASSERT_EQ(42, thread.Join());
  }

  {  // With user data
    int i = 123;
    auto thread = cen::Thread::Init([](int* data) { return *data; }, &i);
    ASSERT_TRUE(thread.IsJoinable());
    ASSERT_EQ(123, thread.Join());
  }
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS
