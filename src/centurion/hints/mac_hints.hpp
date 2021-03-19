#ifndef CENTURION_MAC_HINTS_HEADER
#define CENTURION_MAC_HINTS_HEADER

#include <SDL.h>

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

namespace cen::hint::mac {

struct fullscreen_spaces final : detail::bool_hint<fullscreen_spaces>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES;
  }
};

struct background_app final : detail::bool_hint<background_app>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MAC_BACKGROUND_APP;
  }
};

struct ctrl_click_emulate_right_click final
    : detail::bool_hint<ctrl_click_emulate_right_click>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK;
  }
};

}  // namespace cen::hint::mac

/// \} End of group configuration

#endif  // CENTURION_MAC_HINTS_HEADER