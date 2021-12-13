#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/joystick.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, cen::ToUnderlying(cen::hat_state::centered));
  ASSERT_EQ(SDL_HAT_UP, cen::ToUnderlying(cen::hat_state::up));
  ASSERT_EQ(SDL_HAT_RIGHT, cen::ToUnderlying(cen::hat_state::right));
  ASSERT_EQ(SDL_HAT_DOWN, cen::ToUnderlying(cen::hat_state::down));
  ASSERT_EQ(SDL_HAT_LEFT, cen::ToUnderlying(cen::hat_state::left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, cen::ToUnderlying(cen::hat_state::right_up));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, cen::ToUnderlying(cen::hat_state::right_down));
  ASSERT_EQ(SDL_HAT_LEFTUP, cen::ToUnderlying(cen::hat_state::left_up));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, cen::ToUnderlying(cen::hat_state::left_down));
}

TEST(HatState, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::hat_state>(0x10)), cen::Error);

  ASSERT_EQ("centered", cen::to_string(cen::hat_state::centered));
  ASSERT_EQ("up", cen::to_string(cen::hat_state::up));
  ASSERT_EQ("right", cen::to_string(cen::hat_state::right));
  ASSERT_EQ("down", cen::to_string(cen::hat_state::down));
  ASSERT_EQ("left", cen::to_string(cen::hat_state::left));
  ASSERT_EQ("right_up", cen::to_string(cen::hat_state::right_up));
  ASSERT_EQ("right_down", cen::to_string(cen::hat_state::right_down));
  ASSERT_EQ("left_up", cen::to_string(cen::hat_state::left_up));
  ASSERT_EQ("left_down", cen::to_string(cen::hat_state::left_down));

  std::clog << "Hat state example: " << cen::hat_state::centered << '\n';
}
