#include "rectangle.h"
#include <type_traits>
#include <SDL.h>

namespace centurion {

static_assert(sizeof(Rect) == sizeof(SDL_Rect));
static_assert(std::is_final_v<Rect>);
static_assert(std::is_convertible_v<Rect, const SDL_Rect&>);

static_assert(std::is_nothrow_copy_constructible_v<Rect>);
static_assert(std::is_nothrow_copy_assignable_v<Rect>);

static_assert(std::is_nothrow_move_constructible_v<Rect>);
static_assert(std::is_nothrow_move_assignable_v<Rect>);

static_assert(std::is_nothrow_default_constructible_v<Rect>);
static_assert(std::is_nothrow_destructible_v<Rect>);

Rect::Rect() noexcept = default;

Rect::Rect(int x, int y, int width, int height) noexcept
    : rect{x, y, width, height} {}

void Rect::set_x(int x) noexcept {
  rect.x = x;
}

void Rect::set_y(int y) noexcept {
  rect.y = y;
}

void Rect::set_width(int width) noexcept {
  rect.w = width;
}

void Rect::set_height(int height) noexcept {
  rect.h = height;
}

bool Rect::intersects(const Rect& other) const noexcept {
  return !(get_x() >= other.get_max_x()
      || get_max_x() <= other.get_x()
      || get_y() >= other.get_max_y()
      || get_max_y() <= other.get_y());
}

bool Rect::contains(int px, int py) const noexcept {
  return !(px < get_x() || py < get_y() || px > get_max_x() || py > get_max_y());
}

bool Rect::contains(Point point) const noexcept {
  return contains(point.get_x(), point.get_y());
}

bool Rect::has_area() const noexcept {
  return get_width() > 0 && get_height() > 0;
}

int Rect::get_x() const noexcept {
  return rect.x;
}

int Rect::get_y() const noexcept {
  return rect.y;
}

int Rect::get_max_x() const noexcept {
  return get_x() + get_width();
}

int Rect::get_max_y() const noexcept {
  return get_y() + get_height();
}

int Rect::get_width() const noexcept {
  return rect.w;
}

int Rect::get_height() const noexcept {
  return rect.h;
}

int Rect::get_center_x() const noexcept {
  return get_x() + (get_width() / 2);
}

int Rect::get_center_y() const noexcept {
  return get_y() + (get_height() / 2);
}

std::string Rect::to_string() const {
  const auto x = std::to_string(get_x());
  const auto y = std::to_string(get_y());
  const auto w = std::to_string(get_width());
  const auto h = std::to_string(get_height());
  return "[Rect | X: " + x + ", Y: " + y + ", Width: " + w + ", Height: " + h + "]";
}

Rect::operator const SDL_Rect&() const noexcept {
  return rect;
}

static_assert(sizeof(FRect) == sizeof(SDL_FRect));
static_assert(std::is_final_v<FRect>);
static_assert(std::is_convertible_v<FRect, const SDL_FRect&>);

static_assert(std::is_nothrow_copy_constructible_v<FRect>);
static_assert(std::is_nothrow_copy_assignable_v<FRect>);

static_assert(std::is_nothrow_move_constructible_v<FRect>);
static_assert(std::is_nothrow_move_assignable_v<FRect>);

static_assert(std::is_nothrow_default_constructible_v<FRect>);
static_assert(std::is_nothrow_destructible_v<FRect>);

FRect::FRect() noexcept = default;

FRect::FRect(float x, float y, float width, float height) noexcept
    : rect{x, y, width, height} {}

void FRect::set_x(float x) noexcept {
  rect.x = x;
}

void FRect::set_y(float y) noexcept {
  rect.y = y;
}

void FRect::set_width(float width) noexcept {
  rect.w = width;
}

void FRect::set_height(float height) noexcept {
  rect.h = height;
}

bool FRect::intersects(const FRect& other) const noexcept {
  return !(get_x() >= other.get_max_x()
      || get_max_x() <= other.get_x()
      || get_y() >= other.get_max_y()
      || get_max_y() <= other.get_y());
}

bool FRect::contains(float px, float py) const noexcept {
  return !(px < get_x() || py < get_y() || px > get_max_x() || py > get_max_y());
}

bool FRect::contains(FPoint point) const noexcept {
  return contains(point.get_x(), point.get_y());
}

bool FRect::has_area() const noexcept {
  return get_width() > 0 && get_height() > 0;
}

float FRect::get_x() const noexcept {
  return rect.x;
}

float FRect::get_y() const noexcept {
  return rect.y;
}

float FRect::get_center_x() const noexcept {
  return rect.x + (rect.w / 2.0f);
}

float FRect::get_center_y() const noexcept {
  return rect.y + (rect.h / 2.0f);
}

float FRect::get_max_x() const noexcept {
  return rect.x + rect.w;
}

float FRect::get_max_y() const noexcept {
  return rect.y + rect.h;
}

float FRect::get_width() const noexcept {
  return rect.w;
}

float FRect::get_height() const noexcept {
  return rect.h;
}

std::string FRect::to_string() const {
  const auto x = std::to_string(get_x());
  const auto y = std::to_string(get_y());
  const auto w = std::to_string(get_width());
  const auto h = std::to_string(get_height());
  return "[FRect | X: " + x + ", Y: " + y + ", Width: " + w + ", Height: " + h + "]";
}

FRect::operator const SDL_FRect&() const noexcept {
  return rect;
}

}
