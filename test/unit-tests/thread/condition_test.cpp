#include "thread/condition.hpp"

#include <gtest/gtest.h>

#include "thread/thread.hpp"

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

                       using ms = cen::milliseconds<cen::u32>;
                       cen::thread::sleep(ms{50});

                       cond->signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  ASSERT_TRUE(cond.wait(mutex));
  ASSERT_TRUE(mutex.unlock());
}
