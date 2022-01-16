#ifndef CENTURION_DETAIL_SDL_VERSION_AT_LEAST_HPP_
#define CENTURION_DETAIL_SDL_VERSION_AT_LEAST_HPP_

#include <SDL.h>

#include "../version.hpp"

/// \cond FALSE

namespace cen::detail {

[[nodiscard]] constexpr auto sdl_version_at_least(const int major,
                                                  const int minor,
                                                  const int patch) noexcept -> bool
{
  return SDL_COMPILEDVERSION >= SDL_VERSIONNUM(major, minor, patch);
}

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_SDL_VERSION_AT_LEAST_HPP_
