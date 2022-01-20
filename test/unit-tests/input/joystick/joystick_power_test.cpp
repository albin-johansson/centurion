#include <gtest/gtest.h>

#include <iostream>  // cout

#include "joystick.hpp"

TEST(JoystickPower, Values)
{
  ASSERT_EQ(SDL_JOYSTICK_POWER_UNKNOWN, to_underlying(cen::joystick_power::unknown));
  ASSERT_EQ(SDL_JOYSTICK_POWER_EMPTY, to_underlying(cen::joystick_power::empty));
  ASSERT_EQ(SDL_JOYSTICK_POWER_LOW, to_underlying(cen::joystick_power::low));
  ASSERT_EQ(SDL_JOYSTICK_POWER_MEDIUM, to_underlying(cen::joystick_power::medium));
  ASSERT_EQ(SDL_JOYSTICK_POWER_FULL, to_underlying(cen::joystick_power::full));
  ASSERT_EQ(SDL_JOYSTICK_POWER_WIRED, to_underlying(cen::joystick_power::wired));
  ASSERT_EQ(SDL_JOYSTICK_POWER_MAX, to_underlying(cen::joystick_power::max));
}

TEST(JoystickPower, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::joystick_power>(SDL_JOYSTICK_POWER_MAX + 1)),
               cen::exception);

  ASSERT_EQ("unknown", to_string(cen::joystick_power::unknown));
  ASSERT_EQ("empty", to_string(cen::joystick_power::empty));
  ASSERT_EQ("low", to_string(cen::joystick_power::low));
  ASSERT_EQ("medium", to_string(cen::joystick_power::medium));
  ASSERT_EQ("full", to_string(cen::joystick_power::full));
  ASSERT_EQ("wired", to_string(cen::joystick_power::wired));
  ASSERT_EQ("max", to_string(cen::joystick_power::max));

  std::cout << "joystick_power::wired == " << cen::joystick_power::wired << '\n';
}
