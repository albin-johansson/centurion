#include "area.hpp"

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "log.hpp"

TEST_CASE("Construction", "[area]")
{
  SECTION("Default values")
  {
    const cen::iarea area;
    CHECK(area.width == 0);
    CHECK(area.height == 0);
  }

  const auto w = 7353;
  const auto h = 8395;
  const cen::iarea area{w, h};

  CHECK(area.width == w);
  CHECK(area.height == h);
}

TEST_CASE("area operator==", "[area]")
{
  SECTION("Reflexivity")
  {
    const cen::iarea area{234, 12};
    CHECK(area == area);
  }

  SECTION("Equal")
  {
    const cen::iarea first{47, 9123};
    const cen::iarea second{first};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Different")
  {
    const cen::iarea first{1238, 594};
    const cen::iarea second{8882, 123};
    CHECK_FALSE(first == second);
    CHECK_FALSE(second == first);
  }
}

TEST_CASE("area operator!=", "[area]")
{
  SECTION("Self")
  {
    const cen::iarea area{234, 12};
    CHECK_FALSE(area != area);
  }

  SECTION("Equal")
  {
    const cen::iarea first{47, 9123};
    const cen::iarea second{first};
    CHECK_FALSE(first != second);
    CHECK_FALSE(second != first);
  }

  SECTION("Different")
  {
    const cen::iarea first{1238, 594};
    const cen::iarea second{8882, 123};
    CHECK(first != second);
    CHECK(second != first);
  }
}

TEST_CASE("area to_string", "[area]")
{
  constexpr cen::iarea ia{123, 456};
  constexpr cen::farea fa{78.9f, 23.4f};

  cen::log::put(cen::to_string(ia));
  cen::log::put(cen::to_string(fa));
}

TEST_CASE("area stream operator", "[area]")
{
  constexpr cen::iarea ia{123, 456};
  constexpr cen::farea fa{12.3f, 45.6f};
  std::cout << "COUT: " << ia << '\n';
  std::cout << "COUT: " << fa << '\n';
}