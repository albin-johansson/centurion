#ifndef CENTURION_BUTTON_STATE_HEADER
#define CENTURION_BUTTON_STATE_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/**
 * \enum button_state
 *
 * \ingroup input
 *
 * \brief Represents the two possible states for a button.
 *
 * \details Corresponds to the `SDL_RELEASED` and `SDL_PRESSED` macros.
 *
 * \since 3.1.0
 */
enum class button_state : u8
{
  released = SDL_RELEASED,  ///< Corresponds to `SDL_RELEASED`.
  pressed = SDL_PRESSED     ///< Corresponds to `SDL_PRESSED`.
};

}  // namespace cen

#endif  // CENTURION_BUTTON_STATE_HEADER