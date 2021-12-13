#include <gtest/gtest.h>

#include "system/concurrency.hpp"

TEST(Semaphore, Acquire)
{
  cen::Semaphore semaphore{1};

  ASSERT_TRUE(semaphore.Acquire());
  ASSERT_EQ(semaphore.GetTokens(), 0u);

  ASSERT_TRUE(semaphore.Release());
  ASSERT_EQ(semaphore.GetTokens(), 1u);
}

TEST(Semaphore, AcquireMilliseconds)
{
  using ms = cen::milliseconds<Uint32>;

  cen::Semaphore semaphore{0u};

  ASSERT_EQ(semaphore.Acquire(ms{1}), cen::LockStatus::TimedOut);
  ASSERT_TRUE(semaphore.Release());

  ASSERT_EQ(semaphore.Acquire(ms{1}), cen::LockStatus::Success);
}

TEST(Semaphore, TryAcquire)
{
  cen::Semaphore semaphore{0u};

  ASSERT_EQ(semaphore.TryAcquire(), cen::LockStatus::TimedOut);
  ASSERT_TRUE(semaphore.Release());

  ASSERT_EQ(semaphore.TryAcquire(), cen::LockStatus::Success);
}

TEST(Semaphore, Release)
{
  cen::Semaphore semaphore{0u};
  ASSERT_EQ(semaphore.GetTokens(), 0u);

  ASSERT_TRUE(semaphore.Release());
  ASSERT_EQ(semaphore.GetTokens(), 1u);
}

TEST(Semaphore, GetTokens)
{
  constexpr Uint32 tokens = 32;

  cen::Semaphore semaphore{tokens};
  ASSERT_EQ(semaphore.GetTokens(), tokens);
}
