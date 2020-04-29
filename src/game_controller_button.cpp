#ifndef CENTURION_GAME_CONTROLLER_BUTTON_SOURCE
#define CENTURION_GAME_CONTROLLER_BUTTON_SOURCE

#include "game_controller_button.h"

namespace centurion {
namespace event {

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

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_GAME_CONTROLLER_BUTTON_SOURCE
