#include "input/button_state.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(ButtonState, Values)
{
  ASSERT_EQ(SDL_RELEASED, cen::to_underlying(cen::button_state::released));
  ASSERT_EQ(SDL_PRESSED, cen::to_underlying(cen::button_state::pressed));
}

TEST(ButtonState, ToString)
{
  ASSERT_EQ("released", cen::to_string(cen::button_state::released));
  ASSERT_EQ("pressed", cen::to_string(cen::button_state::pressed));

  std::cout << "Button state example: " << cen::button_state::pressed << '\n';
}
