#include "battery.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("power_state enum values", "[battery]")
{
  using namespace ctn::battery;
  CHECK(power_state::unknown == SDL_POWERSTATE_UNKNOWN);
  CHECK(power_state::on_battery == SDL_POWERSTATE_ON_BATTERY);
  CHECK(power_state::no_battery == SDL_POWERSTATE_NO_BATTERY);
  CHECK(power_state::charging == SDL_POWERSTATE_CHARGING);
  CHECK(power_state::charged == SDL_POWERSTATE_CHARGED);

  CHECK(SDL_POWERSTATE_UNKNOWN == power_state::unknown);
  CHECK(SDL_POWERSTATE_ON_BATTERY == power_state::on_battery);
  CHECK(SDL_POWERSTATE_NO_BATTERY == power_state::no_battery);
  CHECK(SDL_POWERSTATE_CHARGING == power_state::charging);
  CHECK(SDL_POWERSTATE_CHARGED == power_state::charged);

  CHECK(power_state::charged != SDL_POWERSTATE_ON_BATTERY);
  CHECK(SDL_POWERSTATE_CHARGING != power_state::unknown);
}

TEST_CASE("battery::percentage", "[battery]")
{
  CHECK_NOTHROW(ctn::battery::percentage());

  const auto percentage = ctn::battery::percentage();
  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);
    CHECK(percentage == actual);
  }
}

TEST_CASE("battery::seconds_left", "[battery]")
{
  CHECK_NOTHROW(ctn::battery::seconds_left());

  int actual = 0;

  const auto secs = ctn::battery::seconds_left();
  SDL_GetPowerInfo(&actual, nullptr);

  if (secs) {
    const ctn::seconds<int> actualSeconds{actual};
    CHECK(secs.value() == actualSeconds);
  }
}

TEST_CASE("battery::minutes_left", "[battery]")
{
  CHECK_NOTHROW(ctn::battery::minutes_left());

  const auto minutes = ctn::battery::minutes_left();
  if (minutes) {
    int secs = -1;
    SDL_GetPowerInfo(&secs, nullptr);

    const ctn::seconds<int> seconds{secs};

    CHECK(minutes.value() == seconds);
  }
}

TEST_CASE("battery::state", "[battery]")
{
  CHECK_NOTHROW(ctn::battery::state());

  const auto state = ctn::battery::state();
  const auto actual = static_cast<ctn::battery::power_state>(
      SDL_GetPowerInfo(nullptr, nullptr));

  CHECK(state == actual);
}

TEST_CASE("battery::exists", "[battery]")
{
  CHECK(ctn::battery::exists() ==
        (ctn::battery::state() == ctn::battery::power_state::on_battery));
}