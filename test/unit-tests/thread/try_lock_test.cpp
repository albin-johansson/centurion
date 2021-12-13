#include <gtest/gtest.h>

#include <type_traits>

#include "system/concurrency.hpp"

static_assert(!std::is_copy_constructible_v<cen::TryLock>);
static_assert(!std::is_copy_assignable_v<cen::TryLock>);

TEST(TryLock, BasicUsage)
{
  cen::Mutex mutex;
  cen::TryLock lock{mutex};

  ASSERT_TRUE(lock.DidLock());
}

TEST(TryLock, GetStatus)
{
  cen::Mutex mutex;
  cen::TryLock lock{mutex};

  ASSERT_EQ(cen::LockStatus::Success, lock.GetStatus());

  ASSERT_TRUE(lock.DidLock());
  ASSERT_FALSE(lock.DidTimeOut());
  ASSERT_FALSE(lock.DidFail());
}

TEST(TryLock, BoolConversion)
{
  cen::Mutex mutex;
  cen::TryLock lock{mutex};

  ASSERT_TRUE(lock);
}
