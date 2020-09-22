#include "exception.hpp"

#include <catch.hpp>
#include <string>

TEST_CASE("exception(czstring)", "[exception]")
{
  SECTION("Null string")
  {
    cen::exception ce{nullptr};
    CHECK_THAT(ce.what(), Catch::Equals("N/A"));
  }

  SECTION("Normal argument")
  {
    const auto* msg = "Foo";
    cen::exception ce{msg};
    CHECK_THAT(ce.what(), Catch::Equals(msg));
  }
}

TEST_CASE("exception(std::string)", "[exception]")
{
  const std::string msg{"Hello"};
  cen::exception ce{msg};
  CHECK_THAT(ce.what(), Catch::Equals(msg));
}

TEST_CASE("exception(exception&)", "[exception]")
{
  const cen::exception ce{"message"};
  const cen::exception ce2{ce};
  CHECK_THAT(ce.what(), Catch::Equals(ce2.what()));
}