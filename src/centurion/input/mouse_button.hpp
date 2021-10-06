#ifndef CENTURION_MOUSE_BUTTON_HEADER
#define CENTURION_MOUSE_BUTTON_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum mouse_button
 *
 * \brief Provides values that represent various mouse buttons.
 *
 * \since 3.1.0
 */
enum class mouse_button : u8
{
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied mouse button.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(mouse_button::middle) == "middle"`.
 *
 * \param button the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const mouse_button button) -> std::string_view
{
  switch (button) {
    case mouse_button::left:
      return "left";

    case mouse_button::middle:
      return "middle";

    case mouse_button::right:
      return "right";

    case mouse_button::x1:
      return "x1";

    case mouse_button::x2:
      return "x2";

    default:
      throw cen_error{"Did not recognize mouse button!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a mouse button enumerator.
 *
 * \param stream the output stream that will be used.
 * \param button the enumerator that will be printed.
 *
 * \see `to_string(mouse_button)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const mouse_button button) -> std::ostream&
{
  return stream << to_string(button);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_MOUSE_BUTTON_HEADER