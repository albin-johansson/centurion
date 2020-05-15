#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion.h"

int main(int argc, char** argv)
{
  using namespace centurion;
#ifndef CENTURION_NOAUDIO
  const Centurion c;
#else
  CenturionConfig cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const Centurion c{cfg};
#endif
  return Catch::Session().run(argc, argv);
}