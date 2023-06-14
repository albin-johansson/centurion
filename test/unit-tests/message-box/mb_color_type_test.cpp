/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/video/message_box.hpp"

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
