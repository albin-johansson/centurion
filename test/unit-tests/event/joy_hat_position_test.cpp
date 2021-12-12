#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "events/event.hpp"

TEST(JoyHatPosition, Values)
{
  ASSERT_EQ(9, cen::joy_hat_position_count());

  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::left_up), SDL_HAT_LEFTUP);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::left), SDL_HAT_LEFT);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::left_down), SDL_HAT_LEFTDOWN);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::up), SDL_HAT_UP);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::centered), SDL_HAT_CENTERED);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::down), SDL_HAT_DOWN);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::right_up), SDL_HAT_RIGHTUP);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::right), SDL_HAT_RIGHT);
  ASSERT_EQ(cen::to_underlying(cen::joy_hat_position::right_down), SDL_HAT_RIGHTDOWN);
}

TEST(JoyHatPosition, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::joy_hat_position>(SDL_HAT_RIGHTDOWN + 1)),
               cen::Error);

  ASSERT_EQ("left_up", cen::to_string(cen::joy_hat_position::left_up));
  ASSERT_EQ("left", cen::to_string(cen::joy_hat_position::left));
  ASSERT_EQ("left_down", cen::to_string(cen::joy_hat_position::left_down));
  ASSERT_EQ("up", cen::to_string(cen::joy_hat_position::up));
  ASSERT_EQ("centered", cen::to_string(cen::joy_hat_position::centered));
  ASSERT_EQ("down", cen::to_string(cen::joy_hat_position::down));
  ASSERT_EQ("right_up", cen::to_string(cen::joy_hat_position::right_up));
  ASSERT_EQ("right", cen::to_string(cen::joy_hat_position::right));
  ASSERT_EQ("right_down", cen::to_string(cen::joy_hat_position::right_down));

  std::clog << "Joystick hat position example: " << cen::joy_hat_position::left << '\n';
}
