#ifndef CENTURION_EMSCRIPTEN_HINTS_HEADER
#define CENTURION_EMSCRIPTEN_HINTS_HEADER

#include <SDL.h>

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

namespace cen::hint::emscripten {

struct keyboard_element final : detail::string_hint<keyboard_element>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct asyncify final : detail::bool_hint<asyncify>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_EMSCRIPTEN_ASYNCIFY;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen::hint::emscripten

/// \} End of group configuration

#endif  // CENTURION_EMSCRIPTEN_HINTS_HEADER