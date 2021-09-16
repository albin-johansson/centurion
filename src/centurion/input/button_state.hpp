#ifndef CENTURION_BUTTON_STATE_HEADER
#define CENTURION_BUTTON_STATE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum button_state
 *
 * \ingroup input
 *
 * \brief Represents the two possible states for a button.
 *
 * \details Corresponds to the `SDL_RELEASED` and `SDL_PRESSED` macros.
 *
 * \since 3.1.0
 */
enum class button_state : u8
{
  released = SDL_RELEASED,  ///< Corresponds to `SDL_RELEASED`.
  pressed = SDL_PRESSED     ///< Corresponds to `SDL_PRESSED`.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied button state.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(button_state::released) == "released"`.
 *
 * \param state the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const button_state state) -> std::string_view
{
  switch (state) {
    case button_state::released:
      return "released";

    case button_state::pressed:
      return "pressed";

    default:
      throw cen_error{"Did not recognize button state!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a button state enumerator.
 *
 * \param stream the output stream that will be used.
 * \param state the enumerator that will be printed.
 *
 * \see `to_string(button_state)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const button_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_BUTTON_STATE_HEADER