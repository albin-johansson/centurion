#include <gtest/gtest.h>

#include "concurrency.hpp"

TEST(Mutex, LockAndUnlock)
{
  cen::Mutex mutex;

  ASSERT_TRUE(mutex.Lock());
  ASSERT_TRUE(mutex.Unlock());
}

TEST(Mutex, TryLock)
{
  cen::Mutex mutex;

  ASSERT_EQ(mutex.TryLock(), cen::LockStatus::Success);
  ASSERT_TRUE(mutex.Unlock());
}

TEST(Mutex, Get)
{
  cen::Mutex mutex;
  ASSERT_TRUE(mutex.get());
}
