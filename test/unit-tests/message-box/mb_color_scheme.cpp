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

#include "centurion/video/message_box.hpp"

TEST(MessageBoxColorScheme, Defaults)
{
  const cen::message_box_color_scheme scheme;

  const auto* data = scheme.data();
  const auto color = cen::colors::white;

  ASSERT_EQ(color, cen::color {data->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]});
  ASSERT_EQ(color, cen::color {data->colors[SDL_MESSAGEBOX_COLOR_TEXT]});
  ASSERT_EQ(color, cen::color {data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]});
  ASSERT_EQ(color, cen::color {data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]});
  ASSERT_EQ(color, cen::color {data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]});
}

TEST(MessageBoxColorScheme, Custom)
{
  cen::message_box_color_scheme scheme;

  const auto check = [&](const cen::message_box_color_type type, const cen::color& color) {
    scheme.set_color(type, color);
    ASSERT_EQ(color, cen::color {scheme.data()->colors[cen::to_underlying(type)]});
  };

  check(cen::message_box_color_type::text, cen::colors::salmon);
  check(cen::message_box_color_type::background, cen::colors::pink);
  check(cen::message_box_color_type::button_background, cen::colors::violet);
  check(cen::message_box_color_type::button_border, cen::colors::alice_blue);
  check(cen::message_box_color_type::button_selected, cen::colors::wheat);
}
