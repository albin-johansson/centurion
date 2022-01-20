#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/mouse.hpp"

TEST(MouseButton, Values)
{
  ASSERT_EQ(SDL_BUTTON_LEFT, to_underlying(cen::mouse_button::left));
  ASSERT_EQ(SDL_BUTTON_MIDDLE, to_underlying(cen::mouse_button::middle));
  ASSERT_EQ(SDL_BUTTON_RIGHT, to_underlying(cen::mouse_button::right));
  ASSERT_EQ(SDL_BUTTON_X1, to_underlying(cen::mouse_button::x1));
  ASSERT_EQ(SDL_BUTTON_X2, to_underlying(cen::mouse_button::x2));
}

TEST(MouseButton, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::mouse_button>(6)), cen::exception);

  ASSERT_EQ("left", to_string(cen::mouse_button::left));
  ASSERT_EQ("middle", to_string(cen::mouse_button::middle));
  ASSERT_EQ("right", to_string(cen::mouse_button::right));
  ASSERT_EQ("x1", to_string(cen::mouse_button::x1));
  ASSERT_EQ("x2", to_string(cen::mouse_button::x2));

  std::cout << "moues_button::middle == " << cen::mouse_button::middle << '\n';
}
