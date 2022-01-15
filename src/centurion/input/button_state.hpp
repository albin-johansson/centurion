#ifndef CENTURION_INPUT_BUTTON_STATE_HPP_
#define CENTURION_INPUT_BUTTON_STATE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class ButtonState : uint8 {
  Released = SDL_RELEASED,  ///< Corresponds to `SDL_RELEASED`.
  Pressed = SDL_PRESSED     ///< Corresponds to `SDL_PRESSED`.
};

[[nodiscard]] constexpr auto ToString(const ButtonState state) -> std::string_view
{
  switch (state) {
    case ButtonState::Released:
      return "Released";

    case ButtonState::Pressed:
      return "Pressed";

    default:
      throw exception{"Did not recognize button state!"};
  }
}

inline auto operator<<(std::ostream& stream, const ButtonState state) -> std::ostream&
{
  return stream << ToString(state);
}

}  // namespace cen

#endif  // CENTURION_INPUT_BUTTON_STATE_HPP_