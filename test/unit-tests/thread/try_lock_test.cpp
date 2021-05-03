#include "thread/try_lock.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(!std::is_copy_constructible_v<cen::try_lock>);
static_assert(!std::is_copy_assignable_v<cen::try_lock>);

TEST(TryLock, BasicUsage)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_TRUE(lock.success());
}

TEST(TryLock, GetStatus)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_EQ(cen::lock_status::success, lock.get_status());

  ASSERT_TRUE(lock.success());
  ASSERT_FALSE(lock.timed_out());
  ASSERT_FALSE(lock.error());
}

TEST(TryLock, BoolConversion)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_TRUE(lock);
}
