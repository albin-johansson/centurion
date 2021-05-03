#include "system/battery.hpp"

#include <gtest/gtest.h>

TEST(Battery, Percentage)
{
  ASSERT_NO_THROW(cen::battery::percentage());

  const auto percentage = cen::battery::percentage();
  ASSERT_EQ(percentage.has_value(), cen::battery::is_available());

  if (percentage)
  {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);

    ASSERT_EQ(actual, percentage);
  }
}

TEST(Battery, SecondsLeft)
{
  ASSERT_NO_THROW(cen::battery::seconds_left());

  int actual = -1;
  SDL_GetPowerInfo(&actual, nullptr);

  if (const auto secs = cen::battery::seconds_left())
  {
    ASSERT_EQ(cen::seconds<int>{actual}, secs.value());
  }
}

TEST(Battery, MinutesLeft)
{
  ASSERT_NO_THROW(cen::battery::minutes_left());

  if (const auto minutes = cen::battery::minutes_left())
  {
    int actual = -1;
    SDL_GetPowerInfo(&actual, nullptr);

    const cen::seconds<int> s{actual};
    ASSERT_EQ(std::chrono::duration_cast<cen::minutes<int>>(s), minutes.value());
  }
}

TEST(Battery, State)
{
  ASSERT_NO_THROW(cen::battery::state());

  const auto state = cen::battery::state();
  const auto actual = SDL_GetPowerInfo(nullptr, nullptr);

  ASSERT_EQ(actual, static_cast<SDL_PowerState>(state));
}

TEST(Battery, Exists)
{
  const auto state = cen::battery::state();
  const auto exists = state == cen::power_state::on_battery ||
                      state == cen::power_state::charged ||
                      state == cen::power_state::charging;
  ASSERT_EQ(exists, cen::battery::exists());
}

TEST(Battery, IsCharging)
{
  ASSERT_EQ(cen::battery::state() == cen::power_state::charging,
            cen::battery::is_charging());
}

TEST(Battery, IsCharged)
{
  ASSERT_EQ(cen::battery::state() == cen::power_state::charged,
            cen::battery::is_charged());
}

TEST(Battery, IsAvailable)
{
  const auto state = cen::battery::state();
  ASSERT_EQ(state != cen::power_state::unknown && state != cen::power_state::no_battery,
            cen::battery::is_available());
}

TEST(Battery, PowerStateEnum)
{
  ASSERT_EQ(cen::power_state::unknown, SDL_POWERSTATE_UNKNOWN);
  ASSERT_EQ(cen::power_state::on_battery, SDL_POWERSTATE_ON_BATTERY);
  ASSERT_EQ(cen::power_state::no_battery, SDL_POWERSTATE_NO_BATTERY);
  ASSERT_EQ(cen::power_state::charging, SDL_POWERSTATE_CHARGING);
  ASSERT_EQ(cen::power_state::charged, SDL_POWERSTATE_CHARGED);

  ASSERT_EQ(SDL_POWERSTATE_UNKNOWN, cen::power_state::unknown);
  ASSERT_EQ(SDL_POWERSTATE_ON_BATTERY, cen::power_state::on_battery);
  ASSERT_EQ(SDL_POWERSTATE_NO_BATTERY, cen::power_state::no_battery);
  ASSERT_EQ(SDL_POWERSTATE_CHARGING, cen::power_state::charging);
  ASSERT_EQ(SDL_POWERSTATE_CHARGED, cen::power_state::charged);

  ASSERT_NE(cen::power_state::charged, SDL_POWERSTATE_ON_BATTERY);
  ASSERT_NE(SDL_POWERSTATE_CHARGING, cen::power_state::unknown);
}
