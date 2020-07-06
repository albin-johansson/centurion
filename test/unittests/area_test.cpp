#include "area.hpp"

#include <catch.hpp>

using namespace centurion;

// All tests are written using the IArea alias, which uses ints

TEST_CASE("Area()", "[TArea]")
{
  IArea area;
  CHECK(area.width == 0);
  CHECK(area.height == 0);
}

TEST_CASE("Area(T, T)", "[TArea]")
{
  const auto w = 7353;
  const auto h = 8395;
  IArea area{w, h};

  CHECK(area.width == w);
  CHECK(area.height == h);
}

TEST_CASE("Area operator==", "[TArea]")
{
  SECTION("Reflexivity")
  {
    IArea area{234, 12};
    CHECK(area == area);
  }
  SECTION("Equal")
  {
    IArea first{47, 9123};
    IArea second{first};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Different")
  {
    IArea first{1238, 594};
    IArea second{8882, 123};
    CHECK_FALSE(first == second);
    CHECK_FALSE(second == first);
  }
}

TEST_CASE("Area operator!=", "[TArea]")
{
  SECTION("Self")
  {
    IArea area{234, 12};
    CHECK_FALSE(area != area);
  }
  SECTION("Equal")
  {
    IArea first{47, 9123};
    IArea second{first};
    CHECK_FALSE(first != second);
    CHECK_FALSE(second != first);
  }

  SECTION("Different")
  {
    IArea first{1238, 594};
    IArea second{8882, 123};
    CHECK(first != second);
    CHECK(second != first);
  }
}