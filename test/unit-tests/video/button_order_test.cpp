#include "video/button_order.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            static_cast<SDL_MessageBoxFlags>(cen::button_order::left_to_right));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            static_cast<SDL_MessageBoxFlags>(cen::button_order::right_to_left));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ButtonOrder, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::button_order>(0x101)), cen::cen_error);

  ASSERT_EQ("left_to_right", cen::to_string(cen::button_order::left_to_right));
  ASSERT_EQ("right_to_left", cen::to_string(cen::button_order::right_to_left));

  std::clog << "Button order example: " << cen::button_order::left_to_right << '\n';
}