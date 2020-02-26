#ifndef CENTURION_BATTERY_SOURCE
#define CENTURION_BATTERY_SOURCE

#include "battery.h"

namespace centurion {
namespace system {

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF
std::optional<int> Battery::get_seconds_left() noexcept
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft == -1) {
    return std::nullopt;
  } else {
    return secondsLeft;
  }
}

CENTURION_DEF
std::optional<int> Battery::get_minutes_left() noexcept
{
  const auto secondsLeft = get_seconds_left();
  if (secondsLeft) {
    return *secondsLeft / 60;
  } else {
    return std::nullopt;
  }
}

CENTURION_DEF
std::optional<int> Battery::get_percentage() noexcept
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft == -1) {
    return std::nullopt;
  } else {
    return percentageLeft;
  }
}

#endif

CENTURION_DEF
PowerState Battery::get_state() noexcept
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

}  // namespace system
}  // namespace centurion

#endif  // CENTURION_BATTERY_SOURCE