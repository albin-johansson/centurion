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
  ASSERT_THROW(cen::ToString(static_cast<cen::MouseButton>(6)), cen::Error);

  ASSERT_EQ("left", cen::ToString(cen::MouseButton::Left));
  ASSERT_EQ("middle", cen::ToString(cen::MouseButton::Middle));
  ASSERT_EQ("right", cen::ToString(cen::MouseButton::Right));
  ASSERT_EQ("x1", cen::ToString(cen::MouseButton::X1));
  ASSERT_EQ("x2", cen::ToString(cen::MouseButton::X2));

  std::clog << "Mouse button example: " << cen::MouseButton::Middle << '\n';
}
