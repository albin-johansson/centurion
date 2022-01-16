#include <gtest/gtest.h>

#include "core/logging.hpp"
#include "initialization.hpp"

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

#if CENTURION_HAS_FEATURE_CONCEPTS
#if CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
  cen::use_preset_output_function();
#endif  // CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}