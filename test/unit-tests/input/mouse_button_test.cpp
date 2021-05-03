#include "input/mouse_button.hpp"

#include <gtest/gtest.h>

#include "core/integers.hpp"

TEST(MouseButton, EnumValues)
{
  ASSERT_EQ(SDL_BUTTON_LEFT, static_cast<cen::u32>(cen::mouse_button::left));
  ASSERT_EQ(SDL_BUTTON_MIDDLE, static_cast<cen::u32>(cen::mouse_button::middle));
  ASSERT_EQ(SDL_BUTTON_RIGHT, static_cast<cen::u32>(cen::mouse_button::right));
  ASSERT_EQ(SDL_BUTTON_X1, static_cast<cen::u32>(cen::mouse_button::x1));
  ASSERT_EQ(SDL_BUTTON_X2, static_cast<cen::u32>(cen::mouse_button::x2));
}
