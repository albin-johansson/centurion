#ifndef CENTURION_FLASH_OP_HEADER
#define CENTURION_FLASH_OP_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 16)

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum flash_op
 *
 * \brief Represents different window flash operations.
 *
 * \see `basic_window::flash()`
 * \see `to_string(flash_op)`
 *
 * \since 6.2.0
 */
enum class flash_op
{
  cancel = SDL_FLASH_CANCEL,               ///< Cancel any current flashing.
  briefly = SDL_FLASH_BRIEFLY,             ///< Briefly flash the window.
  until_focused = SDL_FLASH_UNTIL_FOCUSED  ///< Flash the window until it's focused.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied window flash operation.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(flash_op::briefly) == "briefly"`.
 *
 * \param op the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const flash_op op) -> std::string_view
{
  switch (op) {
    case flash_op::cancel:
      return "cancel";

    case flash_op::briefly:
      return "briefly";

    case flash_op::until_focused:
      return "until_focused";

    default:
      throw cen_error{"Did not recognize window flash operation!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a window flash operation enumerator.
 *
 * \param stream the output stream that will be used.
 * \param op the enumerator that will be printed.
 *
 * \see `to_string(flash_op)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const flash_op op) -> std::ostream&
{
  return stream << to_string(op);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#endif  // CENTURION_FLASH_OP_HEADER
