#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyHatPosition, EqualityOperator)
{
  const auto cast = [](const cen::joy_hat_position position) {
    return static_cast<cen::u8>(position);
  };

  ASSERT_EQ(cast(cen::joy_hat_position::left_up), SDL_HAT_LEFTUP);
  ASSERT_EQ(cast(cen::joy_hat_position::left), SDL_HAT_LEFT);
  ASSERT_EQ(cast(cen::joy_hat_position::left_down), SDL_HAT_LEFTDOWN);
  ASSERT_EQ(cast(cen::joy_hat_position::up), SDL_HAT_UP);
  ASSERT_EQ(cast(cen::joy_hat_position::centered), SDL_HAT_CENTERED);
  ASSERT_EQ(cast(cen::joy_hat_position::down), SDL_HAT_DOWN);
  ASSERT_EQ(cast(cen::joy_hat_position::right_up), SDL_HAT_RIGHTUP);
  ASSERT_EQ(cast(cen::joy_hat_position::right), SDL_HAT_RIGHT);
  ASSERT_EQ(cast(cen::joy_hat_position::right_down), SDL_HAT_RIGHTDOWN);
}
