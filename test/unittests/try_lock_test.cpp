#include "try_lock.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("try_lock", "[try_lock]")
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  CHECK(lock.success());
}

TEST_CASE("try_lock::get_status", "[try_lock]")
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  CHECK(lock.get_status() == cen::lock_status::success);

  CHECK(lock.success());
  CHECK(!lock.timed_out());
  CHECK(!lock.error());
}

TEST_CASE("try_lock operator bool", "[try_lock]")
{
  cen::mutex mutex;
  cen::try_lock lock{mutex};

  CHECK(lock);
}
