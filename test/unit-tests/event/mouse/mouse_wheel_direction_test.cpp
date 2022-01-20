#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/mouse_events.hpp"

using direction = cen::mouse_wheel_direction;

TEST(MouseWheelDirection, Values)
{
  ASSERT_EQ(SDL_MOUSEWHEEL_NORMAL, to_underlying(direction::normal));
  ASSERT_EQ(SDL_MOUSEWHEEL_FLIPPED, to_underlying(direction::flipped));
}

TEST(MouseWheelDirection, ToString)
{
  ASSERT_THROW(to_string(static_cast<direction>(3)), cen::exception);

  ASSERT_EQ("normal", to_string(direction::normal));
  ASSERT_EQ("flipped", to_string(direction::flipped));

  std::cout << "mouse_wheel_direction::normal == " << direction::normal << '\n';
}
