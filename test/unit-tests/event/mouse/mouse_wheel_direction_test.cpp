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
  ASSERT_THROW(ToString(static_cast<Direction>(3)), cen::Error);

  ASSERT_EQ("Normal", ToString(Direction::Normal));
  ASSERT_EQ("Flipped", ToString(Direction::Flipped));

  std::clog << "Mouse wheel direction example: " << Direction::Normal << '\n';
}
