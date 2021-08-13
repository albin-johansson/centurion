#include "input/controller_axis.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

using axis = cen::controller_axis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(axis::invalid, SDL_CONTROLLER_AXIS_INVALID);
  ASSERT_EQ(axis::left_x, SDL_CONTROLLER_AXIS_LEFTX);
  ASSERT_EQ(axis::left_y, SDL_CONTROLLER_AXIS_LEFTY);
  ASSERT_EQ(axis::right_x, SDL_CONTROLLER_AXIS_RIGHTX);
  ASSERT_EQ(axis::right_y, SDL_CONTROLLER_AXIS_RIGHTY);
  ASSERT_EQ(axis::trigger_left, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  ASSERT_EQ(axis::trigger_right, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  ASSERT_EQ(axis::max, SDL_CONTROLLER_AXIS_MAX);

  ASSERT_EQ(SDL_CONTROLLER_AXIS_INVALID, axis::invalid);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTX, axis::left_x);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTY, axis::left_y);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, axis::right_x);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, axis::right_y);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::trigger_left);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, axis::trigger_right);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_MAX, axis::max);

  ASSERT_NE(axis::left_x, SDL_CONTROLLER_AXIS_MAX);
  ASSERT_NE(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::right_x);
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<axis>(SDL_CONTROLLER_AXIS_MAX + 1)),
               cen::cen_error);

  ASSERT_EQ("invalid", cen::to_string(axis::invalid));
  ASSERT_EQ("left_x", cen::to_string(axis::left_x));
  ASSERT_EQ("left_y", cen::to_string(axis::left_y));
  ASSERT_EQ("right_x", cen::to_string(axis::right_x));
  ASSERT_EQ("right_y", cen::to_string(axis::right_y));
  ASSERT_EQ("trigger_left", cen::to_string(axis::trigger_left));
  ASSERT_EQ("trigger_right", cen::to_string(axis::trigger_right));
  ASSERT_EQ("max", cen::to_string(axis::max));

  std::clog << "Controller axis example: " << axis::right_x << '\n';
}
