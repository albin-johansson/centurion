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

#include "centurion/io/file_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(FileType, Values)
{
  ASSERT_EQ(SDL_RWOPS_UNKNOWN, to_underlying(cen::file_type::unknown));
  ASSERT_EQ(SDL_RWOPS_WINFILE, to_underlying(cen::file_type::win));
  ASSERT_EQ(SDL_RWOPS_STDFILE, to_underlying(cen::file_type::std));
  ASSERT_EQ(SDL_RWOPS_JNIFILE, to_underlying(cen::file_type::jni));
  ASSERT_EQ(SDL_RWOPS_MEMORY, to_underlying(cen::file_type::memory));
  ASSERT_EQ(SDL_RWOPS_MEMORY_RO, to_underlying(cen::file_type::memory_ro));
}

TEST(FileType, ToString)
{
  ASSERT_EQ("unknown", to_string(cen::file_type::unknown));
  ASSERT_EQ("win", to_string(cen::file_type::win));
  ASSERT_EQ("std", to_string(cen::file_type::std));
  ASSERT_EQ("jni", to_string(cen::file_type::jni));
  ASSERT_EQ("memory", to_string(cen::file_type::memory));
  ASSERT_EQ("memory_ro", to_string(cen::file_type::memory_ro));

  std::cout << "file_type::std == " << cen::file_type::std << '\n';
}