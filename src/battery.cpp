#ifndef CENTURION_BATTERY_SOURCE
#define CENTURION_BATTERY_SOURCE

#include "battery.hpp"

#include "centurion_types.hpp"

namespace centurion::battery {

CENTURION_DEF
auto seconds_left() noexcept -> std::optional<seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft == -1) {
    return nothing;
  } else {
    return seconds<int>{secondsLeft};
  }
}

CENTURION_DEF
auto minutes_left() noexcept -> std::optional<minutes<int>>
{
  const auto secondsLeft = seconds_left();
  if (secondsLeft) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto percentage() noexcept -> std::optional<int>
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft == -1) {
    return nothing;
  } else {
    return percentageLeft;
  }
}

CENTURION_DEF
auto state() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

CENTURION_DEF
auto exists() noexcept -> bool
{
  return state() == power_state::on_battery;
}

}  // namespace centurion::battery

#endif  // CENTURION_BATTERY_SOURCE