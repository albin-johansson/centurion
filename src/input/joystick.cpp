#include "joystick.hpp"

#include "centurion_exception.hpp"

namespace centurion {

joystick::joystick(nn_owner<SDL_Joystick*> sdlJoystick) noexcept
    : basic_joystick{sdlJoystick}
{}

joystick::joystick(int deviceIndex)
{
  if (SDL_NumJoysticks() == 0) {
    throw centurion_exception{"There are no available joysticks!"};
  }

  auto& storage = get_storage();
  storage.reset(SDL_JoystickOpen(deviceIndex));
  if (!storage) {
    throw sdl_error{"Failed to open joystick!"};
  }
}

auto joystick::unique(int deviceIndex) -> uptr
{
  return std::make_unique<joystick>(deviceIndex);
}

auto joystick::unique(nn_owner<SDL_Joystick*> sdlJoystick) -> uptr
{
  return std::make_unique<joystick>(sdlJoystick);
}

auto joystick::shared(int deviceIndex) -> sptr
{
  return std::make_shared<joystick>(deviceIndex);
}

auto joystick::shared(nn_owner<SDL_Joystick*> sdlJoystick) -> sptr
{
  return std::make_shared<joystick>(sdlJoystick);
}

}  // namespace centurion
