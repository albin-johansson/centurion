#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "system/system.hpp"

TEST(PowerState, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::PowerState::Unknown), SDL_POWERSTATE_UNKNOWN);
  ASSERT_EQ(cen::to_underlying(cen::PowerState::OnBattery), SDL_POWERSTATE_ON_BATTERY);
  ASSERT_EQ(cen::to_underlying(cen::PowerState::NoBattery), SDL_POWERSTATE_NO_BATTERY);
  ASSERT_EQ(cen::to_underlying(cen::PowerState::Charging), SDL_POWERSTATE_CHARGING);
  ASSERT_EQ(cen::to_underlying(cen::PowerState::Charged), SDL_POWERSTATE_CHARGED);
}

TEST(PowerState, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::PowerState>(6)), cen::Error);

  ASSERT_EQ("Unknown", cen::to_string(cen::PowerState::Unknown));
  ASSERT_EQ("OnBattery", cen::to_string(cen::PowerState::OnBattery));
  ASSERT_EQ("NoBattery", cen::to_string(cen::PowerState::NoBattery));
  ASSERT_EQ("Charging", cen::to_string(cen::PowerState::Charging));
  ASSERT_EQ("Charged", cen::to_string(cen::PowerState::Charged));

  std::clog << "Power state example: " << cen::PowerState::OnBattery << '\n';
}
