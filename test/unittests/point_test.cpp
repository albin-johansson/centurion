#include "point.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

TEST_CASE("point_i()", "[point]")
{
  ctn::point_i p;
  CHECK(p.x() == 0);
  CHECK(p.y() == 0);
}

TEST_CASE("point_i(int, int)", "[point]")
{
  const auto x = 125;
  const auto y = -853;
  ctn::point_i p{x, y};

  CHECK(p.x() == x);
  CHECK(p.y() == y);
}

TEST_CASE("point_i::set_x", "[point]")
{
  const auto x = 992;

  ctn::point_i point;
  point.set_x(x);

  CHECK(x == point.x());
}

TEST_CASE("point_i::set_y", "[point]")
{
  const auto y = 77;

  ctn::point_i point;
  point.set_y(y);

  CHECK(y == point.y());
}

TEST_CASE("point_i::set(point_i&)", "[point]")
{
  ctn::point_i point;

  const auto x = 21006;
  const auto y = 3456;
  const ctn::point_i other{x, y};

  point.set(other);

  CHECK(x == point.x());
  CHECK(y == point.y());
}

TEST_CASE("point_i::set(int, int)", "[point]")
{
  ctn::point_i point;

  const auto x = -2421;
  const auto y = 673;

  point.set(x, y);

  CHECK(x == point.x());
  CHECK(y == point.y());
}

TEST_CASE("point_i::to_string", "[point]")
{
  const ctn::point_i point{27, 82};
  ctn::log::info(ctn::log::category::test, "%s", point.to_string().c_str());
}

TEST_CASE("point to SDL_Point", "[point]")
{
  const ctn::point_i point{124, 82};
  const SDL_Point sdlPoint = static_cast<SDL_Point>(point);

  CHECK(point.x() == sdlPoint.x);
  CHECK(point.y() == sdlPoint.y);
}

TEST_CASE("point_i::distance", "[point]")
{
  SECTION("Basic x-step")
  {
    const ctn::point_i a{0, 0};
    const ctn::point_i b{1, 0};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  SECTION("Basic y-step")
  {
    const ctn::point_i a{0, 0};
    const ctn::point_i b{0, 1};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  const ctn::point_i a{189, 86};
  const ctn::point_i b{66, 36};

  const auto distance =
      std::sqrt(std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()));

  CHECK(static_cast<int>(distance) == a.distance_to(b));
  CHECK(static_cast<int>(distance) == b.distance_to(a));
}

TEST_CASE("point_i::operator==", "[point]")
{
  const ctn::point_i point{812, 4829};
  const ctn::point_i other{point};
  const ctn::point_i different{point.x() + 10, point.y() + 10};

  CHECK(point == point);
  CHECK(point == other);
  CHECK(other == point);
  CHECK(!(point == different));
}

TEST_CASE("point_i::operator!=", "[point]")
{
  const ctn::point_i point{5029, 831};
  const ctn::point_i other{1782, 923};

  CHECK(!(point != point));
  CHECK(point != other);
  CHECK(other != point);
}

TEST_CASE("point_i::operator+", "[point]")
{
  const ctn::point_i point{56, 87};
  const ctn::point_i other{69, 175};

  const ctn::point_i res1 = point + other;
  const ctn::point_i res2 = other + point;

  CHECK(res1 == res2);

  CHECK(res1.x() == point.x() + other.x());
  CHECK(res1.y() == point.y() + other.y());
  CHECK(res2.x() == point.x() + other.x());
  CHECK(res2.y() == point.y() + other.y());
}

TEST_CASE("point_i::operator-", "[point]")
{
  const ctn::point_i point{673, 123};
  const ctn::point_i other{-547, 451};

  const ctn::point_i res1 = point - other;
  const ctn::point_i res2 = other - point;

  CHECK(res1 != res2);

  CHECK(res1.x() == point.x() - other.x());
  CHECK(res1.y() == point.y() - other.y());

  CHECK(res2.x() == other.x() - point.x());
  CHECK(res2.y() == other.y() - point.y());
}

TEST_CASE("point_f()", "[point]")
{
  ctn::point_f point;

  CHECK(point.x() == 0);
  CHECK(point.y() == 0);
}

TEST_CASE("point_f(float, float)", "[point]")
{
  const auto x = 832.3f;
  const auto y = 192.9f;

  const ctn::point_f point{x, y};

  CHECK(point.x() == x);
  CHECK(point.y() == y);
}

TEST_CASE("point_f::set_x", "[point]")
{
  ctn::point_f point;

  const auto x = 48.1f;
  point.set_x(x);

  CHECK(x == point.x());
}

TEST_CASE("point_f::set_y", "[point]")
{
  ctn::point_f point;

  const auto y = 88.8f;
  point.set_y(y);

  CHECK(y == point.y());
}

TEST_CASE("point_f::set(point_f&)", "[point_f]")
{
  ctn::point_f point;

  const auto x = 825.3f;
  const auto y = -425.5f;
  const ctn::point_f other{x, y};

  point.set(other);

  CHECK(x == point.x());
  CHECK(y == point.y());
}

TEST_CASE("point_f::set(float, float)", "[point_f]")
{
  ctn::point_f point;

  const auto x = 2812.5f;
  const auto y = 391.4f;

  point.set(x, y);

  CHECK(x == point.x());
  CHECK(y == point.y());
}

TEST_CASE("point_f::to_string", "[point_f]")
{
  const ctn::point_f point{45.5f, 77.2f};
  ctn::log::info(ctn::log::category::test, "%s", point.to_string().c_str());
}

TEST_CASE("point_f to SDL_FPoint", "[point_f]")
{
  const ctn::point_f point{76.2f, 91.2f};
  const SDL_FPoint sdlPoint = static_cast<SDL_FPoint>(point);

  CHECK(point.x() == sdlPoint.x);
  CHECK(point.y() == sdlPoint.y);
}

TEST_CASE("point_f to SDL_FPoint*", "[point_f]")
{
  SECTION("Const version")
  {
    const ctn::point_f point{44.9f, 22.5f};
    const auto* sdlPoint = static_cast<const SDL_FPoint*>(point);

    CHECK(point.x() == sdlPoint->x);
    CHECK(point.y() == sdlPoint->y);
  }
  SECTION("Non-const version")
  {
    ctn::point_f point{89.7f, -24.6f};
    auto* sdlPoint = static_cast<SDL_FPoint*>(point);

    CHECK(point.x() == sdlPoint->x);
    CHECK(point.y() == sdlPoint->y);
  }
}

TEST_CASE("point_i to SDL_Point*", "[point_f]")
{
  SECTION("Const version")
  {
    const ctn::point_i point{-58, 99};
    const auto* sdlPoint = static_cast<const SDL_Point*>(point);

    CHECK(point.x() == sdlPoint->x);
    CHECK(point.y() == sdlPoint->y);
  }
  SECTION("Non-const version")
  {
    ctn::point_i point{10, 892};
    auto* sdlPoint = static_cast<SDL_Point*>(point);

    CHECK(point.x() == sdlPoint->x);
    CHECK(point.y() == sdlPoint->y);
  }
}

TEST_CASE("point::distance_to", "[point_f]")
{
  SECTION("Basic x-step")
  {
    const ctn::point_f a{0, 0};
    const ctn::point_f b{1, 0};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  SECTION("Basic y-step")
  {
    const ctn::point_f a{0, 0};
    const ctn::point_f b{0, 1};
    CHECK(1 == a.distance_to(b));
    CHECK(1 == b.distance_to(a));
  }

  const ctn::point_f a{123.8f, 82.4f};
  const ctn::point_f b{45.9f, 12.4f};
  const auto distance =
      std::sqrt(std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()));

  CHECK(distance == a.distance_to(b));
  CHECK(distance == b.distance_to(a));
}

TEST_CASE("point_f::equals", "[point_f]")
{
  const ctn::point_f point{11.7f, 38.9f};
  const ctn::point_f other{point};

  CHECK(point.equals(point));
  CHECK(point.equals(other));
  CHECK(other.equals(point));
}

TEST_CASE("point_f::operator==", "[point_f]")
{
  const ctn::point_f point{27.1f, 97.4f};
  const ctn::point_f other{point};
  const ctn::point_f different{point.x() + 10, point.y() + 10};

  CHECK(point == point);
  CHECK(point == other);
  CHECK(other == point);
  CHECK(!(point == different));
}

TEST_CASE("point_f::operator!=", "[point_f]")
{
  const ctn::point_f point{56.2f, 88.8f};
  const ctn::point_f other{66.3f, 15.7f};

  CHECK(!(point != point));
  CHECK(point != other);
  CHECK(other != point);
}

TEST_CASE("point_f::operator+", "[point_f]")
{
  const ctn::point_f point{25.8f, 17.8f};
  const ctn::point_f other{44.6f, 33.7f};

  const ctn::point_f res1 = point + other;
  const ctn::point_f res2 = other + point;

  CHECK(res1 == res2);

  CHECK(res1.x() == point.x() + other.x());
  CHECK(res1.y() == point.y() + other.y());
  CHECK(res2.x() == point.x() + other.x());
  CHECK(res2.y() == point.y() + other.y());
}

TEST_CASE("point_f::operator-", "[point_f]")
{
  const ctn::point_f point{58.9f, 48.6f};
  const ctn::point_f other{12.7f, 69.3f};

  const ctn::point_f res1 = point - other;
  const ctn::point_f res2 = other - point;

  CHECK(res1 != res2);

  CHECK(res1.x() == point.x() - other.x());
  CHECK(res1.y() == point.y() - other.y());

  CHECK(res2.x() == other.x() - point.x());
  CHECK(res2.y() == other.y() - point.y());
}