#include "event.hpp"

namespace centurion {

mouse_button_event::mouse_button_event() noexcept : common_event{}
{}

mouse_button_event::mouse_button_event(
    const SDL_MouseButtonEvent& event) noexcept
    : common_event{event}
{}

void mouse_button_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

void mouse_button_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

void mouse_button_event::set_button(mouse_button button) noexcept
{
  m_event.button = static_cast<u8>(button);
}

void mouse_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

void mouse_button_event::set_clicks(u8 clicks) noexcept
{
  m_event.clicks = clicks;
}

void mouse_button_event::set_x(i32 x) noexcept
{
  m_event.x = x;
}

void mouse_button_event::set_y(i32 y) noexcept
{
  m_event.y = y;
}

auto mouse_button_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

auto mouse_button_event::which() const noexcept -> u32
{
  return m_event.which;
}

auto mouse_button_event::button() const noexcept -> mouse_button
{
  return static_cast<mouse_button>(m_event.button);
}

auto mouse_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

auto mouse_button_event::clicks() const noexcept -> u8
{
  return m_event.clicks;
}

auto mouse_button_event::x() const noexcept -> i32
{
  return m_event.x;
}

auto mouse_button_event::y() const noexcept -> i32
{
  return m_event.y;
}

}  // namespace centurion
