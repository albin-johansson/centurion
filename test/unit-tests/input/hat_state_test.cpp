#include "input/hat_state.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, cen::to_underlying(cen::hat_state::centered));
  ASSERT_EQ(SDL_HAT_UP, cen::to_underlying(cen::hat_state::up));
  ASSERT_EQ(SDL_HAT_RIGHT, cen::to_underlying(cen::hat_state::right));
  ASSERT_EQ(SDL_HAT_DOWN, cen::to_underlying(cen::hat_state::down));
  ASSERT_EQ(SDL_HAT_LEFT, cen::to_underlying(cen::hat_state::left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, cen::to_underlying(cen::hat_state::right_up));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, cen::to_underlying(cen::hat_state::right_down));
  ASSERT_EQ(SDL_HAT_LEFTUP, cen::to_underlying(cen::hat_state::left_up));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, cen::to_underlying(cen::hat_state::left_down));
}
