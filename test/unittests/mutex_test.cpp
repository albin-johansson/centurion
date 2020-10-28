#include "mutex.hpp"

#include <catch.hpp>

#include "scoped_lock.hpp"

TEST_CASE("mutex lock/unlock", "[mutex]")
{
  cen::mutex m;

  CHECK(m.lock());
  CHECK(m.unlock());
}

TEST_CASE("mutex::try_lock", "[mutex]")
{
  cen::mutex m;

  CHECK(m.try_lock() == cen::lock_status::success);
  CHECK(m.unlock());
}

TEST_CASE("mutex::get", "[mutex]")
{
  cen::mutex m;
  CHECK(m.get());
}