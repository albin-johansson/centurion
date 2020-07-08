#ifndef CENTURION_MOUSE_WHEEL_EVENT_SOURCE
#define CENTURION_MOUSE_WHEEL_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
auto operator==(MouseWheelDirection lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return lhs == static_cast<MouseWheelDirection>(rhs);
}

CENTURION_DEF
auto operator==(SDL_MouseWheelDirection lhs, MouseWheelDirection rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

CENTURION_DEF
auto operator!=(MouseWheelDirection lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
auto operator!=(SDL_MouseWheelDirection lhs, MouseWheelDirection rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
MouseWheelEvent::MouseWheelEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
MouseWheelEvent::MouseWheelEvent(const SDL_MouseWheelEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void MouseWheelEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void MouseWheelEvent::set_which(Uint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void MouseWheelEvent::set_x_scroll(Sint32 xScroll) noexcept
{
  m_event.x = xScroll;
}

CENTURION_DEF
void MouseWheelEvent::set_y_scroll(Sint32 yScroll) noexcept
{
  m_event.y = yScroll;
}

CENTURION_DEF
void MouseWheelEvent::set_direction(MouseWheelDirection direction) noexcept
{
  m_event.direction = static_cast<Uint32>(direction);
}

CENTURION_DEF
auto MouseWheelEvent::window_id() const noexcept -> Uint32
{
  return m_event.windowID;
}

CENTURION_DEF
auto MouseWheelEvent::which() const noexcept -> Uint32
{
  return m_event.which;
}

CENTURION_DEF
auto MouseWheelEvent::x_scroll() const noexcept -> Sint32
{
  return m_event.x;
}

CENTURION_DEF
auto MouseWheelEvent::y_scroll() const noexcept -> Sint32
{
  return m_event.y;
}

CENTURION_DEF
auto MouseWheelEvent::direction() const noexcept -> MouseWheelDirection
{
  return static_cast<MouseWheelDirection>(m_event.direction);
}

}  // namespace centurion::event

#endif  // CENTURION_MOUSE_WHEEL_EVENT_SOURCE