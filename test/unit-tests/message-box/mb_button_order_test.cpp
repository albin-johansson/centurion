#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/message_box.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            to_underlying(cen::message_box_button_order::left_to_right));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            to_underlying(cen::message_box_button_order::right_to_left));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::message_box_button_order>(1'000)), cen::exception);

  ASSERT_EQ("left_to_right", to_string(cen::message_box_button_order::left_to_right));
  ASSERT_EQ("right_to_left", to_string(cen::message_box_button_order::right_to_left));

  std::cout << "message_box_button_order::left_to_right == "
            << cen::message_box_button_order::left_to_right << '\n';
}