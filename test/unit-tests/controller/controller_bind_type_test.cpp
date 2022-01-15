#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/controller.hpp"

using BindType = cen::ControllerBindType;

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(ToUnderlying(BindType::Axis), SDL_CONTROLLER_BINDTYPE_AXIS);
  ASSERT_EQ(ToUnderlying(BindType::Button), SDL_CONTROLLER_BINDTYPE_BUTTON);
  ASSERT_EQ(ToUnderlying(BindType::None), SDL_CONTROLLER_BINDTYPE_NONE);
  ASSERT_EQ(ToUnderlying(BindType::Hat), SDL_CONTROLLER_BINDTYPE_HAT);
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(ToString(static_cast<BindType>(4)), cen::exception);

  ASSERT_EQ("None", ToString(BindType::None));
  ASSERT_EQ("Button", ToString(BindType::Button));
  ASSERT_EQ("Axis", ToString(BindType::Axis));
  ASSERT_EQ("Hat", ToString(BindType::Hat));

  std::clog << "Controller bind type example: " << BindType::Button << '\n';
}
