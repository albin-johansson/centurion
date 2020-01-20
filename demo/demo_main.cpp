#include "centurion.h"

#include "window.h"
#include "window_listener.h"
#include "message_box.h"
#include "renderer.h"
#include "image.h"
#include "colors.h"
#include "paths.h"
#include "system.h"
#include "log.h"

#include <SDL.h>
#include <vector>

using namespace centurion;
using namespace centurion::messagebox;

//static void render(Renderer& renderer) {
//  static auto x = 0;
//  static const auto image = Image{renderer, "resources/grass.png"};
//  static const std::vector<SDL_Point> points{
//      {50, 50}, {60, 40}, {70, 60}, {55, 100}
//  };
//
//  renderer.set_color(Colors::black);
//  renderer.clear();
//
//  renderer.draw_image(image,
//                      SDL_Rect{0, 0, 108, 108},
//                      SDL_FRect{200.0f, 200.0f, 108.0f, 108.0f});
//
//  renderer.set_color(Colors::azure);
//  renderer.draw_line(SDL_Point{10, 10}, SDL_Point{300, 300});
//
//  renderer.set_color(Colors::cornflower_blue);
//  renderer.draw_lines(points);
//
//  renderer.set_color(Colors::snow);
//  renderer.fill_rect(100 + x++, 100, 100, 100);
//
//  renderer.present();
//}

static void do_stuff() {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

#ifdef CENTURION_NOAUDIO
  Log::msg("No audio!");
#else
  Log::msg("Using audio!");
#endif

  Window window;

  const auto renderer = Renderer::shared(window,
                                         SDL_RENDERER_ACCELERATED |
                                             SDL_RENDERER_PRESENTVSYNC |
                                             SDL_RENDERER_TARGETTEXTURE);

  if (const AppPath appPath; appPath) {
    Log::msg("Application path: %s", appPath.get());
  }

  if (const PrefPath prefPath{"albinjohansson", "centurion"}; prefPath) {
    Log::msg("Preferred path: %s", prefPath.get());
  }

  Log::msg("CPUs: %i", CPU::get_cores());
  Log::msg("CPU cache line size: %i bytes", CPU::get_cache_line_size());
  Log::msg("RAM: %i GB", RAM::get_size_gb());
  Log::msg("OS: %s", System::get_platform_name()->c_str());

  window.show();

  const auto mk_scheme = []() noexcept {
    ColorScheme sc;
    sc.set_color(ColorSchemeType::Background, Colors::alice_blue);
    sc.set_color(ColorSchemeType::ButtonBackground, Colors::rebecca_purple);
    sc.set_color(ColorSchemeType::ButtonBorder, Colors::fuchsia);
    sc.set_color(ColorSchemeType::ButtonSelected, Colors::tan);
    return sc;
  };

  const auto mk_message_box = [&mk_scheme, &window]() noexcept {
    MessageBox m;
    m.set_title("Centurion message box");
    m.set_message("Hello there fellow Centurion user!");
    m.set_color_scheme(mk_scheme());
    m.set_type(MessageBoxID::Info);
    return m;
  };

  MessageBox mb = mk_message_box();
  mb.show(window);

  bool running = true;
  SDL_Event event;

  if (const auto percentage = Power::get_battery_percentage(); percentage) {
    Log::msg("Battery percentage: %i", percentage);
  }

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.type == SDL_KEYUP) {
        running = false;
      }
    }

//    render(*renderer);
  }

  window.hide();
}

int main(int, char**) {
  Centurion c;
  do_stuff();
  return 0;
}