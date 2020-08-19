#include "mutex.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "scoped_lock.hpp"

TEST_CASE("mutex lock/unlock", "[mutex]")
{
  ctn::mutex m;

  CHECK(m.lock());
  CHECK(m.unlock());
}

TEST_CASE("mutex::try_lock", "[mutex]")
{
  ctn::mutex m;

  CHECK(m.try_lock() == ctn::lock_status::success);
  CHECK(m.unlock());
}

TEST_CASE("mutex::get", "[mutex]")
{
  ctn::mutex m;
  CHECK(m.get());
}