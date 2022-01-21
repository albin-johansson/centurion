#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/power.hpp"

TEST(PowerState, Values)
{
  ASSERT_EQ(SDL_POWERSTATE_UNKNOWN, to_underlying(cen::power_state::unknown));
  ASSERT_EQ(SDL_POWERSTATE_ON_BATTERY, to_underlying(cen::power_state::on_battery));
  ASSERT_EQ(SDL_POWERSTATE_NO_BATTERY, to_underlying(cen::power_state::no_battery));
  ASSERT_EQ(SDL_POWERSTATE_CHARGING, to_underlying(cen::power_state::charging));
  ASSERT_EQ(SDL_POWERSTATE_CHARGED, to_underlying(cen::power_state::charged));
}

TEST(PowerState, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::power_state>(6)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::power_state::unknown));
  ASSERT_EQ("on_battery", to_string(cen::power_state::on_battery));
  ASSERT_EQ("no_battery", to_string(cen::power_state::no_battery));
  ASSERT_EQ("charging", to_string(cen::power_state::charging));
  ASSERT_EQ("charged", to_string(cen::power_state::charged));

  std::cout << "power_state::on_battery == " << cen::power_state::on_battery << '\n';
}
