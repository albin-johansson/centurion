#include "catch.hpp"
#include "system.h"

using namespace centurion::system;

TEST_CASE("PowerState enum", "[Power]") {
  CHECK(PowerState::Unknown == SDL_POWERSTATE_UNKNOWN);
  CHECK(PowerState::OnBattery == SDL_POWERSTATE_ON_BATTERY);
  CHECK(PowerState::NoBattery == SDL_POWERSTATE_NO_BATTERY);
  CHECK(PowerState::Charging == SDL_POWERSTATE_CHARGING);
  CHECK(PowerState::Charged == SDL_POWERSTATE_CHARGED);

  CHECK(SDL_POWERSTATE_UNKNOWN == PowerState::Unknown);
  CHECK(SDL_POWERSTATE_ON_BATTERY == PowerState::OnBattery);
  CHECK(SDL_POWERSTATE_NO_BATTERY == PowerState::NoBattery);
  CHECK(SDL_POWERSTATE_CHARGING == PowerState::Charging);
  CHECK(SDL_POWERSTATE_CHARGED == PowerState::Charged);
}

#ifdef CENTURION_HAS_OPTIONAL

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

#endif

TEST_CASE("PowerState::get_state", "[Power]") {
  CHECK_NOTHROW(Power::get_state());

  const auto state = Power::get_state();
  const auto actual = static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}