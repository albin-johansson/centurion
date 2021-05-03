#include <gtest/gtest.h>

#include "input/controller.hpp"

using axis = cen::controller_axis;

TEST(ControllerAxis, EqualityOperator)
{
  ASSERT_EQ(SDL_CONTROLLER_AXIS_INVALID, axis::invalid);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTX, axis::left_x);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_LEFTY, axis::left_y);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, axis::right_x);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, axis::right_y);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::trigger_left);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, axis::trigger_right);
  ASSERT_EQ(SDL_CONTROLLER_AXIS_MAX, axis::max);

  ASSERT_EQ(axis::invalid, SDL_CONTROLLER_AXIS_INVALID);
  ASSERT_EQ(axis::left_x, SDL_CONTROLLER_AXIS_LEFTX);
  ASSERT_EQ(axis::left_y, SDL_CONTROLLER_AXIS_LEFTY);
  ASSERT_EQ(axis::right_x, SDL_CONTROLLER_AXIS_RIGHTX);
  ASSERT_EQ(axis::right_y, SDL_CONTROLLER_AXIS_RIGHTY);
  ASSERT_EQ(axis::trigger_left, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  ASSERT_EQ(axis::trigger_right, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  ASSERT_EQ(axis::max, SDL_CONTROLLER_AXIS_MAX);
}

TEST(ControllerAxis, InequalityOperator)
{
  ASSERT_NE(SDL_CONTROLLER_AXIS_INVALID, axis::right_x);
  ASSERT_NE(axis::max, SDL_CONTROLLER_AXIS_LEFTX);

  ASSERT_FALSE(SDL_CONTROLLER_AXIS_TRIGGERRIGHT != axis::trigger_right);
}
