#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "power.hpp"

TEST(PowerState, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::PowerState::Unknown), SDL_POWERSTATE_UNKNOWN);
  ASSERT_EQ(cen::ToUnderlying(cen::PowerState::OnBattery), SDL_POWERSTATE_ON_BATTERY);
  ASSERT_EQ(cen::ToUnderlying(cen::PowerState::NoBattery), SDL_POWERSTATE_NO_BATTERY);
  ASSERT_EQ(cen::ToUnderlying(cen::PowerState::Charging), SDL_POWERSTATE_CHARGING);
  ASSERT_EQ(cen::ToUnderlying(cen::PowerState::Charged), SDL_POWERSTATE_CHARGED);
}

TEST(PowerState, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::PowerState>(6)), cen::exception);

  ASSERT_EQ("Unknown", cen::ToString(cen::PowerState::Unknown));
  ASSERT_EQ("OnBattery", cen::ToString(cen::PowerState::OnBattery));
  ASSERT_EQ("NoBattery", cen::ToString(cen::PowerState::NoBattery));
  ASSERT_EQ("Charging", cen::ToString(cen::PowerState::Charging));
  ASSERT_EQ("Charged", cen::ToString(cen::PowerState::Charged));

  std::clog << "Power state example: " << cen::PowerState::OnBattery << '\n';
}
