#include <centurion.hpp>

int main(int, char**)
{
  cen::sdl_cfg cfg; // Assumes the standard configuration values by default
  cfg.flags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO; // No core audio support

  const cen::sdl sdl{cfg};
  const cen::img img;
  const cen::ttf ttf;

  // Initialized SDL with no audio support, and all extension libraries except SDL_mixer

  return 0;
}