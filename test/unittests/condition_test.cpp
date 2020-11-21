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
  using namespace cen::literals;

  cen::mutex mutex;
  cen::condition cond;

  REQUIRE(mutex.lock());

  cen::thread thread{[](cen::condition* condition) {
                       cen::thread::sleep(100_ms);
                       condition->signal();
                     },
                     &cond};

  CHECK(cond.wait(mutex));
  CHECK(mutex.unlock());
}
