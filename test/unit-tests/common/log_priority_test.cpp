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

#include "centurion/common/logging.hpp"
#include "centurion/common/utils.hpp"

TEST(LogPriority, Values)
{
  ASSERT_EQ(SDL_LOG_PRIORITY_INFO, to_underlying(cen::log_priority::info));
  ASSERT_EQ(SDL_LOG_PRIORITY_WARN, to_underlying(cen::log_priority::warn));
  ASSERT_EQ(SDL_LOG_PRIORITY_DEBUG, to_underlying(cen::log_priority::debug));
  ASSERT_EQ(SDL_LOG_PRIORITY_VERBOSE, to_underlying(cen::log_priority::verbose));
  ASSERT_EQ(SDL_LOG_PRIORITY_CRITICAL, to_underlying(cen::log_priority::critical));
  ASSERT_EQ(SDL_LOG_PRIORITY_ERROR, to_underlying(cen::log_priority::error));
}

TEST(LogPriority, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::log_priority>(SDL_NUM_LOG_PRIORITIES)),
               cen::exception);

  ASSERT_EQ("verbose", to_string(cen::log_priority::verbose));
  ASSERT_EQ("debug", to_string(cen::log_priority::debug));
  ASSERT_EQ("info", to_string(cen::log_priority::info));
  ASSERT_EQ("warn", to_string(cen::log_priority::warn));
  ASSERT_EQ("error", to_string(cen::log_priority::error));
  ASSERT_EQ("critical", to_string(cen::log_priority::critical));

  std::cout << "log_priority::info == " << cen::log_priority::info << '\n';
}
