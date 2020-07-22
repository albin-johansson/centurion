#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion_as_ctn.hpp"

auto main(int argc, char** argv) -> int
{
#ifdef CENTURION_NOAUDIO
  ctn::centurion_config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const ctn::centurion_lib c{cfg};
#else
  const ctn::centurion_lib c;
#endif
  return Catch::Session().run(argc, argv);
}