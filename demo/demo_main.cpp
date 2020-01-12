#include "centurion.h"

#include "window.h"
#include "window_listener.h"
#include "renderer.h"
#include "image.h"
#include "colors.h"

#include <SDL.h>

using namespace centurion;

static void do_stuff() {
  Window window;
  Renderer renderer{window};

  Image image{renderer, "resources/grass.png"};

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

    renderer.set_color(Colors::indian_red);
    renderer.clear();

    renderer.draw_image(image, 200, 200, 200, 200);

    renderer.set_color(Colors::snow);
    renderer.fill_rect(100 + x++, 100, 100, 100);

    renderer.present();
  }

  window.hide();
}

int main(int, char**) {
  Centurion::init();
  do_stuff();
  Centurion::quit();
  return 0;
}