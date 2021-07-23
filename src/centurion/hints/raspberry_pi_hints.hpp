#ifndef CENTURION_RASPBERRY_PI_HINTS_HEADER
#define CENTURION_RASPBERRY_PI_HINTS_HEADER

#include <SDL.h>

#include "../core/czstring.hpp"
#include "../detail/hints_impl.hpp"

/// \addtogroup hints
/// \{

namespace cen::hint::raspberrypi {

struct video_layer final : detail::int_hint<video_layer>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_RPI_VIDEO_LAYER;
  }
};

}  // namespace cen::hint::raspberrypi

/// \} End of group hints

#endif  // CENTURION_RASPBERRY_PI_HINTS_HEADER
