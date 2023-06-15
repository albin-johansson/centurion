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

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST(FlashOp, Values)
{
  ASSERT_EQ(SDL_FLASH_CANCEL, to_underlying(cen::flash_op::cancel));
  ASSERT_EQ(SDL_FLASH_BRIEFLY, to_underlying(cen::flash_op::briefly));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, to_underlying(cen::flash_op::until_focused));
}

TEST(FlashOp, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::flash_op>(42)), cen::exception);

  ASSERT_EQ("cancel", to_string(cen::flash_op::cancel));
  ASSERT_EQ("briefly", to_string(cen::flash_op::briefly));
  ASSERT_EQ("until_focused", to_string(cen::flash_op::until_focused));

  std::cout << "flash_op::briefly == " << cen::flash_op::briefly << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)