#include <gtest/gtest.h>

#include <iostream>  // clog

#include "message_box.hpp"

TEST(MessageBoxColorType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_TEXT, cen::ToUnderlying(cen::MessageBoxColorType::Text));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
            cen::ToUnderlying(cen::MessageBoxColorType::ButtonSelected));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
            cen::ToUnderlying(cen::MessageBoxColorType::ButtonBackground));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
            cen::ToUnderlying(cen::MessageBoxColorType::ButtonBorder));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BACKGROUND,
            cen::ToUnderlying(cen::MessageBoxColorType::Background));
}

TEST(MessageBoxColorType, ToString)
{
  ASSERT_THROW(
      cen::to_string(static_cast<cen::MessageBoxColorType>(SDL_MESSAGEBOX_COLOR_MAX + 1)),
      cen::Error);

  ASSERT_EQ("Background", cen::to_string(cen::MessageBoxColorType::Background));
  ASSERT_EQ("Text", cen::to_string(cen::MessageBoxColorType::Text));
  ASSERT_EQ("ButtonBorder", cen::to_string(cen::MessageBoxColorType::ButtonBorder));
  ASSERT_EQ("ButtonBackground", cen::to_string(cen::MessageBoxColorType::ButtonBackground));
  ASSERT_EQ("ButtonSelected", cen::to_string(cen::MessageBoxColorType::ButtonSelected));

  std::clog << "Message box color type example: " << cen::MessageBoxColorType::Background
            << '\n';
}
