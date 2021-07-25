#include <gtest/gtest.h>

#include <iostream>  // cout

#include "events/event.hpp"

TEST(MouseWheelDirection, EqualityOperator)
{
  ASSERT_EQ(cen::mouse_wheel_direction::normal, SDL_MOUSEWHEEL_NORMAL);
  ASSERT_EQ(cen::mouse_wheel_direction::flipped, SDL_MOUSEWHEEL_FLIPPED);

  ASSERT_EQ(SDL_MOUSEWHEEL_NORMAL, cen::mouse_wheel_direction::normal);
  ASSERT_EQ(SDL_MOUSEWHEEL_FLIPPED, cen::mouse_wheel_direction::flipped);

  ASSERT_FALSE(cen::mouse_wheel_direction::normal == SDL_MOUSEWHEEL_FLIPPED);
}

TEST(MouseWheelDirection, InequalityOperator)
{
  ASSERT_NE(cen::mouse_wheel_direction::normal, SDL_MOUSEWHEEL_FLIPPED);
  ASSERT_NE(cen::mouse_wheel_direction::flipped, SDL_MOUSEWHEEL_NORMAL);

  ASSERT_NE(SDL_MOUSEWHEEL_NORMAL, cen::mouse_wheel_direction::flipped);
  ASSERT_NE(SDL_MOUSEWHEEL_FLIPPED, cen::mouse_wheel_direction::normal);

  ASSERT_FALSE(cen::mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_FLIPPED);
}

TEST(MouseWheelDirection, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::mouse_wheel_direction>(3)),
               cen::cen_error);

  ASSERT_EQ("normal", cen::to_string(cen::mouse_wheel_direction::normal));
  ASSERT_EQ("flipped", cen::to_string(cen::mouse_wheel_direction::flipped));

  std::cout << "Mouse wheel direction example: " << cen::mouse_wheel_direction::normal
            << '\n';
}
