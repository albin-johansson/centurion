#include <centurion.hpp>

int main(int, char**) /* The signature of main must be equivalent to this! */
{
  const cen::SDLLibrary sdl;
  const cen::IMGLibrary img;
  const cen::MixLibrary mix;
  const cen::TTFLibrary ttf;

  /* The core SDL library along with the extension libraries are now initialized! */

  return 0;
}