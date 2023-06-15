/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_SYSTEM_POWER_HPP_
#define CENTURION_SYSTEM_POWER_HPP_

#include <SDL.h>

#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common/errors.hpp"
#include "../common/primitives.hpp"

namespace cen {

enum class power_state {
  unknown = SDL_POWERSTATE_UNKNOWN,        ///< The status is unknown.
  on_battery = SDL_POWERSTATE_ON_BATTERY,  ///< Not plugged in and running on battery.
  no_battery = SDL_POWERSTATE_NO_BATTERY,  ///< No battery available.
  charging = SDL_POWERSTATE_CHARGING,      ///< Charging the battery.
  charged = SDL_POWERSTATE_CHARGED         ///< Plugged in and charged.
};

[[nodiscard]] inline auto battery_seconds() -> std::optional<seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int> {secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto battery_minutes() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = battery_seconds()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

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

[[nodiscard]] inline auto query_battery() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

[[nodiscard]] inline auto is_battery_available() noexcept -> bool
{
  const auto state = query_battery();
  return state != power_state::no_battery && state != power_state::unknown;
}

[[nodiscard]] inline auto is_battery_charging() noexcept -> bool
{
  return query_battery() == power_state::charging;
}

[[nodiscard]] inline auto is_battery_charged() noexcept -> bool
{
  return query_battery() == power_state::charged;
}

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
      throw exception {"Did not recognize power state!"};
  }
}

inline auto operator<<(std::ostream& stream, const power_state state) -> std::ostream&
{
  return stream << to_string(state);
}

}  // namespace cen

#endif  // CENTURION_SYSTEM_POWER_HPP_
