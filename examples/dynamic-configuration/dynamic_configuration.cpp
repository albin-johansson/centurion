#include <centurion.hpp>

int main(int, char**)
{
  cen::SDLConfig cfg; /* Assumes the standard configuration values by default */
  cfg.flags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO; /* No core audio support */

  const cen::SDL sdl{cfg};
  const cen::IMG img;
  const cen::TTF ttf;
  // const cen::MixLibrary mix;

  /* Initialized SDL with no audio support, and all extension libraries except SDL_mixer */

  return 0;
}