#ifndef CENTURION_INPUT_HPP_
#define CENTURION_INPUT_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"

namespace cen {

/**
 * \defgroup input Input
 *
 * \brief Provides APIs related to different kinds of input.
 */

/// \addtogroup input
/// \{

enum class button_state : uint8 {
  released = SDL_RELEASED,  ///< Corresponds to `SDL_RELEASED`.
  pressed = SDL_PRESSED     ///< Corresponds to `SDL_PRESSED`.
};

/// \name Button state functions
/// \{

[[nodiscard]] constexpr auto to_string(const button_state state) -> std::string_view
{
  switch (state) {
    case button_state::released:
      return "released";

    case button_state::pressed:
      return "pressed";

    default:
      throw exception{"Did not recognize button state!"};
  }
}

inline auto operator<<(std::ostream& stream, const button_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of button state functions

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HPP_