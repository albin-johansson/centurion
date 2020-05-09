#ifndef CENTURION_BATTERY_SOURCE
#define CENTURION_BATTERY_SOURCE

#include "battery.h"

namespace centurion {

CENTURION_DEF
Optional<int> Battery::seconds_left() noexcept
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
Optional<int> Battery::minutes_left() noexcept
{
  const auto secondsLeft = seconds_left();
  if (secondsLeft) {
    return *secondsLeft / 60;
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<int> Battery::percentage() noexcept
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
PowerState Battery::state() noexcept
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

CENTURION_DEF
bool Battery::exists() noexcept
{
  return state() == PowerState::OnBattery;
}

CENTURION_DEF
bool operator==(PowerState a, SDL_PowerState b) noexcept
{
  return static_cast<SDL_PowerState>(a) == b;
}

CENTURION_DEF
bool operator==(SDL_PowerState a, PowerState b) noexcept
{
  return a == static_cast<SDL_PowerState>(b);
}

}  // namespace centurion

#endif  // CENTURION_BATTERY_SOURCE