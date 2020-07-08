#ifndef CENTURION_MOUSE_MOTION_EVENT_SOURCE
#define CENTURION_MOUSE_MOTION_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void MouseMotionEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void MouseMotionEvent::set_which(Uint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void MouseMotionEvent::set_state(Uint32 state) noexcept
{
  m_event.state = state;
}

CENTURION_DEF
void MouseMotionEvent::set_x(Sint32 x) noexcept
{
  m_event.x = x;
}

CENTURION_DEF
void MouseMotionEvent::set_y(Sint32 y) noexcept
{
  m_event.y = y;
}

CENTURION_DEF
void MouseMotionEvent::set_dx(Sint32 dx) noexcept
{
  m_event.xrel = dx;
}

CENTURION_DEF
void MouseMotionEvent::set_dy(Sint32 dy) noexcept
{
  m_event.yrel = dy;
}

CENTURION_DEF
auto MouseMotionEvent::window_id() const noexcept -> Uint32
{
  return m_event.windowID;
}

CENTURION_DEF
auto MouseMotionEvent::which() const noexcept -> Uint32
{
  return m_event.which;
}

CENTURION_DEF
auto MouseMotionEvent::state() const noexcept -> Uint32
{
  return m_event.state;
}

CENTURION_DEF
auto MouseMotionEvent::pressed(MouseButton button) const noexcept -> bool
{
  return m_event.state & SDL_BUTTON(static_cast<Uint32>(button));
}

CENTURION_DEF
auto MouseMotionEvent::x() const noexcept -> Sint32
{
  return m_event.x;
}

CENTURION_DEF
auto MouseMotionEvent::y() const noexcept -> Sint32
{
  return m_event.y;
}

CENTURION_DEF
auto MouseMotionEvent::dx() const noexcept -> Sint32
{
  return m_event.xrel;
}

CENTURION_DEF
auto MouseMotionEvent::dy() const noexcept -> Sint32
{
  return m_event.yrel;
}

}  // namespace centurion::event

#endif  // CENTURION_MOUSE_MOTION_EVENT_SOURCE