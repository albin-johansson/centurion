#include "point.h"
#include <type_traits>

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

Point::operator SDL_Point() const noexcept {
  return {x, y};
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

FPoint::operator SDL_FPoint() const noexcept {
  return {x, y};
}

}
