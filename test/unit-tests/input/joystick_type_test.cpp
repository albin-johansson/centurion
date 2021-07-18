#include "input/joystick_type.hpp"

#include <gtest/gtest.h>

TEST(JoystickType, Values)
{
  ASSERT_EQ(cen::joystick_type::unknown, SDL_JOYSTICK_TYPE_UNKNOWN);
  ASSERT_EQ(cen::joystick_type::game_controller, SDL_JOYSTICK_TYPE_GAMECONTROLLER);
  ASSERT_EQ(cen::joystick_type::wheel, SDL_JOYSTICK_TYPE_WHEEL);
  ASSERT_EQ(cen::joystick_type::arcade_stick, SDL_JOYSTICK_TYPE_ARCADE_STICK);
  ASSERT_EQ(cen::joystick_type::flight_stick, SDL_JOYSTICK_TYPE_FLIGHT_STICK);
  ASSERT_EQ(cen::joystick_type::dance_pad, SDL_JOYSTICK_TYPE_DANCE_PAD);
  ASSERT_EQ(cen::joystick_type::guitar, SDL_JOYSTICK_TYPE_GUITAR);
  ASSERT_EQ(cen::joystick_type::drum_kit, SDL_JOYSTICK_TYPE_DRUM_KIT);
  ASSERT_EQ(cen::joystick_type::arcade_pad, SDL_JOYSTICK_TYPE_ARCADE_PAD);
  ASSERT_EQ(cen::joystick_type::throttle, SDL_JOYSTICK_TYPE_THROTTLE);

  ASSERT_EQ(SDL_JOYSTICK_TYPE_UNKNOWN, cen::joystick_type::unknown);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GAMECONTROLLER, cen::joystick_type::game_controller);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_WHEEL, cen::joystick_type::wheel);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_STICK, cen::joystick_type::arcade_stick);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_FLIGHT_STICK, cen::joystick_type::flight_stick);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DANCE_PAD, cen::joystick_type::dance_pad);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GUITAR, cen::joystick_type::guitar);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DRUM_KIT, cen::joystick_type::drum_kit);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_PAD, cen::joystick_type::arcade_pad);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_THROTTLE, cen::joystick_type::throttle);
}