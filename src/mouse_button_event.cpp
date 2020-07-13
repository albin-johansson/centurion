#ifndef CENTURION_MOUSE_BUTTON_EVENT_SOURCE
#define CENTURION_MOUSE_BUTTON_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
mouse_button_event::mouse_button_event() noexcept : common_event{}
{}

CENTURION_DEF
mouse_button_event::mouse_button_event(
    const SDL_MouseButtonEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void mouse_button_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void mouse_button_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void mouse_button_event::set_button(mouse_button button) noexcept
{
  m_event.button = static_cast<u8>(button);
}

CENTURION_DEF
void mouse_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
void mouse_button_event::set_clicks(u8 clicks) noexcept
{
  m_event.clicks = clicks;
}

CENTURION_DEF
void mouse_button_event::set_x(i32 x) noexcept
{
  m_event.x = x;
}

CENTURION_DEF
void mouse_button_event::set_y(i32 y) noexcept
{
  m_event.y = y;
}

CENTURION_DEF
auto mouse_button_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto mouse_button_event::which() const noexcept -> u32
{
  return m_event.which;
}

CENTURION_DEF
auto mouse_button_event::button() const noexcept -> mouse_button
{
  return static_cast<mouse_button>(m_event.button);
}

CENTURION_DEF
auto mouse_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

CENTURION_DEF
auto mouse_button_event::clicks() const noexcept -> u8
{
  return m_event.clicks;
}

CENTURION_DEF
auto mouse_button_event::x() const noexcept -> i32
{
  return m_event.x;
}

CENTURION_DEF
auto mouse_button_event::y() const noexcept -> i32
{
  return m_event.y;
}

}  // namespace centurion

#endif  // CENTURION_MOUSE_BUTTON_EVENT_SOURCE