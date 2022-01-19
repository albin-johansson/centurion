#include <gtest/gtest.h>

#include <iostream>  // cout

#include "message_box.hpp"

TEST(MessageBoxColorType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_TEXT, to_underlying(cen::message_box_color_type::text));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
            to_underlying(cen::message_box_color_type::button_selected));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
            to_underlying(cen::message_box_color_type::button_background));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
            to_underlying(cen::message_box_color_type::button_border));
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BACKGROUND,
            to_underlying(cen::message_box_color_type::background));
}

TEST(MessageBoxColorType, ToString)
{
  ASSERT_THROW(
      to_string(static_cast<cen::message_box_color_type>(SDL_MESSAGEBOX_COLOR_MAX + 1)),
      cen::exception);

  ASSERT_EQ("background", to_string(cen::message_box_color_type::background));
  ASSERT_EQ("text", to_string(cen::message_box_color_type::text));
  ASSERT_EQ("button_border", to_string(cen::message_box_color_type::button_border));
  ASSERT_EQ("button_background", to_string(cen::message_box_color_type::button_background));
  ASSERT_EQ("button_selected", to_string(cen::message_box_color_type::button_selected));

  std::cout << "message_box_color_type::background == "
            << cen::message_box_color_type::background << '\n';
}
