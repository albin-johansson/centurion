#include "event.hpp"

namespace cen {

joy_axis_event::joy_axis_event() noexcept : common_event{}
{}

joy_axis_event::joy_axis_event(const SDL_JoyAxisEvent& event) noexcept
    : common_event{event}
{}

void joy_axis_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

void joy_axis_event::set_axis(u8 axis) noexcept
{
  m_event.axis = axis;
}

void joy_axis_event::set_value(i16 value) noexcept
{
  m_event.value = value;
}

auto joy_axis_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

auto joy_axis_event::axis() const noexcept -> u8
{
  return m_event.axis;
}

auto joy_axis_event::value() const noexcept -> i16
{
  return m_event.value;
}

}  // namespace cen
