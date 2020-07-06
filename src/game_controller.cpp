#ifndef CENTURION_GAME_CONTROLLER_SOURCE
#define CENTURION_GAME_CONTROLLER_SOURCE

#include "game_controller.hpp"

namespace centurion {

CENTURION_DEF
bool operator==(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept
{
  return static_cast<SDL_GameControllerAxis>(axis) == sdlAxis;
}

CENTURION_DEF
bool operator==(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept
{
  return sdlAxis == static_cast<SDL_GameControllerAxis>(axis);
}

CENTURION_DEF
bool operator!=(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept
{
  return !(axis == sdlAxis);
}

CENTURION_DEF
bool operator!=(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept
{
  return !(sdlAxis == axis);
}

CENTURION_DEF
bool operator==(GameControllerButton button,
                SDL_GameControllerButton sdlButton) noexcept
{
  return static_cast<SDL_GameControllerButton>(button) == sdlButton;
}

CENTURION_DEF
bool operator==(SDL_GameControllerButton sdlButton,
                GameControllerButton button) noexcept
{
  return sdlButton == static_cast<SDL_GameControllerButton>(button);
}

CENTURION_DEF
bool operator!=(GameControllerButton button,
                SDL_GameControllerButton sdlButton) noexcept
{
  return !(button == sdlButton);
}

CENTURION_DEF
bool operator!=(SDL_GameControllerButton sdlButton,
                GameControllerButton button) noexcept
{
  return !(sdlButton == button);
}

}  // namespace centurion

#endif  // CENTURION_GAME_CONTROLLER_SOURCE
