#include <centurion.hpp>

int main(int, char**)
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::ttf ttf;

  // Create a window and an associated renderer
  cen::window window;
  cen::renderer renderer = window.make_renderer();

  // Here we assume the existence of an image and font
  const cen::texture image = renderer.make_texture(RESOURCE_DIR "panda.png");
  const cen::font font{RESOURCE_DIR "daniel.ttf", 36};

  // Render a string to a texture, which in turn can be rendered to our render target
  auto text = renderer.make_texture(font.render_blended("Hello world!", cen::colors::black));

  window.show();

  bool running = true;
  while (running) {
    cen::event_handler handler;
    while (handler.poll()) {
      if (handler.is(cen::event_type::quit)) {
        running = false;
        break;
      }
    }

    // Clear our render target with an arbitrary color
    renderer.clear_with(cen::colors::light_coral);

    // Draw a filled circle
    renderer.set_color(cen::colors::red);
    renderer.fill_circle(cen::fpoint{150, 150}, 75);

    // Draw an outlined circle
    renderer.set_color(cen::colors::cyan);
    renderer.draw_circle(cen::fpoint{350, 275}, 50);

    // Draw a filled rectangle
    renderer.set_color(cen::colors::lime_green);
    renderer.fill_rect(cen::frect{25.0, 500.0, 125.0, 75.0});

    // Draw an outlined rectangle
    renderer.set_color(cen::colors::khaki);
    renderer.draw_rect(cen::frect{550.0, 50.0, 140.0, 60.0});

    // Draw a line between two points
    renderer.set_color(cen::colors::forest_green);
    renderer.draw_line(cen::fpoint{240.0, 340.0}, cen::fpoint{360.0, 460.0});

    // Render the image along with the text (also in the form of a texture)
    renderer.render(image, cen::fpoint{600.0, 450.0});
    renderer.render(text, cen::fpoint{450.0, 230.0});

#if SDL_VERSION_ATLEAST(2, 0, 18)
    // Render a triangle, using the low level "geometry" rendering API
    const SDL_Vertex vertices[] = {{{650, 400}, cen::colors::red.get(), {}},
                                   {{410, 310}, cen::colors::lime.get(), {}},
                                   {{450, 550}, cen::colors::blue.get(), {}}};
    renderer.render_geo(vertices);
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

    // Apply our draw calls to the render target (the window)
    renderer.present();
  }

  window.hide();

  return 0;
}