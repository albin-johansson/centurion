#ifndef CENTURION_MOUSE_WHEEL_EVENT_SOURCE
#define CENTURION_MOUSE_WHEEL_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
auto operator==(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return lhs == static_cast<mouse_wheel_direction>(rhs);
}

CENTURION_DEF
auto operator==(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

CENTURION_DEF
auto operator!=(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
auto operator!=(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
mouse_wheel_event::mouse_wheel_event() noexcept : common_event{}
{}

CENTURION_DEF
mouse_wheel_event::mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void mouse_wheel_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void mouse_wheel_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void mouse_wheel_event::set_x_scroll(i32 xScroll) noexcept
{
  m_event.x = xScroll;
}

CENTURION_DEF
void mouse_wheel_event::set_y_scroll(i32 yScroll) noexcept
{
  m_event.y = yScroll;
}

CENTURION_DEF
void mouse_wheel_event::set_direction(mouse_wheel_direction direction) noexcept
{
  m_event.direction = static_cast<u32>(direction);
}

CENTURION_DEF
auto mouse_wheel_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto mouse_wheel_event::which() const noexcept -> u32
{
  return m_event.which;
}

CENTURION_DEF
auto mouse_wheel_event::x_scroll() const noexcept -> i32
{
  return m_event.x;
}

CENTURION_DEF
auto mouse_wheel_event::y_scroll() const noexcept -> i32
{
  return m_event.y;
}

CENTURION_DEF
auto mouse_wheel_event::direction() const noexcept -> mouse_wheel_direction
{
  return static_cast<mouse_wheel_direction>(m_event.direction);
}

}  // namespace centurion

#endif  // CENTURION_MOUSE_WHEEL_EVENT_SOURCE