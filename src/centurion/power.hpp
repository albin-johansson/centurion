#ifndef CENTURION_POWER_HPP_
#define CENTURION_POWER_HPP_

#include <SDL.h>

#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"

namespace cen {

/**
 * \ingroup system
 * \defgroup power Power
 *
 * \brief Provides information about the system power resources.
 */

/// \addtogroup power
/// \{

/**
 * \brief Represents different power states of batteries.
 */
enum class power_state
{
  unknown = SDL_POWERSTATE_UNKNOWN,        ///< The status is unknown.
  on_battery = SDL_POWERSTATE_ON_BATTERY,  ///< Not plugged in and running on battery.
  no_battery = SDL_POWERSTATE_NO_BATTERY,  ///< No battery available.
  charging = SDL_POWERSTATE_CHARGING,      ///< Charging the battery.
  charged = SDL_POWERSTATE_CHARGED         ///< Plugged in and charged.
};

/// \name Power state functions
/// \{

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
      throw exception{"Did not recognize power state!"};
  }
}

inline auto operator<<(std::ostream& stream, const power_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of power state functions

/**
 * \brief Returns the seconds of remaining battery life.
 *
 * \return seconds of remaining battery life; an empty optional is returned if the value cannot
 * be obtained.
 */
[[nodiscard]] inline auto battery_seconds() -> std::optional<seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the minutes of remaining battery life.
 *
 * \return minutes of remaining battery life; an empty optional is returned if the value cannot
 * be obtained.
 */
[[nodiscard]] inline auto battery_minutes() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = battery_seconds()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the percentage of remaining battery life.
 *
 * \return percentage of remaining battery life, in the range [0, 100]; an empty
 * optional is returned if the battery percentage isn't available.
 */
[[nodiscard]] inline auto battery_percentage() noexcept -> std::optional<int>
{
  int percentage = -1;
  SDL_GetPowerInfo(nullptr, &percentage);
  if (percentage != -1) {
    return percentage;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the current power state of a potential battery.
 *
 * \return the current power state.
 */
[[nodiscard]] inline auto query_battery() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

/**
 * \brief Indicate whether a battery is available.
 *
 * \return `true` if a battery is available; `false` otherwise.
 */
[[nodiscard]] inline auto is_battery_available() noexcept -> bool
{
  const auto state = query_battery();
  return state != power_state::no_battery && state != power_state::unknown;
}

/**
 * \brief Indicate whether the battery is being charged.
 *
 * \return `true` if the battery is charging; `false` otherwise.
 */
[[nodiscard]] inline auto is_battery_charging() noexcept -> bool
{
  return query_battery() == power_state::charging;
}

/**
 * \brief Indicate whether the battery is charged.
 *
 * \return `true` if the battery is charged; `false` otherwise.
 */
[[nodiscard]] inline auto is_battery_charged() noexcept -> bool
{
  return query_battery() == power_state::charged;
}

/// \} End of group power

}  // namespace cen

#endif  // CENTURION_POWER_HPP_
