#include "area.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

TEST_CASE("Construction", "[area]")
{
  SECTION("Default values")
  {
    const ctn::iarea area;
    CHECK(area.width == 0);
    CHECK(area.height == 0);
  }

  const auto w = 7353;
  const auto h = 8395;
  const ctn::iarea area{w, h};

  CHECK(area.width == w);
  CHECK(area.height == h);
}

TEST_CASE("area operator==", "[area]")
{
  SECTION("Reflexivity")
  {
    const ctn::iarea area{234, 12};
    CHECK(area == area);
  }

  SECTION("Equal")
  {
    const ctn::iarea first{47, 9123};
    const ctn::iarea second{first};
    CHECK(first == second);
    CHECK(second == first);
  }

  SECTION("Different")
  {
    const ctn::iarea first{1238, 594};
    const ctn::iarea second{8882, 123};
    CHECK_FALSE(first == second);
    CHECK_FALSE(second == first);
  }
}

TEST_CASE("area operator!=", "[area]")
{
  SECTION("Self")
  {
    const ctn::iarea area{234, 12};
    CHECK_FALSE(area != area);
  }

  SECTION("Equal")
  {
    const ctn::iarea first{47, 9123};
    const ctn::iarea second{first};
    CHECK_FALSE(first != second);
    CHECK_FALSE(second != first);
  }

  SECTION("Different")
  {
    const ctn::iarea first{1238, 594};
    const ctn::iarea second{8882, 123};
    CHECK(first != second);
    CHECK(second != first);
  }
}

TEST_CASE("area to_string", "[area]")
{
  constexpr ctn::iarea ia{123, 456};
  constexpr ctn::farea fa{78.9f, 23.4f};

  ctn::log::put(ctn::log::category::test, ctn::to_string(ia));
  ctn::log::put(ctn::log::category::test, ctn::to_string(fa));
}

TEST_CASE("area stream operator", "[area]")
{
  constexpr ctn::iarea ia{123, 456};
  constexpr ctn::farea fa{12.3f, 45.6f};
  std::cout << "COUT: " << ia << '\n';
  std::cout << "COUT: " << fa << '\n';
}