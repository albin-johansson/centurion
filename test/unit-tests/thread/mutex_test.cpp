#include "thread/mutex.hpp"

#include <gtest/gtest.h>

TEST(Mutex, LockAndUnlock)
{
  cen::mutex mutex;

  ASSERT_TRUE(mutex.lock());
  ASSERT_TRUE(mutex.unlock());
}

TEST(Mutex, TryLock)
{
  cen::mutex mutex;

  ASSERT_EQ(mutex.try_lock(), cen::lock_status::success);
  ASSERT_TRUE(mutex.unlock());
}

TEST(Mutex, Get)
{
  cen::mutex mutex;
  ASSERT_TRUE(mutex.get());
}
