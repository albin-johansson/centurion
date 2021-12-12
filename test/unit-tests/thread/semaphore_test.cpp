#include "thread/semaphore.hpp"

#include <gtest/gtest.h>

TEST(Semaphore, Acquire)
{
  cen::semaphore semaphore{1};

  ASSERT_TRUE(semaphore.acquire());
  ASSERT_EQ(semaphore.tokens(), 0u);

  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.tokens(), 1u);
}

TEST(Semaphore, AcquireMilliseconds)
{
  using ms = cen::milliseconds<Uint32>;

  cen::semaphore semaphore{0u};

  ASSERT_EQ(semaphore.acquire(ms{1}), cen::lock_status::timed_out);
  ASSERT_TRUE(semaphore.release());

  ASSERT_EQ(semaphore.acquire(ms{1}), cen::lock_status::success);
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

  ASSERT_EQ(semaphore.tokens(), 0u);
  ASSERT_TRUE(semaphore.release());
  ASSERT_EQ(semaphore.tokens(), 1u);
}

TEST(Semaphore, Tokens)
{
  constexpr Uint32 tokens = 32;

  cen::semaphore semaphore{tokens};
  ASSERT_EQ(semaphore.tokens(), tokens);
}
