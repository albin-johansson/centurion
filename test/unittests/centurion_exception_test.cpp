#include "centurion_exception.hpp"

#include <catch.hpp>
#include <string>

using namespace centurion;
using namespace Catch;

TEST_CASE("CenturionException(CZString)", "[CenturionException]")
{
  SECTION("Null string")
  {
    centurion_exception ce{nullptr};
    CHECK_THAT(ce.what(), Equals("N/A"));
  }

  SECTION("Normal argument")
  {
    const auto* msg = "Foo";
    centurion_exception ce{msg};
    CHECK_THAT(ce.what(), Equals(msg));
  }
}

TEST_CASE("CenturionException(std::string)", "[CenturionException]")
{
  const std::string msg{"Hello"};
  centurion_exception ce{msg};
  CHECK_THAT(ce.what(), Equals(msg));
}

TEST_CASE("CenturionException(CenturionException&)", "[CenturionException]")
{
  const centurion_exception ce{"message"};
  const centurion_exception ce2{ce};
  CHECK_THAT(ce.what(), Equals(ce2.what()));
}