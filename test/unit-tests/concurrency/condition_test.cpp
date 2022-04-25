#include <gtest/gtest.h>

#include "centurion/concurrency.hpp"

TEST(Condition, Signal)
{
  cen::condition cond;
  ASSERT_TRUE(cond.signal());
}

TEST(Condition, Broadcast)
{
  cen::condition cond;
  ASSERT_TRUE(cond.broadcast());
}

TEST(Condition, Wait)
{
  cen::mutex mutex;
  cen::condition cond;

  ASSERT_TRUE(mutex.lock());

  cen::thread thread{[](void* data) {
                       auto* cond = reinterpret_cast<cen::condition*>(data);

                       using namespace cen::literals::time_literals;
                       cen::thread::sleep(50_ms);

                       cond->signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  ASSERT_TRUE(cond.wait(mutex));
  ASSERT_TRUE(mutex.unlock());
}
