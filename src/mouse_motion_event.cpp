#ifndef CENTURION_MOUSE_MOTION_EVENT_SOURCE
#define CENTURION_MOUSE_MOTION_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
mouse_motion_event::mouse_motion_event() noexcept : common_event{}
{}

CENTURION_DEF
mouse_motion_event::mouse_motion_event(
    const SDL_MouseMotionEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void mouse_motion_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void mouse_motion_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void mouse_motion_event::set_state(u32 state) noexcept
{
  m_event.state = state;
}

CENTURION_DEF
void mouse_motion_event::set_x(i32 x) noexcept
{
  m_event.x = x;
}

CENTURION_DEF
void mouse_motion_event::set_y(i32 y) noexcept
{
  m_event.y = y;
}

CENTURION_DEF
void mouse_motion_event::set_dx(i32 dx) noexcept
{
  m_event.xrel = dx;
}

CENTURION_DEF
void mouse_motion_event::set_dy(i32 dy) noexcept
{
  m_event.yrel = dy;
}

CENTURION_DEF
auto mouse_motion_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto mouse_motion_event::which() const noexcept -> u32
{
  return m_event.which;
}

CENTURION_DEF
auto mouse_motion_event::state() const noexcept -> u32
{
  return m_event.state;
}

CENTURION_DEF
auto mouse_motion_event::pressed(mouse_button button) const noexcept -> bool
{
  return m_event.state & SDL_BUTTON(static_cast<u32>(button));
}

CENTURION_DEF
auto mouse_motion_event::x() const noexcept -> i32
{
  return m_event.x;
}

CENTURION_DEF
auto mouse_motion_event::y() const noexcept -> i32
{
  return m_event.y;
}

CENTURION_DEF
auto mouse_motion_event::dx() const noexcept -> i32
{
  return m_event.xrel;
}

CENTURION_DEF
auto mouse_motion_event::dy() const noexcept -> i32
{
  return m_event.yrel;
}

}  // namespace centurion

#endif  // CENTURION_MOUSE_MOTION_EVENT_SOURCE