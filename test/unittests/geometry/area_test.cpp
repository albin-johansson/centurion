#include "area.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"

TEST(Area, DefaultConstruction)
{
  const cen::iarea area;
  EXPECT_EQ(area.width, 0);
  EXPECT_EQ(area.height, 0);
}

TEST(Area, Construction)
{
  const auto width = 7353;
  const auto height = 8395;
  const cen::iarea area{width, height};

  EXPECT_EQ(area.width, width);
  EXPECT_EQ(area.height, height);
}

TEST(Area, EqComparisonReflexivity)
{
  const cen::iarea area{234, 12};
  EXPECT_EQ(area, area);
}

TEST(Area, EqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, first);
}

TEST(Area, EqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  EXPECT_NE(first, second);
  EXPECT_NE(second, first);
}

TEST(Area, NotEqComparisonSelf)
{
  const cen::iarea area{234, 12};
  EXPECT_FALSE(area != area);
}

TEST(Area, NotEqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  EXPECT_FALSE(first != second);
  EXPECT_FALSE(second != first);
}

TEST(Area, NotEqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  EXPECT_NE(first, second);
  EXPECT_NE(second, first);
}

TEST(Area, ToString)
{
  constexpr cen::iarea ia{123, 456};
  constexpr cen::farea fa{78.9f, 23.4f};

  cen::log::put(cen::to_string(ia));
  cen::log::put(cen::to_string(fa));
}

TEST(Area, StreamOperator)
{
  constexpr cen::iarea ia{123, 456};
  constexpr cen::farea fa{12.3f, 45.6f};
  std::cout << "COUT: " << ia << '\n';
  std::cout << "COUT: " << fa << '\n';
}

TEST(Area, Cast)
{
  {  // iarea -> farea
    const cen::iarea area{123, 456};
    const auto res = cen::cast<cen::farea>(area);
    EXPECT_EQ(static_cast<float>(area.width), res.width);
    EXPECT_EQ(static_cast<float>(area.height), res.height);
  }

  {  // iarea -> darea
    const cen::iarea area{534, 786};
    const auto res = cen::cast<cen::darea>(area);
    EXPECT_EQ(static_cast<double>(area.width), res.width);
    EXPECT_EQ(static_cast<double>(area.height), res.height);
  }

  {  // farea -> darea
    const cen::farea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::darea>(area);
    EXPECT_EQ(static_cast<double>(area.width), res.width);
    EXPECT_EQ(static_cast<double>(area.height), res.height);
  }

  {  // farea -> iarea
    const cen::farea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::iarea>(area);
    EXPECT_EQ(static_cast<int>(area.width), res.width);
    EXPECT_EQ(static_cast<int>(area.height), res.height);
  }

  {  // darea -> iarea
    const cen::darea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::iarea>(area);
    EXPECT_EQ(static_cast<int>(area.width), res.width);
    EXPECT_EQ(static_cast<int>(area.height), res.height);
  }

  {  // darea -> farea
    const cen::darea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::farea>(area);
    EXPECT_EQ(static_cast<float>(area.width), res.width);
    EXPECT_EQ(static_cast<float>(area.height), res.height);
  }
}