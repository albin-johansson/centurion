#include "joystick_handle.hpp"

#include "joystick.hpp"

namespace cen {

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

auto joystick_from_instance_id(SDL_JoystickID id) noexcept -> joystick_handle
{
  return joystick_handle{SDL_JoystickFromInstanceID(id)};
}

auto joystick_from_player_index(int playerIndex) noexcept -> joystick_handle
{
  return joystick_handle{SDL_JoystickFromPlayerIndex(playerIndex)};
}

}  // namespace cen
