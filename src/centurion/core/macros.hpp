#ifndef CENTURION_MACROS_HEADER
#define CENTURION_MACROS_HEADER

#include <SDL.h>

/// \addtogroup core
/// \{

#ifndef __clang__

/**
 * \def CENTURION_HAS_STD_MEMORY_RESOURCE
 *
 * \brief This macro is defined if the `memory_resource` header is available.
 *
 * \note This is a very rough check, that assumes that as long as we are not
 * using Clang, we are fine.
 *
 * \todo C++20: Use the feature test macro for this instead.
 *
 * \since 5.3.0
 */
#define CENTURION_HAS_STD_MEMORY_RESOURCE

#endif  // __clang__

/**
 * \def CENTURION_SDL_VERSION_IS
 *
 * \brief This macro is meant to be used when conditionally including code for a
 * specific version of SDL. It is useful for applying workarounds.
 *
 * \since 5.3.0
 */
#define CENTURION_SDL_VERSION_IS(x, y, z)                      \
  ((SDL_MAJOR_VERSION == (x)) && (SDL_MINOR_VERSION == (y)) && \
   (SDL_PATCHLEVEL == (z)))

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

// Workaround for this enum being completely anonymous in SDL 2.0.10. We include
// this here because multiple files (key_code.hpp and scan_code.hpp) depend on
// this definition.
using SDL_KeyCode = decltype(SDLK_UNKNOWN);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

/// \} End of group core

#endif  // CENTURION_MACROS_HEADER
