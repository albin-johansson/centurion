#include <gtest/gtest.h>

#include "message_box.hpp"

TEST(MessageBoxButtonFlags, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
            to_underlying(cen::message_box::return_key_default));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
            to_underlying(cen::message_box::escape_key_default));
}
