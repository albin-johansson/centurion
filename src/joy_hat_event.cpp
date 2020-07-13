#ifndef CENTURION_JOY_HAT_EVENT_SOURCE
#define CENTURION_JOY_HAT_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
joy_hat_event::joy_hat_event() noexcept : common_event{}
{}

CENTURION_DEF
joy_hat_event::joy_hat_event(const SDL_JoyHatEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void joy_hat_event::set_hat(u8 hat) noexcept
{
  m_event.hat = hat;
}

CENTURION_DEF
void joy_hat_event::set_position(joy_hat_position value) noexcept
{
  m_event.value = static_cast<u8>(value);
}

CENTURION_DEF
auto joy_hat_event::hat() const noexcept -> u8
{
  return m_event.hat;
}

CENTURION_DEF
auto joy_hat_event::position() const noexcept -> joy_hat_position
{
  return static_cast<joy_hat_position>(m_event.value);
}

}  // namespace centurion

#endif  // CENTURION_JOY_HAT_EVENT_SOURCE