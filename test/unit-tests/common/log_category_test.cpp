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

#include "centurion/logging.hpp"

TEST(LogCategory, Values)
{
  ASSERT_EQ(SDL_LOG_CATEGORY_APPLICATION, to_underlying(cen::log_category::app));
  ASSERT_EQ(SDL_LOG_CATEGORY_ERROR, to_underlying(cen::log_category::error));
  ASSERT_EQ(SDL_LOG_CATEGORY_ASSERT, to_underlying(cen::log_category::assert));
  ASSERT_EQ(SDL_LOG_CATEGORY_SYSTEM, to_underlying(cen::log_category::system));
  ASSERT_EQ(SDL_LOG_CATEGORY_AUDIO, to_underlying(cen::log_category::audio));
  ASSERT_EQ(SDL_LOG_CATEGORY_VIDEO, to_underlying(cen::log_category::video));
  ASSERT_EQ(SDL_LOG_CATEGORY_RENDER, to_underlying(cen::log_category::render));
  ASSERT_EQ(SDL_LOG_CATEGORY_INPUT, to_underlying(cen::log_category::input));
  ASSERT_EQ(SDL_LOG_CATEGORY_TEST, to_underlying(cen::log_category::test));
  ASSERT_EQ(SDL_LOG_CATEGORY_CUSTOM, to_underlying(cen::log_category::custom));
}

TEST(LogCategory, ToString)
{
  ASSERT_THROW(to_string(cen::log_category(SDL_LOG_CATEGORY_RESERVED1)), cen::exception);

  ASSERT_EQ("app", to_string(cen::log_category::app));
  ASSERT_EQ("error", to_string(cen::log_category::error));
  ASSERT_EQ("assert", to_string(cen::log_category::assert));
  ASSERT_EQ("system", to_string(cen::log_category::system));
  ASSERT_EQ("audio", to_string(cen::log_category::audio));
  ASSERT_EQ("video", to_string(cen::log_category::video));
  ASSERT_EQ("render", to_string(cen::log_category::render));
  ASSERT_EQ("input", to_string(cen::log_category::input));
  ASSERT_EQ("test", to_string(cen::log_category::test));

  ASSERT_EQ("custom", to_string(cen::log_category::custom));
  ASSERT_EQ("custom", to_string(cen::log_category(SDL_LOG_CATEGORY_CUSTOM + 1)));

  std::cout << "log_category::video == " << cen::log_category::video << '\n';
}