#ifndef CENTURION_POWER_STATE_HEADER
#define CENTURION_POWER_STATE_HEADER

#include <SDL.h>

namespace cen {

/// \addtogroup system
/// \{

/**
 * \enum power_state
 *
 * \brief Represents different battery power states.
 *
 * \since 3.0.0
 *
 * \see `SDL_PowerState`
 */
enum class power_state
{
  unknown = SDL_POWERSTATE_UNKNOWN,        ///< The status is unknown.
  on_battery = SDL_POWERSTATE_ON_BATTERY,  ///< Not plugged in and running on battery.
  no_battery = SDL_POWERSTATE_NO_BATTERY,  ///< No battery available.
  charging = SDL_POWERSTATE_CHARGING,      ///< Currently charging the battery.
  charged = SDL_POWERSTATE_CHARGED         ///< Currently plugged in and charged.
};

/// \name Power state comparison operators
/// \{

/**
 * \brief Indicates whether or not two power states values are the same.
 *
 * \param lhs the left-hand side power state value.
 * \param rhs the right-hand side power state value.
 *
 * \return `true` if the power states are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const power_state lhs,
                                        const SDL_PowerState rhs) noexcept -> bool
{
  return static_cast<SDL_PowerState>(lhs) == rhs;
}

/// \copydoc operator==(power_state, SDL_PowerState)
[[nodiscard]] constexpr auto operator==(const SDL_PowerState lhs,
                                        const power_state rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two power states values aren't the same.
 *
 * \param lhs the left-hand side power state value.
 * \param rhs the right-hand side power state value.
 *
 * \return `true` if the power states aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const power_state lhs,
                                        const SDL_PowerState rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(power_state, SDL_PowerState)
[[nodiscard]] constexpr auto operator!=(const SDL_PowerState lhs,
                                        const power_state rhs) noexcept -> bool
{
  return rhs != lhs;
}

/// \} End of power state comparison operators

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_POWER_STATE_HEADER
