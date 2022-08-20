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

#include <iostream>  // clog

#include "centurion/font.hpp"

TEST(FontHint, Values)
{
  ASSERT_EQ(TTF_HINTING_NORMAL, to_underlying(cen::font_hint::normal));
  ASSERT_EQ(TTF_HINTING_LIGHT, to_underlying(cen::font_hint::light));
  ASSERT_EQ(TTF_HINTING_MONO, to_underlying(cen::font_hint::mono));
  ASSERT_EQ(TTF_HINTING_NONE, to_underlying(cen::font_hint::none));

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ(TTF_HINTING_LIGHT_SUBPIXEL, to_underlying(cen::font_hint::light_subpixel));
#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)
}

TEST(FontHint, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::font_hint>(100)), cen::exception);

  ASSERT_EQ("normal", to_string(cen::font_hint::normal));
  ASSERT_EQ("light", to_string(cen::font_hint::light));
  ASSERT_EQ("mono", to_string(cen::font_hint::mono));
  ASSERT_EQ("none", to_string(cen::font_hint::none));

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ("light_subpixel", to_string(cen::font_hint::light_subpixel));
#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  std::cout << "Font hint example: " << cen::font_hint::normal << '\n';
}
