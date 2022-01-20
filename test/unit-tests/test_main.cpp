#include <gtest/gtest.h>

#include "centurion/core/logging.hpp"
#include "centurion/initialization.hpp"

int main(int argc, char* argv[])
{
#ifdef CEN_AUDIO
  const cen::sdl sdl;
  const cen::mix mix;
#else
  cen::sdl_cfg cfg;
  cfg.flags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  const cen::sdl sdl{cfg};
#endif

  const cen::img img;
  const cen::ttf ttf;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}