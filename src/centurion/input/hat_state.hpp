#ifndef CENTURION_HAT_STATE_HEADER
#define CENTURION_HAT_STATE_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum hat_state
 *
 * \brief Represents the various states of a joystick "hat".
 *
 * \since 4.2.0
 */
enum class hat_state : u8
{
  centered = SDL_HAT_CENTERED,     ///< The hat is centered.
  up = SDL_HAT_UP,                 ///< The hat is directed "north".
  right = SDL_HAT_RIGHT,           ///< The hat is directed "east".
  down = SDL_HAT_DOWN,             ///< The hat is directed "south".
  left = SDL_HAT_LEFT,             ///< The hat is directed "west".
  right_up = SDL_HAT_RIGHTUP,      ///< The hat is directed "north-east".
  right_down = SDL_HAT_RIGHTDOWN,  ///< The hat is directed "south-east".
  left_up = SDL_HAT_LEFTUP,        ///< The hat is directed "north-west".
  left_down = SDL_HAT_LEFTDOWN,    ///< The hat is directed "south-west".
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAT_STATE_HEADER
