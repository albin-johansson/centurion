#include "battery.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("PowerState enum", "[PowerState]")
{
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

TEST_CASE("Battery::percentage", "[Battery]")
{
  CHECK_NOTHROW(Battery::percentage());

  const auto percentage = Battery::percentage();
  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);
    CHECK(percentage == actual);
  }
}

TEST_CASE("Battery::minutes_left", "[Battery]")
{
  CHECK_NOTHROW(Battery::minutes_left());

  const auto minutes = Battery::minutes_left();
  if (minutes) {
    int secs = -1;
    SDL_GetPowerInfo(&secs, nullptr);
    CHECK(minutes == (secs / 60));
  }
}

TEST_CASE("Battery::state", "[Battery]")
{
  CHECK_NOTHROW(Battery::state());

  const auto state = Battery::state();
  const auto actual =
      static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}

TEST_CASE("Battery::exists", "[Battery]")
{
  CHECK(Battery::exists() == (Battery::state() == PowerState::OnBattery));
}