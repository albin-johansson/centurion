#include "semaphore.hpp"

#include <catch.hpp>

TEST_CASE("semaphore::acquire()", "[semaphore]")
{
  cen::semaphore semaphore{1};

  REQUIRE(semaphore.acquire());
  CHECK(semaphore.tokens() == 0);

  REQUIRE(semaphore.release());
  CHECK(semaphore.tokens() == 1);
}

TEST_CASE("semaphore::acquire(milliseconds)", "[semaphore]")
{
  cen::semaphore semaphore{0};

  using ms = cen::milliseconds<cen::u32>;

  REQUIRE(semaphore.acquire(ms{1}) == cen::lock_status::timed_out);

  REQUIRE(semaphore.release());

  REQUIRE(semaphore.acquire(ms{1}) == cen::lock_status::success);
}

TEST_CASE("semaphore::try_acquire", "[semaphore]")
{
  cen::semaphore semaphore{0};

  REQUIRE(semaphore.try_acquire() == cen::lock_status::timed_out);

  REQUIRE(semaphore.release());

  REQUIRE(semaphore.try_acquire() == cen::lock_status::success);
}

TEST_CASE("semaphore::release", "[semaphore]")
{
  cen::semaphore semaphore{0};

  CHECK(semaphore.tokens() == 0);

  semaphore.release();
  CHECK(semaphore.tokens() == 1);
}

TEST_CASE("semaphore::tokens", "[semaphore]")
{
  const auto tokens = 32;

  cen::semaphore semaphore{32};
  CHECK(semaphore.tokens() == 32);
}
