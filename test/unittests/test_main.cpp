#define CATCH_CONFIG_RUNNER
#include <log.h>
#include "catch.hpp"
#include "centurion.h"

using namespace centurion;

int main(int argc, char** argv) {
  Centurion c;

  Log::set_priority(Priority::Info);
  Log::msg(Category::Test, Priority::Info, "Started running unit tests!");

  const auto result = Catch::Session().run(argc, argv);

  Log::set_priority(Priority::Info);
  Log::msg(Category::Test, Priority::Info, "Finished running unit tests!");

  return result;
}