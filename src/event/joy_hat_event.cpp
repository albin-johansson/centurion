#include "event.hpp"

namespace centurion {

joy_hat_event::joy_hat_event() noexcept : common_event{}
{}

joy_hat_event::joy_hat_event(const SDL_JoyHatEvent& event) noexcept
    : common_event{event}
{}

void joy_hat_event::set_hat(u8 hat) noexcept
{
  m_event.hat = hat;
}

void joy_hat_event::set_position(joy_hat_position value) noexcept
{
  m_event.value = static_cast<u8>(value);
}

auto joy_hat_event::hat() const noexcept -> u8
{
  return m_event.hat;
}

auto joy_hat_event::position() const noexcept -> joy_hat_position
{
  return static_cast<joy_hat_position>(m_event.value);
}

}  // namespace centurion
