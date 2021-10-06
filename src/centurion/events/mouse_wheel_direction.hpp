#ifndef CENTURION_MOUSE_WHEEL_DIRECTION_HEADER
#define CENTURION_MOUSE_WHEEL_DIRECTION_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum mouse_wheel_direction
 *
 * \brief Represents mouse wheel directions.
 *
 * \see `SDL_MouseWheelDirection`
 * \see `mouse_wheel_direction_count()`
 *
 * \since 4.0.0
 */
enum class mouse_wheel_direction : u32
{
  normal = SDL_MOUSEWHEEL_NORMAL,   ///< The scroll direction is normal
  flipped = SDL_MOUSEWHEEL_FLIPPED  ///< The scroll direction is flipped natural
};

/**
 * \brief Returns the number of enumerators for the `mouse_wheel_direction` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto mouse_wheel_direction_count() noexcept -> int
{
  return 2;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied mouse wheel direction.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(mouse_wheel_direction::normal) == "normal"`.
 *
 * \param dir the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const mouse_wheel_direction dir) -> std::string_view
{
  switch (dir) {
    case mouse_wheel_direction::normal:
      return "normal";

    case mouse_wheel_direction::flipped:
      return "flipped";

    default:
      throw cen_error{"Did not recognize mouse wheel direction!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of an mouse wheel direction enumerator.
 *
 * \param stream the output stream that will be used.
 * \param dir the enumerator that will be printed.
 *
 * \see `to_string(mouse_wheel_direction)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const mouse_wheel_direction dir) -> std::ostream&
{
  return stream << to_string(dir);
}

/// \} End of streaming

/// \name Mouse wheel direction comparison operators
/// \{

/**
 * \brief Indicates whether or not two mouse wheel direction values are equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values are equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const mouse_wheel_direction lhs,
                                        const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return lhs == static_cast<mouse_wheel_direction>(rhs);
}

/// \copydoc operator==(mouse_wheel_direction, SDL_MouseWheelDirection)
[[nodiscard]] constexpr auto operator==(const SDL_MouseWheelDirection lhs,
                                        const mouse_wheel_direction rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two mouse wheel direction values aren't
 * equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values aren't equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const mouse_wheel_direction lhs,
                                        const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(mouse_wheel_direction, SDL_MouseWheelDirection)
[[nodiscard]] constexpr auto operator!=(const SDL_MouseWheelDirection lhs,
                                        const mouse_wheel_direction rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of mouse wheel direction comparison operators

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_MOUSE_WHEEL_DIRECTION_HEADER
