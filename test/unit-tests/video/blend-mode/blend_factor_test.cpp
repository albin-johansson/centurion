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

TEST(BlendFactor, Values)
{
  ASSERT_EQ(SDL_BLENDFACTOR_ZERO, to_underlying(cen::blend_factor::zero));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE, to_underlying(cen::blend_factor::one));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, to_underlying(cen::blend_factor::src_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
            to_underlying(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, to_underlying(cen::blend_factor::src_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            to_underlying(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, to_underlying(cen::blend_factor::dst_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
            to_underlying(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_ALPHA, to_underlying(cen::blend_factor::dst_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
            to_underlying(cen::blend_factor::one_minus_dst_alpha));
}

TEST(BlendFactor, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_factor>(100)), cen::exception);

  ASSERT_EQ("zero", to_string(cen::blend_factor::zero));
  ASSERT_EQ("one", to_string(cen::blend_factor::one));

  ASSERT_EQ("src_color", to_string(cen::blend_factor::src_color));
  ASSERT_EQ("one_minus_src_color", to_string(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ("src_alpha", to_string(cen::blend_factor::src_alpha));
  ASSERT_EQ("one_minus_src_alpha", to_string(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ("dst_color", to_string(cen::blend_factor::dst_color));
  ASSERT_EQ("one_minus_dst_color", to_string(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ("dst_alpha", to_string(cen::blend_factor::dst_alpha));
  ASSERT_EQ("one_minus_dst_alpha", to_string(cen::blend_factor::one_minus_dst_alpha));

  std::cout << "blend_factor::src_color == " << cen::blend_factor::src_color << '\n';
}
