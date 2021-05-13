#include "centurion.hpp"

namespace {

auto run() -> int
{
  cen::window window{"Renderer demo"};
  cen::renderer renderer{window};

  const cen::texture texture{renderer, "resources/panda.png"};
  const cen::font font{"resources/daniel.ttf", 36};

  auto text = renderer.render_blended_utf8("Hello world!", font);

  cen::event event;
  bool running{true};

  window.show();

  while (running)
  {
    while (event.poll())
    {
      if (event.is<cen::quit_event>())
      {
        running = false;
        break;
      }
    }

    renderer.clear_with(cen::colors::light_coral);

    renderer.set_color(cen::colors::red);
    renderer.fill_circle(cen::point(150.0, 150.0), 75);

    renderer.set_color(cen::colors::cyan);
    renderer.draw_circle(cen::point(350.0, 275.0), 50);

    renderer.set_color(cen::colors::lime_green);
    renderer.fill_rect(cen::rect(25.0, 500.0, 125.0, 75.0));

    renderer.set_color(cen::colors::khaki);
    renderer.draw_rect(cen::rect(550.0, 50.0, 140.0, 60.0));

    renderer.set_color(cen::colors::forest_green);
    renderer.draw_line(cen::point(240.0, 340.0), cen::point(360.0, 460.0));

    renderer.render(texture, cen::point(600.0, 450.0));
    renderer.render(text, cen::point(450.0, 230.0));

    renderer.present();
  }

  window.hide();
  return 0;
}

}  // namespace

auto main(int argc, char** argv) -> int
{
  const cen::library centurion;
  return run();
}
