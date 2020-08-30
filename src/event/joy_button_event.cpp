#include "event.hpp"

namespace centurion {

joy_button_event::joy_button_event() noexcept : common_event{}
{}

joy_button_event::joy_button_event(const SDL_JoyButtonEvent& event) noexcept
    : common_event{event}
{}

void joy_button_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

void joy_button_event::set_button(u8 button) noexcept
{
  m_event.button = button;
}

void joy_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

auto joy_button_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

auto joy_button_event::button() const noexcept -> u8
{
  return m_event.button;
}

auto joy_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

auto joy_button_event::pressed() const noexcept -> bool
{
  return state() == button_state::pressed;
}

auto joy_button_event::released() const noexcept -> bool
{
  return state() == button_state::released;
}

}  // namespace centurion
