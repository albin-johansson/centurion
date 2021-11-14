#include "math/point.hpp"

#include <gtest/gtest.h>

#include <cmath>        // abs, sqrt
#include <iostream>     // clog
#include <type_traits>  // ...

#include "core/logging.hpp"
#include "serialization_utils.hpp"

static_assert(std::is_nothrow_default_constructible_v<cen::ipoint>);
static_assert(std::is_nothrow_destructible_v<cen::ipoint>);
static_assert(std::is_nothrow_copy_constructible_v<cen::ipoint>);
static_assert(std::is_nothrow_copy_assignable_v<cen::ipoint>);
static_assert(std::is_nothrow_move_constructible_v<cen::ipoint>);
static_assert(std::is_nothrow_move_assignable_v<cen::ipoint>);

static_assert(std::is_nothrow_default_constructible_v<cen::fpoint>);
static_assert(std::is_nothrow_destructible_v<cen::fpoint>);
static_assert(std::is_nothrow_copy_constructible_v<cen::fpoint>);
static_assert(std::is_nothrow_copy_assignable_v<cen::fpoint>);
static_assert(std::is_nothrow_move_constructible_v<cen::fpoint>);
static_assert(std::is_nothrow_move_assignable_v<cen::fpoint>);

static_assert(cen::fpoint::floating);
static_assert(!cen::ipoint::floating);

static_assert(cen::ipoint::integral);
static_assert(!cen::fpoint::integral);

TEST(Point, Point)
{
  // clang-format off
  static_assert(std::is_same_v<decltype(cen::point(1, 1)), cen::ipoint>);
  static_assert(std::is_same_v<decltype(cen::point(1u, 1u)), cen::ipoint>);
  static_assert(std::is_same_v<decltype(cen::point(1.0f, 1.0f)), cen::fpoint>);
  static_assert(std::is_same_v<decltype(cen::point(1.0, 1.0)), cen::fpoint>);
  // clang-format on

  const auto ipoint = cen::point(123, 456);
  const auto fpoint = cen::point(12.3f, 45.6f);

  ASSERT_EQ(123, ipoint.x());
  ASSERT_EQ(456, ipoint.y());
  ASSERT_EQ(12.3f, fpoint.x());
  ASSERT_EQ(45.6f, fpoint.y());
}

TEST(Point, DistanceUnitXStep)
{
  const cen::ipoint a{0, 123};
  const cen::ipoint b{1, 123};

  ASSERT_EQ(cen::distance(a, b), 1);
  ASSERT_EQ(cen::distance(b, a), 1);
}

TEST(Point, DistanceUnitYStep)
{
  const cen::ipoint a{123, 0};
  const cen::ipoint b{123, 1};

  ASSERT_EQ(cen::distance(a, b), 1);
  ASSERT_EQ(cen::distance(b, a), 1);
}

TEST(Point, Distance)
{
  const cen::fpoint a{189.2f, 86.9f};
  const cen::fpoint b{66.5f, 36.6f};

  const auto expected = std::sqrt(std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()));

  ASSERT_EQ(cen::distance(a, b), expected);
  ASSERT_EQ(cen::distance(b, a), expected);
}

TEST(Point, EqualityOperatorReflexivity)
{
  const cen::fpoint point;
  ASSERT_EQ(point, point);
}

TEST(Point, EqualityOperatorComparisonSame)
{
  const cen::fpoint fst{211.5f, 823.1f};
  const cen::fpoint snd{fst};
  ASSERT_EQ(fst, snd);
  ASSERT_EQ(snd, fst);
  ASSERT_FALSE(fst != snd);
  ASSERT_FALSE(snd != fst);
}

TEST(Point, EqualityOperatorComparisonDifferent)
{
  const cen::fpoint fst{531.5f, 8313.4f};
  const cen::fpoint snd{34.2f, 173.3f};
  ASSERT_NE(fst, snd);
  ASSERT_NE(snd, fst);
}

TEST(Point, InequalityOperatorSelf)
{
  const cen::fpoint point;
  ASSERT_FALSE(point != point);
}

TEST(Point, InequalityOperatorDifferent)
{
  const cen::fpoint fst{8392.5f, 12452.4f};
  const cen::fpoint snd{5236.2f, 321.3f};
  ASSERT_NE(fst, snd);
  ASSERT_NE(snd, fst);
}

TEST(Point, InequalityOperatorEqual)
{
  const cen::fpoint fst{211.5f, 823.1f};
  const cen::fpoint snd{fst};
  ASSERT_FALSE(fst != snd);
  ASSERT_FALSE(snd != fst);
}

TEST(Point, AdditionOperator)
{
  const cen::fpoint fst{62.4f, 381.3f};
  const cen::fpoint snd{779.3f, 819.3f};

  const auto expectedX = fst.x() + snd.x();
  const auto expectedY = fst.y() + snd.y();

  const auto fstSnd = fst + snd;
  ASSERT_EQ(fstSnd.x(), expectedX);
  ASSERT_EQ(fstSnd.y(), expectedY);

  const auto sndFst = snd + fst;
  ASSERT_EQ(sndFst.x(), expectedX);
  ASSERT_EQ(sndFst.y(), expectedY);
}

TEST(Point, SubtractionOperator)
{
  const cen::fpoint fst{673, 123};
  const cen::fpoint snd{-547, 451};

  const auto fstSnd = fst - snd;
  ASSERT_EQ(fstSnd.x(), fst.x() - snd.x());
  ASSERT_EQ(fstSnd.y(), fst.y() - snd.y());

  const auto sndFst = snd - fst;
  ASSERT_EQ(sndFst.x(), snd.x() - fst.x());
  ASSERT_EQ(sndFst.y(), snd.y() - fst.y());

  ASSERT_NE(fstSnd, sndFst);
}

TEST(Point, IPointToFPoint)
{
  const cen::ipoint source{684, 912};
  const auto result = cen::cast<cen::fpoint>(source);

  ASSERT_EQ(result.x(), static_cast<float>(source.x()));
  ASSERT_EQ(result.y(), static_cast<float>(source.y()));
}

TEST(Point, FPointToIPoint)
{
  const cen::fpoint source{58.8f, 123.4f};
  const auto result = cen::cast<cen::ipoint>(source);

  ASSERT_EQ(result.x(), static_cast<int>(source.x()));
  ASSERT_EQ(result.y(), static_cast<int>(source.y()));
}

TEST(Point, ConversionToPointer)
{
  cen::fpoint point{3813.3f, 892.5f};

  auto* ptr = static_cast<SDL_FPoint*>(point);
  ASSERT_EQ(point.x(), ptr->x);
  ASSERT_EQ(point.y(), ptr->y);

  const auto* cptr = static_cast<const SDL_FPoint*>(point);
  ASSERT_EQ(point.x(), cptr->x);
  ASSERT_EQ(point.y(), cptr->y);
}

TEST(Point, Get)
{
  const cen::fpoint point{3923.3f, 7718.1f};
  const auto& ptr = point.get();

  ASSERT_EQ(point.x(), ptr.x);
  ASSERT_EQ(point.y(), ptr.y);
}

TEST(Point, Data)
{
  const cen::ipoint ip{123, 456};
  ASSERT_TRUE(ip.data());
  ASSERT_EQ(123, ip.data()->x);
  ASSERT_EQ(456, ip.data()->y);
}

TEST(Point, ToString)
{
  const cen::ipoint ip{123, 456};
  cen::log_info_raw(cen::to_string(ip));

  const cen::fpoint fp{12.3f, 45.6f};
  cen::log_info_raw(cen::to_string(fp));
}

TEST(Point, StreamOperator)
{
  const cen::ipoint ip{123, 456};
  std::clog << ip << '\n';

  const cen::fpoint fp{12.3f, 45.6f};
  std::clog << fp << '\n';
}

TEST(Point, Serialization)
{
  const auto x = 839.9f;
  const auto y = 931.5f;
  serialize_save("point.binary", cen::fpoint{x, y});

  const auto point = serialize_create<cen::fpoint>("point.binary");
  ASSERT_EQ(x, point.x());
  ASSERT_EQ(y, point.y());
}