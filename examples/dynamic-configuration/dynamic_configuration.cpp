#include <centurion.hpp>

int main(int, char**)
{
  cen::SDLConfig cfg; /* Assumes the standard configuration values by default */
  cfg.flags = SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO; /* No core audio support */

  const cen::SDLLibrary sdl{cfg};
  const cen::IMGLibrary img;
  const cen::TTFLibrary ttf;
  // const cen::MixLibrary mix;

  /* Initialized SDL with no audio support, and all extension libraries except SDL_mixer */

  return 0;
}