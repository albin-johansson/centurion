#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::controller_bind_type::axis), SDL_CONTROLLER_BINDTYPE_AXIS);
  ASSERT_EQ(cen::to_underlying(cen::controller_bind_type::button),
            SDL_CONTROLLER_BINDTYPE_BUTTON);
  ASSERT_EQ(cen::to_underlying(cen::controller_bind_type::none), SDL_CONTROLLER_BINDTYPE_NONE);
  ASSERT_EQ(cen::to_underlying(cen::controller_bind_type::hat), SDL_CONTROLLER_BINDTYPE_HAT);
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::controller_bind_type>(4)), cen::Error);

  ASSERT_EQ("none", cen::to_string(cen::controller_bind_type::none));
  ASSERT_EQ("button", cen::to_string(cen::controller_bind_type::button));
  ASSERT_EQ("axis", cen::to_string(cen::controller_bind_type::axis));
  ASSERT_EQ("hat", cen::to_string(cen::controller_bind_type::hat));

  std::clog << "Controller bind type example: " << cen::controller_bind_type::button << '\n';
}
