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

#include "centurion/video/texture.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ScaleMode, Values)
{
  ASSERT_EQ(SDL_ScaleModeLinear, to_underlying(cen::scale_mode::linear));
  ASSERT_EQ(SDL_ScaleModeNearest, to_underlying(cen::scale_mode::nearest));
  ASSERT_EQ(SDL_ScaleModeBest, to_underlying(cen::scale_mode::best));
}

TEST(ScaleMode, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::scale_mode>(4)), cen::exception);

  ASSERT_EQ("nearest", to_string(cen::scale_mode::nearest));
  ASSERT_EQ("linear", to_string(cen::scale_mode::linear));
  ASSERT_EQ("best", to_string(cen::scale_mode::best));

  std::cout << "scale_mode::linear == " << cen::scale_mode::linear << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)