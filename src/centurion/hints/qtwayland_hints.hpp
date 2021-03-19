#ifndef CENTURION_QTWAYLAND_HINTS_HEADER
#define CENTURION_QTWAYLAND_HINTS_HEADER

#include <SDL.h>

#include <utility>  // make_pair

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"
#include "enum_hint.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

namespace cen::hint::qtwayland {

struct content_orientation final : enum_hint<content_orientation>
{
  static inline constexpr detail::string_map<value, 5> map{
      std::make_pair(value::primary, "primary"),
      std::make_pair(value::portrait, "portrait"),
      std::make_pair(value::landscape, "landscape"),
      std::make_pair(value::inverted_portrait, "inverted-portrait"),
      std::make_pair(value::inverted_landscape, "inverted-landscape")};

  constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION;
  }
};

struct window_flags final : detail::string_hint<window_flags>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_QTWAYLAND_WINDOW_FLAGS;
  }
};

}  // namespace cen::hint::qtwayland

/// \} End of group configuration

#endif  // CENTURION_QTWAYLAND_HINTS_HEADER