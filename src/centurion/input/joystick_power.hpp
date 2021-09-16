#ifndef CENTURION_JOYSTICK_POWER_HEADER
#define CENTURION_JOYSTICK_POWER_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum joystick_power
 *
 * \brief Represents different power states of a joystick.
 *
 * \since 4.2.0
 */
enum class joystick_power
{
  unknown = SDL_JOYSTICK_POWER_UNKNOWN,  ///< Unknown power level.
  empty = SDL_JOYSTICK_POWER_EMPTY,      ///< Indicates <= 5% power.
  low = SDL_JOYSTICK_POWER_LOW,          ///< Indicates <= 20% power.
  medium = SDL_JOYSTICK_POWER_MEDIUM,    ///< Indicates <= 70% power.
  full = SDL_JOYSTICK_POWER_FULL,        ///< Indicates <= 100% power.
  wired = SDL_JOYSTICK_POWER_WIRED,      ///< No need to worry about power.
  max = SDL_JOYSTICK_POWER_MAX
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied joystick power.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(joystick_power::medium) == "medium"`.
 *
 * \param power the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const joystick_power power) -> std::string_view
{
  switch (power) {
    case joystick_power::unknown:
      return "unknown";

    case joystick_power::empty:
      return "empty";

    case joystick_power::low:
      return "low";

    case joystick_power::medium:
      return "medium";

    case joystick_power::full:
      return "full";

    case joystick_power::wired:
      return "wired";

    case joystick_power::max:
      return "max";

    default:
      throw cen_error{"Did not recognize joystick power!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a joystick power enumerator.
 *
 * \param stream the output stream that will be used.
 * \param power the enumerator that will be printed.
 *
 * \see `to_string(joystick_power)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const joystick_power power) -> std::ostream&
{
  return stream << to_string(power);
}

/// \} End of streaming

/// \name Joystick power comparison operators
/// \{

/**
 * \brief Indicates whether or not two joystick power values are the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const joystick_power lhs,
                                        const SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return static_cast<SDL_JoystickPowerLevel>(lhs) == rhs;
}

/**
 * \brief Indicates whether or not two joystick power values are the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const SDL_JoystickPowerLevel lhs,
                                        const joystick_power rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two joystick power values aren't the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const joystick_power lhs,
                                        const SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two joystick power values aren't the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const SDL_JoystickPowerLevel lhs,
                                        const joystick_power rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of joystick power comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_JOYSTICK_POWER_HEADER
