#ifndef CENTURION_APPLE_TV_HINTS_HEADER
#define CENTURION_APPLE_TV_HINTS_HEADER

#include <SDL.h>

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::appletv {

/// \addtogroup hints
/// \{

struct controller_ui_events final : detail::bool_hint<controller_ui_events>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS;
  }
};

struct remote_allow_rotation final : detail::bool_hint<remote_allow_rotation>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION;
  }
};

/// \} End of group hints

}  // namespace cen::hint::appletv

#endif  // CENTURION_APPLE_TV_HINTS_HEADER