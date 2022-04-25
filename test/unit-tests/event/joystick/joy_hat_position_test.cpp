#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/event.hpp"

using position = cen::joy_hat_position;

TEST(JoyHatPosition, Values)
{
  ASSERT_EQ(SDL_HAT_LEFTUP, to_underlying(position::left_up));
  ASSERT_EQ(SDL_HAT_LEFT, to_underlying(position::left));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, to_underlying(position::left_down));
  ASSERT_EQ(SDL_HAT_UP, to_underlying(position::up));
  ASSERT_EQ(SDL_HAT_CENTERED, to_underlying(position::centered));
  ASSERT_EQ(SDL_HAT_DOWN, to_underlying(position::down));
  ASSERT_EQ(SDL_HAT_RIGHTUP, to_underlying(position::right_up));
  ASSERT_EQ(SDL_HAT_RIGHT, to_underlying(position::right));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, to_underlying(position::right_down));
}

TEST(JoyHatPosition, ToString)
{
  ASSERT_THROW(to_string(static_cast<position>(SDL_HAT_RIGHTDOWN + 1)), cen::exception);

  ASSERT_EQ("left_up", to_string(position::left_up));
  ASSERT_EQ("left", to_string(position::left));
  ASSERT_EQ("left_down", to_string(position::left_down));
  ASSERT_EQ("up", to_string(position::up));
  ASSERT_EQ("centered", to_string(position::centered));
  ASSERT_EQ("down", to_string(position::down));
  ASSERT_EQ("right_up", to_string(position::right_up));
  ASSERT_EQ("right", to_string(position::right));
  ASSERT_EQ("right_down", to_string(position::right_down));

  std::cout << "joystick_hat_position::left == " << position::left << '\n';
}
