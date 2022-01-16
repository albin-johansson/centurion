#include <centurion.hpp>

int main(int, char**)
{
  /* Initialize the SDL libraries */
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  /* Create a window and an associated renderer */
  auto [window, renderer] = cen::MakeWindowAndRenderer();

  /* Make sure our window is visible */
  window.Show();

  cen::event_handler event;
  bool running = true;

  while (running) {
    while (event.poll()) {
      /* Check if the user wants to quit the application */
      if (event.is<cen::quit_event>()) {
        running = false;
        break;
      }
    }

    renderer.ClearWith(cen::colors::coral);

    /* Miscellaneous rendering code goes here... */

    renderer.Present();
  }

  /* Make the window invisible again, this might not be necessary, but it doesn't hurt */
  window.Hide();

  return 0;
}