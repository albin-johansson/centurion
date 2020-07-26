#include "event.hpp"

namespace centurion {

controller_device_event::controller_device_event() noexcept : common_event{}
{}

controller_device_event::controller_device_event(
    const SDL_ControllerDeviceEvent& event) noexcept
    : common_event{event}
{}

void controller_device_event::set_which(i32 which) noexcept
{
  m_event.which = which;
}

auto controller_device_event::which() const noexcept -> i32
{
  return m_event.which;
}

}  // namespace centurion
