/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <cmath>        // abs, sqrt
#include <iostream>     // cout
#include <type_traits>  // ...

#include "centurion/math.hpp"
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

TEST(Point, GetDistanceUnitXStep)
{
  const cen::ipoint a{0, 0};
  const cen::ipoint b{1, 0};

  ASSERT_EQ(cen::distance(a, b), 1);
  ASSERT_EQ(cen::distance(b, a), 1);
}

TEST(Point, GetDistanceUnitYStep)
{
  const cen::ipoint a{0, 0};
  const cen::ipoint b{0, 1};

  ASSERT_EQ(cen::distance(a, b), 1);
  ASSERT_EQ(cen::distance(b, a), 1);
}

TEST(Point, DistanceInt)
{
  const cen::ipoint a{42, 38};
  const cen::ipoint b{357, 752};
  const auto expected = 780;

  ASSERT_FLOAT_EQ(cen::distance(a, b), expected);
  ASSERT_FLOAT_EQ(cen::distance(b, a), expected);
}

TEST(Point, DistanceFloat)
{
  const cen::fpoint a{189, 86};
  const cen::fpoint b{66, 36};
  const auto expected = 17.0f * std::sqrt(61.0f);

  ASSERT_FLOAT_EQ(cen::distance(a, b), expected);
  ASSERT_FLOAT_EQ(cen::distance(b, a), expected);
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

TEST(Point, AsI)
{
  const cen::fpoint source{58.8f, 123.4f};
  const auto result = source.as_i();

  ASSERT_EQ(result.x(), static_cast<int>(source.x()));
  ASSERT_EQ(result.y(), static_cast<int>(source.y()));
}

TEST(Point, AsF)
{
  const cen::ipoint source{573, 9'382};
  const auto result = source.as_f();

  ASSERT_EQ(result.x(), static_cast<float>(source.x()));
  ASSERT_EQ(result.y(), static_cast<float>(source.y()));
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

TEST(Point, StreamOperator)
{
  std::cout << cen::ipoint{123, 456} << '\n';
  std::cout << cen::fpoint{12.3f, 45.6f} << '\n';
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