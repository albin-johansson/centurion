#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "centurion_as_ctn.hpp"

int main(int argc, char** argv)
{
#ifdef CENTURION_NOAUDIO
  ctn::centurion_config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  cfg.initMixer = false;

  const ctn::centurion_lib c{cfg};
#elif defined(CENTURION_NOVIDEO)
  ctn::centurion_config cfg;

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_VIDEO;

  const ctn::centurion_lib c{cfg};
#else
  const ctn::centurion_lib c;
#endif
  return Catch::Session().run(argc, argv);
}