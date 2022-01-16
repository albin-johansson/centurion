#include "input/button_state.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"

TEST(ButtonState, Values)
{
  ASSERT_EQ(SDL_RELEASED, cen::to_underlying(cen::ButtonState::Released));
  ASSERT_EQ(SDL_PRESSED, cen::to_underlying(cen::ButtonState::Pressed));
}

TEST(ButtonState, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::ButtonState>(3)), cen::exception);

  ASSERT_EQ("Released", cen::ToString(cen::ButtonState::Released));
  ASSERT_EQ("Pressed", cen::ToString(cen::ButtonState::Pressed));

  std::clog << "Button state example: " << cen::ButtonState::Pressed << '\n';
}
