#include "centurion.h"

#include "window.h"
#include "window_listener.h"
#include "renderer.h"
#include "image.h"
#include "image_generator.h"
#include "colors.h"
#include "paths.h"
#include "system.h"
#include "log.h"

#include <SDL.h>
#include <vector>

using namespace centurion;

static void do_stuff() {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

  Window window;
  const auto renderer = Renderer::shared(window);
  const auto imageGenerator = ImageGenerator{renderer};
  const auto image = imageGenerator.unique_img("resources/grass.png");
  const auto appPath = AppPath{};
  const auto prefPath = PrefPath{"albinjohansson", "centurion"};
  const std::vector<SDL_Point> points{{50, 50}, {60, 40}, {70, 60}, {55, 100}};

  if (appPath) {
    Log::msg(Category::App, "Application path: %s", appPath.get());
  }

  if (prefPath) {
    Log::msg(Category::App, "Preferred path: %s", prefPath.get());
  }

  Log::msg(Category::App, Priority::Info,
           "CPUs: %i", CPU::get_cores());

  Log::msg(Category::App, Priority::Info,
           "CPU cache line size: %i bytes", CPU::get_cache_line_size());

  Log::msg(Category::App, Priority::Info,
           "RAM: %i GB", RAM::get_size_gb());

  Log::msg(Category::App, Priority::Info,
           "OS: %s", System::get_platform_name()->c_str());

  window.show();

  bool running = true;
  SDL_Event event;

  while (running) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.type == SDL_KEYUP) {
        running = false;
      }
    }

    static auto x = 0;

    renderer->set_color(Colors::hot_pink);
    renderer->clear();

    renderer->draw_image(*image, 200, 200, 200, 200);

    renderer->set_color(Colors::azure);
    renderer->draw_line(SDL_Point{10, 10}, SDL_Point{300, 300});

    renderer->set_color(Colors::cornflower_blue);
    renderer->draw_lines(points);

    renderer->set_color(Colors::snow);
    renderer->fill_rect(100 + x++, 100, 100, 100);

    renderer->present();
  }

  window.hide();
}

int main(int, char**) {
  Centurion c;
  do_stuff();
  return 0;
}