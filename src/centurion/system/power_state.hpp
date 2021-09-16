#ifndef CENTURION_POWER_STATE_HEADER
#define CENTURION_POWER_STATE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

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

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied power state.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(power_state::on_battery) == "on_battery"`.
 *
 * \param state the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const power_state state) -> std::string_view
{
  switch (state) {
    case power_state::unknown:
      return "unknown";

    case power_state::on_battery:
      return "on_battery";

    case power_state::no_battery:
      return "no_battery";

    case power_state::charging:
      return "charging";

    case power_state::charged:
      return "charged";

    default:
      throw cen_error{"Did not recognize power state!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a power state enumerator.
 *
 * \param stream the output stream that will be used.
 * \param state the enumerator that will be printed.
 *
 * \see `to_string(power_state)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const power_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of streaming

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
