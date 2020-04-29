#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
#define CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE

#include "controller_device_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent() noexcept : BaseEvent{}
{}

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent(
    const SDL_ControllerDeviceEvent& event) noexcept
    : BaseEvent{event}
{}

CENTURION_DEF
ControllerDeviceEvent::ControllerDeviceEvent(
    SDL_ControllerDeviceEvent&& event) noexcept
    : BaseEvent{std::move(event)}
{}

CENTURION_DEF
void ControllerDeviceEvent::set_type(ControllerDeviceEventType type) noexcept
{
  m_event.type = static_cast<Uint32>(type);
}

CENTURION_DEF
void ControllerDeviceEvent::set_which(Sint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
ControllerDeviceEventType ControllerDeviceEvent::type() const noexcept
{
  return static_cast<ControllerDeviceEventType>(m_event.type);
}

CENTURION_DEF
Sint32 ControllerDeviceEvent::which() const noexcept
{
  return m_event.which;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_SOURCE
