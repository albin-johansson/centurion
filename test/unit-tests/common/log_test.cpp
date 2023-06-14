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

#include "centurion/common/logging.hpp"

TEST(Log, SetPriorityAllCategories)
{
  const auto priority = cen::log_priority::critical;
  cen::set_priority(priority);

  ASSERT_EQ(priority, cen::get_priority(cen::log_category::app));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::error));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::assert));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::system));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::audio));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::video));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::render));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::input));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::test));
  ASSERT_EQ(priority, cen::get_priority(cen::log_category::custom));

  cen::reset_log_priorities();
}

TEST(Log, SetPriority)
{
  const auto category = cen::log_category::app;
  const auto priority = cen::log_priority::debug;

  cen::set_priority(category, priority);
  ASSERT_EQ(priority, cen::get_priority(category));

  cen::reset_log_priorities();
}

TEST(Log, GetPriority)
{
  ASSERT_EQ(SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION),
            cen::to_underlying(cen::get_priority(cen::log_category::app)));
}

TEST(Log, MaxMessageSize)
{
  ASSERT_EQ(SDL_MAX_LOG_MESSAGE, cen::max_log_message_size());
}

TEST(Log, Priority)
{
  cen::set_priority(cen::log_priority::verbose);

  cen::log_info("Info message %i", 1);
  cen::log_warn("Warning message %i", 2);
  cen::log_verbose("Verbose message %i", 3);
  cen::log_debug("Debug message %i", 4);
  cen::log_critical("Critical message %i", 5);
  cen::log_error("Error message %i", 6);

  cen::reset_log_priorities();
}

TEST(Log, Macros)
{
  CENTURION_LOG_INFO("%s", "This is for debug only...");
  CENTURION_LOG_WARN("%s", "This is for debug only...");
  CENTURION_LOG_VERBOSE("%s", "This is for debug only...");
  CENTURION_LOG_DEBUG("%s", "This is for debug only...");
  CENTURION_LOG_CRITICAL("%s", "This is for debug only...");
  CENTURION_LOG_ERROR("%s", "This is for debug only...");
}
