#include <gtest/gtest.h>

#include "centurion/concurrency.hpp"

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

TEST(Mutex, Data)
{
  cen::mutex mutex;
  ASSERT_TRUE(mutex.data());

  const auto& ref = mutex;
  ASSERT_TRUE(ref.data());
}
