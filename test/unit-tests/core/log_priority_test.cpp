#include "core/log_priority.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(LogPriority, Values)
{
  ASSERT_EQ(cen::log_priority::info, SDL_LOG_PRIORITY_INFO);
  ASSERT_EQ(cen::log_priority::warn, SDL_LOG_PRIORITY_WARN);
  ASSERT_EQ(cen::log_priority::debug, SDL_LOG_PRIORITY_DEBUG);
  ASSERT_EQ(cen::log_priority::verbose, SDL_LOG_PRIORITY_VERBOSE);
  ASSERT_EQ(cen::log_priority::critical, SDL_LOG_PRIORITY_CRITICAL);
  ASSERT_EQ(cen::log_priority::error, SDL_LOG_PRIORITY_ERROR);

  ASSERT_EQ(SDL_LOG_PRIORITY_INFO, cen::log_priority::info);
  ASSERT_EQ(SDL_LOG_PRIORITY_WARN, cen::log_priority::warn);
  ASSERT_EQ(SDL_LOG_PRIORITY_DEBUG, cen::log_priority::debug);
  ASSERT_EQ(SDL_LOG_PRIORITY_VERBOSE, cen::log_priority::verbose);
  ASSERT_EQ(SDL_LOG_PRIORITY_CRITICAL, cen::log_priority::critical);
  ASSERT_EQ(SDL_LOG_PRIORITY_ERROR, cen::log_priority::error);

  ASSERT_NE(cen::log_priority::info, SDL_LOG_PRIORITY_DEBUG);
  ASSERT_NE(SDL_LOG_PRIORITY_VERBOSE, cen::log_priority::critical);
}

TEST(LogPriority, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::log_priority>(SDL_NUM_LOG_PRIORITIES)),
               cen::cen_error);

  ASSERT_EQ("verbose", cen::to_string(cen::log_priority::verbose));
  ASSERT_EQ("debug", cen::to_string(cen::log_priority::debug));
  ASSERT_EQ("info", cen::to_string(cen::log_priority::info));
  ASSERT_EQ("warn", cen::to_string(cen::log_priority::warn));
  ASSERT_EQ("error", cen::to_string(cen::log_priority::error));
  ASSERT_EQ("critical", cen::to_string(cen::log_priority::critical));

  std::cout << "Log priority example: " << cen::log_priority::info << '\n';
}

TEST(LogPriority, LogPriorityCount)
{
  ASSERT_EQ(SDL_NUM_LOG_PRIORITIES, cen::log_priority_count());
}