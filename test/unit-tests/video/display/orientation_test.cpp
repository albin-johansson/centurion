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

#include "centurion/video.hpp"

TEST(Orientation, Values)
{
  ASSERT_EQ(SDL_ORIENTATION_UNKNOWN, to_underlying(cen::orientation::unknown));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, to_underlying(cen::orientation::landscape));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE_FLIPPED,
            to_underlying(cen::orientation::landscape_flipped));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT, to_underlying(cen::orientation::portrait));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT_FLIPPED,
            to_underlying(cen::orientation::portrait_flipped));
}

TEST(Orientation, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::orientation>(6)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::orientation::unknown));
  ASSERT_EQ("landscape", to_string(cen::orientation::landscape));
  ASSERT_EQ("landscape_flipped", to_string(cen::orientation::landscape_flipped));
  ASSERT_EQ("portrait", to_string(cen::orientation::portrait));
  ASSERT_EQ("portrait_flipped", to_string(cen::orientation::portrait_flipped));

  std::cout << "orientation::portrait == " << cen::orientation::portrait << '\n';
}
