#ifndef CENTURION_SDL_LOG_CATEGORY_WORKAROUND_HEADER
#define CENTURION_SDL_LOG_CATEGORY_WORKAROUND_HEADER

#include <SDL.h>

#include "version.hpp"

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

// Workaround for this enum being completely anonymous in SDL 2.0.10
using SDL_LogCategory = decltype(SDL_LOG_CATEGORY_APPLICATION);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

#endif  // CENTURION_SDL_LOG_CATEGORY_WORKAROUND_HEADER
