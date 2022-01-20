#include <gtest/gtest.h>

#include <iostream>  // cout

#include "controller.hpp"

using bind_type = cen::controller_bind_type;

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_AXIS, to_underlying(bind_type::axis));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_BUTTON, to_underlying(bind_type::button));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_NONE, to_underlying(bind_type::none));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_HAT, to_underlying(bind_type::hat));
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(to_string(static_cast<bind_type>(100)), cen::exception);

  ASSERT_EQ("none", to_string(bind_type::none));
  ASSERT_EQ("button", to_string(bind_type::button));
  ASSERT_EQ("axis", to_string(bind_type::axis));
  ASSERT_EQ("hat", to_string(bind_type::hat));

  std::cout << "controller_bind_type::button == " << bind_type::button << '\n';
}
