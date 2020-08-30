#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "cen.hpp"

int main(int argc, char* argv[])
{
#ifndef CEN_AUDIO
  cen::centurion_config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const cen::centurion_lib c{cfg};
#else
  const cen::centurion_lib c;
#endif
  return Catch::Session().run(argc, argv);
}