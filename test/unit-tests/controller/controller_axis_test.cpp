#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

using Axis = cen::ControllerAxis;

TEST(ControllerAxis, Values)
{
  ASSERT_EQ(ToUnderlying(Axis::Invalid), SDL_CONTROLLER_AXIS_INVALID);
  ASSERT_EQ(ToUnderlying(Axis::LeftX), SDL_CONTROLLER_AXIS_LEFTX);
  ASSERT_EQ(ToUnderlying(Axis::LeftY), SDL_CONTROLLER_AXIS_LEFTY);
  ASSERT_EQ(ToUnderlying(Axis::RightX), SDL_CONTROLLER_AXIS_RIGHTX);
  ASSERT_EQ(ToUnderlying(Axis::RightY), SDL_CONTROLLER_AXIS_RIGHTY);
  ASSERT_EQ(ToUnderlying(Axis::TriggerLeft), SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  ASSERT_EQ(ToUnderlying(Axis::TriggerRight), SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  ASSERT_EQ(ToUnderlying(Axis::Max), SDL_CONTROLLER_AXIS_MAX);
}

TEST(ControllerAxis, ToString)
{
  ASSERT_THROW(to_string(static_cast<Axis>(SDL_CONTROLLER_AXIS_MAX + 1)), cen::Error);

  ASSERT_EQ("Invalid", to_string(Axis::Invalid));
  ASSERT_EQ("LeftX", to_string(Axis::LeftX));
  ASSERT_EQ("LeftY", to_string(Axis::LeftY));
  ASSERT_EQ("RightX", to_string(Axis::RightX));
  ASSERT_EQ("RightY", to_string(Axis::RightY));
  ASSERT_EQ("TriggerLeft", to_string(Axis::TriggerLeft));
  ASSERT_EQ("TriggerRight", to_string(Axis::TriggerRight));
  ASSERT_EQ("Max", to_string(Axis::Max));

  std::clog << "Controller axis example: " << Axis::RightX << '\n';
}
