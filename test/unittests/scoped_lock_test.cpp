#include "scoped_lock.hpp"

#include <catch.hpp>

TEST_CASE("scoped_lock", "[scoped_lock]")
{
  cen::mutex mutex;
  CHECK_NOTHROW(cen::scoped_lock{mutex});
}
