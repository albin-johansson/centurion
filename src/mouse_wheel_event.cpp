#ifndef CENTURION_MOUSE_WHEEL_EVENT_SOURCE
#define CENTURION_MOUSE_WHEEL_EVENT_SOURCE

#include <utility>

#include "event.hpp"

namespace centurion {
namespace event {

CENTURION_DEF
bool operator==(MouseWheelDirection lhs, SDL_MouseWheelDirection rhs) noexcept
{
  return lhs == static_cast<MouseWheelDirection>(rhs);
}

CENTURION_DEF
bool operator==(SDL_MouseWheelDirection lhs, MouseWheelDirection rhs) noexcept
{
  return static_cast<MouseWheelDirection>(lhs) == rhs;
}

CENTURION_DEF
bool operator!=(MouseWheelDirection lhs, SDL_MouseWheelDirection rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_MouseWheelDirection lhs, MouseWheelDirection rhs) noexcept
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
MouseWheelEvent::MouseWheelEvent(SDL_MouseWheelEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
Uint32 MouseWheelEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
Uint32 MouseWheelEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
Sint32 MouseWheelEvent::x_scroll() const noexcept
{
  return m_event.x;
}

CENTURION_DEF
Sint32 MouseWheelEvent::y_scroll() const noexcept
{
  return m_event.y;
}

CENTURION_DEF
MouseWheelDirection MouseWheelEvent::direction() const noexcept
{
  return static_cast<MouseWheelDirection>(m_event.direction);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_MOUSE_WHEEL_EVENT_SOURCE