#include "battery.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("power_state enum values", "[power_state]")
{
  using namespace battery;
  CHECK(power_state::Unknown == SDL_POWERSTATE_UNKNOWN);
  CHECK(power_state::OnBattery == SDL_POWERSTATE_ON_BATTERY);
  CHECK(power_state::NoBattery == SDL_POWERSTATE_NO_BATTERY);
  CHECK(power_state::Charging == SDL_POWERSTATE_CHARGING);
  CHECK(power_state::Charged == SDL_POWERSTATE_CHARGED);

  CHECK(SDL_POWERSTATE_UNKNOWN == power_state::Unknown);
  CHECK(SDL_POWERSTATE_ON_BATTERY == power_state::OnBattery);
  CHECK(SDL_POWERSTATE_NO_BATTERY == power_state::NoBattery);
  CHECK(SDL_POWERSTATE_CHARGING == power_state::Charging);
  CHECK(SDL_POWERSTATE_CHARGED == power_state::Charged);
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
      static_cast<battery::power_state>(SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}

TEST_CASE("battery::exists", "[battery]")
{
  CHECK(battery::exists() ==
        (battery::state() == battery::power_state::OnBattery));
}