#include "rectangle.h"
#include <type_traits>
#include <SDL.h>

namespace centurion {

static_assert(sizeof(Rectangle) == sizeof(SDL_Rect));
static_assert(std::is_final_v<Rectangle>);
static_assert(std::is_convertible_v<Rectangle, const SDL_Rect&>);

static_assert(std::is_nothrow_copy_constructible_v<Rectangle>);
static_assert(std::is_nothrow_copy_assignable_v<Rectangle>);

static_assert(std::is_nothrow_move_constructible_v<Rectangle>);
static_assert(std::is_nothrow_move_assignable_v<Rectangle>);

Rectangle::Rectangle() noexcept = default;

Rectangle::Rectangle(int x, int y, int width, int height) noexcept
    : rect{x, y, width, height} {}

void Rectangle::set_x(int x) noexcept {
  rect.x = x;
}

void Rectangle::set_y(int y) noexcept {
  rect.y = y;
}

void Rectangle::set_width(int width) noexcept {
  rect.w = width;
}

void Rectangle::set_height(int height) noexcept {
  rect.h = height;
}

bool Rectangle::intersects(const Rectangle& r) noexcept {
  return !(get_x() >= r.get_max_x()
      || get_max_x() <= r.get_x()
      || get_y() >= r.get_max_y()
      || get_max_y() <= r.get_y());
}

bool Rectangle::contains(int px, int py) noexcept {
  return !(px < get_x() || py < get_y() || px > get_max_x() || py > get_max_y());
}

bool Rectangle::contains(Point point) noexcept {
  return contains(point.get_x(), point.get_y());
}

bool Rectangle::has_no_area() const noexcept {
  return get_width() <= 0 || get_height() <= 0;
}

int Rectangle::get_x() const noexcept {
  return rect.x;
}

int Rectangle::get_y() const noexcept {
  return rect.y;
}

int Rectangle::get_max_x() const noexcept {
  return get_x() + get_width();
}

int Rectangle::get_max_y() const noexcept {
  return get_y() + get_height();
}

int Rectangle::get_width() const noexcept {
  return rect.w;
}

int Rectangle::get_height() const noexcept {
  return rect.h;
}

int Rectangle::get_center_x() const noexcept {
  return get_x() + (get_width() / 2);
}

int Rectangle::get_center_y() const noexcept {
  return get_y() + (get_height() / 2);
}

Rectangle::operator const SDL_Rect&() const noexcept {
  return rect;
}

}
