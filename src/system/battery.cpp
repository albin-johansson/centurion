#include "battery.hpp"

#include <chrono>

#include "types.hpp"

namespace cen::battery {

auto seconds_left() noexcept -> std::optional<seconds<int>>
{
  int secondsLeft{-1};
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft == -1) {
    return std::nullopt;
  } else {
    return seconds<int>{secondsLeft};
  }
}

auto minutes_left() noexcept -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = seconds_left(); secondsLeft) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  } else {
    return std::nullopt;
  }
}

auto percentage() noexcept -> std::optional<int>
{
  int percentageLeft{-1};
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft == -1) {
    return std::nullopt;
  } else {
    return percentageLeft;
  }
}

auto state() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

auto exists() noexcept -> bool
{
  return state() == power_state::on_battery;
}

}  // namespace cen::battery
