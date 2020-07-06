#include "area.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Construction", "[area]")
{
  SECTION("Default values")
  {
    const area_i area;
    CHECK(area.width == 0);
    CHECK(area.height == 0);
  }

  const auto w = 7353;
  const auto h = 8395;
  const area_i area{w, h};

  CHECK(area.width == w);
  CHECK(area.height == h);
}

TEST_CASE("Area operator==", "[area]")
{
  SECTION("Reflexivity")
  {
    const area_i area{234, 12};
    CHECK(area == area);
  }

  SECTION("Equal")
  {
    const area_i first{47, 9123};
    const area_i second{first};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Different")
  {
    const area_i first{1238, 594};
    const area_i second{8882, 123};
    CHECK_FALSE(first == second);
    CHECK_FALSE(second == first);
  }
}

TEST_CASE("Area operator!=", "[area]")
{
  SECTION("Self")
  {
    const area_i area{234, 12};
    CHECK_FALSE(area != area);
  }

  SECTION("Equal")
  {
    const area_i first{47, 9123};
    const area_i second{first};
    CHECK_FALSE(first != second);
    CHECK_FALSE(second != first);
  }

  SECTION("Different")
  {
    const area_i first{1238, 594};
    const area_i second{8882, 123};
    CHECK(first != second);
    CHECK(second != first);
  }
}