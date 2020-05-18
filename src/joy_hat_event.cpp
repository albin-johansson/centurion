#ifndef CENTURION_JOY_HAT_EVENT_SOURCE
#define CENTURION_JOY_HAT_EVENT_SOURCE

#include "joy_hat_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
JoyHatEvent::JoyHatEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyHatEvent::JoyHatEvent(const SDL_JoyHatEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
JoyHatEvent::JoyHatEvent(SDL_JoyHatEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
Uint8 JoyHatEvent::hat() const noexcept
{
  return m_event.hat;
}

CENTURION_DEF
JoyHatPosition JoyHatEvent::position() const noexcept
{
  return static_cast<JoyHatPosition>(m_event.value);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_JOY_HAT_EVENT_SOURCE