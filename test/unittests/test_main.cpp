#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"

int main(int argc, char** argv) {
  using namespace centurion;
  const Centurion c;
  return Catch::Session().run(argc, argv);
}