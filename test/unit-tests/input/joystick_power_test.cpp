#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/joystick.hpp"

TEST(JoystickPower, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Unknown), SDL_JOYSTICK_POWER_UNKNOWN);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Empty), SDL_JOYSTICK_POWER_EMPTY);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Low), SDL_JOYSTICK_POWER_LOW);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Medium), SDL_JOYSTICK_POWER_MEDIUM);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Full), SDL_JOYSTICK_POWER_FULL);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Wired), SDL_JOYSTICK_POWER_WIRED);
  ASSERT_EQ(cen::to_underlying(cen::JoystickPower::Max), SDL_JOYSTICK_POWER_MAX);
}

TEST(JoystickPower, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::JoystickPower>(SDL_JOYSTICK_POWER_MAX + 1)),
               cen::exception);

  ASSERT_EQ("Unknown", cen::ToString(cen::JoystickPower::Unknown));
  ASSERT_EQ("Empty", cen::ToString(cen::JoystickPower::Empty));
  ASSERT_EQ("Low", cen::ToString(cen::JoystickPower::Low));
  ASSERT_EQ("Medium", cen::ToString(cen::JoystickPower::Medium));
  ASSERT_EQ("Full", cen::ToString(cen::JoystickPower::Full));
  ASSERT_EQ("Wired", cen::ToString(cen::JoystickPower::Wired));
  ASSERT_EQ("Max", cen::ToString(cen::JoystickPower::Max));

  std::clog << "Joystick power example: " << cen::JoystickPower::Wired << '\n';
}
