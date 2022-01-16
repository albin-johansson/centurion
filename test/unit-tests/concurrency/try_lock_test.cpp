#include <gtest/gtest.h>

#include <type_traits>

#include "concurrency.hpp"

static_assert(!std::is_copy_constructible_v<cen::try_lock>);
static_assert(!std::is_copy_assignable_v<cen::try_lock>);

TEST(TryLock, BasicUsage)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_TRUE(lock.locked());
}

TEST(TryLock, GetStatus)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_EQ(cen::lock_status::success, lock.status());

  ASSERT_TRUE(lock.locked());
  ASSERT_FALSE(lock.timed_out());
  ASSERT_FALSE(lock.failed());
}

TEST(TryLock, BoolConversion)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  ASSERT_TRUE(lock);
}
