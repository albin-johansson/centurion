#include "catch.hpp"
#include "system.h"

using namespace centurion;

TEST_CASE("PowerState enum", "[Power]") {
  CHECK(static_cast<SDL_PowerState>(PowerState::Unknown) == SDL_POWERSTATE_UNKNOWN);
  CHECK(static_cast<SDL_PowerState>(PowerState::OnBattery) == SDL_POWERSTATE_ON_BATTERY);
  CHECK(static_cast<SDL_PowerState>(PowerState::NoBattery) == SDL_POWERSTATE_NO_BATTERY);
  CHECK(static_cast<SDL_PowerState>(PowerState::Charging) == SDL_POWERSTATE_CHARGING);
  CHECK(static_cast<SDL_PowerState>(PowerState::Charged) == SDL_POWERSTATE_CHARGED);
}

TEST_CASE("PowerState::get_battery_percentage", "[Power]") {
  CHECK_NOTHROW(Power::get_battery_percentage());

  const auto percentage = Power::get_battery_percentage();
  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);
    CHECK(percentage == actual);
  }
}

TEST_CASE("PowerState::get_battery_minutes_left", "[Power]") {
  CHECK_NOTHROW(Power::get_battery_minutes_left());

  const auto minutes = Power::get_battery_minutes_left();
  if (minutes) {
    int secs = -1;
    SDL_GetPowerInfo(&secs, nullptr);
    CHECK(minutes == (secs / 60));
  }
}

TEST_CASE("PowerState::get_power_state", "[Power]") {
  CHECK_NOTHROW(Power::get_state());

  const auto state = Power::get_state();
  const auto actual = static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}