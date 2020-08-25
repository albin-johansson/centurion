#include "event.hpp"

namespace centurion {

controller_button_event::controller_button_event() noexcept : common_event{}
{}

controller_button_event::controller_button_event(
    const SDL_ControllerButtonEvent& event) noexcept
    : common_event{event}
{}

void controller_button_event::set_button(controller_button button) noexcept
{
  m_event.button = static_cast<u8>(button);
}

void controller_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

void controller_button_event::set_which(SDL_JoystickID id) noexcept
{
  m_event.which = id;
}

auto controller_button_event::button() const noexcept -> controller_button
{
  return static_cast<controller_button>(m_event.button);
}

auto controller_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

auto controller_button_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

}  // namespace centurion
