#include <gtest/gtest.h>

#include "core/initialization.hpp"
#include "core/logging.hpp"

int main(int argc, char* argv[])
{
#ifdef CEN_AUDIO
  const cen::SDLLibrary sdl;
  const cen::MixLibrary mix;
#else
  cen::SDLConfig cfg;
  cfg.flags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;
  const cen::SDLLibrary sdl{cfg};
#endif

  const cen::IMGLibrary img;
  const cen::TTFLibrary ttf;

#if CENTURION_HAS_FEATURE_CONCEPTS
#if CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
  cen::use_preset_output_function();
#endif  // CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}