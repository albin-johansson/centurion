#include "video/button_order.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            cen::to_underlying(cen::button_order::left_to_right));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            cen::to_underlying(cen::button_order::right_to_left));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ButtonOrder, ToString)
{
  ASSERT_EQ("left_to_right", cen::to_string(cen::button_order::left_to_right));
  ASSERT_EQ("right_to_left", cen::to_string(cen::button_order::right_to_left));

  std::cout << "Button order example: " << cen::button_order::left_to_right << '\n';
}