#include <gtest/gtest.h>

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
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}