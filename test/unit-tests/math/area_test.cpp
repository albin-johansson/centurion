#include "math/area.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "misc/log.hpp"
#include "serialization_utils.hpp"

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

TEST(Area, Area)
{
  const auto iarea = cen::area(123, 456);
  const auto farea = cen::area(12.3f, 45.6f);
  const auto darea = cen::area(12.3, 45.6);

  EXPECT_EQ(123, iarea.width);
  EXPECT_EQ(456, iarea.height);

  EXPECT_EQ(12.3f, farea.width);
  EXPECT_EQ(45.6f, farea.height);

  EXPECT_EQ(12.3, darea.width);
  EXPECT_EQ(45.6, darea.height);
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

TEST(Area, AreaOf)
{
  const cen::farea area{123, 456};
  EXPECT_FLOAT_EQ(cen::area_of(area), area.width * area.height);
}

TEST(Area, Serialization)
{
  const auto width = 123;
  const auto height = 845;
  serialize_save("area.binary", cen::iarea{width, height});

  const auto other = serialize_create<cen::iarea>("area.binary");
  EXPECT_EQ(width, other.width);
  EXPECT_EQ(height, other.height);
}