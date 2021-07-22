#include <gtest/gtest.h>

#include <iostream>  // cout

#include "video/message_box.hpp"

using button = cen::message_box::default_button;

TEST(MessageBoxDefaultButton, Values)
{
  ASSERT_EQ(button::return_key, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  ASSERT_EQ(button::escape_key, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, button::return_key);
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, button::escape_key);

  ASSERT_NE(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, button::escape_key);
}

TEST(MessageBoxDefaultButton, ToString)
{
  ASSERT_EQ("return_key", cen::to_string(button::return_key));
  ASSERT_EQ("escape_key", cen::to_string(button::escape_key));

  std::cout << "Message box default button example: " << button::return_key << '\n';
}
