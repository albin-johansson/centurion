#include <gtest/gtest.h>

#include <iostream>  // clog

#include "message_box.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            cen::ToUnderlying(cen::MessageBoxButtonOrder::LeftToRight));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            cen::ToUnderlying(cen::MessageBoxButtonOrder::RightToLeft));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::MessageBoxButtonOrder>(0x101)), cen::Error);

  ASSERT_EQ("LeftToRight", cen::to_string(cen::MessageBoxButtonOrder::LeftToRight));
  ASSERT_EQ("RightToLeft", cen::to_string(cen::MessageBoxButtonOrder::RightToLeft));

  std::clog << "Button order example: " << cen::MessageBoxButtonOrder::LeftToRight << '\n';
}