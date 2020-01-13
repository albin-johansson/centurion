#include "centurion.h"

#include "window.h"
#include "window_listener.h"
#include "renderer.h"
#include "image.h"
#include "image_generator.h"
#include "colors.h"
#include "paths.h"

#include <SDL.h>

using namespace centurion;

static void do_stuff() {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

  Window window;
  auto renderer = Renderer::shared(window);

  ImageGenerator imageGenerator{renderer};

  auto image = imageGenerator.unique_img("resources/grass.png");

  AppPath appPath;
  if (appPath) {
    SDL_Log("Application path: %s", appPath.get());
  }

  PrefPath prefPath{"albinjohansson", "centurion"};
  if (prefPath) {
    SDL_Log("Preferred path: %s", prefPath.get());
  }

  const auto info = renderer->get_info();

  SDL_Log("Renderer driver: %s", info.name);

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

    renderer->set_color(Colors::snow);
    renderer->fill_rect(100 + x++, 100, 100, 100);

    renderer->present();
  }

  window.hide();
}

int main(int, char**) {
  Centurion::init();
  do_stuff();
  Centurion::quit();
  return 0;
}