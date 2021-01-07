/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_BATTERY_HEADER
#define CENTURION_BATTERY_HEADER

#include <SDL.h>

#include <chrono>    // duration_cast
#include <optional>  // optional

#include "centurion_cfg.hpp"
#include "detail/any_eq.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * \namespace cen::battery
 *
 * \ingroup system
 *
 * \brief Contains utilities related to the battery of the system.
 *
 * \since 5.0.0
 */
namespace cen::battery {

/**
 * \enum power_state
 *
 * \brief Mirrors the values of the `SDL_PowerState` enum.
 *
 * \since 3.0.0
 *
 * \headerfile battery.hpp
 */
enum class power_state
{
  unknown = SDL_POWERSTATE_UNKNOWN,  ///< The status is unknown.
  on_battery =
      SDL_POWERSTATE_ON_BATTERY,  ///< Not plugged in and running on battery.
  no_battery = SDL_POWERSTATE_NO_BATTERY,  ///< No battery available.
  charging = SDL_POWERSTATE_CHARGING,      ///< Currently charging the battery.
  charged = SDL_POWERSTATE_CHARGED  ///< Currently plugged in and charged.
};

/**
 * \brief Returns the seconds of battery life that is remaining.
 *
 * \return seconds of remaining battery life; `std::nullopt` if the value cannot
 * be computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto seconds_left() -> std::optional<seconds<int>>
{
  int secondsLeft{-1};
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int>{secondsLeft};
  } else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the amount of minutes of battery life that is remaining.
 *
 * \return minutes of remaining battery life; `std::nullopt` if the value cannot
 * be computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto minutes_left() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = seconds_left()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  } else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the percentage of battery life that is currently left.
 *
 * \return percentage of remaining battery life, in the range [0, 100];
 * `std::nullopt` if the battery percentage isn't available.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto percentage() noexcept -> std::optional<int>
{
  int percentageLeft{-1};
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft != -1) {
    return percentageLeft;
  } else {
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
[[nodiscard]] inline auto state() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

/**
 * \brief Indicates whether or not the system is running on a battery.
 *
 * \details This method is simply a convenience method that is based on the
 * `battery::state()` method.
 *
 * \return `true` if the system is running on a battery; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto exists() noexcept -> bool
{
  return detail::any_eq(state(),
                        power_state::on_battery,
                        power_state::charged,
                        power_state::charging);
}

/**
 * \brief Indicate whether or not the battery is being charged.
 *
 * \details This convenience function is equivalent to checking if
 * `battery::state()` is equal to `power_state::charging`.
 *
 * \return `true` if the battery is charging; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto is_charging() noexcept -> bool
{
  return state() == power_state::charging;
}

/**
 * \brief Indicate whether or not the battery is charged.
 *
 * \details This convenience function is equivalent to checking if
 * `battery::state()` is equal to `power_state::charged`.
 *
 * \return `true` if the battery is charged; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto is_charged() noexcept -> bool
{
  return state() == power_state::charged;
}

/**
 * \brief Indicate whether or not a battery is available.
 *
 * \details This convenience function considers a battery available if the state
 * returned from `battery::state()` is neither `no_battery` nor `unknown`.
 *
 * \return `true` if a battery is available; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto is_available() noexcept -> bool
{
  return !detail::any_eq(state(),
                         power_state::no_battery,
                         power_state::unknown);
}

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
                                        const SDL_PowerState rhs) noexcept
    -> bool
{
  return static_cast<SDL_PowerState>(lhs) == rhs;
}

/**
 * \copydoc operator==(power_state, SDL_PowerState)
 */
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
                                        const SDL_PowerState rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(power_state, SDL_PowerState)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_PowerState lhs,
                                        const power_state rhs) noexcept -> bool
{
  return rhs != lhs;
}

}  // namespace cen::battery

#endif  // CENTURION_BATTERY_HEADER