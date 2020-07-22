#include "rect.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

TEST_CASE("rect_i()", "[rect_i]")
{
  const ctn::rect_i rect;

  CHECK(rect.x() == 0);
  CHECK(rect.y() == 0);
  CHECK(rect.width() == 0);
  CHECK(rect.height() == 0);
}

TEST_CASE("rect_i copy ctor", "[rect_i]")
{
  const ctn::rect_i first{{123, 312}, {495, 9912}};
  const ctn::rect_i copy{first};

  CHECK(first.x() == copy.x());
  CHECK(first.y() == copy.y());
  CHECK(first.width() == copy.width());
  CHECK(first.height() == copy.height());
}

TEST_CASE("rect_i::set_x", "[rect_i]")
{
  ctn::rect_i rect;

  const auto x = 482;
  rect.set_x(x);

  CHECK(x == rect.x());
}

TEST_CASE("rect_i::set_y", "[rect_i]")
{
  ctn::rect_i rect;

  const auto y = 1248;
  rect.set_y(y);

  CHECK(y == rect.y());
}

TEST_CASE("rect_i::move_to", "[rect_i]")
{
  ctn::rect_i rect;

  const ctn::point_i pos{867, 654};

  rect.move_to(pos);

  CHECK(pos == rect.position());
}

TEST_CASE("rect_i::set_width", "[rect_i]")
{
  ctn::rect_i rect;

  const auto width = 10'594;
  rect.set_width(width);

  CHECK(width == rect.width());
}

TEST_CASE("rect_i::set_height", "[rect_i]")
{
  ctn::rect_i rect;

  const auto height = 839'239;
  rect.set_height(height);

  CHECK(height == rect.height());
}

TEST_CASE("rect_i::resize", "[rect_i]")
{
  ctn::rect_i rect;

  const ctn::area_i size{8596, 9235};
  rect.resize(size);

  CHECK(rect.size() == size);
}

TEST_CASE("rect_i::set", "[rect_i]")
{
  ctn::rect_i rect;
  const ctn::rect_i other{{702, 234}, {50, 27}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("rect_i::intersects", "[rect_i]")
{
  const ctn::rect_i rect{{100, 100}, {100, 100}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const ctn::rect_i left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const ctn::rect_i top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const ctn::rect_i right{{rect.x() + rect.width(), rect.y()},
                            {rect.width(), rect.height()}};
    const ctn::rect_i bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
    const ctn::rect_i left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const ctn::rect_i top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const ctn::rect_i right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const ctn::rect_i bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const ctn::rect_i left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const ctn::rect_i top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const ctn::rect_i bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const ctn::rect_i right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("rect_i::contains(int, int)", "[rect_i]")
{
  const ctn::rect_i rect{{10, 10}, {50, 50}};

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

TEST_CASE("rect_i::contains(Point)", "[rect_i]")
{
  const ctn::rect_i rect{{931, 241}, {193, 93}};

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

TEST_CASE("rect_i::has_area", "[rect_i]")
{
  SECTION("Default values")
  {
    const ctn::rect_i rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const ctn::rect_i rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const ctn::rect_i rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const ctn::rect_i rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const ctn::rect_i rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("rect_i::x", "[rect_i]")
{
  const ctn::rect_i rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("rect_i::y", "[rect_i]")
{
  const ctn::rect_i rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("rect_i::max_x", "[rect_i]")
{
  const auto x = 9123;
  const auto width = 1294;
  const ctn::rect_i rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("rect_i::max_y", "[rect_i]")
{
  const auto y = 1245;
  const auto height = 7277;
  const ctn::rect_i rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("rect_i::width", "[rect_i]")
{
  const ctn::rect_i rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("rect_i::height", "[rect_i]")
{
  const ctn::rect_i rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("rect_i::get_union", "[rect_i]")
{
  const ctn::rect_i rect{{10, 10}, {50, 50}};
  const ctn::rect_i other{{40, 40}, {50, 50}};
  const ctn::rect_i res = rect.get_union(other);
  const ctn::rect_i res2 = other.get_union(rect);
  CHECK(res.has_area());
  CHECK(res.x() == 10);
  CHECK(res.y() == 10);
  CHECK(res.width() == 80);
  CHECK(res.height() == 80);
  CHECK(res == res2);
  CHECK(res2 == res);
}

TEST_CASE("rect_i::center_x", "[rect_i]")
{
  const auto x = 728;
  const auto width = 8819;
  const ctn::rect_i rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2));
}

TEST_CASE("rect_i::center_y", "[rect_i]")
{
  const auto y = 8192;
  const auto height = 6637;
  const ctn::rect_i rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2));
}

TEST_CASE("rect_i::area", "[rect_i]")
{
  const auto width = 563;
  const auto height = 194;
  const ctn::rect_i rect{{}, {width, height}};

  CHECK(rect.area() == (width * height));
}

TEST_CASE("rect_i::center", "[rect_i]")
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;
  const ctn::rect_i rect{{x, y}, {w, h}};

  const auto center = rect.center();
  CHECK(center.x() == x + (w / 2));
  CHECK(center.y() == y + (h / 2));
}

TEST_CASE("rect_i::to_string", "[rect_i]")
{
  const ctn::rect_i rect{{20, 45}, {100, 150}};
  ctn::log::info(ctn::log::category::test, "%s", rect.to_string().c_str());
}

TEST_CASE("rect_i to SDL_Rect*", "[rect_i]")
{
  const ctn::rect_i rect{{123, 321}, {782, 991}};
  const auto* sdlRect = static_cast<const SDL_Rect*>(rect);
  CHECK(rect.x() == sdlRect->x);
  CHECK(rect.y() == sdlRect->y);
  CHECK(rect.width() == sdlRect->w);
  CHECK(rect.height() == sdlRect->h);
}

TEST_CASE("rect_f()", "[rect_f]")
{
  const ctn::rect_f rect;
  CHECK(rect.x() == 0);
  CHECK(rect.y() == 0);
  CHECK(rect.width() == 0);
  CHECK(rect.height() == 0);
}

TEST_CASE("rect_f(float, float, float, float)", "[rect_f]")
{
  const auto x = 123.5f;
  const auto y = 81.4f;
  const auto width = 921.8f;
  const auto height = 512.6f;
  const ctn::rect_f rect{{x, y}, {width, height}};

  CHECK(rect.x() == x);
  CHECK(rect.y() == y);
  CHECK(rect.width() == width);
  CHECK(rect.height() == height);

  CHECK_NOTHROW(ctn::rect_f{{0, 0}, {0, 0}});
  CHECK_NOTHROW(ctn::rect_f{{0, 0}, {-1, -1}});
}

TEST_CASE("rect_f(point_f, area_f)", "[rect_f]")
{
  const ctn::point_f pos{123.5f, 81.4f};
  const ctn::area_f area{921.8f, 512.6f};
  const ctn::rect_f rect{pos, area};

  CHECK(rect.x() == pos.x());
  CHECK(rect.y() == pos.y());
  CHECK(rect.width() == area.width);
  CHECK(rect.height() == area.height);

  CHECK_NOTHROW(ctn::rect_f{{0, 0}, {0, 0}});
  CHECK_NOTHROW(ctn::rect_f{{0, 0}, {-1, -1}});
}

TEST_CASE("rect_f::set_x", "[rect_f]")
{
  ctn::rect_f rect;

  const auto x = 91.1f;
  rect.set_x(x);

  CHECK(rect.x() == x);
}

TEST_CASE("rect_f::set_y", "[rect_f]")
{
  ctn::rect_f rect;

  const auto y = 119.7f;
  rect.set_y(y);

  CHECK(rect.y() == y);
}

TEST_CASE("rect_f::move_to", "[rect_f]")
{
  ctn::rect_f rect;

  const ctn::point_f pos{834.4f, 345.8f};

  rect.move_to(pos);

  CHECK(pos == rect.position());
}

TEST_CASE("rect_f::set_width", "[rect_f]")
{
  ctn::rect_f rect;

  const auto width = 991.5f;
  rect.set_width(width);

  CHECK(rect.width() == width);
}

TEST_CASE("rect_f::set_height", "[rect_f]")
{
  ctn::rect_f rect;

  const auto height = 717.2f;
  rect.set_height(height);

  CHECK(rect.height() == height);
}

TEST_CASE("rect_f::resize", "[rect_f]")
{
  ctn::rect_f rect;

  const ctn::area_f size{859.6f, 773.4f};
  rect.resize(size);

  CHECK(rect.size() == size);
}

TEST_CASE("rect_f::set", "[rect_f]")
{
  ctn::rect_f rect;
  const ctn::rect_f other{{123.6f, 738.7f}, {192.9f, 91.3f}};

  rect.set(other);

  CHECK(rect.x() == other.x());
  CHECK(rect.y() == other.y());
  CHECK(rect.width() == other.width());
  CHECK(rect.height() == other.height());
}

TEST_CASE("rect_f::intersects", "[rect_f]")
{
  const ctn::rect_f rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection")
  {
    const ctn::rect_f left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
    const ctn::rect_f top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
    const ctn::rect_f right{{rect.x() + rect.width(), rect.y()},
                            {rect.width(), rect.height()}};
    const ctn::rect_f bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
    const ctn::rect_f left{{90, 100}, {10, 10}};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const ctn::rect_f top{{100, 90}, {10, 10}};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const ctn::rect_f right{{200, 100}, {10, 10}};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const ctn::rect_f bottom{{100, 200}, {10, 10}};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections")
  {
    const ctn::rect_f left{{90, 150}, {50, 1}};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const ctn::rect_f top{{150, 90}, {1, 50}};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const ctn::rect_f bottom{{150, 150}, {10, 50}};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const ctn::rect_f right{{150, 150}, {50, 10}};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("rect_f::contains(float, float)", "[rect_f]")
{
  const ctn::rect_f rect{{24.4f, 82.3f}, {38.9f, 77.2f}};

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

TEST_CASE("rect_f::contains(point_f)", "[rect_f]")
{
  const ctn::rect_f rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

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

TEST_CASE("rect_f::has_area", "[rect_f]")
{
  SECTION("Default values")
  {
    const ctn::rect_f rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width")
  {
    const ctn::rect_f rect{{0, 0}, {0, 1}};
    CHECK(!rect.has_area());
  }

  SECTION("No height")
  {
    const ctn::rect_f rect{{0, 0}, {1, 0}};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions")
  {
    const ctn::rect_f rect{{0, 0}, {-1, -1}};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions")
  {
    const ctn::rect_f rect{{0, 0}, {1, 1}};
    CHECK(rect.has_area());
  }
}

TEST_CASE("rect_f::x", "[rect_f]")
{
  const ctn::rect_f rect;
  CHECK(rect.x() == 0);
}

TEST_CASE("rect_f::y", "[rect_f]")
{
  const ctn::rect_f rect;
  CHECK(rect.y() == 0);
}

TEST_CASE("rect_f::center_x", "[rect_f]")
{
  const auto x = 125.3f;
  const auto width = 3912.8f;
  const ctn::rect_f rect{{x, 0}, {width, 0}};
  CHECK(rect.center_x() == x + (width / 2.0f));
}

TEST_CASE("rect_f::center_y", "[rect_f]")
{
  const auto y = 7128.2f;
  const auto height = 1240.2f;
  const ctn::rect_f rect{{0, y}, {0, height}};
  CHECK(rect.center_y() == y + (height / 2.0f));
}

TEST_CASE("rect_f::area", "[rect_f]")
{
  const auto width = 184.3f;
  const auto height = 728.9f;
  const ctn::rect_f rect{{}, {width, height}};

  CHECK(rect.area() == (width * height));
}

TEST_CASE("rect_f::max_x", "[rect_f]")
{
  const auto x = 289.2f;
  const auto width = 591.0f;
  const ctn::rect_f rect{{x, 0}, {width, 0}};
  CHECK(rect.max_x() == (x + width));
}

TEST_CASE("rect_f::max_y", "[rect_f]")
{
  const auto y = 1029.3f;
  const auto height = 6961.9f;
  const ctn::rect_f rect{{0, y}, {0, height}};
  CHECK(rect.max_y() == (y + height));
}

TEST_CASE("rect_f::width", "[rect_f]")
{
  const ctn::rect_f rect;
  CHECK(rect.width() == 0);
}

TEST_CASE("rect_f::height", "[rect_f]")
{
  const ctn::rect_f rect;
  CHECK(rect.height() == 0);
}

TEST_CASE("rect_f::to_string", "[rect_f]")
{
  const ctn::rect_f rect{{17.5f, 72.9f}, {65.2f, 124.1f}};
  ctn::log::info(ctn::log::category::test, "%s", rect.to_string().c_str());
}

TEST_CASE("rect_f to SDL_FRect*", "[rect_f]")
{
  const ctn::rect_f rect{{120.3f, 89.3f}, {569.5f, 124.8f}};
  const auto* sdlRect = static_cast<const SDL_FRect*>(rect);
  CHECK(rect.x() == sdlRect->x);
  CHECK(rect.y() == sdlRect->y);
  CHECK(rect.width() == sdlRect->w);
  CHECK(rect.height() == sdlRect->h);
}

TEST_CASE("operator==(rect_i&, rect_i&)", "[rect_i]")
{
  SECTION("Reflexivity")
  {
    const ctn::rect_i rect{{22, 34}, {85, 91}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const ctn::rect_i first{{123, 623}, {82, 9912}};
    const ctn::rect_i other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const ctn::rect_i first{{123, 623}, {82, 9912}};
    const ctn::rect_i other{{77, 23}, {2712, 933}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(rect_i&, rect_i&)", "[rect_i]")
{
  SECTION("Self test")
  {
    const ctn::rect_i rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const ctn::rect_i first{{99, 23}, {74, 10}};
    const ctn::rect_i other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const ctn::rect_i first{{-45, 92}, {24, 882}};
    const ctn::rect_i other{{821, 223}, {112, 72}};
    CHECK(first != other);
    CHECK(other != first);
  }
}

TEST_CASE("operator==(rect_f&, rect_f&)", "[rect_f]")
{
  SECTION("Reflexivity")
  {
    const ctn::rect_f rect{{18.2f, 57.7f}, {56.9f, 122.4f}};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles")
  {
    const ctn::rect_f first{{782.2f, 112.4f}, {123.3f, 558.8f}};
    const ctn::rect_f other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles")
  {
    const ctn::rect_f first{{12.2f, 821.3f}, {302.3f, 199.2f}};
    const ctn::rect_f other{{82.2f, -12.3f}, {278.2f, 771.3f}};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(rect_f&, rect_f&)", "[rect_f]")
{
  SECTION("Self test")
  {
    const ctn::rect_f rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles")
  {
    const ctn::rect_f first{{5.3f, 78.3f}, {824.3f, 792.7f}};
    const ctn::rect_f other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles")
  {
    const ctn::rect_f first{{10.5f, 20.1f}, {50.9f, 29.2f}};
    const ctn::rect_f other{{59.2f, 82.4f}, {88.2f, 812.4f}};
    CHECK(first != other);
    CHECK(other != first);
  }
}