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

TEST(BlendMode, Values)
{
  ASSERT_EQ(SDL_BLENDMODE_NONE, to_underlying(cen::blend_mode::none));
  ASSERT_EQ(SDL_BLENDMODE_BLEND, to_underlying(cen::blend_mode::blend));
  ASSERT_EQ(SDL_BLENDMODE_ADD, to_underlying(cen::blend_mode::add));
  ASSERT_EQ(SDL_BLENDMODE_MOD, to_underlying(cen::blend_mode::mod));
  ASSERT_EQ(SDL_BLENDMODE_INVALID, to_underlying(cen::blend_mode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(SDL_BLENDMODE_MUL, to_underlying(cen::blend_mode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
}

TEST(BlendMode, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_mode>(SDL_BLENDMODE_INVALID - 1)),
               cen::exception);

  ASSERT_EQ("none", to_string(cen::blend_mode::none));
  ASSERT_EQ("blend", to_string(cen::blend_mode::blend));
  ASSERT_EQ("add", to_string(cen::blend_mode::add));
  ASSERT_EQ("mod", to_string(cen::blend_mode::mod));
  ASSERT_EQ("invalid", to_string(cen::blend_mode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ("mul", to_string(cen::blend_mode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  std::cout << "blend_mode::blend == " << cen::blend_mode::blend << '\n';
}