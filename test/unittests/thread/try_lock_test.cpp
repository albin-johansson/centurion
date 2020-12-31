#include "try_lock.hpp"

#include <gtest/gtest.h>

TEST(TryLock, BasicUsage)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  EXPECT_TRUE(lock.success());
}

TEST(TryLock, GetStatus)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  EXPECT_EQ(cen::lock_status::success, lock.get_status());

  EXPECT_TRUE(lock.success());
  EXPECT_FALSE(lock.timed_out());
  EXPECT_FALSE(lock.error());
}

TEST(TryLock, BoolConversion)
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  EXPECT_TRUE(lock);
}
