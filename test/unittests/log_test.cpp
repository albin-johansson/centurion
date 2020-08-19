#include "log.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("Priority test", "[log]")
{
  ctn::log::set_priority(ctn::log::priority::verbose);

  ctn::log::info("Info message %i", 1);
  ctn::log::warn("Warning message %i", 2);
  ctn::log::verbose("Verbose message %i", 3);
  ctn::log::debug("Debug message %i", 4);
  ctn::log::critical("Critical message %i", 5);
  ctn::log::error("Error message %i", 6);

  ctn::log::reset_priorities();
}

TEST_CASE("log::set_priority(priority)", "[log]")
{
  const auto priority = ctn::log::priority::critical;
  ctn::log::set_priority(priority);

  CHECK(priority == ctn::log::get_priority(ctn::log::category::app));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::error));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::assert));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::system));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::audio));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::video));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::render));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::input));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::test));
  CHECK(priority == ctn::log::get_priority(ctn::log::category::misc));

  ctn::log::reset_priorities();
}

TEST_CASE("log::set_priority(category, priority)", "[log]")
{
  const auto category = ctn::log::category::app;
  const auto priority = ctn::log::priority::debug;

  ctn::log::set_priority(category, priority);
  CHECK(priority == ctn::log::get_priority(category));

  ctn::log::reset_priorities();
}

TEST_CASE("log::get_priority", "[log]")
{
  const auto prio = ctn::log::get_priority(ctn::log::category::app);
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  CHECK(prio == sdlPrio);
}

TEST_CASE("log::max_message_size", "[log]")
{
  CHECK(ctn::log::max_message_size() == SDL_MAX_LOG_MESSAGE);
}

TEST_CASE("pog::priority values", "[log]")
{
  SECTION("operator==")
  {
    CHECK(ctn::log::priority::info == SDL_LOG_PRIORITY_INFO);
    CHECK(ctn::log::priority::warn == SDL_LOG_PRIORITY_WARN);
    CHECK(ctn::log::priority::debug == SDL_LOG_PRIORITY_DEBUG);
    CHECK(ctn::log::priority::verbose == SDL_LOG_PRIORITY_VERBOSE);
    CHECK(ctn::log::priority::critical == SDL_LOG_PRIORITY_CRITICAL);
    CHECK(ctn::log::priority::error == SDL_LOG_PRIORITY_ERROR);

    CHECK(SDL_LOG_PRIORITY_INFO == ctn::log::priority::info);
    CHECK(SDL_LOG_PRIORITY_WARN == ctn::log::priority::warn);
    CHECK(SDL_LOG_PRIORITY_DEBUG == ctn::log::priority::debug);
    CHECK(SDL_LOG_PRIORITY_VERBOSE == ctn::log::priority::verbose);
    CHECK(SDL_LOG_PRIORITY_CRITICAL == ctn::log::priority::critical);
    CHECK(SDL_LOG_PRIORITY_ERROR == ctn::log::priority::error);
  }

  SECTION("operator!=")
  {
    CHECK(ctn::log::priority::info != SDL_LOG_PRIORITY_DEBUG);
    CHECK(SDL_LOG_PRIORITY_VERBOSE != ctn::log::priority::critical);
  }
}

TEST_CASE("log::category values", "[log]")
{
  SECTION("operator==")
  {
    CHECK(ctn::log::category::app == SDL_LOG_CATEGORY_APPLICATION);
    CHECK(ctn::log::category::error == SDL_LOG_CATEGORY_ERROR);
    CHECK(ctn::log::category::assert == SDL_LOG_CATEGORY_ASSERT);
    CHECK(ctn::log::category::system == SDL_LOG_CATEGORY_SYSTEM);
    CHECK(ctn::log::category::audio == SDL_LOG_CATEGORY_AUDIO);
    CHECK(ctn::log::category::video == SDL_LOG_CATEGORY_VIDEO);
    CHECK(ctn::log::category::render == SDL_LOG_CATEGORY_RENDER);
    CHECK(ctn::log::category::input == SDL_LOG_CATEGORY_INPUT);
    CHECK(ctn::log::category::test == SDL_LOG_CATEGORY_TEST);
    CHECK(ctn::log::category::misc == SDL_LOG_CATEGORY_CUSTOM);

    CHECK(SDL_LOG_CATEGORY_APPLICATION == ctn::log::category::app);
    CHECK(SDL_LOG_CATEGORY_ERROR == ctn::log::category::error);
    CHECK(SDL_LOG_CATEGORY_ASSERT == ctn::log::category::assert);
    CHECK(SDL_LOG_CATEGORY_SYSTEM == ctn::log::category::system);
    CHECK(SDL_LOG_CATEGORY_AUDIO == ctn::log::category::audio);
    CHECK(SDL_LOG_CATEGORY_VIDEO == ctn::log::category::video);
    CHECK(SDL_LOG_CATEGORY_RENDER == ctn::log::category::render);
    CHECK(SDL_LOG_CATEGORY_INPUT == ctn::log::category::input);
    CHECK(SDL_LOG_CATEGORY_TEST == ctn::log::category::test);
    CHECK(SDL_LOG_CATEGORY_CUSTOM == ctn::log::category::misc);
  }
  SECTION("operator!=")
  {
    CHECK(ctn::log::category::audio != SDL_LOG_CATEGORY_ERROR);
    CHECK(SDL_LOG_CATEGORY_SYSTEM != ctn::log::category::render);
  }
}

TEST_CASE("logging macros", "[log]")
{
  CENTURION_LOG_INFO("This is for debug only...");
  CENTURION_LOG_WARN("This is for debug only...");
  CENTURION_LOG_VERBOSE("This is for debug only...");
  CENTURION_LOG_DEBUG("This is for debug only...");
  CENTURION_LOG_CRITICAL("This is for debug only...");
  CENTURION_LOG_ERROR("This is for debug only...");
}
