#include "experimental/font_cache.hpp"

//#include <NFont.h>
//#include <SDL_FontCache.h>

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"
#include "font.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("...", "[.font_cache]")
{
  using unicode = ctn::u16;

  ctn::window window;
  ctn::renderer renderer{window};

  ctn::font font{"resources/daniel.ttf", 32};
  ctn::log::info("%s kerning enabled: %i", font.family_name(), font.kerning());

  ctn::czstring alphabet = "abcdefghijklmnopqrstuvwxyz";

  renderer.set_color(ctn::colors::cyan);
  const auto everyLetter = renderer.text_blended(alphabet, font);

  renderer.set_color(ctn::colors::lime);
  ctn::experimental::font_cache cache{renderer, std::move(font)};

  //  cache.cache_alphabetical(renderer);
  //  cache.cache_numerical(renderer);

  renderer.set_color(ctn::colors::magenta);
  cache.cache_string(renderer, "foo"_hs, "this is a cached string!");

  ctn::event event;
  bool running = true;

  std::string changingStr;

  window.show();
  while (running) {
    while (event.poll()) {
      if (event.is<ctn::quit_event>()) {
        running = false;
        break;
      } else if (const auto* key = event.try_get<ctn::keyboard_event>(); key) {
        if (key->state() == ctn::button_state::released) {  // TODO nicer
                                                            // released() method
          if (key->is_active(SDL_SCANCODE_ESCAPE)) {
            running = false;
            break;
          }
        } else {
          if (key->is_active(SDL_SCANCODE_BACKSPACE)) {
            if (!changingStr.empty()) {
              changingStr.pop_back();
            }
          }
        }

      } else if (const auto* text = event.try_get<ctn::text_input_event>();
                 text) {
        changingStr += text->text();
      }
    }

    renderer.clear_with(ctn::colors::black);

    renderer.render(*everyLetter, ctn::point_i{50, 50});
    cache.render(renderer, alphabet, {50, 150});
    cache.render(renderer, changingStr.data(), {50, 250});
    cache.render(renderer, "Foo\nBar", {50, 350});
    cache.render_cached(renderer, "foo"_hs, {50, 300});

    renderer.present();
  }
  window.hide();
}