#include <gtest/gtest.h>

#include "system.hpp"

TEST(Battery, GetBatteryPercentage)
{
  ASSERT_NO_THROW(cen::GetBatteryPercentage());

  const auto percentage = cen::GetBatteryPercentage();
  ASSERT_EQ(percentage.has_value(), cen::IsBatteryAvailable());

  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);

    ASSERT_EQ(actual, percentage);
  }
}

TEST(Battery, GetBatterySeconds)
{
  ASSERT_NO_THROW(cen::GetBatterySeconds());

  int actual = -1;
  SDL_GetPowerInfo(&actual, nullptr);

  if (const auto secs = cen::GetBatterySeconds()) {
    ASSERT_EQ(cen::Seconds<int>{actual}, secs.value());
  }
}

TEST(Battery, GetBatteryMinutes)
{
  ASSERT_NO_THROW(cen::GetBatteryMinutes());

  if (const auto minutes = cen::GetBatteryMinutes()) {
    int actual = -1;
    SDL_GetPowerInfo(&actual, nullptr);

    const cen::Seconds<int> s{actual};
    ASSERT_EQ(std::chrono::duration_cast<cen::Minutes<int>>(s), minutes.value());
  }
}

TEST(Battery, QueryBattery)
{
  ASSERT_NO_THROW(cen::QueryBattery());

  const auto state = cen::QueryBattery();
  const auto actual = SDL_GetPowerInfo(nullptr, nullptr);

  ASSERT_EQ(actual, static_cast<SDL_PowerState>(state));
}

TEST(Battery, IsBatteryAvailable)
{
  const auto state = cen::QueryBattery();
  const auto exists = state == cen::PowerState::OnBattery ||
                      state == cen::PowerState::Charged || state == cen::PowerState::Charging;
  ASSERT_EQ(exists, cen::IsBatteryAvailable());
}

TEST(Battery, IsBatteryCharging)
{
  ASSERT_EQ(cen::QueryBattery() == cen::PowerState::Charging, cen::IsBatteryCharging());
}

TEST(Battery, IsBatteryCharged)
{
  ASSERT_EQ(cen::QueryBattery() == cen::PowerState::Charged, cen::IsBatteryCharged());
}
