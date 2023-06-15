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

#include "centurion/video/window.hpp"

TEST(WindowHandle, PointerConstructor)
{
  {  // From null pointer
    cen::window_handle handle {nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // From valid pointer
    cen::window window;
    cen::window_handle handle {window.get()};
    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST(WindowHandle, FromWindowRef)
{
  cen::window window;
  cen::window_handle handle {window};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST(WindowHandle, StreamOperator)
{
  cen::window window;
  cen::window_handle handle {window};

  std::cout << handle << '\n';
}