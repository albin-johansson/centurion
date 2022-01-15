#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/joystick.hpp"

TEST(JoystickType, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::Unknown), SDL_JOYSTICK_TYPE_UNKNOWN);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::GameController),
            SDL_JOYSTICK_TYPE_GAMECONTROLLER);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::Wheel), SDL_JOYSTICK_TYPE_WHEEL);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::ArcadeStick), SDL_JOYSTICK_TYPE_ARCADE_STICK);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::FlightStick), SDL_JOYSTICK_TYPE_FLIGHT_STICK);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::DancePad), SDL_JOYSTICK_TYPE_DANCE_PAD);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::Guitar), SDL_JOYSTICK_TYPE_GUITAR);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::DrumKit), SDL_JOYSTICK_TYPE_DRUM_KIT);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::ArcadePad), SDL_JOYSTICK_TYPE_ARCADE_PAD);
  ASSERT_EQ(cen::ToUnderlying(cen::JoystickType::Throttle), SDL_JOYSTICK_TYPE_THROTTLE);
}

TEST(JoystickType, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::JoystickType>(11)), cen::exception);

  ASSERT_EQ("Unknown", cen::ToString(cen::JoystickType::Unknown));
  ASSERT_EQ("GameController", cen::ToString(cen::JoystickType::GameController));
  ASSERT_EQ("Wheel", cen::ToString(cen::JoystickType::Wheel));
  ASSERT_EQ("ArcadeStick", cen::ToString(cen::JoystickType::ArcadeStick));
  ASSERT_EQ("FlightStick", cen::ToString(cen::JoystickType::FlightStick));
  ASSERT_EQ("DancePad", cen::ToString(cen::JoystickType::DancePad));
  ASSERT_EQ("Guitar", cen::ToString(cen::JoystickType::Guitar));
  ASSERT_EQ("DrumKit", cen::ToString(cen::JoystickType::DrumKit));
  ASSERT_EQ("ArcadePad", cen::ToString(cen::JoystickType::ArcadePad));
  ASSERT_EQ("Throttle", cen::ToString(cen::JoystickType::Throttle));

  std::clog << "Joystick type example: " << cen::JoystickType::Guitar << '\n';
}
