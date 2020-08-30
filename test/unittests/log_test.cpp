#include "log.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("Priority test", "[log]")
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

TEST_CASE("log::set_priority(priority)", "[log]")
{
  const auto priority = cen::log::priority::critical;
  cen::log::set_priority(priority);

  CHECK(priority == cen::log::get_priority(cen::log::category::app));
  CHECK(priority == cen::log::get_priority(cen::log::category::error));
  CHECK(priority == cen::log::get_priority(cen::log::category::assert));
  CHECK(priority == cen::log::get_priority(cen::log::category::system));
  CHECK(priority == cen::log::get_priority(cen::log::category::audio));
  CHECK(priority == cen::log::get_priority(cen::log::category::video));
  CHECK(priority == cen::log::get_priority(cen::log::category::render));
  CHECK(priority == cen::log::get_priority(cen::log::category::input));
  CHECK(priority == cen::log::get_priority(cen::log::category::test));
  CHECK(priority == cen::log::get_priority(cen::log::category::misc));

  cen::log::reset_priorities();
}

TEST_CASE("log::set_priority(category, priority)", "[log]")
{
  const auto category = cen::log::category::app;
  const auto priority = cen::log::priority::debug;

  cen::log::set_priority(category, priority);
  CHECK(priority == cen::log::get_priority(category));

  cen::log::reset_priorities();
}

TEST_CASE("log::get_priority", "[log]")
{
  const auto prio = cen::log::get_priority(cen::log::category::app);
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  CHECK(prio == sdlPrio);
}

TEST_CASE("log::max_message_size", "[log]")
{
  CHECK(cen::log::max_message_size() == SDL_MAX_LOG_MESSAGE);
}

TEST_CASE("pog::priority values", "[log]")
{
  SECTION("operator==")
  {
    CHECK(cen::log::priority::info == SDL_LOG_PRIORITY_INFO);
    CHECK(cen::log::priority::warn == SDL_LOG_PRIORITY_WARN);
    CHECK(cen::log::priority::debug == SDL_LOG_PRIORITY_DEBUG);
    CHECK(cen::log::priority::verbose == SDL_LOG_PRIORITY_VERBOSE);
    CHECK(cen::log::priority::critical == SDL_LOG_PRIORITY_CRITICAL);
    CHECK(cen::log::priority::error == SDL_LOG_PRIORITY_ERROR);

    CHECK(SDL_LOG_PRIORITY_INFO == cen::log::priority::info);
    CHECK(SDL_LOG_PRIORITY_WARN == cen::log::priority::warn);
    CHECK(SDL_LOG_PRIORITY_DEBUG == cen::log::priority::debug);
    CHECK(SDL_LOG_PRIORITY_VERBOSE == cen::log::priority::verbose);
    CHECK(SDL_LOG_PRIORITY_CRITICAL == cen::log::priority::critical);
    CHECK(SDL_LOG_PRIORITY_ERROR == cen::log::priority::error);
  }

  SECTION("operator!=")
  {
    CHECK(cen::log::priority::info != SDL_LOG_PRIORITY_DEBUG);
    CHECK(SDL_LOG_PRIORITY_VERBOSE != cen::log::priority::critical);
  }
}

TEST_CASE("log::category values", "[log]")
{
  SECTION("operator==")
  {
    CHECK(cen::log::category::app == SDL_LOG_CATEGORY_APPLICATION);
    CHECK(cen::log::category::error == SDL_LOG_CATEGORY_ERROR);
    CHECK(cen::log::category::assert == SDL_LOG_CATEGORY_ASSERT);
    CHECK(cen::log::category::system == SDL_LOG_CATEGORY_SYSTEM);
    CHECK(cen::log::category::audio == SDL_LOG_CATEGORY_AUDIO);
    CHECK(cen::log::category::video == SDL_LOG_CATEGORY_VIDEO);
    CHECK(cen::log::category::render == SDL_LOG_CATEGORY_RENDER);
    CHECK(cen::log::category::input == SDL_LOG_CATEGORY_INPUT);
    CHECK(cen::log::category::test == SDL_LOG_CATEGORY_TEST);
    CHECK(cen::log::category::misc == SDL_LOG_CATEGORY_CUSTOM);

    CHECK(SDL_LOG_CATEGORY_APPLICATION == cen::log::category::app);
    CHECK(SDL_LOG_CATEGORY_ERROR == cen::log::category::error);
    CHECK(SDL_LOG_CATEGORY_ASSERT == cen::log::category::assert);
    CHECK(SDL_LOG_CATEGORY_SYSTEM == cen::log::category::system);
    CHECK(SDL_LOG_CATEGORY_AUDIO == cen::log::category::audio);
    CHECK(SDL_LOG_CATEGORY_VIDEO == cen::log::category::video);
    CHECK(SDL_LOG_CATEGORY_RENDER == cen::log::category::render);
    CHECK(SDL_LOG_CATEGORY_INPUT == cen::log::category::input);
    CHECK(SDL_LOG_CATEGORY_TEST == cen::log::category::test);
    CHECK(SDL_LOG_CATEGORY_CUSTOM == cen::log::category::misc);
  }
  SECTION("operator!=")
  {
    CHECK(cen::log::category::audio != SDL_LOG_CATEGORY_ERROR);
    CHECK(SDL_LOG_CATEGORY_SYSTEM != cen::log::category::render);
  }
}

TEST_CASE("logging macros", "[log]")
{
  CENTURION_LOG_INFO("%s", "This is for debug only...");
  CENTURION_LOG_WARN("%s", "This is for debug only...");
  CENTURION_LOG_VERBOSE("%s", "This is for debug only...");
  CENTURION_LOG_DEBUG("%s", "This is for debug only...");
  CENTURION_LOG_CRITICAL("%s", "This is for debug only...");
  CENTURION_LOG_ERROR("%s", "This is for debug only...");
}
