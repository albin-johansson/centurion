#include "condition.hpp"

#include <catch.hpp>

#include "thread.hpp"

TEST_CASE("condition::signal", "[condition]")
{
  cen::condition cond;
  CHECK(cond.signal());
}

TEST_CASE("condition::broadcast", "[condition]")
{
  cen::condition cond;
  CHECK(cond.broadcast());
}

TEST_CASE("condition::wait(mutex&)", "[condition]")
{
  cen::mutex mutex;
  cen::condition cond;

  REQUIRE(mutex.lock());

  cen::thread thread{[](void* data) {
                       auto* cond = reinterpret_cast<cen::condition*>(data);

                       using ms = cen::milliseconds<cen::u32>;
                       cen::thread::sleep(ms{100});

                       cond->signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  CHECK(cond.wait(mutex));
  CHECK(mutex.unlock());
}
