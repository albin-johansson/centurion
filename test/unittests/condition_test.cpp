#include "condition.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "thread.hpp"

TEST_CASE("condition::signal", "[condition]")
{
  ctn::condition cond;
  CHECK(cond.signal());
}

TEST_CASE("condition::broadcast", "[condition]")
{
  ctn::condition cond;
  CHECK(cond.broadcast());
}

TEST_CASE("condition::wait(mutex&)", "[condition]")
{
  ctn::mutex mutex;
  ctn::condition cond;

  using enum ctn::lock_status;

  auto x = success;

  REQUIRE(mutex.lock());

  ctn::thread thread{[](void* data) {
                       auto* cond = reinterpret_cast<ctn::condition*>(data);

                       using ms = ctn::milliseconds<ctn::u32>;
                       ctn::thread::sleep(ms{100});

                       cond->signal();

                       return 0;
                     },
                     "thread",
                     &cond};

  CHECK(cond.wait(mutex));
  CHECK(mutex.unlock());
}
