#include "catch.hpp"
#include "point.h"
#include "log.h"

using namespace centurion;

TEST_CASE("Point()", "[Point]") {
  Point p;
  CHECK(p.get_x() == 0);
  CHECK(p.get_y() == 0);
}

TEST_CASE("Point(int, int)", "[Point]") {
  const auto x = 125;
  const auto y = -853;
  Point p{x, y};

  CHECK(p.get_x() == x);
  CHECK(p.get_y() == y);
}

TEST_CASE("Point(SDL_Point)", "[Point]") {
  SDL_Point sdlPoint{467, 829};
  Point point{sdlPoint};

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}

TEST_CASE("Point::set_x", "[Point]") {
  const auto x = 992;

  Point point;
  point.set_x(x);

  CHECK(x == point.get_x());
}

TEST_CASE("Point::set_y", "[Point]") {
  const auto y = 77;

  Point point;
  point.set_y(y);

  CHECK(y == point.get_y());
}

TEST_CASE("Point::to_string", "[Point]") {
  const Point point{27, 82};
  Log::msgf(Category::Test, "%s", point.to_string().c_str());
}

TEST_CASE("Point::operator SDL_Point", "[Point]") {
  const Point point{124, 82};
  const SDL_Point sdlPoint = point;

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}

TEST_CASE("Point::operator==", "[Point]") {
  const Point point{812, 4829};
  const Point other{point};
  const Point different{point.get_x() + 10, point.get_y() + 10};

  CHECK(point == point);
  CHECK(point == other);
  CHECK(other == point);
  CHECK(!(point == different));
}

TEST_CASE("Point::operator!=", "[Point]") {
  const Point point{5029, 831};
  const Point other{1782, 923};

  CHECK(!(point != point));
  CHECK(point != other);
  CHECK(other != point);
}

TEST_CASE("FPoint()", "[Point]") {
  FPoint point;

  CHECK(point.get_x() == 0);
  CHECK(point.get_y() == 0);
}

TEST_CASE("FPoint(float, float)" "[Point]") {
  const auto x = 832.3f;
  const auto y = 192.9f;

  const FPoint point{x, y};

  CHECK(point.get_x() == x);
  CHECK(point.get_y() == y);
}

TEST_CASE("FPoint(SDL_FPoint)", "[Point]") {
  const SDL_FPoint sdlPoint{12.5f, 428.4f};
  const FPoint point{sdlPoint};

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
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

TEST_CASE("FPoint::to_string", "[FPoint]") {
  const FPoint point{45.5f, 77.2f};
  Log::msgf(Category::Test, "%s", point.to_string().c_str());
}

TEST_CASE("FPoint operator SDL_FPoint", "[Point]") {
  const FPoint point{76.2f, 91.2f};
  const SDL_FPoint sdlPoint = point;

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}

TEST_CASE("FPoint::equals", "[FPoint]") {
  const FPoint point{11.7f, 38.9f};
  const FPoint other{point};

  CHECK(FPoint::equals(point, point));
  CHECK(FPoint::equals(point, other));
  CHECK(FPoint::equals(other, point));
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