#include "event.hpp"

namespace centurion {

joy_device_event::joy_device_event() noexcept : common_event{}
{}

joy_device_event::joy_device_event(const SDL_JoyDeviceEvent& event) noexcept
    : common_event{event}
{}

void joy_device_event::set_which(i32 which) noexcept
{
  m_event.which = which;
}

auto joy_device_event::which() const noexcept -> i32
{
  return m_event.which;
}

}  // namespace centurion
