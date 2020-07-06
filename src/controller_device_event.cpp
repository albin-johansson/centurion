#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
#define CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE

#include "controller_device_event.hpp"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent(
    const SDL_ControllerDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent(
    SDL_ControllerDeviceEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void ControllerDeviceEvent::set_which(Sint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
Sint32 ControllerDeviceEvent::which() const noexcept
{
  return m_event.which;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
