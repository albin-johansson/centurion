#include "button_state.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(ButtonState, Values)
{
  ASSERT_EQ(SDL_RELEASED, to_underlying(cen::button_state::released));
  ASSERT_EQ(SDL_PRESSED, to_underlying(cen::button_state::pressed));
}

TEST(ButtonState, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::button_state>(3)), cen::exception);

  ASSERT_EQ("released", to_string(cen::button_state::released));
  ASSERT_EQ("pressed", to_string(cen::button_state::pressed));

  std::cout << "button_state::pressed == " << cen::button_state::pressed << '\n';
}
