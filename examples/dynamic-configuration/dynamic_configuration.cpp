#include <centurion.hpp>

int main(int, char**)
{
  cen::config cfg;  // Assumes the standard configuration values by default

  cfg.coreFlags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO;  // No core audio support
  cfg.initMixer = false;                                  // Don't initialize SDL_mixer

  cen::library centurion{cfg};

  // Initialized SDL with no audio support along with no SDL_image nor SDL_ttf

  return 0;
}