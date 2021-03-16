#ifndef CENTURION_MOUSE_BUTTON_HEADER
#define CENTURION_MOUSE_BUTTON_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum mouse_button
 *
 * \brief Provides values that represent various mouse buttons.
 *
 * \since 3.1.0
 *
 * \headerfile mouse_button.hpp
 */
enum class mouse_button
{
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

/// \}

}  // namespace cen

#endif  // CENTURION_MOUSE_BUTTON_HEADER