#include <gtest/gtest.h>

#include <iostream>  // clog

#include "message_box.hpp"

TEST(MessageBoxButtonFlags, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
            cen::ToUnderlying(cen::MessageBox::ReturnKeyDefault));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
            cen::ToUnderlying(cen::MessageBox::EscapeKeyDefault));
}
