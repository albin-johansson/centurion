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
  ASSERT_THROW(to_string(static_cast<BindType>(4)), cen::Error);

  ASSERT_EQ("None", to_string(BindType::None));
  ASSERT_EQ("Button", to_string(BindType::Button));
  ASSERT_EQ("Axis", to_string(BindType::Axis));
  ASSERT_EQ("Hat", to_string(BindType::Hat));

  std::clog << "Controller bind type example: " << BindType::Button << '\n';
}
