#include "log.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Log priority test", "[Log]")
{
  log::set_priority(log::priority::verbose);

  log::info("Info message %i", 1);
  log::warn("Warning message %i", 2);
  log::verbose("Verbose message %i", 3);
  log::debug("Debug message %i", 4);
  log::critical("Critical message %i", 5);
  log::error("Error message %i", 6);

  log::reset_priorities();
}

TEST_CASE("Log::set_priority(Priority)", "[Log]")
{
  const auto priority = log::priority::critical;
  log::set_priority(priority);

  CHECK(priority == log::priority(log::category::app));
  CHECK(priority == log::priority(log::category::error));
  CHECK(priority == log::priority(log::category::assert));
  CHECK(priority == log::priority(log::category::system));
  CHECK(priority == log::priority(log::category::audio));
  CHECK(priority == log::priority(log::category::video));
  CHECK(priority == log::priority(log::category::render));
  CHECK(priority == log::priority(log::category::input));
  CHECK(priority == log::priority(log::category::test));
  CHECK(priority == log::priority(log::category::misc));

  log::reset_priorities();
}

TEST_CASE("Log::set_priority(Category, Priority)", "[Log]")
{
  const auto category = log::category::app;
  const auto priority = log::priority::debug;

  log::set_priority(category, priority);
  CHECK(priority == log::priority(category));

  log::reset_priorities();
}

TEST_CASE("Log::priority", "[Log]")
{
  const auto prio = log::priority(log::category::app);
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  CHECK(prio == sdlPrio);
}

TEST_CASE("Log::max_message_size", "[Log]")
{
  CHECK(log::max_message_size() == SDL_MAX_LOG_MESSAGE);
}

TEST_CASE("Log::Priority", "[Log]")
{
  SECTION("operator==")
  {
    CHECK(log::priority::info == SDL_LOG_PRIORITY_INFO);
    CHECK(log::priority::warn == SDL_LOG_PRIORITY_WARN);
    CHECK(log::priority::debug == SDL_LOG_PRIORITY_DEBUG);
    CHECK(log::priority::verbose == SDL_LOG_PRIORITY_VERBOSE);
    CHECK(log::priority::critical == SDL_LOG_PRIORITY_CRITICAL);
    CHECK(log::priority::error == SDL_LOG_PRIORITY_ERROR);

    CHECK(SDL_LOG_PRIORITY_INFO == log::priority::info);
    CHECK(SDL_LOG_PRIORITY_WARN == log::priority::warn);
    CHECK(SDL_LOG_PRIORITY_DEBUG == log::priority::debug);
    CHECK(SDL_LOG_PRIORITY_VERBOSE == log::priority::verbose);
    CHECK(SDL_LOG_PRIORITY_CRITICAL == log::priority::critical);
    CHECK(SDL_LOG_PRIORITY_ERROR == log::priority::error);
  }

  SECTION("operator!=")
  {
    CHECK(log::priority::info != SDL_LOG_PRIORITY_DEBUG);
    CHECK(SDL_LOG_PRIORITY_VERBOSE != log::priority::critical);
  }
}

TEST_CASE("Log::Category", "[Log]")
{
  SECTION("operator==")
  {
    CHECK(log::category::app == SDL_LOG_CATEGORY_APPLICATION);
    CHECK(log::category::error == SDL_LOG_CATEGORY_ERROR);
    CHECK(log::category::assert == SDL_LOG_CATEGORY_ASSERT);
    CHECK(log::category::system == SDL_LOG_CATEGORY_SYSTEM);
    CHECK(log::category::audio == SDL_LOG_CATEGORY_AUDIO);
    CHECK(log::category::video == SDL_LOG_CATEGORY_VIDEO);
    CHECK(log::category::render == SDL_LOG_CATEGORY_RENDER);
    CHECK(log::category::input == SDL_LOG_CATEGORY_INPUT);
    CHECK(log::category::test == SDL_LOG_CATEGORY_TEST);
    CHECK(log::category::misc == SDL_LOG_CATEGORY_CUSTOM);

    CHECK(SDL_LOG_CATEGORY_APPLICATION == log::category::app);
    CHECK(SDL_LOG_CATEGORY_ERROR == log::category::error);
    CHECK(SDL_LOG_CATEGORY_ASSERT == log::category::assert);
    CHECK(SDL_LOG_CATEGORY_SYSTEM == log::category::system);
    CHECK(SDL_LOG_CATEGORY_AUDIO == log::category::audio);
    CHECK(SDL_LOG_CATEGORY_VIDEO == log::category::video);
    CHECK(SDL_LOG_CATEGORY_RENDER == log::category::render);
    CHECK(SDL_LOG_CATEGORY_INPUT == log::category::input);
    CHECK(SDL_LOG_CATEGORY_TEST == log::category::test);
    CHECK(SDL_LOG_CATEGORY_CUSTOM == log::category::misc);
  }
  SECTION("operator!=")
  {
    CHECK(log::category::audio != SDL_LOG_CATEGORY_ERROR);
    CHECK(SDL_LOG_CATEGORY_SYSTEM != log::category::render);
  }
}
