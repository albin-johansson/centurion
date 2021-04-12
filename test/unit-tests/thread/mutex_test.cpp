#include "thread/mutex.hpp"

#include <gtest/gtest.h>

TEST(Mutex, LockAndUnlock)
{
  cen::mutex mutex;

  EXPECT_TRUE(mutex.lock());
  EXPECT_TRUE(mutex.unlock());
}

TEST(Mutex, TryLock)
{
  cen::mutex mutex;

  EXPECT_EQ(mutex.try_lock(), cen::lock_status::success);
  EXPECT_TRUE(mutex.unlock());
}

TEST(Mutex, Get)
{
  cen::mutex mutex;
  EXPECT_TRUE(mutex.get());
}
