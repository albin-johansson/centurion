#ifndef CENTURION_EMSCRIPTEN_HINTS_HEADER
#define CENTURION_EMSCRIPTEN_HINTS_HEADER

#include <SDL.h>

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::emscripten {

/// \addtogroup hints
/// \{

struct keyboard_element final : detail::string_hint<keyboard_element>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct asyncify final : detail::bool_hint<asyncify>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_EMSCRIPTEN_ASYNCIFY;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \} End of group hints

}  // namespace cen::hint::emscripten

#endif  // CENTURION_EMSCRIPTEN_HINTS_HEADER