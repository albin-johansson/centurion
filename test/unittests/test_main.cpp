#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "centurion.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

using namespace centurion;

int main(int argc, char** argv) {
  SDL_setenv("AUDIODEV", "null", 1);

  Centurion c;
  return Catch::Session().run(argc, argv);
}