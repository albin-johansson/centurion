#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion.h"

int main(int argc, char** argv)
{
  namespace ctn = centurion;
#ifndef CENTURION_NOAUDIO
  const ctn::Centurion c;
#else
  ctn::CenturionConfig cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const ctn::Centurion c{cfg};
#endif
  return Catch::Session().run(argc, argv);
}