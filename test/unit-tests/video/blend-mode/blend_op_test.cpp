/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

TEST(BlendOp, Values)
{
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, to_underlying(cen::blend_op::add));
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, to_underlying(cen::blend_op::sub));
  ASSERT_EQ(SDL_BLENDOPERATION_REV_SUBTRACT, to_underlying(cen::blend_op::reverse_sub));
  ASSERT_EQ(SDL_BLENDOPERATION_MINIMUM, to_underlying(cen::blend_op::min));
  ASSERT_EQ(SDL_BLENDOPERATION_MAXIMUM, to_underlying(cen::blend_op::max));
}

TEST(BlendOp, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_op>(42)), cen::exception);

  ASSERT_EQ("add", to_string(cen::blend_op::add));
  ASSERT_EQ("sub", to_string(cen::blend_op::sub));
  ASSERT_EQ("reverse_sub", to_string(cen::blend_op::reverse_sub));
  ASSERT_EQ("min", to_string(cen::blend_op::min));
  ASSERT_EQ("max", to_string(cen::blend_op::max));

  std::cout << "blend_op::add == " << cen::blend_op::add << '\n';
}
