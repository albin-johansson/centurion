#ifndef CENTURION_RASPBERRY_PI_HINTS_HEADER
#define CENTURION_RASPBERRY_PI_HINTS_HEADER

#include <SDL.h>

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

namespace cen::hint::raspberrypi {

struct video_layer final : detail::int_hint<video_layer>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_RPI_VIDEO_LAYER;
  }
};

/// \} End of group configuration

}  // namespace cen::hint::raspberrypi

#endif  // CENTURION_RASPBERRY_PI_HINTS_HEADER
