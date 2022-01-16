#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/controller.hpp"

using Axis = cen::ControllerAxis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(to_underlying(Axis::Invalid), SDL_CONTROLLER_AXIS_INVALID);
  ASSERT_EQ(to_underlying(Axis::LeftX), SDL_CONTROLLER_AXIS_LEFTX);
  ASSERT_EQ(to_underlying(Axis::LeftY), SDL_CONTROLLER_AXIS_LEFTY);
  ASSERT_EQ(to_underlying(Axis::RightX), SDL_CONTROLLER_AXIS_RIGHTX);
  ASSERT_EQ(to_underlying(Axis::RightY), SDL_CONTROLLER_AXIS_RIGHTY);
  ASSERT_EQ(to_underlying(Axis::TriggerLeft), SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  ASSERT_EQ(to_underlying(Axis::TriggerRight), SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  ASSERT_EQ(to_underlying(Axis::Max), SDL_CONTROLLER_AXIS_MAX);
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(ToString(static_cast<Axis>(SDL_CONTROLLER_AXIS_MAX + 1)), cen::exception);

  ASSERT_EQ("Invalid", ToString(Axis::Invalid));
  ASSERT_EQ("LeftX", ToString(Axis::LeftX));
  ASSERT_EQ("LeftY", ToString(Axis::LeftY));
  ASSERT_EQ("RightX", ToString(Axis::RightX));
  ASSERT_EQ("RightY", ToString(Axis::RightY));
  ASSERT_EQ("TriggerLeft", ToString(Axis::TriggerLeft));
  ASSERT_EQ("TriggerRight", ToString(Axis::TriggerRight));
  ASSERT_EQ("Max", ToString(Axis::Max));

  std::clog << "Controller axis example: " << Axis::RightX << '\n';
}
