#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(MouseWheelDirection, EqualityOperator)
{
  EXPECT_EQ(cen::mouse_wheel_direction::normal, SDL_MOUSEWHEEL_NORMAL);
  EXPECT_EQ(cen::mouse_wheel_direction::flipped, SDL_MOUSEWHEEL_FLIPPED);

  EXPECT_EQ(SDL_MOUSEWHEEL_NORMAL, cen::mouse_wheel_direction::normal);
  EXPECT_EQ(SDL_MOUSEWHEEL_FLIPPED, cen::mouse_wheel_direction::flipped);

  EXPECT_FALSE(cen::mouse_wheel_direction::normal == SDL_MOUSEWHEEL_FLIPPED);
}

TEST(MouseWheelDirection, InequalityOperator)
{
  EXPECT_NE(cen::mouse_wheel_direction::normal, SDL_MOUSEWHEEL_FLIPPED);
  EXPECT_NE(cen::mouse_wheel_direction::flipped, SDL_MOUSEWHEEL_NORMAL);

  EXPECT_NE(SDL_MOUSEWHEEL_NORMAL, cen::mouse_wheel_direction::flipped);
  EXPECT_NE(SDL_MOUSEWHEEL_FLIPPED, cen::mouse_wheel_direction::normal);

  EXPECT_FALSE(cen::mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_FLIPPED);
}
