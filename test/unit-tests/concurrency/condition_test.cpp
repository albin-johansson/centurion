#include <gtest/gtest.h>

#include "concurrency.hpp"

TEST(Condition, Signal)
{
  cen::Condition cond;
  ASSERT_TRUE(cond.Signal());
}

TEST(Condition, Broadcast)
{
  cen::Condition cond;
  ASSERT_TRUE(cond.Broadcast());
}

TEST(Condition, Wait)
{
  cen::Mutex mutex;
  cen::Condition cond;

  ASSERT_TRUE(mutex.Lock());

  cen::Thread thread{[](void* data) {
                       auto* cond = reinterpret_cast<cen::Condition*>(data);

                       using namespace cen::literals::time_literals;
                       cen::Thread::Sleep(50_ms);

                       cond->Signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  ASSERT_TRUE(cond.Wait(mutex));
  ASSERT_TRUE(mutex.Unlock());
}
