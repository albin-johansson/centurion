#include "scoped_lock.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("scoped_lock", "[scoped_lock]")
{
  ctn::mutex mutex;
  CHECK_NOTHROW(ctn::scoped_lock{mutex});
}
