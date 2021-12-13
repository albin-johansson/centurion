#include "input/button_state.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"

TEST(ButtonState, Values)
{
  ASSERT_EQ(SDL_RELEASED, cen::ToUnderlying(cen::button_state::released));
  ASSERT_EQ(SDL_PRESSED, cen::ToUnderlying(cen::button_state::pressed));
}

TEST(ButtonState, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::button_state>(3)), cen::Error);

  ASSERT_EQ("released", cen::to_string(cen::button_state::released));
  ASSERT_EQ("pressed", cen::to_string(cen::button_state::pressed));

  std::clog << "Button state example: " << cen::button_state::pressed << '\n';
}
