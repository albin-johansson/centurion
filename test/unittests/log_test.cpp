#include "catch.hpp"
#include "log.h"

using namespace centurion;

TEST_CASE("Specific logging category", "[Log]") {
  const auto category = Category::App;

  CHECK(Priority::Info == Log::get_priority(category));

  const auto priority = Priority::Debug;
  Log::set_priority(category, priority);

  CHECK(priority == Log::get_priority(category));
}

TEST_CASE("Global logging priority", "[Log]") {
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
}