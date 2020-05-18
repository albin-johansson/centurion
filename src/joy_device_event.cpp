#ifndef CENTURION_JOY_DEVICE_EVENT_SOURCE
#define CENTURION_JOY_DEVICE_EVENT_SOURCE

#include "joy_device_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
JoyDeviceEvent::JoyDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyDeviceEvent::JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
JoyDeviceEvent::JoyDeviceEvent(SDL_JoyDeviceEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void JoyDeviceEvent::set_which(Sint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
Sint32 JoyDeviceEvent::which() const noexcept
{
  return m_event.which;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_JOY_DEVICE_EVENT_SOURCE