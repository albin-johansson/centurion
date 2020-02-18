#include "centurion_exception.h"

#include "catch.hpp"

using namespace centurion;
using namespace Catch;

TEST_CASE("CenturionException()", "[CenturionException]")
{
  SECTION("Null string")
  {
    CenturionException ce{nullptr};
    CHECK_THAT(ce.what(), Equals("N/A"));
  }

  SECTION("Normal argument")
  {
    const auto* msg = "Foo";
    CenturionException ce{msg};
    CHECK_THAT(ce.what(), Equals(msg));
  }
}