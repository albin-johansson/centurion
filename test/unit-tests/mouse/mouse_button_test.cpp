#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "mouse.hpp"

TEST(MouseButton, Values)
{
  ASSERT_EQ(SDL_BUTTON_LEFT, cen::ToUnderlying(cen::MouseButton::Left));
  ASSERT_EQ(SDL_BUTTON_MIDDLE, cen::ToUnderlying(cen::MouseButton::Middle));
  ASSERT_EQ(SDL_BUTTON_RIGHT, cen::ToUnderlying(cen::MouseButton::Right));
  ASSERT_EQ(SDL_BUTTON_X1, cen::ToUnderlying(cen::MouseButton::X1));
  ASSERT_EQ(SDL_BUTTON_X2, cen::ToUnderlying(cen::MouseButton::X2));
}

TEST(MouseButton, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::MouseButton>(6)), cen::Error);

  ASSERT_EQ("left", cen::to_string(cen::MouseButton::Left));
  ASSERT_EQ("middle", cen::to_string(cen::MouseButton::Middle));
  ASSERT_EQ("right", cen::to_string(cen::MouseButton::Right));
  ASSERT_EQ("x1", cen::to_string(cen::MouseButton::X1));
  ASSERT_EQ("x2", cen::to_string(cen::MouseButton::X2));

  std::clog << "Mouse button example: " << cen::MouseButton::Middle << '\n';
}
