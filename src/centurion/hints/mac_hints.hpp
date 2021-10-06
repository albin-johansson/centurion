#ifndef CENTURION_MAC_HINTS_HEADER
#define CENTURION_MAC_HINTS_HEADER

#include <SDL.h>

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::mac {

/// \addtogroup hints
/// \{

struct fullscreen_spaces final : detail::bool_hint<fullscreen_spaces>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES;
  }
};

struct background_app final : detail::bool_hint<background_app>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_MAC_BACKGROUND_APP;
  }
};

struct ctrl_click_emulate_right_click final : detail::bool_hint<ctrl_click_emulate_right_click>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK;
  }
};

/// \} End of group hints

}  // namespace cen::hint::mac

#endif  // CENTURION_MAC_HINTS_HEADER