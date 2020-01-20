#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"

int main(int argc, char** argv) {
  using namespace centurion;
  Centurion c;

#ifdef CENTURION_NOAUDIO
  Log::msg(Category::App, "No audio!");
#else
  Log::msg(Category::App, "Using audio!");
#endif

  return Catch::Session().run(argc, argv);
}