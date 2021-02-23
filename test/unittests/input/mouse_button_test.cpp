#include "mouse_button.hpp"

#include <gtest/gtest.h>

#include "integers.hpp"

TEST(MouseButton, EnumValues)
{
  EXPECT_EQ(SDL_BUTTON_LEFT, static_cast<cen::u32>(cen::mouse_button::left));
  EXPECT_EQ(SDL_BUTTON_MIDDLE,
            static_cast<cen::u32>(cen::mouse_button::middle));
  EXPECT_EQ(SDL_BUTTON_RIGHT, static_cast<cen::u32>(cen::mouse_button::right));
  EXPECT_EQ(SDL_BUTTON_X1, static_cast<cen::u32>(cen::mouse_button::x1));
  EXPECT_EQ(SDL_BUTTON_X2, static_cast<cen::u32>(cen::mouse_button::x2));
}
