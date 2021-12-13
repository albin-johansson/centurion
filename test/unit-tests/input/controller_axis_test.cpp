#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

using axis = cen::controller_axis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(cen::ToUnderlying(axis::invalid), SDL_CONTROLLER_AXIS_INVALID);
  ASSERT_EQ(cen::ToUnderlying(axis::left_x), SDL_CONTROLLER_AXIS_LEFTX);
  ASSERT_EQ(cen::ToUnderlying(axis::left_y), SDL_CONTROLLER_AXIS_LEFTY);
  ASSERT_EQ(cen::ToUnderlying(axis::right_x), SDL_CONTROLLER_AXIS_RIGHTX);
  ASSERT_EQ(cen::ToUnderlying(axis::right_y), SDL_CONTROLLER_AXIS_RIGHTY);
  ASSERT_EQ(cen::ToUnderlying(axis::trigger_left), SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  ASSERT_EQ(cen::ToUnderlying(axis::trigger_right), SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  ASSERT_EQ(cen::ToUnderlying(axis::max), SDL_CONTROLLER_AXIS_MAX);
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<axis>(SDL_CONTROLLER_AXIS_MAX + 1)), cen::Error);

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
