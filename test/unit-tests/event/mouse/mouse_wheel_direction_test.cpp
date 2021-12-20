#include <gtest/gtest.h>

#include <iostream>  // clog

#include "event.hpp"

using Direction = cen::MouseWheelDirection;

TEST(MouseWheelDirection, Values)
{
  ASSERT_EQ(ToUnderlying(Direction::Normal), SDL_MOUSEWHEEL_NORMAL);
  ASSERT_EQ(ToUnderlying(Direction::Flipped), SDL_MOUSEWHEEL_FLIPPED);
}

TEST(MouseWheelDirection, ToString)
{
  ASSERT_THROW(to_string(static_cast<Direction>(3)), cen::Error);

  ASSERT_EQ("Normal", to_string(Direction::Normal));
  ASSERT_EQ("Flipped", to_string(Direction::Flipped));

  std::clog << "Mouse wheel direction example: " << Direction::Normal << '\n';
}
