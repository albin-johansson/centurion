#include <gtest/gtest.h>

#include "core/library.hpp"
#include "core/log.hpp"

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

#if CENTURION_HAS_FEATURE_CONCEPTS
#if CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
  cen::log::use_preset_output_function();
#endif  // CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}