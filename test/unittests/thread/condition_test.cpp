#include "condition.hpp"

#include <gtest/gtest.h>

#include "thread.hpp"

TEST(Condition, Signal)
{
  cen::condition cond;
  EXPECT_TRUE(cond.signal());
}

TEST(Condition, Broadcast)
{
  cen::condition cond;
  EXPECT_TRUE(cond.broadcast());
}

TEST(Condition, Wait)
{
  cen::mutex mutex;
  cen::condition cond;

  ASSERT_TRUE(mutex.lock());

  cen::thread thread{[](void* data) {
                       auto* cond = reinterpret_cast<cen::condition*>(data);

                       using ms = cen::milliseconds<cen::u32>;
                       cen::thread::sleep(ms{100});

                       cond->signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  EXPECT_TRUE(cond.wait(mutex));
  EXPECT_TRUE(mutex.unlock());
}
