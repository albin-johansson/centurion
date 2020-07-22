#include "centurion_exception.hpp"

#include <catch.hpp>
#include <string>

#include "centurion_as_ctn.hpp"

using namespace Catch;

TEST_CASE("centurion_exception(czstring)", "[centurion_exception]")
{
  SECTION("Null string")
  {
    ctn::centurion_exception ce{nullptr};
    CHECK_THAT(ce.what(), Equals("N/A"));
  }

  SECTION("Normal argument")
  {
    const auto* msg = "Foo";
    ctn::centurion_exception ce{msg};
    CHECK_THAT(ce.what(), Equals(msg));
  }
}

TEST_CASE("centurion_exception(std::string)", "[centurion_exception]")
{
  const std::string msg{"Hello"};
  ctn::centurion_exception ce{msg};
  CHECK_THAT(ce.what(), Equals(msg));
}

TEST_CASE("centurion_exception(centurion_exception&)", "[centurion_exception]")
{
  const ctn::centurion_exception ce{"message"};
  const ctn::centurion_exception ce2{ce};
  CHECK_THAT(ce.what(), Equals(ce2.what()));
}