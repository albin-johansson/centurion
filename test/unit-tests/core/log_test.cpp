#include <gtest/gtest.h>

#include "core/logging.hpp"
#include "core/to_underlying.hpp"

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
