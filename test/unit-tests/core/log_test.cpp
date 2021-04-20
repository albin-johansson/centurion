#include "core/log.hpp"

#include <gtest/gtest.h>

TEST(Log, SetPriorityAllCategories)
{
  const auto priority = cen::log::priority::critical;
  cen::log::set_priority(priority);

  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::app));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::error));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::assert));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::system));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::audio));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::video));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::render));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::input));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::test));
  EXPECT_EQ(priority, cen::log::get_priority(cen::log::category::misc));

  cen::log::reset_priorities();
}

TEST(Log, SetPriority)
{
  const auto category = cen::log::category::app;
  const auto priority = cen::log::priority::debug;

  cen::log::set_priority(category, priority);
  EXPECT_EQ(priority, cen::log::get_priority(category));

  cen::log::reset_priorities();
}

TEST(Log, GetPriority)
{
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  EXPECT_EQ(sdlPrio, cen::log::get_priority(cen::log::category::app));
}

TEST(Log, MaxMessageSize)
{
  EXPECT_EQ(SDL_MAX_LOG_MESSAGE, cen::log::max_message_size());
}

TEST(Log, Priority)
{
  cen::log::set_priority(cen::log::priority::verbose);

  cen::log::info("Info message %i", 1);
  cen::log::warn("Warning message %i", 2);
  cen::log::verbose("Verbose message %i", 3);
  cen::log::debug("Debug message %i", 4);
  cen::log::critical("Critical message %i", 5);
  cen::log::error("Error message %i", 6);

  cen::log::reset_priorities();
}

TEST(Log, PriorityEqualityOperator)
{
  EXPECT_EQ(cen::log::priority::info, SDL_LOG_PRIORITY_INFO);
  EXPECT_EQ(cen::log::priority::warn, SDL_LOG_PRIORITY_WARN);
  EXPECT_EQ(cen::log::priority::debug, SDL_LOG_PRIORITY_DEBUG);
  EXPECT_EQ(cen::log::priority::verbose, SDL_LOG_PRIORITY_VERBOSE);
  EXPECT_EQ(cen::log::priority::critical, SDL_LOG_PRIORITY_CRITICAL);
  EXPECT_EQ(cen::log::priority::error, SDL_LOG_PRIORITY_ERROR);

  EXPECT_EQ(SDL_LOG_PRIORITY_INFO, cen::log::priority::info);
  EXPECT_EQ(SDL_LOG_PRIORITY_WARN, cen::log::priority::warn);
  EXPECT_EQ(SDL_LOG_PRIORITY_DEBUG, cen::log::priority::debug);
  EXPECT_EQ(SDL_LOG_PRIORITY_VERBOSE, cen::log::priority::verbose);
  EXPECT_EQ(SDL_LOG_PRIORITY_CRITICAL, cen::log::priority::critical);
  EXPECT_EQ(SDL_LOG_PRIORITY_ERROR, cen::log::priority::error);
}

TEST(Log, PriorityInequalityOperator)
{
  EXPECT_NE(cen::log::priority::info, SDL_LOG_PRIORITY_DEBUG);
  EXPECT_NE(SDL_LOG_PRIORITY_VERBOSE, cen::log::priority::critical);
}

TEST(Log, CategoryEqualityOperator)
{
  EXPECT_EQ(cen::log::category::app, SDL_LOG_CATEGORY_APPLICATION);
  EXPECT_EQ(cen::log::category::error, SDL_LOG_CATEGORY_ERROR);
  EXPECT_EQ(cen::log::category::assert, SDL_LOG_CATEGORY_ASSERT);
  EXPECT_EQ(cen::log::category::system, SDL_LOG_CATEGORY_SYSTEM);
  EXPECT_EQ(cen::log::category::audio, SDL_LOG_CATEGORY_AUDIO);
  EXPECT_EQ(cen::log::category::video, SDL_LOG_CATEGORY_VIDEO);
  EXPECT_EQ(cen::log::category::render, SDL_LOG_CATEGORY_RENDER);
  EXPECT_EQ(cen::log::category::input, SDL_LOG_CATEGORY_INPUT);
  EXPECT_EQ(cen::log::category::test, SDL_LOG_CATEGORY_TEST);
  EXPECT_EQ(cen::log::category::misc, SDL_LOG_CATEGORY_CUSTOM);

  EXPECT_EQ(SDL_LOG_CATEGORY_APPLICATION, cen::log::category::app);
  EXPECT_EQ(SDL_LOG_CATEGORY_ERROR, cen::log::category::error);
  EXPECT_EQ(SDL_LOG_CATEGORY_ASSERT, cen::log::category::assert);
  EXPECT_EQ(SDL_LOG_CATEGORY_SYSTEM, cen::log::category::system);
  EXPECT_EQ(SDL_LOG_CATEGORY_AUDIO, cen::log::category::audio);
  EXPECT_EQ(SDL_LOG_CATEGORY_VIDEO, cen::log::category::video);
  EXPECT_EQ(SDL_LOG_CATEGORY_RENDER, cen::log::category::render);
  EXPECT_EQ(SDL_LOG_CATEGORY_INPUT, cen::log::category::input);
  EXPECT_EQ(SDL_LOG_CATEGORY_TEST, cen::log::category::test);
  EXPECT_EQ(SDL_LOG_CATEGORY_CUSTOM, cen::log::category::misc);
}

TEST(Log, CategoryInequalityOperator)
{
  EXPECT_NE(cen::log::category::audio, SDL_LOG_CATEGORY_ERROR);
  EXPECT_NE(SDL_LOG_CATEGORY_SYSTEM, cen::log::category::render);
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
