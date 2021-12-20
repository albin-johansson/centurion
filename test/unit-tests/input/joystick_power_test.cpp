#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/joystick.hpp"

TEST(JoystickPower, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Unknown), SDL_JOYSTICK_POWER_UNKNOWN);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Empty), SDL_JOYSTICK_POWER_EMPTY);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Low), SDL_JOYSTICK_POWER_LOW);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Medium), SDL_JOYSTICK_POWER_MEDIUM);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Full), SDL_JOYSTICK_POWER_FULL);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Wired), SDL_JOYSTICK_POWER_WIRED);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickPower::Max), SDL_JOYSTICK_POWER_MAX);
}

TEST(JoystickPower, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::JoystickPower>(SDL_JOYSTICK_POWER_MAX + 1)),
               cen::Error);

  ASSERT_EQ("Unknown", cen::to_string(cen::JoystickPower::Unknown));
  ASSERT_EQ("Empty", cen::to_string(cen::JoystickPower::Empty));
  ASSERT_EQ("Low", cen::to_string(cen::JoystickPower::Low));
  ASSERT_EQ("Medium", cen::to_string(cen::JoystickPower::Medium));
  ASSERT_EQ("Full", cen::to_string(cen::JoystickPower::Full));
  ASSERT_EQ("Wired", cen::to_string(cen::JoystickPower::Wired));
  ASSERT_EQ("Max", cen::to_string(cen::JoystickPower::Max));

  std::clog << "Joystick power example: " << cen::JoystickPower::Wired << '\n';
}
