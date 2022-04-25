#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/logging.hpp"

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
