#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"

using namespace centurion;

int main(int argc, char** argv) {

  Centurion::init();
  const auto result = Catch::Session().run(argc, argv);
  Centurion::quit();

  return result;
}