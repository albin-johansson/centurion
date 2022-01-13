#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/logging.hpp"
#include "math.hpp"
#include "serialization_utils.hpp"

TEST(Area, DefaultConstruction)
{
  const cen::Area area;
  ASSERT_EQ(area.width, 0);
  ASSERT_EQ(area.height, 0);
}

TEST(Area, Construction)
{
  const auto width = 7353;
  const auto height = 8395;
  const cen::Area area{width, height};

  ASSERT_EQ(area.width, width);
  ASSERT_EQ(area.height, height);
}

TEST(Area, Area)
{
  const cen::Area iarea{123, 456};
  const cen::FArea farea{12.3f, 45.6f};

  ASSERT_EQ(123, iarea.width);
  ASSERT_EQ(456, iarea.height);

  ASSERT_EQ(12.3f, farea.width);
  ASSERT_EQ(45.6f, farea.height);
}

TEST(Area, EqComparisonReflexivity)
{
  const cen::Area area{234, 12};
  ASSERT_EQ(area, area);
}

TEST(Area, EqComparisonSame)
{
  const cen::Area first{47, 9123};
  const cen::Area second{first};
  ASSERT_EQ(first, second);
  ASSERT_EQ(second, first);
}

TEST(Area, EqComparisonDifferent)
{
  const cen::Area first{1238, 594};
  const cen::Area second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
}

TEST(Area, NotEqComparisonSelf)
{
  const cen::Area area{234, 12};
  ASSERT_FALSE(area != area);
}

TEST(Area, NotEqComparisonSame)
{
  const cen::Area first{47, 9123};
  const cen::Area second{first};
  ASSERT_FALSE(first != second);
  ASSERT_FALSE(second != first);
}

TEST(Area, NotEqComparisonDifferent)
{
  const cen::Area first{1238, 594};
  const cen::Area second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
}

TEST(Area, ToString)
{
  constexpr cen::Area ia{123, 456};
  constexpr cen::FArea fa{78.9f, 23.4f};

  cen::log_info_raw(cen::ToString(ia));
  cen::log_info_raw(cen::ToString(fa));
}

TEST(Area, StreamOperator)
{
  constexpr cen::Area ia{123, 456};
  constexpr cen::FArea fa{12.3f, 45.6f};
  std::clog << ia << '\n';
  std::clog << fa << '\n';
}

TEST(Area, Cast)
{
  {  // Area -> FArea
    const cen::Area area{123, 456};
    const auto res = cen::cast<cen::FArea>(area);
    ASSERT_EQ(static_cast<float>(area.width), res.width);
    ASSERT_EQ(static_cast<float>(area.height), res.height);
  }

  {  // FArea -> Area
    const cen::FArea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::Area>(area);
    ASSERT_EQ(static_cast<int>(area.width), res.width);
    ASSERT_EQ(static_cast<int>(area.height), res.height);
  }
}

TEST(Area, AreaOf)
{
  const cen::FArea area{123, 456};
  ASSERT_FLOAT_EQ(cen::AreaOf(area), area.width * area.height);
}

TEST(Area, Serialization)
{
  const auto width = 123;
  const auto height = 845;
  serialize_save("area.binary", cen::Area{width, height});

  const auto other = serialize_create<cen::Area>("area.binary");
  ASSERT_EQ(width, other.width);
  ASSERT_EQ(height, other.height);
}