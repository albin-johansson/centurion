#include "audio.h"

#include "catch.hpp"

using namespace centurion;

TEST_CASE("audio | Max volume constant", "[audio]")
{
  CHECK(MIX_MAX_VOLUME == audio::maxVolume);
}

TEST_CASE("audio | Loop forever constant", "[audio]")
{
  CHECK(-1 == audio::loopForever);
}