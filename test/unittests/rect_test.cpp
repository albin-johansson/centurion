#include "rect.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "log.hpp"

TEST_CASE("Rect default values", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect;

    CHECK(rect.x() == 0);
    CHECK(rect.y() == 0);
    CHECK(rect.width() == 0);
    CHECK(rect.height() == 0);
    CHECK(!rect.has_area());
  }
  SECTION("frect")
  {
    const cen::frect rect;

    CHECK(rect.x() == 0);
    CHECK(rect.y() == 0);
    CHECK(rect.width() == 0);
    CHECK(rect.height() == 0);
    CHECK(!rect.has_area());
  }
}

TEST_CASE("Rect construction", "[rect]")
{
  SECTION("irect")
  {
    const cen::ipoint pos{1124, 4125};
    const cen::iarea area{713, 372};
    const cen::irect rect{pos, area};

    CHECK(rect.x() == pos.x());
    CHECK(rect.y() == pos.y());
    CHECK(rect.width() == area.width);
    CHECK(rect.height() == area.height);

    CHECK_NOTHROW(cen::irect{{0, 0}, {0, 0}});
    CHECK_NOTHROW(cen::irect{{0, 0}, {-1, -1}});
  }

  SECTION("frect")
  {
    const cen::fpoint pos{123.5f, 81.4f};
    const cen::farea area{921.8f, 512.6f};
    const cen::frect rect{pos, area};

    CHECK(rect.x() == pos.x());
    CHECK(rect.y() == pos.y());
    CHECK(rect.width() == area.width);
    CHECK(rect.height() == area.height);

    CHECK_NOTHROW(cen::frect{{0, 0}, {0, 0}});
    CHECK_NOTHROW(cen::frect{{0, 0}, {-1, -1}});
  }
}

TEST_CASE("rect::set_x", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const auto x = 482;
    rect.set_x(x);

    CHECK(x == rect.x());
  }

  SECTION("frect")
  {
    cen::frect rect;

    const auto x = 74.3f;
    rect.set_x(x);

    CHECK(x == rect.x());
  }
}

TEST_CASE("rect::set_y", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const auto y = 1248;
    rect.set_y(y);

    CHECK(y == rect.y());
  }

  SECTION("frect")
  {
    cen::frect rect;

    const auto y = 839.4f;
    rect.set_y(y);

    CHECK(y == rect.y());
  }
}

TEST_CASE("rect::move_to", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const cen::ipoint pos{867, 654};

    rect.move_to(pos);

    CHECK(pos == rect.position());
  }

  SECTION("frect")
  {
    cen::frect rect;

    const cen::fpoint pos{742.3f, 377.2f};

    rect.move_to(pos);

    CHECK(pos == rect.position());
  }
}

TEST_CASE("rect::set_width", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const auto width = 10'594;
    rect.set_width(width);

    CHECK(width == rect.width());
  }

  SECTION("frect")
  {
    cen::frect rect;

    const auto width = 943.3f;
    rect.set_width(width);

    CHECK(width == rect.width());
  }
}

TEST_CASE("rect::set_height", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const auto height = 839'239;
    rect.set_height(height);

    CHECK(height == rect.height());
  }

  SECTION("frect")
  {
    cen::frect rect;

    const auto height = 62.35f;
    rect.set_height(height);

    CHECK(height == rect.height());
  }
}

TEST_CASE("rect::resize", "[rect]")
{
  SECTION("irect")
  {
    cen::irect rect;

    const cen::iarea size{8596, 9235};
    rect.resize(size);

    CHECK(rect.size() == size);
  }

  SECTION("frect")
  {
    cen::frect rect;

    const cen::farea size{345.8f, 289.7f};
    rect.resize(size);

    CHECK(rect.size() == size);
  }
}

TEST_CASE("rect::contains", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect{{931, 241}, {193, 93}};

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

  SECTION("frect")
  {
    const cen::frect rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

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
}

TEST_CASE("rect::has_area", "[rect]")
{
  SECTION("irect")
  {
    SECTION("Default values")
    {
      const cen::irect rect;
      CHECK(!rect.has_area());
    }

    SECTION("No width")
    {
      const cen::irect rect{{0, 0}, {0, 1}};
      CHECK(!rect.has_area());
    }

    SECTION("No height")
    {
      const cen::irect rect{{0, 0}, {1, 0}};
      CHECK(!rect.has_area());
    }

    SECTION("Negative dimensions")
    {
      const cen::irect rect{{0, 0}, {-1, -1}};
      CHECK(!rect.has_area());
    }

    SECTION("Valid dimensions")
    {
      const cen::irect rect{{0, 0}, {1, 1}};
      CHECK(rect.has_area());
    }
  }

  SECTION("frect")
  {
    SECTION("Default values")
    {
      const cen::frect rect;
      CHECK(!rect.has_area());
    }

    SECTION("No width")
    {
      const cen::frect rect{{0, 0}, {0, 1}};
      CHECK(!rect.has_area());
    }

    SECTION("No height")
    {
      const cen::frect rect{{0, 0}, {1, 0}};
      CHECK(!rect.has_area());
    }

    SECTION("Negative dimensions")
    {
      const cen::frect rect{{0, 0}, {-1, -1}};
      CHECK(!rect.has_area());
    }

    SECTION("Valid dimensions")
    {
      const cen::frect rect{{0, 0}, {1, 1}};
      CHECK(rect.has_area());
    }
  }
}

TEST_CASE("rect::x", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect;
    CHECK(rect.x() == 0);
  }

  SECTION("frect")
  {
    const cen::frect rect;
    CHECK(rect.x() == 0);
  }
}

TEST_CASE("rect::y", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect;
    CHECK(rect.y() == 0);
  }

  SECTION("frect")
  {
    const cen::frect rect;
    CHECK(rect.y() == 0);
  }
}

TEST_CASE("rect::width", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect;
    CHECK(rect.width() == 0);
  }

  SECTION("frect")
  {
    const cen::frect rect;
    CHECK(rect.width() == 0);
  }
}

TEST_CASE("rect::height", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect;
    CHECK(rect.height() == 0);
  }

  SECTION("frect")
  {
    const cen::frect rect;
    CHECK(rect.height() == 0);
  }
}

TEST_CASE("rect::max_x", "[rect]")
{
  SECTION("irect")
  {
    const auto x = 9123;
    const auto width = 1294;
    const cen::irect rect{{x, 0}, {width, 0}};

    CHECK(rect.max_x() == (x + width));
  }

  SECTION("frect")
  {
    const auto x = 289.2f;
    const auto width = 591.0f;
    const cen::frect rect{{x, 0}, {width, 0}};

    CHECK(rect.max_x() == (x + width));
  }
}

TEST_CASE("rect::max_y", "[rect]")
{
  SECTION("irect")
  {
    const auto y = 1245;
    const auto height = 7277;
    const cen::irect rect{{0, y}, {0, height}};

    CHECK(rect.max_y() == (y + height));
  }

  SECTION("frect")
  {
    const auto y = 1029.3f;
    const auto height = 6961.9f;
    const cen::frect rect{{0, y}, {0, height}};

    CHECK(rect.max_y() == (y + height));
  }
}

TEST_CASE("rect::center_x", "[rect]")
{
  SECTION("irect")
  {
    const auto x = 728;
    const auto width = 8819;
    const cen::irect rect{{x, 0}, {width, 0}};

    CHECK(rect.center_x() == x + (width / 2));
  }

  SECTION("frect")
  {
    const auto x = 125.3f;
    const auto width = 3912.8f;
    const cen::frect rect{{x, 0}, {width, 0}};

    CHECK(rect.center_x() == x + (width / 2.0f));
  }
}

TEST_CASE("rect::center_y", "[rect]")
{
  SECTION("irect")
  {
    const auto y = 8192;
    const auto height = 6637;
    const cen::irect rect{{0, y}, {0, height}};

    CHECK(rect.center_y() == y + (height / 2));
  }

  SECTION("frect")
  {
    const auto y = 7128.2f;
    const auto height = 1240.2f;
    const cen::frect rect{{0, y}, {0, height}};

    CHECK(rect.center_y() == y + (height / 2.0f));
  }
}

TEST_CASE("rect::area", "[rect]")
{
  SECTION("irect")
  {
    const auto width = 563;
    const auto height = 194;
    const cen::irect rect{{}, {width, height}};

    CHECK(rect.area() == (width * height));
  }

  SECTION("frect")
  {
    const auto width = 184.3f;
    const auto height = 728.9f;
    const cen::frect rect{{}, {width, height}};

    CHECK(rect.area() == (width * height));
  }
}

TEST_CASE("rect::center", "[rect]")
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;
  const cen::irect rect{{x, y}, {w, h}};

  const auto center = rect.center();
  CHECK(center.x() == x + (w / 2));
  CHECK(center.y() == y + (h / 2));
}

TEST_CASE("rect intersects", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect{{100, 100}, {100, 100}};

    CHECK(cen::intersects(rect, rect));

    SECTION("Empty rectangle")
    {
      const cen::irect empty;
      CHECK(!cen::intersects(empty, empty));

      CHECK(!cen::intersects(rect, empty));
      CHECK(!cen::intersects(empty, rect));
    }

    SECTION("Obviously no intersection")
    {
      const cen::irect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};

      const cen::irect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};

      const cen::irect right{{rect.x() + rect.width(), rect.y()},
                             {rect.width(), rect.height()}};

      const cen::irect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

      CHECK(!cen::intersects(left, rect));
      CHECK(!cen::intersects(rect, left));

      CHECK(!cen::intersects(top, rect));
      CHECK(!cen::intersects(rect, top));

      CHECK(!cen::intersects(right, rect));
      CHECK(!cen::intersects(rect, right));

      CHECK(!cen::intersects(bottom, rect));
      CHECK(!cen::intersects(rect, bottom));
    }

    SECTION("Edge cases")
    {
      const cen::irect left{{90, 100}, {10, 10}};
      CHECK(!cen::intersects(left, rect));
      CHECK(!cen::intersects(rect, left));

      const cen::irect top{{100, 90}, {10, 10}};
      CHECK(!cen::intersects(top, rect));
      CHECK(!cen::intersects(rect, top));

      const cen::irect right{{200, 100}, {10, 10}};
      CHECK(!cen::intersects(right, rect));
      CHECK(!cen::intersects(rect, right));

      const cen::irect bottom{{100, 200}, {10, 10}};
      CHECK(!cen::intersects(bottom, rect));
      CHECK(!cen::intersects(rect, bottom));
    }

    SECTION("Obvious intersections")
    {
      const cen::irect left{{90, 150}, {50, 1}};
      CHECK(cen::intersects(left, rect));
      CHECK(cen::intersects(rect, left));

      const cen::irect top{{150, 90}, {1, 50}};
      CHECK(cen::intersects(top, rect));
      CHECK(cen::intersects(rect, top));

      const cen::irect bottom{{150, 150}, {10, 50}};
      CHECK(cen::intersects(bottom, rect));
      CHECK(cen::intersects(rect, bottom));

      const cen::irect right{{150, 150}, {50, 10}};
      CHECK(cen::intersects(right, rect));
      CHECK(cen::intersects(rect, right));
    }
  }

  SECTION("frect")
  {
    const cen::frect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
    CHECK(cen::intersects(rect, rect));

    SECTION("Empty rectangle")
    {
      const cen::frect empty;
      CHECK(!cen::intersects(empty, empty));

      CHECK(!cen::intersects(rect, empty));
      CHECK(!cen::intersects(empty, rect));
    }

    SECTION("Obviously no intersection")
    {
      const cen::frect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
      const cen::frect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
      const cen::frect right{{rect.x() + rect.width(), rect.y()},
                             {rect.width(), rect.height()}};
      const cen::frect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

      CHECK(!cen::intersects(left, rect));
      CHECK(!cen::intersects(rect, left));

      CHECK(!cen::intersects(top, rect));
      CHECK(!cen::intersects(rect, top));

      CHECK(!cen::intersects(right, rect));
      CHECK(!cen::intersects(rect, right));

      CHECK(!cen::intersects(bottom, rect));
      CHECK(!cen::intersects(rect, bottom));
    }

    SECTION("Edge cases")
    {
      const cen::frect left{{90, 100}, {10, 10}};
      CHECK(!cen::intersects(left, rect));
      CHECK(!cen::intersects(rect, left));

      const cen::frect top{{100, 90}, {10, 10}};
      CHECK(!cen::intersects(top, rect));
      CHECK(!cen::intersects(rect, top));

      const cen::frect right{{200, 100}, {10, 10}};
      CHECK(!cen::intersects(right, rect));
      CHECK(!cen::intersects(rect, right));

      const cen::frect bottom{{100, 200}, {10, 10}};
      CHECK(!cen::intersects(bottom, rect));
      CHECK(!cen::intersects(rect, bottom));
    }

    SECTION("Obvious intersections")
    {
      const cen::frect left{{90, 150}, {50, 1}};
      CHECK(cen::intersects(left, rect));
      CHECK(cen::intersects(rect, left));

      const cen::frect top{{150, 90}, {1, 50}};
      CHECK(cen::intersects(top, rect));
      CHECK(cen::intersects(rect, top));

      const cen::frect bottom{{150, 150}, {10, 50}};
      CHECK(cen::intersects(bottom, rect));
      CHECK(cen::intersects(rect, bottom));

      const cen::frect right{{150, 150}, {50, 10}};
      CHECK(cen::intersects(right, rect));
      CHECK(cen::intersects(rect, right));
    }
  }
}

TEST_CASE("rect collides", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect{{100, 100}, {100, 100}};

    CHECK(cen::collides(rect, rect));

    SECTION("Obviously no collision")
    {
      const cen::irect left{{rect.x() - rect.width() - 1, rect.y()}, {10, 10}};

      const cen::irect top{{rect.x(), rect.y() - rect.height() - 1}, {10, 10}};

      const cen::irect right{{rect.x() + rect.width() + 1, rect.y()},
                             {rect.width(), rect.height()}};

      const cen::irect bottom{{rect.x(), rect.y() + rect.height() + 1},
                              {10, 10}};

      CHECK(!cen::collides(left, rect));
      CHECK(!cen::collides(rect, left));

      CHECK(!cen::collides(top, rect));
      CHECK(!cen::collides(rect, top));

      CHECK(!cen::collides(right, rect));
      CHECK(!cen::collides(rect, right));

      CHECK(!cen::collides(bottom, rect));
      CHECK(!cen::collides(rect, bottom));
    }

    SECTION("Edge cases")
    {
      const cen::irect left{{89, 100}, {10, 10}};
      CHECK(!cen::collides(left, rect));
      CHECK(!cen::collides(rect, left));

      const cen::irect top{{100, 89}, {10, 10}};
      CHECK(!cen::collides(top, rect));
      CHECK(!cen::collides(rect, top));

      const cen::irect right{{201, 100}, {10, 10}};
      CHECK(!cen::collides(right, rect));
      CHECK(!cen::collides(rect, right));

      const cen::irect bottom{{100, 201}, {10, 10}};
      CHECK(!cen::collides(bottom, rect));
      CHECK(!cen::collides(rect, bottom));
    }

    SECTION("Obvious collisions")
    {
      const cen::irect left{{90, 150}, {50, 1}};
      CHECK(cen::collides(left, rect));
      CHECK(cen::collides(rect, left));

      const cen::irect top{{150, 90}, {1, 50}};
      CHECK(cen::collides(top, rect));
      CHECK(cen::collides(rect, top));

      const cen::irect bottom{{150, 150}, {10, 50}};
      CHECK(cen::collides(bottom, rect));
      CHECK(cen::collides(rect, bottom));

      const cen::irect right{{150, 150}, {50, 10}};
      CHECK(cen::collides(right, rect));
      CHECK(cen::collides(rect, right));
    }
  }

  SECTION("frect")
  {
    const cen::frect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
    CHECK(cen::collides(rect, rect));

    SECTION("Obviously no collisions")
    {
      const cen::frect left{{rect.x() - rect.width() - 1, rect.y()}, {10, 10}};
      const cen::frect top{{rect.x(), rect.y() - rect.height() - 1}, {10, 10}};
      const cen::frect right{{rect.x() + rect.width() + 1, rect.y()},
                             {rect.width(), rect.height()}};
      const cen::frect bottom{{rect.x(), rect.y() + rect.height() + 1},
                              {10, 10}};

      CHECK(!cen::collides(left, rect));
      CHECK(!cen::collides(rect, left));

      CHECK(!cen::collides(top, rect));
      CHECK(!cen::collides(rect, top));

      CHECK(!cen::collides(right, rect));
      CHECK(!cen::collides(rect, right));

      CHECK(!cen::collides(bottom, rect));
      CHECK(!cen::collides(rect, bottom));
    }

    SECTION("Edge cases")
    {
      const cen::frect left{{89, 100}, {10, 10}};
      CHECK(!cen::collides(left, rect));
      CHECK(!cen::collides(rect, left));

      const cen::frect top{{100, 89}, {10, 10}};
      CHECK(!cen::collides(top, rect));
      CHECK(!cen::collides(rect, top));

      const cen::frect right{{201, 100}, {10, 10}};
      CHECK(!cen::collides(right, rect));
      CHECK(!cen::collides(rect, right));

      const cen::frect bottom{{100, 201}, {10, 10}};
      CHECK(!cen::collides(bottom, rect));
      CHECK(!cen::collides(rect, bottom));
    }

    SECTION("Obvious collisions")
    {
      const cen::frect left{{90, 150}, {50, 1}};
      CHECK(cen::collides(left, rect));
      CHECK(cen::collides(rect, left));

      const cen::frect top{{150, 90}, {1, 50}};
      CHECK(cen::collides(top, rect));
      CHECK(cen::collides(rect, top));

      const cen::frect bottom{{150, 150}, {10, 50}};
      CHECK(cen::collides(bottom, rect));
      CHECK(cen::collides(rect, bottom));

      const cen::frect right{{150, 150}, {50, 10}};
      CHECK(cen::collides(right, rect));
      CHECK(cen::collides(rect, right));
    }
  }
}

TEST_CASE("rect to_string", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect rect{{20, 45}, {100, 150}};
    cen::log::put(cen::to_string(rect));
  }

  SECTION("frect")
  {
    const cen::frect rect{{14.3f, 34.2f}, {182.8f, 120.9f}};
    cen::log::put(cen::to_string(rect));
  }
}

TEST_CASE("rect get_union", "[rect]")
{
  SECTION("irect")
  {
    const cen::irect fst{{10, 10}, {50, 50}};
    const cen::irect snd{{40, 40}, {50, 50}};

    SECTION("With empty rect")
    {
      const cen::irect empty;

      CHECK(cen::get_union(empty, empty) == empty);
      CHECK(cen::get_union(empty, fst) == fst);
      CHECK(cen::get_union(fst, empty) == fst);
    }

    const auto fstSnd = cen::get_union(fst, snd);
    const auto sndFst = cen::get_union(snd, fst);

    CHECK(fstSnd.has_area());

    CHECK(fstSnd.x() == 10);
    CHECK(fstSnd.y() == 10);
    CHECK(fstSnd.width() == 80);
    CHECK(fstSnd.height() == 80);

    CHECK(fstSnd == sndFst);
    CHECK(sndFst == fstSnd);
  }

  SECTION("frect")
  {
    const cen::frect fst{{10.0f, 10.0f}, {50.0f, 50.0f}};
    const cen::frect snd{{40.0f, 40.0f}, {50.0f, 50.0f}};

    SECTION("With empty rect")
    {
      const cen::frect empty;

      CHECK(cen::get_union(empty, empty) == empty);
      CHECK(cen::get_union(empty, fst) == fst);
      CHECK(cen::get_union(fst, empty) == fst);
    }

    const auto fstSnd = cen::get_union(fst, snd);
    const auto sndFst = cen::get_union(snd, fst);

    CHECK(fstSnd.has_area());

    CHECK(fstSnd.x() == 10.0f);
    CHECK(fstSnd.y() == 10.0f);
    CHECK(fstSnd.width() == 80.0f);
    CHECK(fstSnd.height() == 80.0f);

    CHECK(fstSnd == sndFst);
    CHECK(sndFst == fstSnd);
  }
}

TEST_CASE("Rect conversions", "[rect]")
{
  SECTION("irect -> frect")
  {
    const cen::irect from{{78, 12}, {283, 313}};
    const auto to = cen::cast<cen::frect>(from);

    CHECK(to.x() == static_cast<float>(from.x()));
    CHECK(to.y() == static_cast<float>(from.y()));
    CHECK(to.width() == static_cast<float>(from.width()));
    CHECK(to.height() == static_cast<float>(from.height()));
  }

  SECTION("frect -> irect")
  {
    const cen::frect from{{831.3f, 899.1f}, {67.2f, 91.7f}};
    const auto to = cen::cast<cen::irect>(from);

    CHECK(to.x() == static_cast<int>(from.x()));
    CHECK(to.y() == static_cast<int>(from.y()));
    CHECK(to.width() == static_cast<int>(from.width()));
    CHECK(to.height() == static_cast<int>(from.height()));
  }

  SECTION("frect -> SDL_FRect*")
  {
    const cen::frect rect{{78.3f, 623.2f}, {99.13f, 64.3f}};
    const auto* ptr = static_cast<const SDL_FRect*>(rect);

    CHECK(rect.x() == ptr->x);
    CHECK(rect.y() == ptr->y);
    CHECK(rect.width() == ptr->w);
    CHECK(rect.height() == ptr->h);
  }

  SECTION("irect -> SDL_Rect*")
  {
    const cen::irect rect{{123, 321}, {782, 991}};
    const auto* ptr = static_cast<const SDL_Rect*>(rect);

    CHECK(rect.x() == ptr->x);
    CHECK(rect.y() == ptr->y);
    CHECK(rect.width() == ptr->w);
    CHECK(rect.height() == ptr->h);
  }
}

TEST_CASE("Rect operator==", "[rect]")
{
  SECTION("irect")
  {
    SECTION("Self")
    {
      const cen::irect rect{{22, 34}, {85, 91}};
      CHECK(rect == rect);
    }

    SECTION("Equal rectangles")
    {
      const cen::irect first{{123, 623}, {82, 9912}};
      const cen::irect other{first};
      CHECK(first == other);
      CHECK(other == first);
    }

    SECTION("Non-equal rectangles")
    {
      const cen::irect first{{123, 623}, {82, 9912}};
      const cen::irect other{{77, 23}, {2712, 933}};
      CHECK(!(first == other));
      CHECK(!(other == first));
    }
  }

  SECTION("frect")
  {
    SECTION("Self")
    {
      const cen::frect rect{{93.3f, 67.2f}, {54.2f, 777.8f}};
      CHECK(rect == rect);
    }

    SECTION("Equal rectangles")
    {
      const cen::frect fst{{78.2f, 21.2f}, {9.2f, 162.3f}};
      const cen::frect snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
    }

    SECTION("Non-equal rectangles")
    {
      const cen::frect fst{{8.2f, 123.3f}, {63.1f, 672.3f}};
      const cen::frect snd{{89.13f, 781.3f}, {781.2f, 331.3f}};
      CHECK_FALSE(fst == snd);
      CHECK_FALSE(snd == fst);
    }
  }
}

TEST_CASE("Rect operator!=", "[rect]")
{
  SECTION("irect")
  {
    SECTION("Self")
    {
      const cen::irect rect;
      CHECK_FALSE(rect != rect);
    }

    SECTION("Equal rectangles")
    {
      const cen::irect first{{99, 23}, {74, 10}};
      const cen::irect other{first};
      CHECK_FALSE(first != other);
      CHECK_FALSE(other != first);
    }

    SECTION("Different rectangles")
    {
      const cen::irect first{{-45, 92}, {24, 882}};
      const cen::irect other{{821, 223}, {112, 72}};
      CHECK(first != other);
      CHECK(other != first);
    }
  }

  SECTION("frect")
  {
    SECTION("Self")
    {
      const cen::frect rect;
      CHECK_FALSE(rect != rect);
    }

    SECTION("Equal rectangles")
    {
      const cen::frect fst{{712.3f, 34.3f}, {65.8f, 348.2f}};
      const cen::frect snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("Different rectangles")
    {
      const cen::frect fst{{-45.37f, 12.3f}, {89.13f, 371.3f}};
      const cen::frect snd{{738.3f, 8.24f}, {67.3f, 89.23f}};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }
  }
}
