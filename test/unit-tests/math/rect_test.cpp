#include <gtest/gtest.h>

#include <iostream>     // clog
#include <type_traits>  // ...

#include "core/logging.hpp"
#include "math.hpp"
#include "serialization_utils.hpp"

static_assert(std::is_nothrow_default_constructible_v<cen::FRect>);
static_assert(std::is_nothrow_default_constructible_v<cen::Rect>);

static_assert(std::is_nothrow_copy_constructible_v<cen::FRect>);
static_assert(std::is_nothrow_copy_constructible_v<cen::Rect>);

static_assert(std::is_nothrow_copy_assignable_v<cen::FRect>);
static_assert(std::is_nothrow_copy_assignable_v<cen::Rect>);

static_assert(std::is_nothrow_move_constructible_v<cen::FRect>);
static_assert(std::is_nothrow_move_constructible_v<cen::Rect>);

static_assert(std::is_nothrow_move_assignable_v<cen::FRect>);
static_assert(std::is_nothrow_move_assignable_v<cen::Rect>);

static_assert(std::is_nothrow_destructible_v<cen::FRect>);
static_assert(std::is_nothrow_destructible_v<cen::Rect>);

TEST(Rect, ConstexprConstruction)
{
  constexpr cen::FRect rect{1, 2, 3, 4};
  static_assert(rect.GetX() == 1);
  static_assert(rect.GetY() == 2);
  static_assert(rect.GetWidth() == 3);
  static_assert(rect.GetHeight() == 4);
  static_assert(rect.HasArea());
}

TEST(Rect, DefaultConstructor)
{
  const cen::FRect rect;
  ASSERT_EQ(rect.GetX(), 0);
  ASSERT_EQ(rect.GetY(), 0);
  ASSERT_EQ(rect.GetWidth(), 0);
  ASSERT_EQ(rect.GetHeight(), 0);
  ASSERT_FALSE(rect.HasArea());
}

TEST(Rect, SDLRectConstructor)
{
  const SDL_FRect source{12.0f, 34.0f, 56.0f, 78.0f};
  const cen::FRect rect{source};

  ASSERT_EQ(source.x, rect.GetX());
  ASSERT_EQ(source.y, rect.GetY());
  ASSERT_EQ(source.w, rect.GetWidth());
  ASSERT_EQ(source.h, rect.GetHeight());
  ASSERT_TRUE(rect.HasArea());
}

TEST(Rect, PositionAndSizeConstructor)
{
  const cen::FPoint pos{123.5f, 81.4f};
  const cen::FArea size{921.8f, 512.6f};
  const cen::FRect rect{pos, size};

  ASSERT_EQ(rect.GetX(), pos.GetX());
  ASSERT_EQ(rect.GetY(), pos.GetY());
  ASSERT_EQ(rect.GetWidth(), size.width);
  ASSERT_EQ(rect.GetHeight(), size.height);

  ASSERT_NO_THROW(cen::FRect({{0, 0}, {0, 0}}));
  ASSERT_NO_THROW(cen::FRect({{0, 0}, {-1, -1}}));
}

TEST(Rect, ValueConstructor)
{
  const auto x = 123.0f;
  const auto y = 711.3f;
  const auto width = 231.9f;
  const auto height = 365.1f;
  const cen::FRect rect{x, y, width, height};

  ASSERT_EQ(x, rect.GetX());
  ASSERT_EQ(y, rect.GetY());
  ASSERT_EQ(width, rect.GetWidth());
  ASSERT_EQ(height, rect.GetHeight());
}

TEST(Rect, SetX)
{
  cen::FRect rect;

  const auto x = 123.4f;
  rect.SetX(x);

  ASSERT_EQ(rect.GetX(), x);
}

TEST(Rect, SetY)
{
  cen::FRect rect;

  const auto y = 8527.1f;
  rect.SetY(y);

  ASSERT_EQ(rect.GetY(), y);
}

TEST(Rect, SetMaxX)
{
  cen::FRect rect{{12, 92}, {241, 393}};

  const auto mx = 74.3f;
  rect.SetMaxX(mx);

  ASSERT_FLOAT_EQ(mx, rect.GetMaxX());
  ASSERT_FLOAT_EQ(241, rect.GetWidth());
}

TEST(Rect, SetMaxY)
{
  cen::FRect rect{{12, 92}, {241, 393}};

  const auto my = 34.3f;
  rect.SetMaxY(my);

  ASSERT_FLOAT_EQ(my, rect.GetMaxY());
  ASSERT_FLOAT_EQ(393, rect.GetHeight());
}

TEST(Rect, SetPosition)
{
  cen::FRect rect;

  const cen::FPoint pos{742.3f, 377.2f};
  rect.SetPosition(pos);

  ASSERT_EQ(rect.GetPosition(), pos);
}

TEST(Rect, SetWidth)
{
  cen::FRect rect;

  const auto width = 943.3f;
  rect.SetWidth(width);

  ASSERT_EQ(rect.GetWidth(), width);
}

TEST(Rect, SetHeight)
{
  cen::FRect rect;

  const auto height = 62.35f;
  rect.SetHeight(height);

  ASSERT_EQ(rect.GetHeight(), height);
}

TEST(Rect, SetSize)
{
  cen::FRect rect;

  const cen::FArea size{345.8f, 289.7f};
  rect.SetSize(size);

  ASSERT_EQ(rect.GetSize(), size);
}

TEST(Rect, OffsetX)
{
  const auto x = 123;
  const auto y = 27;
  const auto width = 100;
  const auto height = 50;

  const auto offset = 84;

  cen::Rect rect{x, y, width, height};
  rect.OffsetX(offset);

  ASSERT_EQ(x + offset, rect.GetX());
  ASSERT_EQ(y, rect.GetY());
  ASSERT_EQ(width, rect.GetWidth());
  ASSERT_EQ(height, rect.GetHeight());
}

TEST(Rect, OffsetY)
{
  const auto x = 412;
  const auto y = 754;
  const auto width = 213;
  const auto height = 886;

  const auto offset = -45;

  cen::Rect rect{x, y, width, height};
  rect.OffsetY(offset);

  ASSERT_EQ(x, rect.GetX());
  ASSERT_EQ(y + offset, rect.GetY());
  ASSERT_EQ(width, rect.GetWidth());
  ASSERT_EQ(height, rect.GetHeight());
}

TEST(Rect, OffsetWidth)
{
  const auto x = 213;
  const auto y = 3125;
  const auto width = 324;
  const auto height = 423;

  const auto offset = 221;

  cen::Rect rect{x, y, width, height};
  rect.OffsetWidth(offset);

  ASSERT_EQ(x, rect.GetX());
  ASSERT_EQ(y, rect.GetY());
  ASSERT_EQ(width + offset, rect.GetWidth());
  ASSERT_EQ(height, rect.GetHeight());
}

TEST(Rect, OffsetHeight)
{
  const auto x = 34;
  const auto y = 4532;
  const auto width = 5431;
  const auto height = 6567;

  const auto offset = 812;

  cen::Rect rect{x, y, width, height};
  rect.OffsetHeight(offset);

  ASSERT_EQ(x, rect.GetX());
  ASSERT_EQ(y, rect.GetY());
  ASSERT_EQ(width, rect.GetWidth());
  ASSERT_EQ(height + offset, rect.GetHeight());
}

TEST(Rect, Contains)
{
  const cen::FRect rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

  {  // Top-left corner
    ASSERT_TRUE(rect.Contains({rect.GetX(), rect.GetY()}));
    ASSERT_FALSE(rect.Contains({rect.GetX() - 1, rect.GetY()}));
    ASSERT_FALSE(rect.Contains({rect.GetX(), rect.GetY() - 1}));
  }

  {  // Top-right corner
    ASSERT_TRUE(rect.Contains({rect.GetMaxX(), rect.GetY()}));
    ASSERT_FALSE(rect.Contains({rect.GetMaxX() + 1, rect.GetY()}));
    ASSERT_FALSE(rect.Contains({rect.GetMaxX(), rect.GetY() - 1}));
  }

  {  // Bottom-left corner
    ASSERT_TRUE(rect.Contains({rect.GetX(), rect.GetMaxY()}));
    ASSERT_FALSE(rect.Contains({rect.GetX() - 1, rect.GetMaxY()}));
    ASSERT_FALSE(rect.Contains({rect.GetX(), rect.GetMaxY() + 1}));
  }

  {  // Bottom-right corner
    ASSERT_TRUE(rect.Contains({rect.GetMaxX(), rect.GetMaxY()}));
    ASSERT_FALSE(rect.Contains({rect.GetMaxX() + 1, rect.GetMaxY()}));
    ASSERT_FALSE(rect.Contains({rect.GetMaxY(), rect.GetMaxY() + 1}));
  }
}

TEST(Rect, HasArea)
{
  {  // Default constructed rectangle
    const cen::FRect rect;
    ASSERT_FALSE(rect.HasArea());
  }

  {  // No width
    const cen::FRect rect{{0, 0}, {0, 1}};
    ASSERT_FALSE(rect.HasArea());
  }

  {  // No height
    const cen::FRect rect{{0, 0}, {1, 0}};
    ASSERT_FALSE(rect.HasArea());
  }

  {  // Negative dimensions
    const cen::FRect rect{{0, 0}, {-1, -1}};
    ASSERT_FALSE(rect.HasArea());
  }

  {  // Valid dimensions
    const cen::FRect rect{{0, 0}, {1, 1}};
    ASSERT_TRUE(rect.HasArea());
  }
}

TEST(Rect, GetX)
{
  const cen::FRect rect;
  ASSERT_EQ(rect.GetX(), 0);
}

TEST(Rect, GetY)
{
  const cen::FRect rect;
  ASSERT_EQ(rect.GetY(), 0);
}

TEST(Rect, GetWidth)
{
  const cen::FRect rect;
  ASSERT_EQ(rect.GetWidth(), 0);
}

TEST(Rect, GetHeight)
{
  const cen::FRect rect;
  ASSERT_EQ(rect.GetHeight(), 0);
}

TEST(Rect, GetMaxX)
{
  const auto x = 289.2f;
  const auto width = 591.0f;

  const cen::FRect rect{{x, 0}, {width, 0}};

  ASSERT_EQ(rect.GetMaxX(), x + width);
}

TEST(Rect, GetMaxY)
{
  const auto y = 1029.3f;
  const auto height = 6961.9f;

  const cen::FRect rect{{0, y}, {0, height}};

  ASSERT_EQ(rect.GetMaxY(), y + height);
}

TEST(Rect, GetCenterX)
{
  const auto x = 125.3f;
  const auto width = 3912.8f;

  const cen::FRect rect{{x, 0}, {width, 0}};

  ASSERT_EQ(rect.GetCenterX(), x + (width / 2.0f));
}

TEST(Rect, GetCenterY)
{
  const auto y = 7128.2f;
  const auto height = 1240.2f;

  const cen::FRect rect{{0, y}, {0, height}};

  ASSERT_EQ(rect.GetCenterY(), y + (height / 2.0f));
}

TEST(Rect, GetArea)
{
  const auto width = 184.3f;
  const auto height = 728.9f;

  const cen::FRect rect{{}, {width, height}};

  ASSERT_EQ(rect.GetArea(), width * height);
}

TEST(Rect, Center)
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;

  const cen::Rect rect{{x, y}, {w, h}};
  const auto center = rect.GetCenter();

  ASSERT_EQ(center.GetX(), x + (w / 2));
  ASSERT_EQ(center.GetY(), y + (h / 2));
}

TEST(Rect, Data)
{
  const cen::Rect rect{{12, 34}, {56, 78}};
  ASSERT_TRUE(rect.data());
  ASSERT_EQ(12, rect.data()->x);
  ASSERT_EQ(34, rect.data()->y);
  ASSERT_EQ(56, rect.data()->w);
  ASSERT_EQ(78, rect.data()->h);
}

TEST(Rect, Intersects)
{
  const cen::FRect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
  ASSERT_TRUE(cen::Intersects(rect, rect));

  {  // Empty rectangle
    const cen::FRect empty;
    ASSERT_FALSE(cen::Intersects(empty, empty));
    ASSERT_FALSE(cen::Intersects(rect, empty));
    ASSERT_FALSE(cen::Intersects(empty, rect));
  }

  {  // Obviously no intersection
    const cen::FRect left{{rect.GetX() - rect.GetWidth(), rect.GetY()}, {10, 10}};
    const cen::FRect top{{rect.GetX(), rect.GetY() - rect.GetHeight()}, {10, 10}};
    const cen::FRect right{{rect.GetX() + rect.GetWidth(), rect.GetY()},
                           {rect.GetWidth(), rect.GetHeight()}};
    const cen::FRect bottom{{rect.GetX(), rect.GetY() + rect.GetHeight()}, {10, 10}};

    ASSERT_FALSE(cen::Intersects(left, rect));
    ASSERT_FALSE(cen::Intersects(rect, left));

    ASSERT_FALSE(cen::Intersects(top, rect));
    ASSERT_FALSE(cen::Intersects(rect, top));

    ASSERT_FALSE(cen::Intersects(right, rect));
    ASSERT_FALSE(cen::Intersects(rect, right));

    ASSERT_FALSE(cen::Intersects(bottom, rect));
    ASSERT_FALSE(cen::Intersects(rect, bottom));
  }

  {  // Edge cases
    const cen::FRect left{{90, 100}, {10, 10}};
    ASSERT_FALSE(cen::Intersects(left, rect));
    ASSERT_FALSE(cen::Intersects(rect, left));

    const cen::FRect top{{100, 90}, {10, 10}};
    ASSERT_FALSE(cen::Intersects(top, rect));
    ASSERT_FALSE(cen::Intersects(rect, top));

    const cen::FRect right{{200, 100}, {10, 10}};
    ASSERT_FALSE(cen::Intersects(right, rect));
    ASSERT_FALSE(cen::Intersects(rect, right));

    const cen::FRect bottom{{100, 200}, {10, 10}};
    ASSERT_FALSE(cen::Intersects(bottom, rect));
    ASSERT_FALSE(cen::Intersects(rect, bottom));
  }

  {  // Obvious intersections
    const cen::FRect left{{90, 150}, {50, 1}};
    ASSERT_TRUE(cen::Intersects(left, rect));
    ASSERT_TRUE(cen::Intersects(rect, left));

    const cen::FRect top{{150, 90}, {1, 50}};
    ASSERT_TRUE(cen::Intersects(top, rect));
    ASSERT_TRUE(cen::Intersects(rect, top));

    const cen::FRect bottom{{150, 150}, {10, 50}};
    ASSERT_TRUE(cen::Intersects(bottom, rect));
    ASSERT_TRUE(cen::Intersects(rect, bottom));

    const cen::FRect right{{150, 150}, {50, 10}};
    ASSERT_TRUE(cen::Intersects(right, rect));
    ASSERT_TRUE(cen::Intersects(rect, right));
  }
}

TEST(Rect, Collides)
{
  const cen::FRect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
  ASSERT_TRUE(cen::Overlaps(rect, rect));

  {  // Obviously no collisions
    const cen::FRect left{{rect.GetX() - rect.GetWidth() - 1, rect.GetY()}, {10, 10}};
    const cen::FRect top{{rect.GetX(), rect.GetY() - rect.GetHeight() - 1}, {10, 10}};
    const cen::FRect right{{rect.GetX() + rect.GetWidth() + 1, rect.GetY()},
                           {rect.GetWidth(), rect.GetHeight()}};
    const cen::FRect bottom{{rect.GetX(), rect.GetY() + rect.GetHeight() + 1}, {10, 10}};

    ASSERT_FALSE(cen::Overlaps(left, rect));
    ASSERT_FALSE(cen::Overlaps(rect, left));

    ASSERT_FALSE(cen::Overlaps(top, rect));
    ASSERT_FALSE(cen::Overlaps(rect, top));

    ASSERT_FALSE(cen::Overlaps(right, rect));
    ASSERT_FALSE(cen::Overlaps(rect, right));

    ASSERT_FALSE(cen::Overlaps(bottom, rect));
    ASSERT_FALSE(cen::Overlaps(rect, bottom));
  }

  {  // Edge cases
    const cen::FRect left{{89, 100}, {10, 10}};
    ASSERT_FALSE(cen::Overlaps(left, rect));
    ASSERT_FALSE(cen::Overlaps(rect, left));

    const cen::FRect top{{100, 89}, {10, 10}};
    ASSERT_FALSE(cen::Overlaps(top, rect));
    ASSERT_FALSE(cen::Overlaps(rect, top));

    const cen::FRect right{{201, 100}, {10, 10}};
    ASSERT_FALSE(cen::Overlaps(right, rect));
    ASSERT_FALSE(cen::Overlaps(rect, right));

    const cen::FRect bottom{{100, 201}, {10, 10}};
    ASSERT_FALSE(cen::Overlaps(bottom, rect));
    ASSERT_FALSE(cen::Overlaps(rect, bottom));
  }

  {  // Obvious collisions
    const cen::FRect left{{90, 150}, {50, 1}};
    ASSERT_TRUE(cen::Overlaps(left, rect));
    ASSERT_TRUE(cen::Overlaps(rect, left));

    const cen::FRect top{{150, 90}, {1, 50}};
    ASSERT_TRUE(cen::Overlaps(top, rect));
    ASSERT_TRUE(cen::Overlaps(rect, top));

    const cen::FRect bottom{{150, 150}, {10, 50}};
    ASSERT_TRUE(cen::Overlaps(bottom, rect));
    ASSERT_TRUE(cen::Overlaps(rect, bottom));

    const cen::FRect right{{150, 150}, {50, 10}};
    ASSERT_TRUE(cen::Overlaps(right, rect));
    ASSERT_TRUE(cen::Overlaps(rect, right));
  }
}

TEST(Rect, ToString)
{
  const cen::FRect rect{{14.3f, 34.2f}, {182.8f, 120.9f}};
  cen::log_info_raw(cen::to_string(rect));
}

TEST(Rect, StreamOperator)
{
  const cen::FRect rect{{14.3f, 34.2f}, {182.8f, 120.9f}};
  std::clog << rect << '\n';
}

TEST(Rect, GetUnion)
{
  const cen::FRect fst{{10.0f, 10.0f}, {50.0f, 50.0f}};
  const cen::FRect snd{{40.0f, 40.0f}, {50.0f, 50.0f}};

  {  // With empty rectangle
    const cen::FRect empty;

    ASSERT_EQ(cen::Union(empty, empty), empty);
    ASSERT_EQ(cen::Union(empty, fst), fst);
    ASSERT_EQ(cen::Union(fst, empty), fst);
  }

  const auto fstSnd = cen::Union(fst, snd);
  const auto sndFst = cen::Union(snd, fst);

  ASSERT_TRUE(fstSnd.HasArea());

  ASSERT_EQ(fstSnd.GetX(), 10.0f);
  ASSERT_EQ(fstSnd.GetY(), 10.0f);
  ASSERT_EQ(fstSnd.GetWidth(), 80.0f);
  ASSERT_EQ(fstSnd.GetHeight(), 80.0f);

  ASSERT_EQ(fstSnd, sndFst);
  ASSERT_EQ(sndFst, fstSnd);
}

TEST(Rect, IRectToFRect)
{
  const cen::Rect source{{78, 12}, {283, 313}};
  const auto result = cen::cast<cen::FRect>(source);

  ASSERT_EQ(result.GetX(), static_cast<float>(source.GetX()));
  ASSERT_EQ(result.GetY(), static_cast<float>(source.GetY()));
  ASSERT_EQ(result.GetWidth(), static_cast<float>(source.GetWidth()));
  ASSERT_EQ(result.GetHeight(), static_cast<float>(source.GetHeight()));
}

TEST(Rect, FRectToIRect)
{
  const cen::FRect source{{831.3f, 899.1f}, {67.2f, 91.7f}};
  const auto result = cen::cast<cen::Rect>(source);

  ASSERT_EQ(result.GetX(), static_cast<int>(source.GetX()));
  ASSERT_EQ(result.GetY(), static_cast<int>(source.GetY()));
  ASSERT_EQ(result.GetWidth(), static_cast<int>(source.GetWidth()));
  ASSERT_EQ(result.GetHeight(), static_cast<int>(source.GetHeight()));
}

TEST(Rect, EqualityOperatorReflexivity)
{
  const cen::FRect rect{{93.3f, 67.2f}, {54.2f, 777.8f}};
  ASSERT_EQ(rect, rect);
}

TEST(Rect, EqualityOperatorComparison)
{
  const cen::FRect fst{{78.2f, 21.2f}, {9.2f, 162.3f}};
  const cen::FRect snd{fst};
  ASSERT_EQ(fst, snd);
  ASSERT_EQ(snd, fst);
}

TEST(Rect, EqualityOperatorComparisonDifferent)
{
  const cen::FRect fst{{8.2f, 123.3f}, {63.1f, 672.3f}};
  const cen::FRect snd{{89.13f, 781.3f}, {781.2f, 331.3f}};
  ASSERT_FALSE(fst == snd);
  ASSERT_FALSE(snd == fst);
}

TEST(Rect, InequalityOperatorSelf)
{
  const cen::FRect rect{{21.7f, 32.2f}, {442.2f, 383.8f}};
  ASSERT_FALSE(rect != rect);
}

TEST(Rect, InequalityOperatorComparisonEqual)
{
  const cen::FRect fst{{712.3f, 34.3f}, {65.8f, 348.2f}};
  const cen::FRect snd{fst};
  ASSERT_FALSE(fst != snd);
  ASSERT_FALSE(snd != fst);
}

TEST(Rect, InequalityOperatorComparisonDifferent)
{
  const cen::FRect fst{{-45.37f, 12.3f}, {89.13f, 371.3f}};
  const cen::FRect snd{{738.3f, 8.24f}, {67.3f, 89.23f}};
  ASSERT_NE(fst, snd);
  ASSERT_NE(snd, fst);
}

TEST(Rect, Serialization)
{
  const auto x = 845;
  const auto y = 3348;
  const auto width = 412;
  const auto height = 7421;
  serialize_save("rect.binary", cen::Rect{x, y, width, height});

  const auto rect = serialize_create<cen::Rect>("rect.binary");
  ASSERT_EQ(x, rect.GetX());
  ASSERT_EQ(y, rect.GetY());
  ASSERT_EQ(width, rect.GetWidth());
  ASSERT_EQ(height, rect.GetHeight());
}
