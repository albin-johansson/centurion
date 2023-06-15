#include <centurion.hpp>

int main(int, char**)  // The signature of main must be equivalent to this!
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  // The core SDL library along with the extension libraries are now initialized!

  return 0;
}