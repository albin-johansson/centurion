#include <gtest/gtest.h>

#include <cmath>        // abs, sqrt
#include <iostream>     // clog
#include <type_traits>  // ...

#include "core/logging.hpp"
#include "math.hpp"
#include "serialization_utils.hpp"

static_assert(std::is_nothrow_default_constructible_v<cen::Point>);
static_assert(std::is_nothrow_destructible_v<cen::Point>);
static_assert(std::is_nothrow_copy_constructible_v<cen::Point>);
static_assert(std::is_nothrow_copy_assignable_v<cen::Point>);
static_assert(std::is_nothrow_move_constructible_v<cen::Point>);
static_assert(std::is_nothrow_move_assignable_v<cen::Point>);

static_assert(std::is_nothrow_default_constructible_v<cen::FPoint>);
static_assert(std::is_nothrow_destructible_v<cen::FPoint>);
static_assert(std::is_nothrow_copy_constructible_v<cen::FPoint>);
static_assert(std::is_nothrow_copy_assignable_v<cen::FPoint>);
static_assert(std::is_nothrow_move_constructible_v<cen::FPoint>);
static_assert(std::is_nothrow_move_assignable_v<cen::FPoint>);

static_assert(cen::FPoint::floating);
static_assert(!cen::Point::floating);

static_assert(cen::Point::integral);
static_assert(!cen::FPoint::integral);

TEST(Point, GetDistanceUnitXStep)
{
  const cen::Point a{0, 123};
  const cen::Point b{1, 123};

  ASSERT_EQ(cen::GetDistance(a, b), 1);
  ASSERT_EQ(cen::GetDistance(b, a), 1);
}

TEST(Point, GetDistanceUnitYStep)
{
  const cen::Point a{123, 0};
  const cen::Point b{123, 1};

  ASSERT_EQ(cen::GetDistance(a, b), 1);
  ASSERT_EQ(cen::GetDistance(b, a), 1);
}

TEST(Point, GetDistance)
{
  const cen::FPoint a{189.2f, 86.9f};
  const cen::FPoint b{66.5f, 36.6f};

  const auto expected =
      std::sqrt(std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()));

  ASSERT_EQ(cen::GetDistance(a, b), expected);
  ASSERT_EQ(cen::GetDistance(b, a), expected);
}

TEST(Point, EqualityOperatorReflexivity)
{
  const cen::FPoint point;
  ASSERT_EQ(point, point);
}

TEST(Point, EqualityOperatorComparisonSame)
{
  const cen::FPoint fst{211.5f, 823.1f};
  const cen::FPoint snd{fst};
  ASSERT_EQ(fst, snd);
  ASSERT_EQ(snd, fst);
  ASSERT_FALSE(fst != snd);
  ASSERT_FALSE(snd != fst);
}

TEST(Point, EqualityOperatorComparisonDifferent)
{
  const cen::FPoint fst{531.5f, 8313.4f};
  const cen::FPoint snd{34.2f, 173.3f};
  ASSERT_NE(fst, snd);
  ASSERT_NE(snd, fst);
}

TEST(Point, InequalityOperatorSelf)
{
  const cen::FPoint point;
  ASSERT_FALSE(point != point);
}

TEST(Point, InequalityOperatorDifferent)
{
  const cen::FPoint fst{8392.5f, 12452.4f};
  const cen::FPoint snd{5236.2f, 321.3f};
  ASSERT_NE(fst, snd);
  ASSERT_NE(snd, fst);
}

TEST(Point, InequalityOperatorEqual)
{
  const cen::FPoint fst{211.5f, 823.1f};
  const cen::FPoint snd{fst};
  ASSERT_FALSE(fst != snd);
  ASSERT_FALSE(snd != fst);
}

TEST(Point, AdditionOperator)
{
  const cen::FPoint fst{62.4f, 381.3f};
  const cen::FPoint snd{779.3f, 819.3f};

  const auto expectedX = fst.GetX() + snd.GetX();
  const auto expectedY = fst.GetY() + snd.GetY();

  const auto fstSnd = fst + snd;
  ASSERT_EQ(fstSnd.GetX(), expectedX);
  ASSERT_EQ(fstSnd.GetY(), expectedY);

  const auto sndFst = snd + fst;
  ASSERT_EQ(sndFst.GetX(), expectedX);
  ASSERT_EQ(sndFst.GetY(), expectedY);
}

TEST(Point, SubtractionOperator)
{
  const cen::FPoint fst{673, 123};
  const cen::FPoint snd{-547, 451};

  const auto fstSnd = fst - snd;
  ASSERT_EQ(fstSnd.GetX(), fst.GetX() - snd.GetX());
  ASSERT_EQ(fstSnd.GetY(), fst.GetY() - snd.GetY());

  const auto sndFst = snd - fst;
  ASSERT_EQ(sndFst.GetX(), snd.GetX() - fst.GetX());
  ASSERT_EQ(sndFst.GetY(), snd.GetY() - fst.GetY());

  ASSERT_NE(fstSnd, sndFst);
}

TEST(Point, IPointToFPoint)
{
  const cen::Point source{684, 912};
  const auto result = cen::cast<cen::FPoint>(source);

  ASSERT_EQ(result.GetX(), static_cast<float>(source.GetX()));
  ASSERT_EQ(result.GetY(), static_cast<float>(source.GetY()));
}

TEST(Point, FPointToIPoint)
{
  const cen::FPoint source{58.8f, 123.4f};
  const auto result = cen::cast<cen::Point>(source);

  ASSERT_EQ(result.GetX(), static_cast<int>(source.GetX()));
  ASSERT_EQ(result.GetY(), static_cast<int>(source.GetY()));
}

TEST(Point, Get)
{
  const cen::FPoint point{3923.3f, 7718.1f};
  const auto& ptr = point.get();

  ASSERT_EQ(point.GetX(), ptr.x);
  ASSERT_EQ(point.GetY(), ptr.y);
}

TEST(Point, Data)
{
  const cen::Point ip{123, 456};
  ASSERT_TRUE(ip.data());
  ASSERT_EQ(123, ip.data()->x);
  ASSERT_EQ(456, ip.data()->y);
}

TEST(Point, ToString)
{
  const cen::Point ip{123, 456};
  cen::log_info_raw(cen::ToString(ip));

  const cen::FPoint fp{12.3f, 45.6f};
  cen::log_info_raw(cen::ToString(fp));
}

TEST(Point, StreamOperator)
{
  const cen::Point ip{123, 456};
  std::clog << ip << '\n';

  const cen::FPoint fp{12.3f, 45.6f};
  std::clog << fp << '\n';
}

TEST(Point, Serialization)
{
  const auto x = 839.9f;
  const auto y = 931.5f;
  serialize_save("point.binary", cen::FPoint{x, y});

  const auto point = serialize_create<cen::FPoint>("point.binary");
  ASSERT_EQ(x, point.GetX());
  ASSERT_EQ(y, point.GetY());
}