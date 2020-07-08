#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
#define CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent(
    const SDL_ControllerDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void ControllerDeviceEvent::set_which(i32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
auto ControllerDeviceEvent::which() const noexcept -> i32
{
  return m_event.which;
}

}  // namespace centurion::event

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
