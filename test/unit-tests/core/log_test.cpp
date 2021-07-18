#include "core/log.hpp"

#include <gtest/gtest.h>

#include "core/log_macros.hpp"

TEST(Log, SetPriorityAllCategories)
{
  const auto priority = cen::log_priority::critical;
  cen::log::set_priority(priority);

  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::app));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::error));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::assert));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::system));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::audio));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::video));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::render));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::input));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::test));
  ASSERT_EQ(priority, cen::log::get_priority(cen::log_category::misc));

  cen::log::reset_priorities();
}

TEST(Log, SetPriority)
{
  const auto category = cen::log_category::app;
  const auto priority = cen::log_priority::debug;

  cen::log::set_priority(category, priority);
  ASSERT_EQ(priority, cen::log::get_priority(category));

  cen::log::reset_priorities();
}

TEST(Log, GetPriority)
{
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  ASSERT_EQ(sdlPrio, cen::log::get_priority(cen::log_category::app));
}

TEST(Log, MaxMessageSize)
{
  ASSERT_EQ(SDL_MAX_LOG_MESSAGE, cen::log::max_message_size());
}

TEST(Log, Priority)
{
  cen::log::set_priority(cen::log_priority::verbose);

  cen::log::info("Info message %i", 1);
  cen::log::warn("Warning message %i", 2);
  cen::log::verbose("Verbose message %i", 3);
  cen::log::debug("Debug message %i", 4);
  cen::log::critical("Critical message %i", 5);
  cen::log::error("Error message %i", 6);

  cen::log::reset_priorities();
}

TEST(Log, CategoryEqualityOperator)
{
  ASSERT_EQ(cen::log_category::app, SDL_LOG_CATEGORY_APPLICATION);
  ASSERT_EQ(cen::log_category::error, SDL_LOG_CATEGORY_ERROR);
  ASSERT_EQ(cen::log_category::assert, SDL_LOG_CATEGORY_ASSERT);
  ASSERT_EQ(cen::log_category::system, SDL_LOG_CATEGORY_SYSTEM);
  ASSERT_EQ(cen::log_category::audio, SDL_LOG_CATEGORY_AUDIO);
  ASSERT_EQ(cen::log_category::video, SDL_LOG_CATEGORY_VIDEO);
  ASSERT_EQ(cen::log_category::render, SDL_LOG_CATEGORY_RENDER);
  ASSERT_EQ(cen::log_category::input, SDL_LOG_CATEGORY_INPUT);
  ASSERT_EQ(cen::log_category::test, SDL_LOG_CATEGORY_TEST);
  ASSERT_EQ(cen::log_category::misc, SDL_LOG_CATEGORY_CUSTOM);

  ASSERT_EQ(SDL_LOG_CATEGORY_APPLICATION, cen::log_category::app);
  ASSERT_EQ(SDL_LOG_CATEGORY_ERROR, cen::log_category::error);
  ASSERT_EQ(SDL_LOG_CATEGORY_ASSERT, cen::log_category::assert);
  ASSERT_EQ(SDL_LOG_CATEGORY_SYSTEM, cen::log_category::system);
  ASSERT_EQ(SDL_LOG_CATEGORY_AUDIO, cen::log_category::audio);
  ASSERT_EQ(SDL_LOG_CATEGORY_VIDEO, cen::log_category::video);
  ASSERT_EQ(SDL_LOG_CATEGORY_RENDER, cen::log_category::render);
  ASSERT_EQ(SDL_LOG_CATEGORY_INPUT, cen::log_category::input);
  ASSERT_EQ(SDL_LOG_CATEGORY_TEST, cen::log_category::test);
  ASSERT_EQ(SDL_LOG_CATEGORY_CUSTOM, cen::log_category::misc);
}

TEST(Log, CategoryInequalityOperator)
{
  ASSERT_NE(cen::log_category::audio, SDL_LOG_CATEGORY_ERROR);
  ASSERT_NE(SDL_LOG_CATEGORY_SYSTEM, cen::log_category::render);
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
