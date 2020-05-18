#include "centurion_exception.h"

#include <catch.hpp>
#include <string>

using namespace centurion;
using namespace Catch;

TEST_CASE("CenturionException(CZString)", "[CenturionException]")
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

TEST_CASE("CenturionException(std::string)", "[CenturionException]")
{
  const std::string msg{"Hello"};
  CenturionException ce{msg};
  CHECK_THAT(ce.what(), Equals(msg));
}

TEST_CASE("CenturionException(CenturionException&)", "[CenturionException]")
{
  const CenturionException ce{"message"};
  const CenturionException ce2{ce};
  CHECK_THAT(ce.what(), Equals(ce2.what()));
}