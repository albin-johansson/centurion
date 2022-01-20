#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/controller.hpp"

using axis = cen::controller_axis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_AXIS_INVALID, to_underlying(axis::invalid));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTX, to_underlying(axis::left_x));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTY, to_underlying(axis::left_y));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, to_underlying(axis::right_x));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, to_underlying(axis::right_y));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, to_underlying(axis::trigger_left));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, to_underlying(axis::trigger_right));
  ASSERT_EQ(SDL_CONTROLLER_AXIS_MAX, to_underlying(axis::max));
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(to_string(static_cast<axis>(SDL_CONTROLLER_AXIS_MAX + 1)), cen::exception);

  ASSERT_EQ("invalid", to_string(axis::invalid));

  ASSERT_EQ("left_x", to_string(axis::left_x));
  ASSERT_EQ("left_y", to_string(axis::left_y));

  ASSERT_EQ("right_x", to_string(axis::right_x));
  ASSERT_EQ("right_y", to_string(axis::right_y));

  ASSERT_EQ("trigger_left", to_string(axis::trigger_left));
  ASSERT_EQ("trigger_right", to_string(axis::trigger_right));

  ASSERT_EQ("max", to_string(axis::max));

  std::cout << "controller_axis::right_x == " << axis::right_x << '\n';
}
