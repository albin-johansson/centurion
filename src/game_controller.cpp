#ifndef CENTURION_GAME_CONTROLLER_SOURCE
#define CENTURION_GAME_CONTROLLER_SOURCE

#include "game_controller.hpp"

namespace centurion {

CENTURION_DEF
auto operator==(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept -> bool
{
  return static_cast<SDL_GameControllerAxis>(axis) == sdlAxis;
}

CENTURION_DEF
auto operator==(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept -> bool
{
  return sdlAxis == static_cast<SDL_GameControllerAxis>(axis);
}

CENTURION_DEF
auto operator!=(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept -> bool
{
  return !(axis == sdlAxis);
}

CENTURION_DEF
auto operator!=(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept -> bool
{
  return !(sdlAxis == axis);
}

CENTURION_DEF
auto operator==(GameControllerButton button,
                SDL_GameControllerButton sdlButton) noexcept -> bool
{
  return static_cast<SDL_GameControllerButton>(button) == sdlButton;
}

CENTURION_DEF
auto operator==(SDL_GameControllerButton sdlButton,
                GameControllerButton button) noexcept -> bool
{
  return sdlButton == static_cast<SDL_GameControllerButton>(button);
}

CENTURION_DEF
auto operator!=(GameControllerButton button,
                SDL_GameControllerButton sdlButton) noexcept -> bool
{
  return !(button == sdlButton);
}

CENTURION_DEF
auto operator!=(SDL_GameControllerButton sdlButton,
                GameControllerButton button) noexcept -> bool
{
  return !(sdlButton == button);
}

}  // namespace centurion

#endif  // CENTURION_GAME_CONTROLLER_SOURCE
