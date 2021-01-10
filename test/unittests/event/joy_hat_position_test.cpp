#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyHatPosition, EqualityOperator)
{
  const auto cast = [](const cen::joy_hat_position position) {
    return static_cast<cen::u8>(position);
  };

  EXPECT_EQ(cast(cen::joy_hat_position::left_up), SDL_HAT_LEFTUP);
  EXPECT_EQ(cast(cen::joy_hat_position::left), SDL_HAT_LEFT);
  EXPECT_EQ(cast(cen::joy_hat_position::left_down), SDL_HAT_LEFTDOWN);
  EXPECT_EQ(cast(cen::joy_hat_position::up), SDL_HAT_UP);
  EXPECT_EQ(cast(cen::joy_hat_position::centered), SDL_HAT_CENTERED);
  EXPECT_EQ(cast(cen::joy_hat_position::down), SDL_HAT_DOWN);
  EXPECT_EQ(cast(cen::joy_hat_position::right_up), SDL_HAT_RIGHTUP);
  EXPECT_EQ(cast(cen::joy_hat_position::right), SDL_HAT_RIGHT);
  EXPECT_EQ(cast(cen::joy_hat_position::right_down), SDL_HAT_RIGHTDOWN);
}
