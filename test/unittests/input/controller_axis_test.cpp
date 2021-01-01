#include <gtest/gtest.h>

#include "controller.hpp"

using axis = cen::controller_axis;

TEST(ControllerAxis, EqualityOperator)
{
  EXPECT_EQ(SDL_CONTROLLER_AXIS_INVALID, axis::invalid);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_LEFTX, axis::left_x);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_LEFTY, axis::left_y);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, axis::right_x);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, axis::right_y);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::trigger_left);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, axis::trigger_right);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_MAX, axis::max);

  EXPECT_EQ(axis::invalid, SDL_CONTROLLER_AXIS_INVALID);
  EXPECT_EQ(axis::left_x, SDL_CONTROLLER_AXIS_LEFTX);
  EXPECT_EQ(axis::left_y, SDL_CONTROLLER_AXIS_LEFTY);
  EXPECT_EQ(axis::right_x, SDL_CONTROLLER_AXIS_RIGHTX);
  EXPECT_EQ(axis::right_y, SDL_CONTROLLER_AXIS_RIGHTY);
  EXPECT_EQ(axis::trigger_left, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  EXPECT_EQ(axis::trigger_right, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  EXPECT_EQ(axis::max, SDL_CONTROLLER_AXIS_MAX);
}

TEST(ControllerAxis, InequalityOperator)
{
  EXPECT_NE(SDL_CONTROLLER_AXIS_INVALID, axis::right_x);
  EXPECT_NE(axis::max, SDL_CONTROLLER_AXIS_LEFTX);

  EXPECT_FALSE(SDL_CONTROLLER_AXIS_TRIGGERRIGHT != axis::trigger_right);
}
