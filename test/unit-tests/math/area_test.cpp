#include "math/area.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/log.hpp"
#include "serialization_utils.hpp"

TEST(Area, DefaultConstruction)
{
  const cen::iarea area;
  ASSERT_EQ(area.width, 0);
  ASSERT_EQ(area.height, 0);
}

TEST(Area, Construction)
{
  const auto width = 7353;
  const auto height = 8395;
  const cen::iarea area{width, height};

  ASSERT_EQ(area.width, width);
  ASSERT_EQ(area.height, height);
}

TEST(Area, Area)
{
  const auto iarea = cen::area(123, 456);
  const auto farea = cen::area(12.3f, 45.6f);
  const auto darea = cen::area(12.3, 45.6);

  ASSERT_EQ(123, iarea.width);
  ASSERT_EQ(456, iarea.height);

  ASSERT_EQ(12.3f, farea.width);
  ASSERT_EQ(45.6f, farea.height);

  ASSERT_EQ(12.3, darea.width);
  ASSERT_EQ(45.6, darea.height);
}

TEST(Area, EqComparisonReflexivity)
{
  const cen::iarea area{234, 12};
  ASSERT_EQ(area, area);
}

TEST(Area, EqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  ASSERT_EQ(first, second);
  ASSERT_EQ(second, first);
}

TEST(Area, EqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
}

TEST(Area, NotEqComparisonSelf)
{
  const cen::iarea area{234, 12};
  ASSERT_FALSE(area != area);
}

TEST(Area, NotEqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  ASSERT_FALSE(first != second);
  ASSERT_FALSE(second != first);
}

TEST(Area, NotEqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
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
  std::clog << ia << '\n';
  std::clog << fa << '\n';
}

TEST(Area, Cast)
{
  {  // iarea -> farea
    const cen::iarea area{123, 456};
    const auto res = cen::cast<cen::farea>(area);
    ASSERT_EQ(static_cast<float>(area.width), res.width);
    ASSERT_EQ(static_cast<float>(area.height), res.height);
  }

  {  // iarea -> darea
    const cen::iarea area{534, 786};
    const auto res = cen::cast<cen::darea>(area);
    ASSERT_EQ(static_cast<double>(area.width), res.width);
    ASSERT_EQ(static_cast<double>(area.height), res.height);
  }

  {  // farea -> darea
    const cen::farea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::darea>(area);
    ASSERT_EQ(static_cast<double>(area.width), res.width);
    ASSERT_EQ(static_cast<double>(area.height), res.height);
  }

  {  // farea -> iarea
    const cen::farea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::iarea>(area);
    ASSERT_EQ(static_cast<int>(area.width), res.width);
    ASSERT_EQ(static_cast<int>(area.height), res.height);
  }

  {  // darea -> iarea
    const cen::darea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::iarea>(area);
    ASSERT_EQ(static_cast<int>(area.width), res.width);
    ASSERT_EQ(static_cast<int>(area.height), res.height);
  }

  {  // darea -> farea
    const cen::darea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::farea>(area);
    ASSERT_EQ(static_cast<float>(area.width), res.width);
    ASSERT_EQ(static_cast<float>(area.height), res.height);
  }
}

TEST(Area, AreaOf)
{
  const cen::farea area{123, 456};
  ASSERT_FLOAT_EQ(cen::area_of(area), area.width * area.height);
}

TEST(Area, Serialization)
{
  const auto width = 123;
  const auto height = 845;
  serialize_save("area.binary", cen::iarea{width, height});

  const auto other = serialize_create<cen::iarea>("area.binary");
  ASSERT_EQ(width, other.width);
  ASSERT_EQ(height, other.height);
}