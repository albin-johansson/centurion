#include "battery.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("PowerState enum values", "[PowerState]")
{
  using namespace battery;
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

TEST_CASE("battery::percentage", "[battery]")
{
  CHECK_NOTHROW(battery::percentage());

  const auto percentage = battery::percentage();
  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);
    CHECK(percentage == actual);
  }
}

TEST_CASE("battery::minutes_left", "[battery]")
{
  CHECK_NOTHROW(battery::minutes_left());

  const auto minutes = battery::minutes_left();
  if (minutes) {
    int secs = -1;
    SDL_GetPowerInfo(&secs, nullptr);
    CHECK(minutes == (secs / 60));
  }
}

TEST_CASE("battery::state", "[battery]")
{
  CHECK_NOTHROW(battery::state());

  const auto state = battery::state();
  const auto actual =
      static_cast<battery::PowerState>(SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}

TEST_CASE("battery::exists", "[battery]")
{
  CHECK(battery::exists() ==
        (battery::state() == battery::PowerState::OnBattery));
}