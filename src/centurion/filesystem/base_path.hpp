#ifndef CENTURION_BASE_PATH_HEADER
#define CENTURION_BASE_PATH_HEADER

#include <SDL.h>

#include "../core/sdl_string.hpp"

namespace cen {

/// \addtogroup filesystem
/// \{

/**
 * \brief Returns the "base" path associated with the application.
 *
 * \details The returned string represents the path to the directory from which
 * application was run from, and will end with a path separator (e.g. "\\" or "/").
 *
 * \note This might be an expensive operation, so it's recommended to only call this
 * function once and cache the returned path.
 *
 * \return the base path of the application; a null string is returned if the path cannot
 * be obtained.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto base_path() -> sdl_string
{
  return sdl_string{SDL_GetBasePath()};
}

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_BASE_PATH_HEADER
