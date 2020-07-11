#include "sleep.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("sleep", "[sleep]")
{
  CHECK_NOTHROW(ctn::sleep(ctn::milliseconds<ctn::u32>{10}));
  CHECK_NOTHROW(ctn::sleep(ctn::milliseconds<ctn::u32>{0}));
}
