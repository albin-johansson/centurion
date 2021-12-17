#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::ControllerBindType::axis), SDL_CONTROLLER_BINDTYPE_AXIS);
  ASSERT_EQ(cen::ToUnderlying(cen::ControllerBindType::button),
            SDL_CONTROLLER_BINDTYPE_BUTTON);
  ASSERT_EQ(cen::ToUnderlying(cen::ControllerBindType::none), SDL_CONTROLLER_BINDTYPE_NONE);
  ASSERT_EQ(cen::ToUnderlying(cen::ControllerBindType::hat), SDL_CONTROLLER_BINDTYPE_HAT);
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::ControllerBindType>(4)), cen::Error);

  ASSERT_EQ("none", cen::to_string(cen::ControllerBindType::none));
  ASSERT_EQ("button", cen::to_string(cen::ControllerBindType::button));
  ASSERT_EQ("axis", cen::to_string(cen::ControllerBindType::axis));
  ASSERT_EQ("hat", cen::to_string(cen::ControllerBindType::hat));

  std::clog << "Controller bind type example: " << cen::ControllerBindType::button << '\n';
}
