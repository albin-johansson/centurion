#include "catch.hpp"
#include "rectangle.h"
#include "log.h"

using namespace centurion;

TEST_CASE("Rect()", "[Rect]") {
  const Rect rect;

  CHECK(rect.get_x() == 0);
  CHECK(rect.get_y() == 0);
  CHECK(rect.get_width() == 0);
  CHECK(rect.get_height() == 0);
}

TEST_CASE("Rect(int, int, int, int)", "[Rect]") {
  const auto x = 124;
  const auto y = 2145;
  const auto w = -124;
  const auto h = 912;
  const Rect rect{x, y, w, h};

  CHECK(rect.get_x() == x);
  CHECK(rect.get_y() == y);
  CHECK(rect.get_width() == w);
  CHECK(rect.get_height() == h);
}

TEST_CASE("Rect copy ctor", "[Rect]") {
  const Rect first{123, 312, 495, 9912};
  const Rect copy{first};

  CHECK(first.get_x() == copy.get_x());
  CHECK(first.get_y() == copy.get_y());
  CHECK(first.get_width() == copy.get_width());
  CHECK(first.get_height() == copy.get_height());
}

TEST_CASE("Rect::set_x", "[Rect]") {
  Rect rect;

  const auto x = 482;
  rect.set_x(x);

  CHECK(x == rect.get_x());
}

TEST_CASE("Rect::set_y", "[Rect]") {
  Rect rect;

  const auto y = 1248;
  rect.set_y(y);

  CHECK(y == rect.get_y());
}

TEST_CASE("Rect::set_width", "[Rect]") {
  Rect rect;

  const auto width = 10'594;
  rect.set_width(width);

  CHECK(width == rect.get_width());
}

TEST_CASE("Rect::set_height", "[Rect]") {
  Rect rect;

  const auto height = 839'239;
  rect.set_height(height);

  CHECK(height == rect.get_height());
}

TEST_CASE("Rect::set", "[Rect]") {
  Rect rect;
  const Rect other{702, 234, 50, 27};

  rect.set(other);

  CHECK(rect.get_x() == other.get_x());
  CHECK(rect.get_y() == other.get_y());
  CHECK(rect.get_width() == other.get_width());
  CHECK(rect.get_height() == other.get_height());
}

TEST_CASE("Rect::intersects", "[Rect]") {
  const Rect rect{100, 100, 100, 100};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection") {
    const Rect left{rect.get_x() - rect.get_width(), rect.get_y(), 10, 10};
    const Rect top{rect.get_x(), rect.get_y() - rect.get_height(), 10, 10};
    const Rect right{rect.get_x() + rect.get_width(),
                     rect.get_y(),
                     rect.get_width(),
                     rect.get_height()};
    const Rect bottom{rect.get_x(), rect.get_y() + rect.get_height(), 10, 10};

    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Edge cases") {
    const Rect left{90, 100, 10, 10};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const Rect top{100, 90, 10, 10};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const Rect right{200, 100, 10, 10};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const Rect bottom{100, 200, 10, 10};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections") {
    const Rect left{90, 150, 50, 1};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const Rect top{150, 90, 1, 50};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const Rect bottom{150, 150, 10, 50};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const Rect right{150, 150, 50, 10};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("Rect::contains(int, int)", "[Rect]") {
  const Rect rect{10, 10, 50, 50};

  CHECK(rect.contains(rect.get_center_x(), rect.get_center_y()));

  SECTION("Top-left corner") {
    CHECK(rect.contains(rect.get_x(), rect.get_y()));
    CHECK(!rect.contains(rect.get_x() - 1, rect.get_y()));
    CHECK(!rect.contains(rect.get_x(), rect.get_y() - 1));
  }

  SECTION("Top-right corner") {
    CHECK(rect.contains(rect.get_max_x(), rect.get_y()));
    CHECK(!rect.contains(rect.get_max_x() + 1, rect.get_y()));
    CHECK(!rect.contains(rect.get_max_x(), rect.get_y() - 1));
  }

  SECTION("Bottom-left corner") {
    CHECK(rect.contains(rect.get_x(), rect.get_max_y()));
    CHECK(!rect.contains(rect.get_x() - 1, rect.get_max_y()));
    CHECK(!rect.contains(rect.get_x(), rect.get_max_y() + 1));
  }

  SECTION("Bottom-right corner") {
    CHECK(rect.contains(rect.get_max_x(), rect.get_max_y()));
    CHECK(!rect.contains(rect.get_max_x() + 1, rect.get_max_y()));
    CHECK(!rect.contains(rect.get_max_y(), rect.get_max_y() + 1));
  }
}

TEST_CASE("Rect::contains(Point)", "[Rect]") {
  const Rect rect{931, 241, 193, 93};

  CHECK(rect.contains({rect.get_center_x(), rect.get_center_y()}));

  SECTION("Top-left corner") {
    CHECK(rect.contains({rect.get_x(), rect.get_y()}));
    CHECK(!rect.contains({rect.get_x() - 1, rect.get_y()}));
    CHECK(!rect.contains({rect.get_x(), rect.get_y() - 1}));
  }

  SECTION("Top-right corner") {
    CHECK(rect.contains({rect.get_max_x(), rect.get_y()}));
    CHECK(!rect.contains({rect.get_max_x() + 1, rect.get_y()}));
    CHECK(!rect.contains({rect.get_max_x(), rect.get_y() - 1}));
  }

  SECTION("Bottom-left corner") {
    CHECK(rect.contains({rect.get_x(), rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_x() - 1, rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_x(), rect.get_max_y() + 1}));
  }

  SECTION("Bottom-right corner") {
    CHECK(rect.contains({rect.get_max_x(), rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_max_x() + 1, rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_max_y(), rect.get_max_y() + 1}));
  }
}

TEST_CASE("Rect::has_area", "[Rect]") {
  SECTION("Default values") {
    const Rect rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width") {
    const Rect rect{0, 0, 0, 1};
    CHECK(!rect.has_area());
  }

  SECTION("No height") {
    const Rect rect{0, 0, 1, 0};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions") {
    const Rect rect{0, 0, -1, -1};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions") {
    const Rect rect{0, 0, 1, 1};
    CHECK(rect.has_area());
  }
}

TEST_CASE("Rect::get_x", "[Rect]") {
  const Rect rect;
  CHECK(rect.get_x() == 0);
}

TEST_CASE("Rect::get_y", "[Rect]") {
  const Rect rect;
  CHECK(rect.get_y() == 0);
}

TEST_CASE("Rect::get_max_x", "[Rect]") {
  const auto x = 9123;
  const auto width = 1294;
  const Rect rect{x, 0, width, 0};
  CHECK(rect.get_max_x() == (x + width));
}

TEST_CASE("Rect::get_max_y", "[Rect]") {
  const auto y = 1245;
  const auto height = 7277;
  const Rect rect{0, y, 0, height};
  CHECK(rect.get_max_y() == (y + height));
}

TEST_CASE("Rect::get_width", "[Rect]") {
  const Rect rect;
  CHECK(rect.get_width() == 0);
}

TEST_CASE("Rect::get_height", "[Rect]") {
  const Rect rect;
  CHECK(rect.get_height() == 0);
}

TEST_CASE("Rect::get_union", "[Rect]") {
  const Rect rect{10, 10, 50, 50};
  const Rect other{40, 40, 50, 50};
  const Rect res = rect.get_union(other);
  const Rect res2 = other.get_union(rect);
  CHECK(res.has_area());
  CHECK(res.get_x() == 10);
  CHECK(res.get_y() == 10);
  CHECK(res.get_width() == 80);
  CHECK(res.get_height() == 80);
  CHECK(res == res2);
  CHECK(res2 == res);
}

TEST_CASE("Rect::get_center_x", "[Rect]") {
  const auto x = 728;
  const auto width = 8819;
  const Rect rect{x, 0, width, 0};
  CHECK(rect.get_center_x() == x + (width / 2));
}

TEST_CASE("Rect::get_center_y", "[Rect]") {
  const auto y = 8192;
  const auto height = 6637;
  const Rect rect{0, y, 0, height};
  CHECK(rect.get_center_y() == y + (height / 2));
}

TEST_CASE("Rect::to_string", "[Rect]") {
  const Rect rect{20, 45, 100, 150};
  Log::msgf(Category::Test, "%s", rect.to_string().c_str());
}

TEST_CASE("Rect to SDL_Rect", "[Rect]") {
  const Rect rect{123, 321, 782, 991};
  const SDL_Rect sdlRect = rect;
  CHECK(rect.get_x() == sdlRect.x);
  CHECK(rect.get_y() == sdlRect.y);
  CHECK(rect.get_width() == sdlRect.w);
  CHECK(rect.get_height() == sdlRect.h);
}

TEST_CASE("FRect()", "[FRect]") {
  const FRect rect;
  CHECK(rect.get_x() == 0);
  CHECK(rect.get_y() == 0);
  CHECK(rect.get_width() == 0);
  CHECK(rect.get_height() == 0);
}

TEST_CASE("FRect(SDL_FRect&)", "[FRect]") {
  SDL_FRect sdlRect {4.5f, 16.2f, 25.9f, 56.8f};
  FRect rect{sdlRect};
  CHECK(rect == sdlRect);
  CHECK(sdlRect == rect);
}

TEST_CASE("FRect(float, float, float, float)", "[FRect]") {
  const auto x = 123.5f;
  const auto y = 81.4f;
  const auto width = 921.8f;
  const auto height = 512.6f;
  const FRect rect{x, y, width, height};

  CHECK(rect.get_x() == x);
  CHECK(rect.get_y() == y);
  CHECK(rect.get_width() == width);
  CHECK(rect.get_height() == height);

  CHECK_NOTHROW(FRect{0, 0, 0, 0});
  CHECK_NOTHROW(FRect{0, 0, -1, -1});
}

TEST_CASE("FRect::set_x", "[FRect]") {
  FRect rect;

  const auto x = 91.1f;
  rect.set_x(x);

  CHECK(rect.get_x() == x);
}

TEST_CASE("FRect::set_y", "[FRect]") {
  FRect rect;

  const auto y = 119.7f;
  rect.set_y(y);

  CHECK(rect.get_y() == y);
}

TEST_CASE("FRect::set_width", "[FRect]") {
  FRect rect;

  const auto width = 991.5f;
  rect.set_width(width);

  CHECK(rect.get_width() == width);
}

TEST_CASE("FRect::set_height", "[FRect]") {
  FRect rect;

  const auto height = 717.2f;
  rect.set_height(height);

  CHECK(rect.get_height() == height);
}

TEST_CASE("FRect::set", "[FRect]") {
  FRect rect;
  const FRect other{123.6f, 738.7f, 192.9f, 91.3f};

  rect.set(other);

  CHECK(rect.get_x() == other.get_x());
  CHECK(rect.get_y() == other.get_y());
  CHECK(rect.get_width() == other.get_width());
  CHECK(rect.get_height() == other.get_height());
}

TEST_CASE("FRect::intersects", "[FRect]") {
  const FRect rect{100.0f, 100.0f, 100.0f, 100.0f};
  CHECK(rect.intersects(rect));

  SECTION("Obviously no intersection") {
    const FRect left{rect.get_x() - rect.get_width(), rect.get_y(), 10, 10};
    const FRect top{rect.get_x(), rect.get_y() - rect.get_height(), 10, 10};
    const FRect right{rect.get_x() + rect.get_width(),
                      rect.get_y(),
                      rect.get_width(),
                      rect.get_height()};
    const FRect bottom{rect.get_x(), rect.get_y() + rect.get_height(), 10, 10};

    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Edge cases") {
    const FRect left{90, 100, 10, 10};
    CHECK(!left.intersects(rect));
    CHECK(!rect.intersects(left));

    const FRect top{100, 90, 10, 10};
    CHECK(!top.intersects(rect));
    CHECK(!rect.intersects(top));

    const FRect right{200, 100, 10, 10};
    CHECK(!right.intersects(rect));
    CHECK(!rect.intersects(right));

    const FRect bottom{100, 200, 10, 10};
    CHECK(!bottom.intersects(rect));
    CHECK(!rect.intersects(bottom));
  }

  SECTION("Obvious intersections") {
    const FRect left{90, 150, 50, 1};
    CHECK(left.intersects(rect));
    CHECK(rect.intersects(left));

    const FRect top{150, 90, 1, 50};
    CHECK(top.intersects(rect));
    CHECK(rect.intersects(top));

    const FRect bottom{150, 150, 10, 50};
    CHECK(bottom.intersects(rect));
    CHECK(rect.intersects(bottom));

    const FRect right{150, 150, 50, 10};
    CHECK(right.intersects(rect));
    CHECK(rect.intersects(right));
  }
}

TEST_CASE("FRect::contains(float, float)", "[FRect]") {
  const FRect rect{24.4f, 82.3f, 38.9f, 77.2f};

  CHECK(rect.contains(rect.get_center_x(), rect.get_center_y()));

  SECTION("Top-left corner") {
    CHECK(rect.contains(rect.get_x(), rect.get_y()));
    CHECK(!rect.contains(rect.get_x() - 1, rect.get_y()));
    CHECK(!rect.contains(rect.get_x(), rect.get_y() - 1));
  }

  SECTION("Top-right corner") {
    CHECK(rect.contains(rect.get_max_x(), rect.get_y()));
    CHECK(!rect.contains(rect.get_max_x() + 1, rect.get_y()));
    CHECK(!rect.contains(rect.get_max_x(), rect.get_y() - 1));
  }

  SECTION("Bottom-left corner") {
    CHECK(rect.contains(rect.get_x(), rect.get_max_y()));
    CHECK(!rect.contains(rect.get_x() - 1, rect.get_max_y()));
    CHECK(!rect.contains(rect.get_x(), rect.get_max_y() + 1));
  }

  SECTION("Bottom-right corner") {
    CHECK(rect.contains(rect.get_max_x(), rect.get_max_y()));
    CHECK(!rect.contains(rect.get_max_x() + 1, rect.get_max_y()));
    CHECK(!rect.contains(rect.get_max_y(), rect.get_max_y() + 1));
  }
}

TEST_CASE("FRect::contains(FPoint)", "[FRect]") {
  const FRect rect{277.5f, 189.2f, 79.2f, 58.2f};

  CHECK(rect.contains({rect.get_center_x(), rect.get_center_y()}));

  SECTION("Top-left corner") {
    CHECK(rect.contains({rect.get_x(), rect.get_y()}));
    CHECK(!rect.contains({rect.get_x() - 1, rect.get_y()}));
    CHECK(!rect.contains({rect.get_x(), rect.get_y() - 1}));
  }

  SECTION("Top-right corner") {
    CHECK(rect.contains({rect.get_max_x(), rect.get_y()}));
    CHECK(!rect.contains({rect.get_max_x() + 1, rect.get_y()}));
    CHECK(!rect.contains({rect.get_max_x(), rect.get_y() - 1}));
  }

  SECTION("Bottom-left corner") {
    CHECK(rect.contains({rect.get_x(), rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_x() - 1, rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_x(), rect.get_max_y() + 1}));
  }

  SECTION("Bottom-right corner") {
    CHECK(rect.contains({rect.get_max_x(), rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_max_x() + 1, rect.get_max_y()}));
    CHECK(!rect.contains({rect.get_max_y(), rect.get_max_y() + 1}));
  }
}

TEST_CASE("FRect::has_area", "[FRect]") {
  SECTION("Default values") {
    const FRect rect;
    CHECK(!rect.has_area());
  }

  SECTION("No width") {
    const FRect rect{0, 0, 0, 1};
    CHECK(!rect.has_area());
  }

  SECTION("No height") {
    const FRect rect{0, 0, 1, 0};
    CHECK(!rect.has_area());
  }

  SECTION("Negative dimensions") {
    const FRect rect{0, 0, -1, -1};
    CHECK(!rect.has_area());
  }

  SECTION("Valid dimensions") {
    const FRect rect{0, 0, 1, 1};
    CHECK(rect.has_area());
  }
}

TEST_CASE("FRect::get_x", "[FRect]") {
  const FRect rect;
  CHECK(rect.get_x() == 0);
}

TEST_CASE("FRect::get_y", "[FRect]") {
  const FRect rect;
  CHECK(rect.get_y() == 0);
}

TEST_CASE("FRect::get_center_x", "[FRect]") {
  const auto x = 125.3f;
  const auto width = 3912.8f;
  const FRect rect{x, 0, width, 0};
  CHECK(rect.get_center_x() == x + (width / 2.0f));
}

TEST_CASE("FRect::get_center_y", "[FRect]") {
  const auto y = 7128.2f;
  const auto height = 1240.2f;
  const FRect rect{0, y, 0, height};
  CHECK(rect.get_center_y() == y + (height / 2.0f));
}

TEST_CASE("FRect::get_max_x", "[FRect]") {
  const auto x = 289.2f;
  const auto width = 591.0f;
  const FRect rect{x, 0, width, 0};
  CHECK(rect.get_max_x() == (x + width));
}

TEST_CASE("FRect::get_max_y", "[FRect]") {
  const auto y = 1029.3f;
  const auto height = 6961.9f;
  const FRect rect{0, y, 0, height};
  CHECK(rect.get_max_y() == (y + height));
}

TEST_CASE("FRect::get_width", "[FRect]") {
  const FRect rect;
  CHECK(rect.get_width() == 0);
}

TEST_CASE("FRect::get_height", "[FRect]") {
  const FRect rect;
  CHECK(rect.get_height() == 0);
}

TEST_CASE("FRect::to_string", "[FRect]") {
  const FRect rect{17.5f, 72.9f, 65.2f, 124.1f};
  Log::msgf(Category::Test, "%s", rect.to_string().c_str());
}

TEST_CASE("FRect::equals", "[FRect]") {
  SECTION("Reflexivity") {
    const FRect rect{81.0f, 92.3f, 24.3f, 12.3f};
    CHECK(FRect::equals(rect, rect));
    CHECK(FRect::equals(rect, rect, 0));
    CHECK(FRect::equals(rect, rect, -1));
  }

  SECTION("Exclusive epsilon range") {
    const FRect first{10, 10, 10, 10};
    const FRect other{11, 10, 10, 10};
    CHECK(!FRect::equals(first, other, 1));
  }

  SECTION("In-range check") {
    const FRect first{10, 10, 10, 10};
    const FRect other{10.5f, 10, 10, 10};
    CHECK(FRect::equals(first, other, 1));
  }
}

TEST_CASE("FRect to SDL_FRect", "[FRect]") {
  const FRect rect{120.3f, 89.3f, 569.5f, 124.8f};
  const SDL_FRect sdlRect = rect;
  CHECK(rect.get_x() == sdlRect.x);
  CHECK(rect.get_y() == sdlRect.y);
  CHECK(rect.get_width() == sdlRect.w);
  CHECK(rect.get_height() == sdlRect.h);
}

TEST_CASE("operator==(Rect&, Rect&)", "[Rect]") {
  SECTION("Reflexivity") {
    const Rect rect{22, 34, 85, 91};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles") {
    const Rect first{123, 623, 82, 9912};
    const Rect other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles") {
    const Rect first{123, 623, 82, 9912};
    const Rect other{77, 23, 2712, 933};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(Rect&, Rect&)", "[Rect]") {
  SECTION("Self test") {
    const Rect rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles") {
    const Rect first{99, 23, 74, 10};
    const Rect other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles") {
    const Rect first{-45, 92, 24, 882};
    const Rect other{821, 223, 112, 72};
    CHECK(first != other);
    CHECK(other != first);
  }
}

TEST_CASE("operator==(FRect&, FRect&)", "[FRect]") {
  SECTION("Reflexivity") {
    const FRect rect{18.2f, 57.7f, 56.9f, 122.4f};
    CHECK(rect == rect);
  }

  SECTION("Equal rectangles") {
    const FRect first{782.2f, 112.4f, 123.3f, 558.8f};
    const FRect other{first};
    CHECK(first == other);
    CHECK(other == first);
  }

  SECTION("Non-equal rectangles") {
    const FRect first{12.2f, 821.3f, 302.3f, 199.2f};
    const FRect other{82.2f, -12.3f, 278.2f, 771.3f};
    CHECK(!(first == other));
    CHECK(!(other == first));
  }
}

TEST_CASE("operator!=(FRect&, FRect&)", "[FRect]") {
  SECTION("Self test") {
    const FRect rect;
    CHECK(!(rect != rect));
  }

  SECTION("Equal rectangles") {
    const FRect first{5.3f, 78.3f, 824.3f, 792.7f};
    const FRect other{first};
    CHECK(!(first != other));
    CHECK(!(other != first));
  }

  SECTION("Different rectangles") {
    const FRect first{10.5f, 20.1f, 50.9f, 29.2f};
    const FRect other{59.2f, 82.4f, 88.2f, 812.4f};
    CHECK(first != other);
    CHECK(other != first);
  }
}