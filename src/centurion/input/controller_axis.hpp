#ifndef CENTURION_CONTROLLER_AXIS_HEADER
#define CENTURION_CONTROLLER_AXIS_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum controller_axis
 *
 * \brief Represents different game controller axes.
 *
 * \see `SDL_GameControllerAxis`
 *
 * \since 4.0.0
 */
enum class controller_axis
{
  invalid = SDL_CONTROLLER_AXIS_INVALID,
  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max = SDL_CONTROLLER_AXIS_MAX
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied controller axis.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(controller_axis::right_x) == "right_x"`.
 *
 * \param axis the controller axis that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const controller_axis axis) -> std::string_view
{
  switch (axis) {
    case controller_axis::invalid:
      return "invalid";

    case controller_axis::left_x:
      return "left_x";

    case controller_axis::left_y:
      return "left_y";

    case controller_axis::right_x:
      return "right_x";

    case controller_axis::right_y:
      return "right_y";

    case controller_axis::trigger_left:
      return "trigger_left";

    case controller_axis::trigger_right:
      return "trigger_right";

    case controller_axis::max:
      return "max";

    default:
      throw cen_error{"Did not recognize controller axis!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a controller axis enumerator.
 *
 * \param stream the output stream that will be used.
 * \param axis the controller axis that will be printed.
 *
 * \see `to_string(controller_axis)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const controller_axis axis) -> std::ostream&
{
  return stream << to_string(axis);
}

/// \} End of streaming

/// \name Controller axis comparison operators
/// \{

/**
 * \brief Indicates whether or not two game controller axis values are the same.
 *
 * \param lhs the left-hand-side game controller axis value.
 * \param rhs the right-hand-side game controller axis value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const controller_axis lhs,
                                        const SDL_GameControllerAxis rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerAxis>(lhs) == rhs;
}

/// \copydoc operator==(controller_axis, SDL_GameControllerAxis)
[[nodiscard]] constexpr auto operator==(const SDL_GameControllerAxis lhs,
                                        const controller_axis rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two game controller axis values aren't the
 * same.
 *
 * \param lhs the left-hand-side game controller axis value.
 * \param rhs the right-hand-side game controller axis value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const controller_axis lhs,
                                        const SDL_GameControllerAxis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(controller_axis, SDL_GameControllerAxis)
[[nodiscard]] constexpr auto operator!=(const SDL_GameControllerAxis lhs,
                                        const controller_axis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of controller axis comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_CONTROLLER_AXIS_HEADER
