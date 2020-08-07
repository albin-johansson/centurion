#include "semaphore.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("semaphore::acquire()", "[semaphore]")
{
  ctn::semaphore semaphore{1};

  REQUIRE(semaphore.acquire());
  CHECK(semaphore.tokens() == 0);

  REQUIRE(semaphore.release());
  CHECK(semaphore.tokens() == 1);
}

TEST_CASE("semaphore::acquire(milliseconds)", "[semaphore]")
{
  ctn::semaphore semaphore{0};

  using ms = ctn::milliseconds<ctn::u32>;

  REQUIRE(semaphore.acquire(ms{1}) == ctn::lock_status::timed_out);

  REQUIRE(semaphore.release());

  REQUIRE(semaphore.acquire(ms{1}) == ctn::lock_status::success);
}

TEST_CASE("semaphore::try_acquire", "[semaphore]")
{
  ctn::semaphore semaphore{0};

  REQUIRE(semaphore.try_acquire() == ctn::lock_status::timed_out);

  REQUIRE(semaphore.release());

  REQUIRE(semaphore.try_acquire() == ctn::lock_status::success);
}

TEST_CASE("semaphore::release", "[semaphore]")
{
  ctn::semaphore semaphore{0};

  CHECK(semaphore.tokens() == 0);

  semaphore.release();
  CHECK(semaphore.tokens() == 1);
}

TEST_CASE("semaphore::tokens", "[semaphore]")
{
  const auto tokens = 32;

  ctn::semaphore semaphore{32};
  CHECK(semaphore.tokens() == 32);
}
