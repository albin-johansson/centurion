#include "point.h"
#include <type_traits>
#include <cmath>

namespace centurion {

static_assert(std::is_final_v<Point>);
static_assert(std::is_convertible_v<Point, SDL_Point>);
static_assert(sizeof(Point) == sizeof(SDL_Point));

static_assert(std::is_nothrow_move_assignable_v<Point>);
static_assert(std::is_nothrow_move_constructible_v<Point>);

static_assert(std::is_nothrow_copy_assignable_v<Point>);
static_assert(std::is_nothrow_copy_constructible_v<Point>);

static_assert(std::is_nothrow_default_constructible_v<Point>);
static_assert(std::is_nothrow_destructible_v<Point>);

Point::Point() noexcept = default;

Point::Point(int x, int y) noexcept : x{x}, y{y} {}

Point::Point(SDL_Point point) noexcept : x{point.x}, y{point.y} {}

void Point::set_x(int x) noexcept {
  this->x = x;
}

void Point::set_y(int y) noexcept {
  this->y = y;
}

int Point::get_x() const noexcept {
  return x;
}

int Point::get_y() const noexcept {
  return y;
}

std::string Point::to_string() const {
  return "[Point | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + "]";
}

Point::operator SDL_Point() const noexcept {
  return {x, y};
}

bool operator==(const Point& lhs, const Point& rhs) noexcept {
  return lhs.get_x() == rhs.get_x()
      && lhs.get_y() == rhs.get_y();
}

bool operator!=(const Point& lhs, const Point& rhs) noexcept {
  return !(lhs == rhs);
}

static_assert(std::is_final_v<FPoint>);
static_assert(std::is_convertible_v<FPoint, SDL_FPoint>);
static_assert(sizeof(FPoint) == sizeof(SDL_FPoint));

static_assert(std::is_nothrow_move_assignable_v<FPoint>);
static_assert(std::is_nothrow_move_constructible_v<FPoint>);

static_assert(std::is_nothrow_copy_assignable_v<FPoint>);
static_assert(std::is_nothrow_copy_constructible_v<FPoint>);

static_assert(std::is_nothrow_default_constructible_v<FPoint>);
static_assert(std::is_nothrow_destructible_v<FPoint>);

FPoint::FPoint() noexcept = default;

FPoint::FPoint(float x, float y) noexcept : x{x}, y{y} {}

FPoint::FPoint(SDL_FPoint point) noexcept : x{point.x}, y{point.y} {}

void FPoint::set_x(float x) noexcept {
  this->x = x;
}

void FPoint::set_y(float y) noexcept {
  this->y = y;
}

float FPoint::get_x() const noexcept {
  return x;
}

float FPoint::get_y() const noexcept {
  return y;
}

std::string FPoint::to_string() const {
  return "[FPoint | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + "]";
}

FPoint::operator SDL_FPoint() const noexcept {
  return {x, y};
}

bool FPoint::equals(const FPoint& lhs, const FPoint& rhs, float epsilon) noexcept {
  return std::abs(lhs.get_x() - rhs.get_x()) < epsilon
      && std::abs(lhs.get_x() - rhs.get_x()) < epsilon;
}

bool operator==(const FPoint& lhs, const FPoint& rhs) noexcept {
  return FPoint::equals(lhs, rhs);
}

bool operator!=(const FPoint& lhs, const FPoint& rhs) noexcept {
  return !(lhs == rhs);
}

}
