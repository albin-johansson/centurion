#ifndef CENTURION_JOYSTICK_POWER_HEADER
#define CENTURION_JOYSTICK_POWER_HEADER

#include <SDL.h>

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
  max = SDL_JOYSTICK_POWER_MAX           ///< Maximum power level.
};

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
