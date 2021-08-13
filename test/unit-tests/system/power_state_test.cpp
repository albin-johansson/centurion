#include "system/power_state.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(PowerState, Values)
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

TEST(PowerState, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::power_state>(6)), cen::cen_error);

  ASSERT_EQ("unknown", cen::to_string(cen::power_state::unknown));
  ASSERT_EQ("on_battery", cen::to_string(cen::power_state::on_battery));
  ASSERT_EQ("no_battery", cen::to_string(cen::power_state::no_battery));
  ASSERT_EQ("charging", cen::to_string(cen::power_state::charging));
  ASSERT_EQ("charged", cen::to_string(cen::power_state::charged));

  std::clog << "Power state example: " << cen::power_state::on_battery << '\n';
}
