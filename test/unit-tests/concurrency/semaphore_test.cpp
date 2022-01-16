#include <gtest/gtest.h>

#include "concurrency.hpp"

TEST(Semaphore, Acquire)
{
  cen::semaphore semaphore{1};

  ASSERT_TRUE(semaphore.acquire());
  ASSERT_EQ(semaphore.count(), 0u);

  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.count(), 1u);
}

TEST(Semaphore, AcquireMilliseconds)
{
  using namespace cen::literals::time_literals;

  cen::semaphore semaphore{0u};

  ASSERT_EQ(semaphore.acquire(1_ms), cen::lock_status::timed_out);
  ASSERT_TRUE(semaphore.release());

  ASSERT_EQ(semaphore.acquire(1_ms), cen::lock_status::success);
}

TEST(Semaphore, TryAcquire)
{
  cen::semaphore semaphore{0u};

  ASSERT_EQ(semaphore.try_acquire(), cen::lock_status::timed_out);
  ASSERT_TRUE(semaphore.release());

  ASSERT_EQ(semaphore.try_acquire(), cen::lock_status::success);
}

TEST(Semaphore, Release)
{
  cen::semaphore semaphore{0u};
  ASSERT_EQ(semaphore.count(), 0u);

  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.count(), 1u);
}

TEST(Semaphore, Count)
{
  constexpr Uint32 tokens = 32;

  cen::semaphore semaphore{tokens};
  ASSERT_EQ(semaphore.count(), tokens);
}
