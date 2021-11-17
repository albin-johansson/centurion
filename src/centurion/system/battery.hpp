#ifndef CENTURION_BATTERY_HEADER
#define CENTURION_BATTERY_HEADER

#include <SDL.h>

#include <chrono>    // duration_cast
#include <optional>  // optional

#include "../core/time.hpp"
#include "power_state.hpp"

namespace cen {

/// \addtogroup system
/// \{

/// \name Battery functions
/// \{

/**
 * \brief Returns the seconds of battery life that is remaining.
 *
 * \return seconds of remaining battery life; `std::nullopt` if the value cannot be
 * computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_seconds() -> std::optional<seconds<int>>
{
  int secondsLeft{-1};
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the amount of minutes of battery life that is remaining.
 *
 * \return minutes of remaining battery life; `std::nullopt` if the value cannot be
 * computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_minutes() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = seconds_left()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the percentage of battery life that is currently left.
 *
 * \return percentage of remaining battery life, in the range [0, 100]; `std::nullopt` if
 * the battery percentage isn't available.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_percentage() noexcept -> std::optional<int>
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft != -1) {
    return percentageLeft;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the current power state.
 *
 * \return the current power state.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto query_battery() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

/**
 * \brief Indicates whether or not the system is running on a battery.
 *
 * \details This function is simply a convenience function that is based on the
 * `battery::state()` function.
 *
 * \return `true` if the system is running on a battery; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto battery_exists() noexcept -> bool
{
  const auto state = query_battery();
  return state == power_state::on_battery || state == power_state::charged ||
         state == power_state::charging;
}

/**
 * \brief Indicate whether or not the battery is being charged.
 *
 * \details This convenience function is equivalent to checking if `battery::state()` is
 * equal to `power_state::charging`.
 *
 * \return `true` if the battery is charging; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_charging() noexcept -> bool
{
  return query_battery() == power_state::charging;
}

/**
 * \brief Indicate whether or not the battery is charged.
 *
 * \details This convenience function is equivalent to checking if `battery::state()` is
 * equal to `power_state::charged`.
 *
 * \return `true` if the battery is charged; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_charged() noexcept -> bool
{
  return query_battery() == power_state::charged;
}

/**
 * \brief Indicate whether or not a battery is available.
 *
 * \details This convenience function considers a battery available if the state returned
 * from `battery::state()` is neither `no_battery` nor `unknown`.
 *
 * \return `true` if a battery is available; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_available() noexcept -> bool
{
  const auto state = query_battery();
  return state != power_state::no_battery && state != power_state::unknown;
}

/// \} End of battery functions

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_BATTERY_HEADER