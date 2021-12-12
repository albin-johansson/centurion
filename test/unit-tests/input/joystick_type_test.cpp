#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/joystick.hpp"

TEST(JoystickType, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::unknown), SDL_JOYSTICK_TYPE_UNKNOWN);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::game_controller),
            SDL_JOYSTICK_TYPE_GAMECONTROLLER);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::wheel), SDL_JOYSTICK_TYPE_WHEEL);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::arcade_stick),
            SDL_JOYSTICK_TYPE_ARCADE_STICK);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::flight_stick),
            SDL_JOYSTICK_TYPE_FLIGHT_STICK);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::dance_pad), SDL_JOYSTICK_TYPE_DANCE_PAD);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::guitar), SDL_JOYSTICK_TYPE_GUITAR);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::drum_kit), SDL_JOYSTICK_TYPE_DRUM_KIT);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::arcade_pad), SDL_JOYSTICK_TYPE_ARCADE_PAD);
  ASSERT_EQ(cen::to_underlying(cen::joystick_type::throttle), SDL_JOYSTICK_TYPE_THROTTLE);
}

TEST(JoystickType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::joystick_type>(11)), cen::Error);

  ASSERT_EQ("unknown", cen::to_string(cen::joystick_type::unknown));
  ASSERT_EQ("game_controller", cen::to_string(cen::joystick_type::game_controller));
  ASSERT_EQ("wheel", cen::to_string(cen::joystick_type::wheel));
  ASSERT_EQ("arcade_stick", cen::to_string(cen::joystick_type::arcade_stick));
  ASSERT_EQ("flight_stick", cen::to_string(cen::joystick_type::flight_stick));
  ASSERT_EQ("dance_pad", cen::to_string(cen::joystick_type::dance_pad));
  ASSERT_EQ("guitar", cen::to_string(cen::joystick_type::guitar));
  ASSERT_EQ("drum_kit", cen::to_string(cen::joystick_type::drum_kit));
  ASSERT_EQ("arcade_pad", cen::to_string(cen::joystick_type::arcade_pad));
  ASSERT_EQ("throttle", cen::to_string(cen::joystick_type::throttle));

  std::clog << "Joystick type example: " << cen::joystick_type::guitar << '\n';
}
