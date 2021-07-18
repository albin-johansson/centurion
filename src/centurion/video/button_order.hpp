#ifndef CENTURION_BUTTON_ORDER_HEADER
#define CENTURION_BUTTON_ORDER_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum button_order
 *
 * \brief Provides hints for how the buttons in a message box should be aligned.
 *
 * \note This enum has no effect and shouldn't be used if you're using SDL 2.0.10!
 *
 * \since 4.0.0
 */
enum class button_order : u32
{
#if SDL_VERSION_ATLEAST(2, 0, 12)
  left_to_right = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
  right_to_left = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
#else
  left_to_right,
  right_to_left
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_BUTTON_ORDER_HEADER
