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

#include "centurion/font.hpp"

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

TEST(WrapAlignment, Values)
{
  ASSERT_EQ(TTF_WRAPPED_ALIGN_LEFT, to_underlying(cen::wrap_alignment::left));
  ASSERT_EQ(TTF_WRAPPED_ALIGN_CENTER, to_underlying(cen::wrap_alignment::center));
  ASSERT_EQ(TTF_WRAPPED_ALIGN_RIGHT, to_underlying(cen::wrap_alignment::right));
}

TEST(WrapAlignment, ToString)
{
  ASSERT_EQ("left", to_string(cen::wrap_alignment::left));
  ASSERT_EQ("center", to_string(cen::wrap_alignment::center));
  ASSERT_EQ("right", to_string(cen::wrap_alignment::right));

  ASSERT_THROW(to_string(static_cast<cen::wrap_alignment>(100)), cen::exception);
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)
