#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"

int main(int argc, char** argv) {
  using namespace centurion;
  Centurion c;

  Log::set_priority(Priority::Error);
  Log::set_priority(Category::Test, Priority::Info);

#ifdef CENTURION_NOAUDIO
  Log::msgf("%s", "No audio!");
#else
  Log::msgf("%s", "Using audio!");
#endif

  return Catch::Session().run(argc, argv);
}