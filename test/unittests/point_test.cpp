#include "point.h"

#include "catch.hpp"
#include "log.h"

using namespace centurion;
using namespace centurion::math;

TEST_CASE("IPoint()", "[Point]") {
  IPoint p;
  CHECK(p.get_x() == 0);
  CHECK(p.get_y() == 0);
}

TEST_CASE("IPoint(int, int)", "[Point]") {
  const auto x = 125;
  const auto y = -853;
  IPoint p{x, y};

  CHECK(p.get_x() == x);
  CHECK(p.get_y() == y);
}

TEST_CASE("IPoint::set_x", "[Point]") {
  const auto x = 992;

  IPoint point;
  point.set_x(x);

  CHECK(x == point.get_x());
}

TEST_CASE("IPoint::set_y", "[Point]") {
  const auto y = 77;

  IPoint point;
  point.set_y(y);

  CHECK(y == point.get_y());
}

TEST_CASE("IPoint::set(IPoint&)", "[Point]") {
  IPoint point;

  const auto x = 21006;
  const auto y = 3456;
  const IPoint other{x, y};

  point.set(other);

  CHECK(x == point.get_x());
  CHECK(y == point.get_y());
}

TEST_CASE("IPoint::set(int, int)", "[Point]") {
  IPoint point;

  const auto x = -2421;
  const auto y = 673;

  point.set(x, y);

  CHECK(x == point.get_x());
  CHECK(y == point.get_y());
}

TEST_CASE("IPoint::to_string", "[Point]") {
  const IPoint point{27, 82};
  Log::msgf(Category::Test, "%s", point.to_string().c_str());
}

TEST_CASE("Point to SDL_Point", "[Point]") {
  const IPoint point{124, 82};
  const SDL_Point sdlPoint = point.to_sdl_point();

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}

TEST_CASE("IPoint::distance", "[Point]") {
  SECTION("Basic x-step") {
    const IPoint a{0, 0};
    const IPoint b{1, 0};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  SECTION("Basic y-step") {
    const IPoint a{0, 0};
    const IPoint b{0, 1};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  const IPoint a{189, 86};
  const IPoint b{66, 36};

  const auto distance = std::sqrt(std::abs(a.get_x() - b.get_x()) +
                                  std::abs(a.get_y() - b.get_y()));

  CHECK(static_cast<int>(distance) == a.distance_to(b));
  CHECK(static_cast<int>(distance) == b.distance_to(a));
}

TEST_CASE("IPoint::operator==", "[Point]") {
  const IPoint point{812, 4829};
  const IPoint other{point};
  const IPoint different{point.get_x() + 10, point.get_y() + 10};

  CHECK(point == point);
  CHECK(point == other);
  CHECK(other == point);
  CHECK(!(point == different));
}

TEST_CASE("IPoint::operator!=", "[Point]") {
  const IPoint point{5029, 831};
  const IPoint other{1782, 923};

  CHECK(!(point != point));
  CHECK(point != other);
  CHECK(other != point);
}

TEST_CASE("IPoint::operator+", "[Point]") {
  const IPoint point{56, 87};
  const IPoint other{69, 175};

  const IPoint res1 = point + other;
  const IPoint res2 = other + point;

  CHECK(res1 == res2);

  CHECK(res1.get_x() == point.get_x() + other.get_x());
  CHECK(res1.get_y() == point.get_y() + other.get_y());
  CHECK(res2.get_x() == point.get_x() + other.get_x());
  CHECK(res2.get_y() == point.get_y() + other.get_y());
}

TEST_CASE("IPoint::operator-", "[Point]") {
  const IPoint point{673, 123};
  const IPoint other{-547, 451};

  const IPoint res1 = point - other;
  const IPoint res2 = other - point;

  CHECK(res1 != res2);

  CHECK(res1.get_x() == point.get_x() - other.get_x());
  CHECK(res1.get_y() == point.get_y() - other.get_y());

  CHECK(res2.get_x() == other.get_x() - point.get_x());
  CHECK(res2.get_y() == other.get_y() - point.get_y());
}

TEST_CASE("FPoint()", "[Point]") {
  FPoint point;

  CHECK(point.get_x() == 0);
  CHECK(point.get_y() == 0);
}

TEST_CASE("FPoint(float, float)", "[Point]") {
  const auto x = 832.3f;
  const auto y = 192.9f;

  const FPoint point{x, y};

  CHECK(point.get_x() == x);
  CHECK(point.get_y() == y);
}

TEST_CASE("FPoint::set_x", "[Point]") {
  FPoint point;

  const auto x = 48.1f;
  point.set_x(x);

  CHECK(x == point.get_x());
}

TEST_CASE("FPoint::set_y", "[Point]") {
  FPoint point;

  const auto y = 88.8f;
  point.set_y(y);

  CHECK(y == point.get_y());
}

TEST_CASE("FPoint::set(FPoint&)", "[FPoint]") {
  FPoint point;

  const auto x = 825.3f;
  const auto y = -425.5f;
  const FPoint other{x, y};

  point.set(other);

  CHECK(x == point.get_x());
  CHECK(y == point.get_y());
}

TEST_CASE("FPoint::set(float, float)", "[FPoint]") {
  FPoint point;

  const auto x = 2812.5f;
  const auto y = 391.4f;

  point.set(x, y);

  CHECK(x == point.get_x());
  CHECK(y == point.get_y());
}

TEST_CASE("FPoint::to_string", "[FPoint]") {
  const FPoint point{45.5f, 77.2f};
  Log::msgf(Category::Test, "%s", point.to_string().c_str());
}

TEST_CASE("FPoint to SDL_FPoint", "[FPoint]") {
  const FPoint point{76.2f, 91.2f};
  const SDL_FPoint sdlPoint = point.to_sdl_fpoint();

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}

TEST_CASE("Point::distance_to", "[FPoint]") {
  SECTION("Basic x-step") {
    const FPoint a{0, 0};
    const FPoint b{1, 0};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  SECTION("Basic y-step") {
    const FPoint a{0, 0};
    const FPoint b{0, 1};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  const FPoint a{123.8f, 82.4f};
  const FPoint b{45.9f, 12.4f};
  const auto distance = std::sqrt(std::abs(a.get_x() - b.get_x()) +
                                  std::abs(a.get_y() - b.get_y()));

  CHECK(distance == a.distance_to(b));
  CHECK(distance == b.distance_to(a));
}

TEST_CASE("FPoint::equals", "[FPoint]") {
  const FPoint point{11.7f, 38.9f};
  const FPoint other{point};

  CHECK(point.equals(point));
  CHECK(point.equals(other));
  CHECK(other.equals(point));
}

TEST_CASE("FPoint::operator==", "[FPoint]") {
  const FPoint point{27.1f, 97.4f};
  const FPoint other{point};
  const FPoint different{point.get_x() + 10, point.get_y() + 10};

  CHECK(point == point);
  CHECK(point == other);
  CHECK(other == point);
  CHECK(!(point == different));
}

TEST_CASE("FPoint::operator!=", "[FPoint]") {
  const FPoint point{56.2f, 88.8f};
  const FPoint other{66.3f, 15.7f};

  CHECK(!(point != point));
  CHECK(point != other);
  CHECK(other != point);
}

TEST_CASE("FPoint::operator+", "[FPoint]") {
  const FPoint point{25.8f, 17.8f};
  const FPoint other{44.6f, 33.7f};

  const FPoint res1 = point + other;
  const FPoint res2 = other + point;

  CHECK(res1 == res2);

  CHECK(res1.get_x() == point.get_x() + other.get_x());
  CHECK(res1.get_y() == point.get_y() + other.get_y());
  CHECK(res2.get_x() == point.get_x() + other.get_x());
  CHECK(res2.get_y() == point.get_y() + other.get_y());
}

TEST_CASE("FPoint::operator-", "[FPoint]") {
  const FPoint point{58.9f, 48.6f};
  const FPoint other{12.7f, 69.3f};

  const FPoint res1 = point - other;
  const FPoint res2 = other - point;

  CHECK(res1 != res2);

  CHECK(res1.get_x() == point.get_x() - other.get_x());
  CHECK(res1.get_y() == point.get_y() - other.get_y());

  CHECK(res2.get_x() == other.get_x() - point.get_x());
  CHECK(res2.get_y() == other.get_y() - point.get_y());
}