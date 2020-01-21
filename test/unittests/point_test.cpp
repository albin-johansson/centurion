#include "catch.hpp"
#include "point.h"

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

TEST_CASE("Point::operator SDL_Point", "[Point]") {
  const Point point{124, 82};
  const SDL_Point sdlPoint = point;

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
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

TEST_CASE("FPoint operator SDL_FPoint", "[Point]") {
  const FPoint point{76.2f, 91.2f};
  const SDL_FPoint sdlPoint = point;

  CHECK(point.get_x() == sdlPoint.x);
  CHECK(point.get_y() == sdlPoint.y);
}