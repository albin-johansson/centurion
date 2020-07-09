#include "rect.hpp"

#include <catch.hpp>

#include "log.hpp"

using namespace centurion;

TEST_CASE("IRect()", "[Rect]")
{
  const rect_i rect;

  CHECK(rect.x() == 0);
  CHECK(rect.y() == 0);
  CHECK(rect.width() == 0);
  CHECK(rect.height() == 0);
}

// TEST_CASE("IRect(x, y, width, height)", "[Rect]")
//{
//  using namespace literals;
//
//  const x_i x{124};
//  const y_i y{2145};
//  const width_i w{-124};
//  const height_i h{912};
//
//  const IRect rect{x, y, w, h};
//
//  IRect{1_xi, 2_yi, 100_wi, 100_hi};
//  FRect{1.0_xf, 2.0_yf, 100.0_wf, 100.0_hf};
//
//  //  CHECK(rect.x() == *x);
//  //  CHECK(rect.y() == y);
//  //  CHECK(rect.width() == w);
//  //  CHECK(rect.height() == h);
//}

TEST_CASE("IRect copy ctor", "[Rect]")
{
  const rect_i first{{123, 312}, {495, 9912}};
  const rect_i copy{first};

  CHECK(first.x() == copy.x());
  CHECK(first.y() == copy.y());
  CHECK(first.width() == copy.width());
  CHECK(first.height() == copy.height());
}

TEST_CASE("IRect::set_x", "[Rect]")
{
  rect_i rect;

  const auto x = 482;
  rect.set_x(x);

  CHECK(x == rect.x());
}

TEST_CASE("IRect::set_y", "[Rect]")
{
  rect_i rect;

  const auto y = 1248;
  rect.set_y(y);

  CHECK(y == rect.y());
}

TEST_CASE("IRect::move_to", "[Rect]")
{
  rect_i rect;

  const point_i pos{867, 654};

  rect.move_to(pos);

  CHECK(pos == rect.position());
}

TEST_CASE("IRect::set_width", "[Rect]")
{
  rect_i rect;

  const auto width = 10'594;
  rect.set_width(width);

  CHECK(width == rect.width());
}

TEST_CASE("IRect::set_height", "[Rect]")
{
  rect_i rect;

  const auto height = 839'239;
  rect.set_height(height);

  CHECK(height == rect.height());
}

TEST_CASE("IRect::resize", "[Rect]")
{
  rect_i rect;

  const area_i size{8596, 9235};
  rect.resize(size);

  CHECK(rect.size() == size);
}

TEST_CASE("IRect::set", "[Rect]")
{
  rect_i rect;
  const rect_i other{{702, 234}, {50, 27}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("IRect::intersects", "[Rect]")
{
  const rect_i rect{{100, 100}, {100, 100}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const rect_i left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const rect_i top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const rect_i right{{rect.x() + rect.width(), rect.y()},
                       {rect.width(), rect.height()}};
    const rect_i bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
    const rect_i left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const rect_i top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const rect_i right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const rect_i bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const rect_i left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const rect_i top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const rect_i bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const rect_i right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("IRect::contains(int, int)", "[Rect]")
{
  const rect_i rect{{10, 10}, {50, 50}};

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
  const rect_i rect{{931, 241}, {193, 93}};

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
    const rect_i rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const rect_i rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const rect_i rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const rect_i rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const rect_i rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("IRect::x", "[Rect]")
{
  const rect_i rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("IRect::y", "[Rect]")
{
  const rect_i rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("IRect::max_x", "[Rect]")
{
  const auto x = 9123;
  const auto width = 1294;
  const rect_i rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("IRect::max_y", "[Rect]")
{
  const auto y = 1245;
  const auto height = 7277;
  const rect_i rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("IRect::width", "[Rect]")
{
  const rect_i rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("IRect::height", "[Rect]")
{
  const rect_i rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("IRect::get_union", "[Rect]")
{
  const rect_i rect{{10, 10}, {50, 50}};
  const rect_i other{{40, 40}, {50, 50}};
  const rect_i res = rect.get_union(other);
  const rect_i res2 = other.get_union(rect);
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
  const rect_i rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2));
}

TEST_CASE("IRect::center_y", "[Rect]")
{
  const auto y = 8192;
  const auto height = 6637;
  const rect_i rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2));
}

TEST_CASE("IRect::area", "[Rect]")
{
  const auto width = 563;
  const auto height = 194;
  const rect_i rect{{}, {width, height}};

  CHECK(rect.area() == (width * height));
}

TEST_CASE("IRect::center", "[Rect]")
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;
  const rect_i rect{{x, y}, {w, h}};

  const auto center = rect.center();
  CHECK(center.x() == x + (w / 2));
  CHECK(center.y() == y + (h / 2));
}

TEST_CASE("IRect::to_string", "[Rect]")
{
  const rect_i rect{{20, 45}, {100, 150}};
  Log::info(Log::Category::Test, "%s", rect.to_string().c_str());
}

TEST_CASE("IRect to SDL_Rect*", "[Rect]")
{
  const rect_i rect{{123, 321}, {782, 991}};
  const auto* sdlRect = static_cast<const SDL_Rect*>(rect);
  CHECK(rect.x() == sdlRect->x);
  CHECK(rect.y() == sdlRect->y);
  CHECK(rect.width() == sdlRect->w);
  CHECK(rect.height() == sdlRect->h);
}

TEST_CASE("FRect()", "[FRect]")
{
  const rect_f rect;
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
  const rect_f rect{{x, y}, {width, height}};

  CHECK(rect.x() == x);
  CHECK(rect.y() == y);
  CHECK(rect.width() == width);
  CHECK(rect.height() == height);

  CHECK_NOTHROW(rect_f{{0, 0}, {0, 0}});
  CHECK_NOTHROW(rect_f{{0, 0}, {-1, -1}});
}

TEST_CASE("FRect(FPoint, FArea)", "[FRect]")
{
  const point_f pos{123.5f, 81.4f};
  const area_f area{921.8f, 512.6f};
  const rect_f rect{pos, area};

  CHECK(rect.x() == pos.x());
  CHECK(rect.y() == pos.y());
  CHECK(rect.width() == area.width);
  CHECK(rect.height() == area.height);

  CHECK_NOTHROW(rect_f{{0, 0}, {0, 0}});
  CHECK_NOTHROW(rect_f{{0, 0}, {-1, -1}});
}

TEST_CASE("FRect::set_x", "[FRect]")
{
  rect_f rect;

  const auto x = 91.1f;
  rect.set_x(x);

  CHECK(rect.x() == x);
}

TEST_CASE("FRect::set_y", "[FRect]")
{
  rect_f rect;

  const auto y = 119.7f;
  rect.set_y(y);

  CHECK(rect.y() == y);
}

TEST_CASE("FRect::move_to", "[FRect]")
{
  rect_f rect;

  const point_f pos{834.4f, 345.8f};

  rect.move_to(pos);

  CHECK(pos == rect.position());
}

TEST_CASE("FRect::set_width", "[FRect]")
{
  rect_f rect;

  const auto width = 991.5f;
  rect.set_width(width);

  CHECK(rect.width() == width);
}

TEST_CASE("FRect::set_height", "[FRect]")
{
  rect_f rect;

  const auto height = 717.2f;
  rect.set_height(height);

  CHECK(rect.height() == height);
}

TEST_CASE("FRect::resize", "[FRect]")
{
  rect_f rect;

  const area_f size{859.6f, 773.4f};
  rect.resize(size);

  CHECK(rect.size() == size);
}

TEST_CASE("FRect::set", "[FRect]")
{
  rect_f rect;
  const rect_f other{{123.6f, 738.7f}, {192.9f, 91.3f}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("FRect::intersects", "[FRect]")
{
  const rect_f rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const rect_f left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const rect_f top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const rect_f right{{rect.x() + rect.width(), rect.y()},
                       {rect.width(), rect.height()}};
    const rect_f bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
    const rect_f left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const rect_f top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const rect_f right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const rect_f bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const rect_f left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const rect_f top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const rect_f bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const rect_f right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("FRect::contains(float, float)", "[FRect]")
{
  const rect_f rect{{24.4f, 82.3f}, {38.9f, 77.2f}};

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
  const rect_f rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

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
    const rect_f rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const rect_f rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const rect_f rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const rect_f rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const rect_f rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("FRect::x", "[FRect]")
{
  const rect_f rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("FRect::y", "[FRect]")
{
  const rect_f rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("FRect::center_x", "[FRect]")
{
  const auto x = 125.3f;
  const auto width = 3912.8f;
  const rect_f rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2.0f));
}

TEST_CASE("FRect::center_y", "[FRect]")
{
  const auto y = 7128.2f;
  const auto height = 1240.2f;
  const rect_f rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2.0f));
}

TEST_CASE("FRect::area", "[FRect]")
{
  const auto width = 184.3f;
  const auto height = 728.9f;
  const rect_f rect{{}, {width, height}};

  CHECK(rect.area() == (width * height));
}

TEST_CASE("FRect::max_x", "[FRect]")
{
  const auto x = 289.2f;
  const auto width = 591.0f;
  const rect_f rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("FRect::max_y", "[FRect]")
{
  const auto y = 1029.3f;
  const auto height = 6961.9f;
  const rect_f rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("FRect::width", "[FRect]")
{
  const rect_f rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("FRect::height", "[FRect]")
{
  const rect_f rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("FRect::to_string", "[FRect]")
{
  const rect_f rect{{17.5f, 72.9f}, {65.2f, 124.1f}};
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
  const rect_f rect{{120.3f, 89.3f}, {569.5f, 124.8f}};
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
    const rect_i rect{{22, 34}, {85, 91}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const rect_i first{{123, 623}, {82, 9912}};
    const rect_i other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const rect_i first{{123, 623}, {82, 9912}};
    const rect_i other{{77, 23}, {2712, 933}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(IRect&, IRect&)", "[Rect]")
{
  SECTION("Self test")
  {
    const rect_i rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const rect_i first{{99, 23}, {74, 10}};
    const rect_i other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const rect_i first{{-45, 92}, {24, 882}};
    const rect_i other{{821, 223}, {112, 72}};
    CHECK(first != other);
    CHECK(other != first);
  }
}

TEST_CASE("operator==(FRect&, FRect&)", "[FRect]")
{
  SECTION("Reflexivity")
  {
    const rect_f rect{{18.2f, 57.7f}, {56.9f, 122.4f}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const rect_f first{{782.2f, 112.4f}, {123.3f, 558.8f}};
    const rect_f other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const rect_f first{{12.2f, 821.3f}, {302.3f, 199.2f}};
    const rect_f other{{82.2f, -12.3f}, {278.2f, 771.3f}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(FRect&, FRect&)", "[FRect]")
{
  SECTION("Self test")
  {
    const rect_f rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const rect_f first{{5.3f, 78.3f}, {824.3f, 792.7f}};
    const rect_f other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const rect_f first{{10.5f, 20.1f}, {50.9f, 29.2f}};
    const rect_f other{{59.2f, 82.4f}, {88.2f, 812.4f}};
    CHECK(first != other);
    CHECK(other != first);
  }
}