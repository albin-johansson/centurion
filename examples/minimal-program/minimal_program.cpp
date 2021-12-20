#include <centurion.hpp>

int main(int, char**) /* The signature of main must be equivalent to this! */
{
  const cen::SDL sdl;
  const cen::IMG img;
  const cen::Mix mix;
  const cen::TTF ttf;

  /* The core SDL library along with the extension libraries are now initialized! */

  return 0;
}