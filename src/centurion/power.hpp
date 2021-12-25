#ifndef CENTURION_POWER_HPP_
#define CENTURION_POWER_HPP_

#include <SDL.h>

#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"

namespace cen {

enum class PowerState {
  Unknown = SDL_POWERSTATE_UNKNOWN,      /* The status is unknown. */
  OnBattery = SDL_POWERSTATE_ON_BATTERY, /* Not plugged in and running on battery. */
  NoBattery = SDL_POWERSTATE_NO_BATTERY, /* No battery available. */
  Charging = SDL_POWERSTATE_CHARGING,    /* Charging the battery. */
  Charged = SDL_POWERSTATE_CHARGED       /* Plugged in and charged. */
};

/* Returns the seconds of remaining battery life. */
[[nodiscard]] inline auto GetBatterySeconds() -> std::optional<Seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return Seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/* Returns the minutes of remaining battery life. */
[[nodiscard]] inline auto GetBatteryMinutes() -> std::optional<Minutes<int>>
{
  if (const auto secondsLeft = GetBatterySeconds()) {
    return std::chrono::duration_cast<Minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

/* Returns the percentage of remaining battery life. */
[[nodiscard]] inline auto GetBatteryPercentage() noexcept -> std::optional<int>
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

[[nodiscard]] inline auto QueryBattery() noexcept -> PowerState
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

[[nodiscard]] inline auto IsBatteryAvailable() noexcept -> bool
{
  const auto state = QueryBattery();
  return state != PowerState::NoBattery && state != PowerState::Unknown;
}

[[nodiscard]] inline auto IsBatteryCharging() noexcept -> bool
{
  return QueryBattery() == PowerState::Charging;
}

[[nodiscard]] inline auto IsBatteryCharged() noexcept -> bool
{
  return QueryBattery() == PowerState::Charged;
}

[[nodiscard]] constexpr auto to_string(const PowerState state) -> std::string_view
{
  switch (state) {
    case PowerState::Unknown:
      return "Unknown";

    case PowerState::OnBattery:
      return "OnBattery";

    case PowerState::NoBattery:
      return "NoBattery";

    case PowerState::Charging:
      return "Charging";

    case PowerState::Charged:
      return "Charged";

    default:
      throw Error{"Did not recognize power state!"};
  }
}

inline auto operator<<(std::ostream& stream, const PowerState state) -> std::ostream&
{
  return stream << to_string(state);
}

}  // namespace cen

#endif  // CENTURION_POWER_HPP_
