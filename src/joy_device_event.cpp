#ifndef CENTURION_JOY_DEVICE_EVENT_SOURCE
#define CENTURION_JOY_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
JoyDeviceEvent::JoyDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyDeviceEvent::JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void JoyDeviceEvent::set_which(Sint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
auto JoyDeviceEvent::which() const noexcept -> Sint32
{
  return m_event.which;
}

}  // namespace centurion::event

#endif  // CENTURION_JOY_DEVICE_EVENT_SOURCE