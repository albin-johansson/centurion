#ifndef CENTURION_JOY_DEVICE_EVENT_SOURCE
#define CENTURION_JOY_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
joy_device_event::joy_device_event() noexcept : common_event{}
{}

CENTURION_DEF
joy_device_event::joy_device_event(const SDL_JoyDeviceEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void joy_device_event::set_which(i32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
auto joy_device_event::which() const noexcept -> i32
{
  return m_event.which;
}

}  // namespace centurion

#endif  // CENTURION_JOY_DEVICE_EVENT_SOURCE