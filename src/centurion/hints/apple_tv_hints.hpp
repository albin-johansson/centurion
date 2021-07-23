#ifndef CENTURION_APPLE_TV_HINTS_HEADER
#define CENTURION_APPLE_TV_HINTS_HEADER

#include <SDL.h>

#include "../core/czstring.hpp"
#include "../detail/hints_impl.hpp"

/// \addtogroup hints
/// \{

namespace cen::hint::appletv {

struct controller_ui_events final : detail::bool_hint<controller_ui_events>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS;
  }
};

struct remote_allow_rotation final : detail::bool_hint<remote_allow_rotation>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION;
  }
};

}  // namespace cen::hint::appletv

/// \} End of group hints

#endif  // CENTURION_APPLE_TV_HINTS_HEADER