#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion.hpp"

int main(int argc, char* argv[])
{
#ifndef CEN_AUDIO
  cen::config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const cen::library lib{cfg};
#else
  const cen::library lib;
#endif
  return Catch::Session().run(argc, argv);
}