#ifndef CENTURION_BATTERY_SOURCE
#define CENTURION_BATTERY_SOURCE

#include "battery.hpp"

#include "centurion_types.hpp"

namespace centurion::battery {

CENTURION_DEF
auto seconds_left() noexcept -> std::optional<int>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft == -1) {
    return nothing;
  } else {
    return secondsLeft;
  }
}

CENTURION_DEF
auto minutes_left() noexcept -> std::optional<int>
{
  const auto secondsLeft = seconds_left();
  if (secondsLeft) {
    return *secondsLeft / 60;
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
auto state() noexcept -> PowerState
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

CENTURION_DEF
auto exists() noexcept -> bool
{
  return state() == PowerState::OnBattery;
}

}  // namespace centurion::battery

#endif  // CENTURION_BATTERY_SOURCE