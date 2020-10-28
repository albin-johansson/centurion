#include "event.hpp"

namespace cen {

auto operator==(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return lhs == static_cast<mouse_wheel_direction>(rhs);
}

auto operator==(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

auto operator!=(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

auto operator!=(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

mouse_wheel_event::mouse_wheel_event() noexcept : common_event{}
{}

mouse_wheel_event::mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept
    : common_event{event}
{}

void mouse_wheel_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

void mouse_wheel_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

void mouse_wheel_event::set_x_scroll(i32 xScroll) noexcept
{
  m_event.x = xScroll;
}

void mouse_wheel_event::set_y_scroll(i32 yScroll) noexcept
{
  m_event.y = yScroll;
}

void mouse_wheel_event::set_direction(mouse_wheel_direction direction) noexcept
{
  m_event.direction = static_cast<u32>(direction);
}

auto mouse_wheel_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

auto mouse_wheel_event::which() const noexcept -> u32
{
  return m_event.which;
}

auto mouse_wheel_event::x_scroll() const noexcept -> i32
{
  return m_event.x;
}

auto mouse_wheel_event::y_scroll() const noexcept -> i32
{
  return m_event.y;
}

auto mouse_wheel_event::direction() const noexcept -> mouse_wheel_direction
{
  return static_cast<mouse_wheel_direction>(m_event.direction);
}

}  // namespace cen
