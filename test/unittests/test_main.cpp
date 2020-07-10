#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion_as_ctn.hpp"

int main(int argc, char** argv)
{
#ifndef CENTURION_NOAUDIO
  const ctn::centurion_lib c;
#else
  ctn::centurion_config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const ctn::centurion_lib c{cfg};
#endif
  return Catch::Session().run(argc, argv);
}