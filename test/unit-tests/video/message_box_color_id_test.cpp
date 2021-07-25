#include <gtest/gtest.h>

#include <iostream>  // clog

#include "video/message_box.hpp"

using id = cen::message_box::color_id;

TEST(MessageBoxColorID, Values)
{
  ASSERT_EQ(id::button_selected, SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  ASSERT_EQ(id::button_background, SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  ASSERT_EQ(id::button_border, SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  ASSERT_EQ(id::background, SDL_MESSAGEBOX_COLOR_BACKGROUND);

  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED, id::button_selected);
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND, id::button_background);
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER, id::button_border);
  ASSERT_EQ(SDL_MESSAGEBOX_COLOR_BACKGROUND, id::background);

  ASSERT_NE(id::background, SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  ASSERT_NE(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER, id::button_selected);
}

TEST(MessageBoxColorID, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<id>(SDL_MESSAGEBOX_COLOR_MAX + 1)),
               cen::cen_error);

  ASSERT_EQ("background", cen::to_string(id::background));
  ASSERT_EQ("text", cen::to_string(id::text));
  ASSERT_EQ("button_border", cen::to_string(id::button_border));
  ASSERT_EQ("button_background", cen::to_string(id::button_background));
  ASSERT_EQ("button_selected", cen::to_string(id::button_selected));

  std::clog << "Message box color ID example: " << id::background << '\n';
}
