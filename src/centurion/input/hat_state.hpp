#ifndef CENTURION_HAT_STATE_HEADER
#define CENTURION_HAT_STATE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum hat_state
 *
 * \brief Represents the various states of a joystick "hat".
 *
 * \since 4.2.0
 */
enum class hat_state : u8
{
  centered = SDL_HAT_CENTERED,     ///< The hat is centered.
  up = SDL_HAT_UP,                 ///< The hat is directed "north".
  right = SDL_HAT_RIGHT,           ///< The hat is directed "east".
  down = SDL_HAT_DOWN,             ///< The hat is directed "south".
  left = SDL_HAT_LEFT,             ///< The hat is directed "west".
  right_up = SDL_HAT_RIGHTUP,      ///< The hat is directed "north-east".
  right_down = SDL_HAT_RIGHTDOWN,  ///< The hat is directed "south-east".
  left_up = SDL_HAT_LEFTUP,        ///< The hat is directed "north-west".
  left_down = SDL_HAT_LEFTDOWN,    ///< The hat is directed "south-west".
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied hat state.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(hat_state::down) == "down"`.
 *
 * \param state the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const hat_state state) -> std::string_view
{
  switch (state) {
    case hat_state::centered:
      return "centered";

    case hat_state::up:
      return "up";

    case hat_state::right:
      return "right";

    case hat_state::down:
      return "down";

    case hat_state::left:
      return "left";

    case hat_state::right_up:
      return "right_up";

    case hat_state::right_down:
      return "right_down";

    case hat_state::left_up:
      return "left_up";

    case hat_state::left_down:
      return "left_down";

    default:
      throw cen_error{"Did not recognize hat state!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a hat state enumerator.
 *
 * \param stream the output stream that will be used.
 * \param state the enumerator that will be printed.
 *
 * \see `to_string(hat_state)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const hat_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_HAT_STATE_HEADER
