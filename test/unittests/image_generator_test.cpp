#include "catch.hpp"
#include "image_generator.h"
#include "centurion_exception.h"

using namespace centurion;

TEST_CASE("ImageGenerator(Renderer)", "[Renderer]") {
  CHECK_THROWS_AS(ImageGenerator{nullptr}, CenturionException);
}