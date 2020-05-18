#ifndef CENTURION_MOUSE_MOTION_EVENT_SOURCE
#define CENTURION_MOUSE_MOTION_EVENT_SOURCE

#include "mouse_motion_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent(SDL_MouseMotionEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
Uint32 MouseMotionEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
Uint32 MouseMotionEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
Uint32 MouseMotionEvent::state() const noexcept
{
  return m_event.state;
}

CENTURION_DEF
bool MouseMotionEvent::pressed(MouseButton button) const noexcept
{
  return m_event.state & SDL_BUTTON(static_cast<Uint32>(button));
}

CENTURION_DEF
Sint32 MouseMotionEvent::x() const noexcept
{
  return m_event.x;
}

CENTURION_DEF
Sint32 MouseMotionEvent::y() const noexcept
{
  return m_event.y;
}

CENTURION_DEF
Sint32 MouseMotionEvent::dx() const noexcept
{
  return m_event.xrel;
}

CENTURION_DEF
Sint32 MouseMotionEvent::dy() const noexcept
{
  return m_event.yrel;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_MOUSE_MOTION_EVENT_SOURCE