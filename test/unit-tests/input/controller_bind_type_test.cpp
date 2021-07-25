#include "input/controller_bind_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(cen::controller_bind_type::axis, SDL_CONTROLLER_BINDTYPE_AXIS);
  ASSERT_EQ(cen::controller_bind_type::button, SDL_CONTROLLER_BINDTYPE_BUTTON);
  ASSERT_EQ(cen::controller_bind_type::none, SDL_CONTROLLER_BINDTYPE_NONE);
  ASSERT_EQ(cen::controller_bind_type::hat, SDL_CONTROLLER_BINDTYPE_HAT);

  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_AXIS, cen::controller_bind_type::axis);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_BUTTON, cen::controller_bind_type::button);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_NONE, cen::controller_bind_type::none);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_HAT, cen::controller_bind_type::hat);

  ASSERT_NE(cen::controller_bind_type::axis, SDL_CONTROLLER_BINDTYPE_HAT);
  ASSERT_NE(SDL_CONTROLLER_BINDTYPE_BUTTON, cen::controller_bind_type::none);
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::controller_bind_type>(4)), cen::cen_error);

  ASSERT_EQ("none", cen::to_string(cen::controller_bind_type::none));
  ASSERT_EQ("button", cen::to_string(cen::controller_bind_type::button));
  ASSERT_EQ("axis", cen::to_string(cen::controller_bind_type::axis));
  ASSERT_EQ("hat", cen::to_string(cen::controller_bind_type::hat));

  std::cout << "Controller bind type example: " << cen::controller_bind_type::button
            << '\n';
}
