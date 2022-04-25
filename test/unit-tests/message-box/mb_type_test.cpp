#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/message_box.hpp"

TEST(MessageBoxType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_INFORMATION, to_underlying(cen::message_box_type::information));
  ASSERT_EQ(SDL_MESSAGEBOX_WARNING, to_underlying(cen::message_box_type::warning));
  ASSERT_EQ(SDL_MESSAGEBOX_ERROR, to_underlying(cen::message_box_type::error));
}

TEST(MessageBoxType, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::message_box_type>(0x41)), cen::exception);

  ASSERT_EQ("information", to_string(cen::message_box_type::information));
  ASSERT_EQ("error", to_string(cen::message_box_type::error));
  ASSERT_EQ("warning", to_string(cen::message_box_type::warning));

  std::cout << "message_box_type::information == " << cen::message_box_type::information
            << '\n';
}
