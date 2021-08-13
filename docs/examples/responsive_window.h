/**
 * \page page-responsive-window Responsive Window
 *
 * This example demonstrates how to setup a basic event-driven application that results in
 * a "responsive" window, i.e. a window that handles program events. The below program
 * should result in a blank window that can be moved around and closed to quit the
 * program.
 *
 * \code{cpp}
 * #include <centurion.hpp>
 *
 * int main(int, char**)
 * {
 *   // Initialize the library
 *   cen::library centurion;
 *
 *   // Create a window and an associated renderer
 *   auto [window, renderer] = cen::make_window_and_renderer();
 *
 *   // Make sure our window is visible
 *   window.show();
 *
 *   cen::event event;
 *   bool running = true;
 *   while (running)
 *   {
 *     while (event.poll())
 *     {
 *       // Check if the user wants to quit the application
 *       if (event.is<cen::quit_event>())
 *       {
 *         running = false;
 *         break;
 *       }
 *     }
 *
 *     renderer.clear_with(cen::colors::black);
 *
 *     // Miscellaneous rendering code goes here...
 *
 *     renderer.present();
 *   }
 *
 *   // Make the window invisible again, this might not be necessary but it doesn't hurt
 *   window.hide();
 *
 *   return 0;
 * }
 * \endcode
 */