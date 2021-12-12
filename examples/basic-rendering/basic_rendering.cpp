#include <centurion.hpp>

int main(int, char**)
{
  const cen::SDLLibrary sdl;
  const cen::IMGLibrary img;
  const cen::TTFLibrary ttf;

  // Create our window and renderer
  auto [window, renderer] = cen::make_window_and_renderer();

  // Here we assume the existence of an image and font
  const cen::texture image{renderer, RESOURCE_DIR "panda.png"};
  const cen::font font{RESOURCE_DIR "daniel.ttf", 36};
  window.show();

  // Render a string to a texture, which in turn can be rendered to our render target
  auto text = renderer.render_blended_utf8("Hello world!", font);

  // Clear our render target with an arbitrary color
  renderer.clear_with(cen::colors::light_coral);

  // Draw a filled circle
  renderer.set_color(cen::colors::red);
  renderer.fill_circle(cen::point(150.0, 150.0), 75);

  // Draw an outlined circle
  renderer.set_color(cen::colors::cyan);
  renderer.draw_circle(cen::point(350, 275), 50);

  // Draw a filled rectangle
  renderer.set_color(cen::colors::lime_green);
  renderer.fill_rect(cen::rect(25.0, 500.0, 125.0, 75.0));

  // Draw an outlined rectangle
  renderer.set_color(cen::colors::khaki);
  renderer.draw_rect(cen::rect(550.0, 50.0, 140.0, 60.0));

  // Draw a line between two points
  renderer.set_color(cen::colors::forest_green);
  renderer.draw_line(cen::point(240.0, 340.0), cen::point(360.0, 460.0));

  // Render the image along with the text (also in the form of a texture)
  renderer.render(image, cen::point(600.0, 450.0));
  renderer.render(text, cen::point(450.0, 230.0));

  // Apply our draw calls to the render target (the window)
  renderer.present();

  using namespace cen::literals;  // For _ms literal
  cen::thread::sleep(2000_ms);    // Wait for 2 seconds so that we can see the result
  window.hide();

  return 0;
}