#include "log.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Log priority test", "[Log]")
{
  Log::set_priority(Log::Priority::Verbose);

  Log::info("Info message %i", 1);
  Log::warn("Warning message %i", 2);
  Log::verbose("Verbose message %i", 3);
  Log::debug("Debug message %i", 4);
  Log::critical("Critical message %i", 5);
  Log::error("Error message %i", 6);

  Log::reset_priorities();
}

TEST_CASE("Log::set_priority(Priority)", "[Log]")
{
  const auto priority = Log::Priority::Critical;
  Log::set_priority(priority);

  CHECK(priority == Log::priority(Log::Category::App));
  CHECK(priority == Log::priority(Log::Category::Error));
  CHECK(priority == Log::priority(Log::Category::Assert));
  CHECK(priority == Log::priority(Log::Category::System));
  CHECK(priority == Log::priority(Log::Category::Audio));
  CHECK(priority == Log::priority(Log::Category::Video));
  CHECK(priority == Log::priority(Log::Category::Render));
  CHECK(priority == Log::priority(Log::Category::Input));
  CHECK(priority == Log::priority(Log::Category::Test));
  CHECK(priority == Log::priority(Log::Category::Misc));

  Log::reset_priorities();
}

TEST_CASE("Log::set_priority(Category, Priority)", "[Log]")
{
  const auto category = Log::Category::App;
  const auto priority = Log::Priority::Debug;

  Log::set_priority(category, priority);
  CHECK(priority == Log::priority(category));

  Log::reset_priorities();
}

TEST_CASE("Log::priority", "[Log]")
{
  const auto prio = Log::priority(Log::Category::App);
  const auto sdlPrio = SDL_LogGetPriority(SDL_LOG_CATEGORY_APPLICATION);
  CHECK(prio == sdlPrio);
}

TEST_CASE("Log::max_message_size", "[Log]")
{
  CHECK(Log::max_message_size() == SDL_MAX_LOG_MESSAGE);
}

TEST_CASE("Log::Priority", "[Log]")
{
  SECTION("operator==")
  {
    CHECK(Log::Priority::Info == SDL_LOG_PRIORITY_INFO);
    CHECK(Log::Priority::Warn == SDL_LOG_PRIORITY_WARN);
    CHECK(Log::Priority::Debug == SDL_LOG_PRIORITY_DEBUG);
    CHECK(Log::Priority::Verbose == SDL_LOG_PRIORITY_VERBOSE);
    CHECK(Log::Priority::Critical == SDL_LOG_PRIORITY_CRITICAL);
    CHECK(Log::Priority::Error == SDL_LOG_PRIORITY_ERROR);

    CHECK(SDL_LOG_PRIORITY_INFO == Log::Priority::Info);
    CHECK(SDL_LOG_PRIORITY_WARN == Log::Priority::Warn);
    CHECK(SDL_LOG_PRIORITY_DEBUG == Log::Priority::Debug);
    CHECK(SDL_LOG_PRIORITY_VERBOSE == Log::Priority::Verbose);
    CHECK(SDL_LOG_PRIORITY_CRITICAL == Log::Priority::Critical);
    CHECK(SDL_LOG_PRIORITY_ERROR == Log::Priority::Error);
  }

  SECTION("operator!=")
  {
    CHECK(Log::Priority::Info != SDL_LOG_PRIORITY_DEBUG);
    CHECK(SDL_LOG_PRIORITY_VERBOSE != Log::Priority::Critical);
  }
}

TEST_CASE("Log::Category", "[Log]")
{
  SECTION("operator==")
  {
    CHECK(Log::Category::App == SDL_LOG_CATEGORY_APPLICATION);
    CHECK(Log::Category::Error == SDL_LOG_CATEGORY_ERROR);
    CHECK(Log::Category::Assert == SDL_LOG_CATEGORY_ASSERT);
    CHECK(Log::Category::System == SDL_LOG_CATEGORY_SYSTEM);
    CHECK(Log::Category::Audio == SDL_LOG_CATEGORY_AUDIO);
    CHECK(Log::Category::Video == SDL_LOG_CATEGORY_VIDEO);
    CHECK(Log::Category::Render == SDL_LOG_CATEGORY_RENDER);
    CHECK(Log::Category::Input == SDL_LOG_CATEGORY_INPUT);
    CHECK(Log::Category::Test == SDL_LOG_CATEGORY_TEST);
    CHECK(Log::Category::Misc == SDL_LOG_CATEGORY_CUSTOM);

    CHECK(SDL_LOG_CATEGORY_APPLICATION == Log::Category::App);
    CHECK(SDL_LOG_CATEGORY_ERROR == Log::Category::Error);
    CHECK(SDL_LOG_CATEGORY_ASSERT == Log::Category::Assert);
    CHECK(SDL_LOG_CATEGORY_SYSTEM == Log::Category::System);
    CHECK(SDL_LOG_CATEGORY_AUDIO == Log::Category::Audio);
    CHECK(SDL_LOG_CATEGORY_VIDEO == Log::Category::Video);
    CHECK(SDL_LOG_CATEGORY_RENDER == Log::Category::Render);
    CHECK(SDL_LOG_CATEGORY_INPUT == Log::Category::Input);
    CHECK(SDL_LOG_CATEGORY_TEST == Log::Category::Test);
    CHECK(SDL_LOG_CATEGORY_CUSTOM == Log::Category::Misc);
  }
  SECTION("operator!=")
  {
    CHECK(Log::Category::Audio != SDL_LOG_CATEGORY_ERROR);
    CHECK(SDL_LOG_CATEGORY_SYSTEM != Log::Category::Render);
  }
}
