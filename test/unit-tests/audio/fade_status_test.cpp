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

#include "centurion/audio.hpp"
#include "centurion/common/utils.hpp"

TEST(FadeStatus, Values)
{
  ASSERT_EQ(MIX_NO_FADING, to_underlying(cen::fade_status::none));
  ASSERT_EQ(MIX_FADING_IN, to_underlying(cen::fade_status::in));
  ASSERT_EQ(MIX_FADING_OUT, to_underlying(cen::fade_status::out));
}

TEST(FadeStatus, ToString)
{
  ASSERT_EQ("none", to_string(cen::fade_status::none));
  ASSERT_EQ("in", to_string(cen::fade_status::in));
  ASSERT_EQ("out", to_string(cen::fade_status::out));

  std::cout << "fade_status::in == " << cen::fade_status::in << '\n';
}
