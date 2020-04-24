#ifndef CENTURION_BATTERY_SOURCE
#define CENTURION_BATTERY_SOURCE

#include "battery.h"

namespace centurion {
namespace system {

CENTURION_DEF
Optional<int> Battery::get_seconds_left() noexcept
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft == -1) {
    return tl::nullopt;
  } else {
    return secondsLeft;
  }
}

CENTURION_DEF
Optional<int> Battery::get_minutes_left() noexcept
{
  const auto secondsLeft = get_seconds_left();
  if (secondsLeft) {
    return *secondsLeft / 60;
  } else {
    return tl::nullopt;
  }
}

CENTURION_DEF
Optional<int> Battery::get_percentage() noexcept
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft == -1) {
    return tl::nullopt;
  } else {
    return percentageLeft;
  }
}

CENTURION_DEF
PowerState Battery::get_state() noexcept
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

}  // namespace system
}  // namespace centurion

#endif  // CENTURION_BATTERY_SOURCE