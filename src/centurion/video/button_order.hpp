#ifndef CENTURION_BUTTON_ORDER_HEADER
#define CENTURION_BUTTON_ORDER_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum button_order
 *
 * \brief Provides hints for how the buttons in a message box should be aligned.
 *
 * \note This enum has no effect and shouldn't be used if you're using SDL 2.0.10!
 *
 * \since 4.0.0
 */
enum class button_order : u32
{
#if SDL_VERSION_ATLEAST(2, 0, 12)
  left_to_right = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
  right_to_left = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
#else
  left_to_right,
  right_to_left
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied button order.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(button_order::left_to_right) == "left_to_right"`.
 *
 * \param order the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const button_order order) -> std::string_view
{
  switch (order) {
    case button_order::left_to_right:
      return "left_to_right";

    case button_order::right_to_left:
      return "right_to_left";

    default:
      throw cen_error{"Did not recognize button order!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a button order enumerator.
 *
 * \param stream the output stream that will be used.
 * \param order the enumerator that will be printed.
 *
 * \see `to_string(button_order)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const button_order order) -> std::ostream&
{
  return stream << to_string(order);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_BUTTON_ORDER_HEADER
