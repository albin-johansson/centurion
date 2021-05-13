#ifndef CENTURION_MOUSE_BUTTON_HEADER
#define CENTURION_MOUSE_BUTTON_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum mouse_button
 *
 * \brief Provides values that represent various mouse buttons.
 *
 * \since 3.1.0
 */
enum class mouse_button : u8
{
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_MOUSE_BUTTON_HEADER