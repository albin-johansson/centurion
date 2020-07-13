#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
#define CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
controller_device_event::controller_device_event() noexcept : common_event{}
{}

CENTURION_DEF
controller_device_event::controller_device_event(
    const SDL_ControllerDeviceEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void controller_device_event::set_which(i32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
auto controller_device_event::which() const noexcept -> i32
{
  return m_event.which;
}

}  // namespace centurion

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
