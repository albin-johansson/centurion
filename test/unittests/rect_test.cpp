#include "rect.h"

#include <catch.hpp>

#include "log.h"

using namespace centurion;

TEST_CASE("IRect()", "[Rect]")
{
  const IRect rect;

  CHECK(rect.x() == 0);
  CHECK(rect.y() == 0);
  CHECK(rect.width() == 0);
  CHECK(rect.height() == 0);
}

TEST_CASE("IRect(int, int, int, int)", "[Rect]")
{
  const auto x = 124;
  const auto y = 2145;
  const auto w = -124;
  const auto h = 912;
  const IRect rect{{x, y}, {w, h}};

  CHECK(rect.x() == x);
  CHECK(rect.y() == y);
  CHECK(rect.width() == w);
  CHECK(rect.height() == h);
}

TEST_CASE("IRect copy ctor", "[Rect]")
{
  const IRect first{{123, 312}, {495, 9912}};
  const IRect copy{first};

  CHECK(first.x() == copy.x());
  CHECK(first.y() == copy.y());
  CHECK(first.width() == copy.width());
  CHECK(first.height() == copy.height());
}

TEST_CASE("IRect::set_x", "[Rect]")
{
  IRect rect;

  const auto x = 482;
  rect.set_x(x);

  CHECK(x == rect.x());
}

TEST_CASE("IRect::set_y", "[Rect]")
{
  IRect rect;

  const auto y = 1248;
  rect.set_y(y);

  CHECK(y == rect.y());
}

TEST_CASE("IRect::set_width", "[Rect]")
{
  IRect rect;

  const auto width = 10'594;
  rect.set_width(width);

  CHECK(width == rect.width());
}

TEST_CASE("IRect::set_height", "[Rect]")
{
  IRect rect;

  const auto height = 839'239;
  rect.set_height(height);

  CHECK(height == rect.height());
}

TEST_CASE("IRect::set", "[Rect]")
{
  IRect rect;
  const IRect other{{702, 234}, {50, 27}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("IRect::intersects", "[Rect]")
{
  const IRect rect{{100, 100}, {100, 100}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const IRect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const IRect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const IRect right{{rect.x() + rect.width(), rect.y()},
                      {rect.width(), rect.height()}};
    const IRect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Edge cases")
  {
    const IRect left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const IRect top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const IRect right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const IRect bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const IRect left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const IRect top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const IRect bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const IRect right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("IRect::contains(int, int)", "[Rect]")
{
  const IRect rect{{10, 10}, {50, 50}};

  CHECK(rect.contains({rect.center_x(), rect.center_y()}));

  SECTION("Top-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.y()}));
    CHECK(!rect.contains({rect.x(), rect.y() - 1}));
  }

  SECTION("Top-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.y()}));
    CHECK(!rect.contains({rect.max_x(), rect.y() - 1}));
  }

  SECTION("Bottom-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.max_y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.max_y()}));
    CHECK(!rect.contains({rect.x(), rect.max_y() + 1}));
  }

  SECTION("Bottom-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.max_y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.max_y()}));
    CHECK(!rect.contains({rect.max_y(), rect.max_y() + 1}));
  }
}

TEST_CASE("IRect::contains(Point)", "[Rect]")
{
  const IRect rect{{931, 241}, {193, 93}};

  CHECK(rect.contains({rect.center_x(), rect.center_y()}));

  SECTION("Top-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.y()}));
    CHECK(!rect.contains({rect.x(), rect.y() - 1}));
  }

  SECTION("Top-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.y()}));
    CHECK(!rect.contains({rect.max_x(), rect.y() - 1}));
  }

  SECTION("Bottom-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.max_y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.max_y()}));
    CHECK(!rect.contains({rect.x(), rect.max_y() + 1}));
  }

  SECTION("Bottom-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.max_y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.max_y()}));
    CHECK(!rect.contains({rect.max_y(), rect.max_y() + 1}));
  }
}

TEST_CASE("IRect::has_area", "[Rect]")
{
  SECTION("Default values")
  {
    const IRect rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const IRect rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const IRect rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const IRect rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const IRect rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("IRect::x", "[Rect]")
{
  const IRect rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("IRect::y", "[Rect]")
{
  const IRect rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("IRect::max_x", "[Rect]")
{
  const auto x = 9123;
  const auto width = 1294;
  const IRect rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("IRect::max_y", "[Rect]")
{
  const auto y = 1245;
  const auto height = 7277;
  const IRect rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("IRect::width", "[Rect]")
{
  const IRect rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("IRect::height", "[Rect]")
{
  const IRect rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("IRect::get_union", "[Rect]")
{
  const IRect rect{{10, 10}, {50, 50}};
  const IRect other{{40, 40}, {50, 50}};
  const IRect res = rect.get_union(other);
  const IRect res2 = other.get_union(rect);
  CHECK(res.has_area());
  CHECK(res.x() == 10);
  CHECK(res.y() == 10);
  CHECK(res.width() == 80);
  CHECK(res.height() == 80);
  CHECK(res == res2);
  CHECK(res2 == res);
}

TEST_CASE("IRect::center_x", "[Rect]")
{
  const auto x = 728;
  const auto width = 8819;
  const IRect rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2));
}

TEST_CASE("IRect::center_y", "[Rect]")
{
  const auto y = 8192;
  const auto height = 6637;
  const IRect rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2));
}

TEST_CASE("IRect::center", "[Rect]")
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;
  const IRect rect{{x, y}, {w, h}};

  const auto center = rect.center();
  CHECK(center.x() == x + (w / 2));
  CHECK(center.y() == y + (h / 2));
}

TEST_CASE("IRect::to_string", "[Rect]")
{
  const IRect rect{{20, 45}, {100, 150}};
  Log::info(Log::Category::Test, "%s", rect.to_string().c_str());
}

TEST_CASE("IRect to SDL_Rect*", "[Rect]")
{
  const IRect rect{{123, 321}, {782, 991}};
  const auto* sdlRect = static_cast<const SDL_Rect*>(rect);
  CHECK(rect.x() == sdlRect->x);
  CHECK(rect.y() == sdlRect->y);
  CHECK(rect.width() == sdlRect->w);
  CHECK(rect.height() == sdlRect->h);
}

TEST_CASE("FRect()", "[FRect]")
{
  const FRect rect;
  CHECK(rect.x() == 0);
  CHECK(rect.y() == 0);
  CHECK(rect.width() == 0);
  CHECK(rect.height() == 0);
}

TEST_CASE("FRect(float, float, float, float)", "[FRect]")
{
  const auto x = 123.5f;
  const auto y = 81.4f;
  const auto width = 921.8f;
  const auto height = 512.6f;
  const FRect rect{{x, y}, {width, height}};

  CHECK(rect.x() == x);
  CHECK(rect.y() == y);
  CHECK(rect.width() == width);
  CHECK(rect.height() == height);

  CHECK_NOTHROW(FRect{{0, 0}, {0, 0}});
  CHECK_NOTHROW(FRect{{0, 0}, {-1, -1}});
}

TEST_CASE("FRect(FPoint, FArea)", "[FRect]")
{
  const FPoint pos{123.5f, 81.4f};
  const FArea area{921.8f, 512.6f};
  const FRect rect{pos, area};

  CHECK(rect.x() == pos.x());
  CHECK(rect.y() == pos.y());
  CHECK(rect.width() == area.width);
  CHECK(rect.height() == area.height);

  CHECK_NOTHROW(FRect{{0, 0}, {0, 0}});
  CHECK_NOTHROW(FRect{{0, 0}, {-1, -1}});
}

TEST_CASE("FRect::set_x", "[FRect]")
{
  FRect rect;

  const auto x = 91.1f;
  rect.set_x(x);

  CHECK(rect.x() == x);
}

TEST_CASE("FRect::set_y", "[FRect]")
{
  FRect rect;

  const auto y = 119.7f;
  rect.set_y(y);

  CHECK(rect.y() == y);
}

TEST_CASE("FRect::set_width", "[FRect]")
{
  FRect rect;

  const auto width = 991.5f;
  rect.set_width(width);

  CHECK(rect.width() == width);
}

TEST_CASE("FRect::set_height", "[FRect]")
{
  FRect rect;

  const auto height = 717.2f;
  rect.set_height(height);

  CHECK(rect.height() == height);
}

TEST_CASE("FRect::set", "[FRect]")
{
  FRect rect;
  const FRect other{{123.6f, 738.7f}, {192.9f, 91.3f}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("FRect::intersects", "[FRect]")
{
  const FRect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const FRect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const FRect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const FRect right{{rect.x() + rect.width(), rect.y()},
                      {rect.width(), rect.height()}};
    const FRect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Edge cases")
  {
    const FRect left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const FRect top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const FRect right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const FRect bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const FRect left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const FRect top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const FRect bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const FRect right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("FRect::contains(float, float)", "[FRect]")
{
  const FRect rect{{24.4f, 82.3f}, {38.9f, 77.2f}};

  CHECK(rect.contains({rect.center_x(), rect.center_y()}));

  SECTION("Top-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.y()}));
    CHECK(!rect.contains({rect.x(), rect.y() - 1}));
  }

  SECTION("Top-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.y()}));
    CHECK(!rect.contains({rect.max_x(), rect.y() - 1}));
  }

  SECTION("Bottom-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.max_y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.max_y()}));
    CHECK(!rect.contains({rect.x(), rect.max_y() + 1}));
  }

  SECTION("Bottom-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.max_y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.max_y()}));
    CHECK(!rect.contains({rect.max_y(), rect.max_y() + 1}));
  }
}

TEST_CASE("FRect::contains(FPoint)", "[FRect]")
{
  const FRect rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

  CHECK(rect.contains({rect.center_x(), rect.center_y()}));

  SECTION("Top-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.y()}));
    CHECK(!rect.contains({rect.x(), rect.y() - 1}));
  }

  SECTION("Top-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.y()}));
    CHECK(!rect.contains({rect.max_x(), rect.y() - 1}));
  }

  SECTION("Bottom-left corner")
  {
    CHECK(rect.contains({rect.x(), rect.max_y()}));
    CHECK(!rect.contains({rect.x() - 1, rect.max_y()}));
    CHECK(!rect.contains({rect.x(), rect.max_y() + 1}));
  }

  SECTION("Bottom-right corner")
  {
    CHECK(rect.contains({rect.max_x(), rect.max_y()}));
    CHECK(!rect.contains({rect.max_x() + 1, rect.max_y()}));
    CHECK(!rect.contains({rect.max_y(), rect.max_y() + 1}));
  }
}

TEST_CASE("FRect::has_area", "[FRect]")
{
  SECTION("Default values")
  {
    const FRect rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const FRect rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const FRect rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const FRect rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const FRect rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("FRect::x", "[FRect]")
{
  const FRect rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("FRect::y", "[FRect]")
{
  const FRect rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("FRect::center_x", "[FRect]")
{
  const auto x = 125.3f;
  const auto width = 3912.8f;
  const FRect rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2.0f));
}

TEST_CASE("FRect::center_y", "[FRect]")
{
  const auto y = 7128.2f;
  const auto height = 1240.2f;
  const FRect rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2.0f));
}

TEST_CASE("FRect::max_x", "[FRect]")
{
  const auto x = 289.2f;
  const auto width = 591.0f;
  const FRect rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("FRect::max_y", "[FRect]")
{
  const auto y = 1029.3f;
  const auto height = 6961.9f;
  const FRect rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("FRect::width", "[FRect]")
{
  const FRect rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("FRect::height", "[FRect]")
{
  const FRect rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("FRect::to_string", "[FRect]")
{
  const FRect rect{{17.5f, 72.9f}, {65.2f, 124.1f}};
  Log::info(Log::Category::Test, "%s", rect.to_string().c_str());
}

// TEST_CASE("FRect::equals", "[FRect]") {
//  SECTION("Reflexivity") {
//    const FRect rect{81.0f, 92.3f, 24.3f, 12.3f};
//    CHECK(FRect::equals(rect, rect));
//    CHECK(FRect::equals(rect, rect, 0));
//    CHECK(FRect::equals(rect, rect, -1));
//  }
//
//  SECTION("Exclusive epsilon range") {
//    const FRect first{10, 10, 10, 10};
//    const FRect other{11, 10, 10, 10};
//    CHECK(!FRect::equals(first, other, 1));
//  }
//
//  SECTION("In-range check") {
//    const FRect first{10, 10, 10, 10};
//    const FRect other{10.5f, 10, 10, 10};
//    CHECK(FRect::equals(first, other, 1));
//  }
//}

TEST_CASE("FRect to SDL_FRect*", "[FRect]")
{
  const FRect rect{{120.3f, 89.3f}, {569.5f, 124.8f}};
  const auto* sdlRect = static_cast<const SDL_FRect*>(rect);
  CHECK(rect.x() == sdlRect->x);
  CHECK(rect.y() == sdlRect->y);
  CHECK(rect.width() == sdlRect->w);
  CHECK(rect.height() == sdlRect->h);
}

TEST_CASE("operator==(IRect&, IRect&)", "[Rect]")
{
  SECTION("Reflexivity")
  {
    const IRect rect{{22, 34}, {85, 91}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const IRect first{{123, 623}, {82, 9912}};
    const IRect other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const IRect first{{123, 623}, {82, 9912}};
    const IRect other{{77, 23}, {2712, 933}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(IRect&, IRect&)", "[Rect]")
{
  SECTION("Self test")
  {
    const IRect rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const IRect first{{99, 23}, {74, 10}};
    const IRect other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const IRect first{{-45, 92}, {24, 882}};
    const IRect other{{821, 223}, {112, 72}};
    CHECK(first != other);
    CHECK(other != first);
  }
}

TEST_CASE("operator==(FRect&, FRect&)", "[FRect]")
{
  SECTION("Reflexivity")
  {
    const FRect rect{{18.2f, 57.7f}, {56.9f, 122.4f}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const FRect first{{782.2f, 112.4f}, {123.3f, 558.8f}};
    const FRect other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const FRect first{{12.2f, 821.3f}, {302.3f, 199.2f}};
    const FRect other{{82.2f, -12.3f}, {278.2f, 771.3f}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(FRect&, FRect&)", "[FRect]")
{
  SECTION("Self test")
  {
    const FRect rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const FRect first{{5.3f, 78.3f}, {824.3f, 792.7f}};
    const FRect other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const FRect first{{10.5f, 20.1f}, {50.9f, 29.2f}};
    const FRect other{{59.2f, 82.4f}, {88.2f, 812.4f}};
    CHECK(first != other);
    CHECK(other != first);
  }
}