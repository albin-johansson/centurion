#include "joystick_handle.hpp"

#include "joystick.hpp"

namespace centurion {

joystick_handle::joystick_handle(SDL_Joystick* sdlJoystick) noexcept
    : basic_joystick{sdlJoystick}
{}

joystick_handle::joystick_handle(joystick& joystick) noexcept
    : basic_joystick{joystick.get()}
{}

joystick_handle::operator bool() const noexcept
{
  return get_storage();
}

}  // namespace centurion
