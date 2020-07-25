#include "rect.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

TEST_CASE("Rect default values", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect;

    CHECK(rect.x() == 0);
    CHECK(rect.y() == 0);
    CHECK(rect.width() == 0);
    CHECK(rect.height() == 0);
    CHECK(!rect.has_area());
  }
  SECTION("frect")
  {
    const ctn::frect rect;

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
    const ctn::ipoint pos{1124, 4125};
    const ctn::area_i area{713, 372};
    const ctn::irect rect{pos, area};

    CHECK(rect.x() == pos.x());
    CHECK(rect.y() == pos.y());
    CHECK(rect.width() == area.width);
    CHECK(rect.height() == area.height);

    CHECK_NOTHROW(ctn::irect{{0, 0}, {0, 0}});
    CHECK_NOTHROW(ctn::irect{{0, 0}, {-1, -1}});
  }

  SECTION("frect")
  {
    const ctn::fpoint pos{123.5f, 81.4f};
    const ctn::area_f area{921.8f, 512.6f};
    const ctn::frect rect{pos, area};

    CHECK(rect.x() == pos.x());
    CHECK(rect.y() == pos.y());
    CHECK(rect.width() == area.width);
    CHECK(rect.height() == area.height);

    CHECK_NOTHROW(ctn::frect{{0, 0}, {0, 0}});
    CHECK_NOTHROW(ctn::frect{{0, 0}, {-1, -1}});
  }
}

TEST_CASE("rect::set_x", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const auto x = 482;
    rect.set_x(x);

    CHECK(x == rect.x());
  }

  SECTION("frect")
  {
    ctn::frect rect;

    const auto x = 74.3f;
    rect.set_x(x);

    CHECK(x == rect.x());
  }
}

TEST_CASE("rect::set_y", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const auto y = 1248;
    rect.set_y(y);

    CHECK(y == rect.y());
  }

  SECTION("frect")
  {
    ctn::irect rect;

    const auto y = 839.4f;
    rect.set_y(y);

    CHECK(y == rect.y());
  }
}

TEST_CASE("rect::move_to", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const ctn::ipoint pos{867, 654};

    rect.move_to(pos);

    CHECK(pos == rect.position());
  }

  SECTION("frect")
  {
    ctn::frect rect;

    const ctn::fpoint pos{742.3f, 377.2f};

    rect.move_to(pos);

    CHECK(pos == rect.position());
  }
}

TEST_CASE("rect::set_width", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const auto width = 10'594;
    rect.set_width(width);

    CHECK(width == rect.width());
  }

  SECTION("frect")
  {
    ctn::frect rect;

    const auto width = 943.3f;
    rect.set_width(width);

    CHECK(width == rect.width());
  }
}

TEST_CASE("rect::set_height", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const auto height = 839'239;
    rect.set_height(height);

    CHECK(height == rect.height());
  }

  SECTION("frect")
  {
    ctn::frect rect;

    const auto height = 62.35f;
    rect.set_height(height);

    CHECK(height == rect.height());
  }
}

TEST_CASE("rect::resize", "[rect]")
{
  SECTION("irect")
  {
    ctn::irect rect;

    const ctn::area_i size{8596, 9235};
    rect.resize(size);

    CHECK(rect.size() == size);
  }

  SECTION("frect")
  {
    ctn::frect rect;

    const ctn::area_f size{345.8f, 289.7f};
    rect.resize(size);

    CHECK(rect.size() == size);
  }
}

TEST_CASE("rect::intersects", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect{{100, 100}, {100, 100}};

    CHECK(rect.intersects(rect));

    SECTION("Obviously no intersection")
    {
      const ctn::irect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};

      const ctn::irect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};

      const ctn::irect right{{rect.x() + rect.width(), rect.y()},
                             {rect.width(), rect.height()}};

      const ctn::irect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
      const ctn::irect left{{90, 100}, {10, 10}};
      CHECK(!left.intersects(rect));
      CHECK(!rect.intersects(left));

      const ctn::irect top{{100, 90}, {10, 10}};
      CHECK(!top.intersects(rect));
      CHECK(!rect.intersects(top));

      const ctn::irect right{{200, 100}, {10, 10}};
      CHECK(!right.intersects(rect));
      CHECK(!rect.intersects(right));

      const ctn::irect bottom{{100, 200}, {10, 10}};
      CHECK(!bottom.intersects(rect));
      CHECK(!rect.intersects(bottom));
    }

    SECTION("Obvious intersections")
    {
      const ctn::irect left{{90, 150}, {50, 1}};
      CHECK(left.intersects(rect));
      CHECK(rect.intersects(left));

      const ctn::irect top{{150, 90}, {1, 50}};
      CHECK(top.intersects(rect));
      CHECK(rect.intersects(top));

      const ctn::irect bottom{{150, 150}, {10, 50}};
      CHECK(bottom.intersects(rect));
      CHECK(rect.intersects(bottom));

      const ctn::irect right{{150, 150}, {50, 10}};
      CHECK(right.intersects(rect));
      CHECK(rect.intersects(right));
    }
  }

  SECTION("frect")
  {
    const ctn::frect rect{{100.0f, 100.0f}, {100.0f, 100.0f}};
    CHECK(rect.intersects(rect));

    SECTION("Obviously no intersection")
    {
      const ctn::frect left{{rect.x() - rect.width(), rect.y()}, {10, 10}};
      const ctn::frect top{{rect.x(), rect.y() - rect.height()}, {10, 10}};
      const ctn::frect right{{rect.x() + rect.width(), rect.y()},
                             {rect.width(), rect.height()}};
      const ctn::frect bottom{{rect.x(), rect.y() + rect.height()}, {10, 10}};

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
      const ctn::frect left{{90, 100}, {10, 10}};
      CHECK(!left.intersects(rect));
      CHECK(!rect.intersects(left));

      const ctn::frect top{{100, 90}, {10, 10}};
      CHECK(!top.intersects(rect));
      CHECK(!rect.intersects(top));

      const ctn::frect right{{200, 100}, {10, 10}};
      CHECK(!right.intersects(rect));
      CHECK(!rect.intersects(right));

      const ctn::frect bottom{{100, 200}, {10, 10}};
      CHECK(!bottom.intersects(rect));
      CHECK(!rect.intersects(bottom));
    }

    SECTION("Obvious intersections")
    {
      const ctn::frect left{{90, 150}, {50, 1}};
      CHECK(left.intersects(rect));
      CHECK(rect.intersects(left));

      const ctn::frect top{{150, 90}, {1, 50}};
      CHECK(top.intersects(rect));
      CHECK(rect.intersects(top));

      const ctn::frect bottom{{150, 150}, {10, 50}};
      CHECK(bottom.intersects(rect));
      CHECK(rect.intersects(bottom));

      const ctn::frect right{{150, 150}, {50, 10}};
      CHECK(right.intersects(rect));
      CHECK(rect.intersects(right));
    }
  }
}

TEST_CASE("rect::contains", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect{{931, 241}, {193, 93}};

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
    const ctn::frect rect{{277.5f, 189.2f}, {79.2f, 58.2f}};

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
      const ctn::irect rect;
      CHECK(!rect.has_area());
    }

    SECTION("No width")
    {
      const ctn::irect rect{{0, 0}, {0, 1}};
      CHECK(!rect.has_area());
    }

    SECTION("No height")
    {
      const ctn::irect rect{{0, 0}, {1, 0}};
      CHECK(!rect.has_area());
    }

    SECTION("Negative dimensions")
    {
      const ctn::irect rect{{0, 0}, {-1, -1}};
      CHECK(!rect.has_area());
    }

    SECTION("Valid dimensions")
    {
      const ctn::irect rect{{0, 0}, {1, 1}};
      CHECK(rect.has_area());
    }
  }

  SECTION("frect")
  {
    SECTION("Default values")
    {
      const ctn::frect rect;
      CHECK(!rect.has_area());
    }

    SECTION("No width")
    {
      const ctn::frect rect{{0, 0}, {0, 1}};
      CHECK(!rect.has_area());
    }

    SECTION("No height")
    {
      const ctn::frect rect{{0, 0}, {1, 0}};
      CHECK(!rect.has_area());
    }

    SECTION("Negative dimensions")
    {
      const ctn::frect rect{{0, 0}, {-1, -1}};
      CHECK(!rect.has_area());
    }

    SECTION("Valid dimensions")
    {
      const ctn::frect rect{{0, 0}, {1, 1}};
      CHECK(rect.has_area());
    }
  }
}

TEST_CASE("rect::x", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect;
    CHECK(rect.x() == 0);
  }

  SECTION("frect")
  {
    const ctn::frect rect;
    CHECK(rect.x() == 0);
  }
}

TEST_CASE("rect::y", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect;
    CHECK(rect.y() == 0);
  }

  SECTION("frect")
  {
    const ctn::frect rect;
    CHECK(rect.y() == 0);
  }
}

TEST_CASE("rect::width", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect;
    CHECK(rect.width() == 0);
  }

  SECTION("frect")
  {
    const ctn::frect rect;
    CHECK(rect.width() == 0);
  }
}

TEST_CASE("rect::height", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect;
    CHECK(rect.height() == 0);
  }

  SECTION("frect")
  {
    const ctn::frect rect;
    CHECK(rect.height() == 0);
  }
}

TEST_CASE("rect::max_x", "[rect]")
{
  SECTION("irect")
  {
    const auto x = 9123;
    const auto width = 1294;
    const ctn::irect rect{{x, 0}, {width, 0}};

    CHECK(rect.max_x() == (x + width));
  }

  SECTION("frect")
  {
    const auto x = 289.2f;
    const auto width = 591.0f;
    const ctn::frect rect{{x, 0}, {width, 0}};

    CHECK(rect.max_x() == (x + width));
  }
}

TEST_CASE("rect::max_y", "[rect]")
{
  SECTION("irect")
  {
    const auto y = 1245;
    const auto height = 7277;
    const ctn::irect rect{{0, y}, {0, height}};

    CHECK(rect.max_y() == (y + height));
  }

  SECTION("frect")
  {
    const auto y = 1029.3f;
    const auto height = 6961.9f;
    const ctn::frect rect{{0, y}, {0, height}};

    CHECK(rect.max_y() == (y + height));
  }
}

TEST_CASE("rect::center_x", "[rect]")
{
  SECTION("irect")
  {
    const auto x = 728;
    const auto width = 8819;
    const ctn::irect rect{{x, 0}, {width, 0}};

    CHECK(rect.center_x() == x + (width / 2));
  }

  SECTION("frect")
  {
    const auto x = 125.3f;
    const auto width = 3912.8f;
    const ctn::frect rect{{x, 0}, {width, 0}};

    CHECK(rect.center_x() == x + (width / 2.0f));
  }
}

TEST_CASE("rect::center_y", "[rect]")
{
  SECTION("irect")
  {
    const auto y = 8192;
    const auto height = 6637;
    const ctn::irect rect{{0, y}, {0, height}};

    CHECK(rect.center_y() == y + (height / 2));
  }

  SECTION("frect")
  {
    const auto y = 7128.2f;
    const auto height = 1240.2f;
    const ctn::frect rect{{0, y}, {0, height}};

    CHECK(rect.center_y() == y + (height / 2.0f));
  }
}

TEST_CASE("rect::area", "[rect]")
{
  SECTION("irect")
  {
    const auto width = 563;
    const auto height = 194;
    const ctn::irect rect{{}, {width, height}};

    CHECK(rect.area() == (width * height));
  }

  SECTION("frect")
  {
    const auto width = 184.3f;
    const auto height = 728.9f;
    const ctn::frect rect{{}, {width, height}};

    CHECK(rect.area() == (width * height));
  }
}

TEST_CASE("rect::center", "[rect]")
{
  const auto x = 77;
  const auto y = 81;
  const auto w = 128;
  const auto h = 256;
  const ctn::irect rect{{x, y}, {w, h}};

  const auto center = rect.center();
  CHECK(center.x() == x + (w / 2));
  CHECK(center.y() == y + (h / 2));
}

TEST_CASE("rect::to_string", "[rect]")
{
  SECTION("irect")
  {
    const ctn::irect rect{{20, 45}, {100, 150}};
    ctn::log::info(
        ctn::log::category::test, "%s", ctn::to_string(rect).c_str());
  }

  SECTION("frect")
  {
    const ctn::frect rect{{14.3f, 34.2f}, {182.8f, 120.9f}};
    ctn::log::info(
        ctn::log::category::test, "%s", ctn::to_string(rect).c_str());
  }
}

TEST_CASE("rect::get_union", "[rect]")
{
  const ctn::irect fst{{10, 10}, {50, 50}};
  const ctn::irect snd{{40, 40}, {50, 50}};

  const auto fstSnd = ctn::get_union(fst, snd);
  const auto sndFst = ctn::get_union(snd, fst);

  CHECK(fstSnd.has_area());

  CHECK(fstSnd.x() == 10);
  CHECK(fstSnd.y() == 10);
  CHECK(fstSnd.width() == 80);
  CHECK(fstSnd.height() == 80);

  CHECK(fstSnd == sndFst);
  CHECK(sndFst == fstSnd);
}

TEST_CASE("Rect conversions", "[rect]")
{
  SECTION("irect -> frect")
  {
    const ctn::irect from{{78, 12}, {283, 313}};
    const auto to = static_cast<ctn::frect>(from);

    CHECK(to.x() == static_cast<float>(from.x()));
    CHECK(to.y() == static_cast<float>(from.y()));
    CHECK(to.width() == static_cast<float>(from.width()));
    CHECK(to.height() == static_cast<float>(from.height()));
  }

  SECTION("frect -> irect")
  {
    const ctn::frect from{{831.3f, 899.1f}, {67.2f, 91.7f}};
    const auto to = static_cast<ctn::irect>(from);

    CHECK(to.x() == static_cast<int>(from.x()));
    CHECK(to.y() == static_cast<int>(from.y()));
    CHECK(to.width() == static_cast<int>(from.width()));
    CHECK(to.height() == static_cast<int>(from.height()));
  }

  SECTION("frect -> SDL_FRect*")
  {
    const ctn::frect rect{{78.3f, 623.2f}, {99.13f, 64.3f}};
    const auto* ptr = static_cast<const SDL_FRect*>(rect);

    CHECK(rect.x() == ptr->x);
    CHECK(rect.y() == ptr->y);
    CHECK(rect.width() == ptr->w);
    CHECK(rect.height() == ptr->h);
  }

  SECTION("irect -> SDL_Rect*")
  {
    const ctn::irect rect{{123, 321}, {782, 991}};
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
      const ctn::irect rect{{22, 34}, {85, 91}};
      CHECK(rect == rect);
    }

    SECTION("Equal rectangles")
    {
      const ctn::irect first{{123, 623}, {82, 9912}};
      const ctn::irect other{first};
      CHECK(first == other);
      CHECK(other == first);
    }

    SECTION("Non-equal rectangles")
    {
      const ctn::irect first{{123, 623}, {82, 9912}};
      const ctn::irect other{{77, 23}, {2712, 933}};
      CHECK(!(first == other));
      CHECK(!(other == first));
    }
  }

  SECTION("frect")
  {
    SECTION("Self")
    {
      const ctn::frect rect{{93.3f, 67.2f}, {54.2f, 777.8f}};
      CHECK(rect == rect);
    }

    SECTION("Equal rectangles")
    {
      const ctn::frect fst{{78.2f, 21.2f}, {9.2f, 162.3f}};
      const ctn::frect snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
    }

    SECTION("Non-equal rectangles")
    {
      const ctn::frect fst{{8.2f, 123.3f}, {63.1f, 672.3f}};
      const ctn::frect snd{{89.13f, 781.3f}, {781.2f, 331.3f}};
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
      const ctn::irect rect;
      CHECK_FALSE(rect != rect);
    }

    SECTION("Equal rectangles")
    {
      const ctn::irect first{{99, 23}, {74, 10}};
      const ctn::irect other{first};
      CHECK_FALSE(first != other);
      CHECK_FALSE(other != first);
    }

    SECTION("Different rectangles")
    {
      const ctn::irect first{{-45, 92}, {24, 882}};
      const ctn::irect other{{821, 223}, {112, 72}};
      CHECK(first != other);
      CHECK(other != first);
    }
  }

  SECTION("frect")
  {
    SECTION("Self")
    {
      const ctn::frect rect;
      CHECK_FALSE(rect != rect);
    }

    SECTION("Equal rectangles")
    {
      const ctn::frect fst{{712.3f, 34.3f}, {65.8f, 348.2f}};
      const ctn::frect snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("Different rectangles")
    {
      const ctn::frect fst{{-45.37f, 12.3f}, {89.13f, 371.3f}};
      const ctn::frect snd{{738.3f, 8.24f}, {67.3f, 89.23f}};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }
  }
}
