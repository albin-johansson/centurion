#include "log.h"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Log methods bad arg resistance", "[Log]")
{
  const char* msg = nullptr;
  CHECK_NOTHROW(Log::msgf(msg));
  CHECK_NOTHROW(Log::msgf(Category::App, msg));
  CHECK_NOTHROW(Log::msgf(Category::App, Priority::Info, msg));
}

TEST_CASE("Specific logging category", "[Log]")
{
  const auto category = Category::App;
  const auto priority = Priority::Debug;
  Log::set_priority(category, priority);

  CHECK(priority == Log::get_priority(category));
  Log::reset_priorites();
}

TEST_CASE("Global logging priority", "[Log]")
{
  const auto priority = Priority::Critical;
  Log::set_priority(priority);

  CHECK(priority == Log::get_priority(Category::App));
  CHECK(priority == Log::get_priority(Category::Error));
  CHECK(priority == Log::get_priority(Category::Assert));
  CHECK(priority == Log::get_priority(Category::System));
  CHECK(priority == Log::get_priority(Category::Audio));
  CHECK(priority == Log::get_priority(Category::Video));
  CHECK(priority == Log::get_priority(Category::Render));
  CHECK(priority == Log::get_priority(Category::Input));
  CHECK(priority == Log::get_priority(Category::Test));
  CHECK(priority == Log::get_priority(Category::Misc));

  Log::reset_priorites();
}

TEST_CASE("Priority enum values", "[Log]")
{
  CHECK(Priority::Info == SDL_LOG_PRIORITY_INFO);
  CHECK(Priority::Warn == SDL_LOG_PRIORITY_WARN);
  CHECK(Priority::Debug == SDL_LOG_PRIORITY_DEBUG);
  CHECK(Priority::Verbose == SDL_LOG_PRIORITY_VERBOSE);
  CHECK(Priority::Critical == SDL_LOG_PRIORITY_CRITICAL);
  CHECK(Priority::Error == SDL_LOG_PRIORITY_ERROR);

  CHECK(SDL_LOG_PRIORITY_INFO == Priority::Info);
  CHECK(SDL_LOG_PRIORITY_WARN == Priority::Warn);
  CHECK(SDL_LOG_PRIORITY_DEBUG == Priority::Debug);
  CHECK(SDL_LOG_PRIORITY_VERBOSE == Priority::Verbose);
  CHECK(SDL_LOG_PRIORITY_CRITICAL == Priority::Critical);
  CHECK(SDL_LOG_PRIORITY_ERROR == Priority::Error);
}

TEST_CASE("Category enum values", "[Log]")
{
  CHECK(static_cast<int>(Category::App) == SDL_LOG_CATEGORY_APPLICATION);
  CHECK(static_cast<int>(Category::Error) == SDL_LOG_CATEGORY_ERROR);
  CHECK(static_cast<int>(Category::Assert) == SDL_LOG_CATEGORY_ASSERT);
  CHECK(static_cast<int>(Category::System) == SDL_LOG_CATEGORY_SYSTEM);
  CHECK(static_cast<int>(Category::Audio) == SDL_LOG_CATEGORY_AUDIO);
  CHECK(static_cast<int>(Category::Video) == SDL_LOG_CATEGORY_VIDEO);
  CHECK(static_cast<int>(Category::Render) == SDL_LOG_CATEGORY_RENDER);
  CHECK(static_cast<int>(Category::Input) == SDL_LOG_CATEGORY_INPUT);
  CHECK(static_cast<int>(Category::Test) == SDL_LOG_CATEGORY_TEST);
  CHECK(static_cast<int>(Category::Misc) == SDL_LOG_CATEGORY_CUSTOM);
}