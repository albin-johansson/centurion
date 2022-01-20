#include <gtest/gtest.h>

#include <iostream>  // cout

#include "joystick.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, to_underlying(cen::hat_state::centered));
  ASSERT_EQ(SDL_HAT_UP, to_underlying(cen::hat_state::up));
  ASSERT_EQ(SDL_HAT_RIGHT, to_underlying(cen::hat_state::right));
  ASSERT_EQ(SDL_HAT_DOWN, to_underlying(cen::hat_state::down));
  ASSERT_EQ(SDL_HAT_LEFT, to_underlying(cen::hat_state::left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, to_underlying(cen::hat_state::right_up));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, to_underlying(cen::hat_state::right_down));
  ASSERT_EQ(SDL_HAT_LEFTUP, to_underlying(cen::hat_state::left_up));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, to_underlying(cen::hat_state::left_down));
}

TEST(HatState, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::hat_state>(0x10)), cen::exception);

  ASSERT_EQ("centered", to_string(cen::hat_state::centered));
  ASSERT_EQ("up", to_string(cen::hat_state::up));
  ASSERT_EQ("right", to_string(cen::hat_state::right));
  ASSERT_EQ("down", to_string(cen::hat_state::down));
  ASSERT_EQ("left", to_string(cen::hat_state::left));
  ASSERT_EQ("right_up", to_string(cen::hat_state::right_up));
  ASSERT_EQ("right_down", to_string(cen::hat_state::right_down));
  ASSERT_EQ("left_up", to_string(cen::hat_state::left_up));
  ASSERT_EQ("left_down", to_string(cen::hat_state::left_down));

  std::cout << "hat_state::centered == " << cen::hat_state::centered << '\n';
}
