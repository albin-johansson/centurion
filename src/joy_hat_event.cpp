#ifndef CENTURION_JOY_HAT_EVENT_SOURCE
#define CENTURION_JOY_HAT_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
JoyHatEvent::JoyHatEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyHatEvent::JoyHatEvent(const SDL_JoyHatEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void JoyHatEvent::set_hat(Uint8 hat) noexcept
{
  m_event.hat = hat;
}

CENTURION_DEF
void JoyHatEvent::set_position(JoyHatPosition value) noexcept
{
  m_event.value = static_cast<Uint8>(value);
}

CENTURION_DEF
auto JoyHatEvent::hat() const noexcept -> Uint8
{
  return m_event.hat;
}

CENTURION_DEF
auto JoyHatEvent::position() const noexcept -> JoyHatPosition
{
  return static_cast<JoyHatPosition>(m_event.value);
}

}  // namespace centurion::event

#endif  // CENTURION_JOY_HAT_EVENT_SOURCE