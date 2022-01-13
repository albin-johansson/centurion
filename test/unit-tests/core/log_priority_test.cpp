#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "core/logging.hpp"

TEST(LogPriority, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::info), SDL_LOG_PRIORITY_INFO);
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::warn), SDL_LOG_PRIORITY_WARN);
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::debug), SDL_LOG_PRIORITY_DEBUG);
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::verbose), SDL_LOG_PRIORITY_VERBOSE);
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::critical), SDL_LOG_PRIORITY_CRITICAL);
  ASSERT_EQ(cen::ToUnderlying(cen::log_priority::error), SDL_LOG_PRIORITY_ERROR);
}

TEST(LogPriority, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::log_priority>(SDL_NUM_LOG_PRIORITIES)),
               cen::Error);

  ASSERT_EQ("verbose", cen::ToString(cen::log_priority::verbose));
  ASSERT_EQ("debug", cen::ToString(cen::log_priority::debug));
  ASSERT_EQ("info", cen::ToString(cen::log_priority::info));
  ASSERT_EQ("warn", cen::ToString(cen::log_priority::warn));
  ASSERT_EQ("error", cen::ToString(cen::log_priority::error));
  ASSERT_EQ("critical", cen::ToString(cen::log_priority::critical));

  std::clog << "Log priority example: " << cen::log_priority::info << '\n';
}

TEST(LogPriority, LogPriorityCount)
{
  ASSERT_EQ(SDL_NUM_LOG_PRIORITIES, cen::log_priority_count());
}