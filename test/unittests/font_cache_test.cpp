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
  using ctn::experimental::unicode;

  ctn::window window;
  ctn::renderer renderer{window};
  ctn::experimental::font_cache cache{"resources/fira_code.ttf", 32};

  renderer.set_color(ctn::colors::white);
  cache.cache_latin1(renderer);

  renderer.set_color(ctn::colors::magenta);
  cache.cache_blended_latin1(
      renderer.get(), "foo"_hs, "this is a cached string!");

  //  ctn::experimental::unicode_string cool = {0x2665};
  ctn::experimental::unicode_string cool = {0x2192, 0x2665, 0x2190, 0x263A};
  cache.cache_blended_unicode(renderer.get(), "cool"_hs, cool);

  //  cache.cache_utf8(renderer, ""_hs, "");

  ctn::experimental::unicode_string str = {'a', 'b', 'c', 0xE4};

  ctn::czstring alphabet = "abcdefghijklmnopqrstuvwxyz";
  std::string changingStr;

  ctn::event event;
  bool running = true;

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
        changingStr += text->text();  // TODO rename text to text_utf8
      }
    }

    renderer.clear_with(ctn::colors::black);

    cache.render(renderer, alphabet, {50, 10});
    cache.render(renderer, changingStr.data(), {50, 60});

    cache.render(renderer, "Foo\nBar", {50, 110});
    cache.render_unicode(renderer, str, {300, 110});

    renderer.render(cache.cached("foo"_hs), ctn::point_i{50, 200});
    renderer.render(cache.cached("cool"_hs), ctn::point_i{300, 400});

    renderer.present();
  }
  window.hide();
}

TEST_CASE("font_cache::has", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::experimental::font_cache cache{"resources/daniel.ttf", 12};

  cache.cache_basic_latin(renderer);

  SECTION("Lowercase latin alphabet")
  {
    CHECK(cache.has('a'));
    CHECK(cache.has('b'));
    CHECK(cache.has('c'));
    CHECK(cache.has('d'));
    CHECK(cache.has('e'));
    CHECK(cache.has('f'));
    CHECK(cache.has('g'));
    CHECK(cache.has('h'));
    CHECK(cache.has('i'));
    CHECK(cache.has('j'));
    CHECK(cache.has('k'));
    CHECK(cache.has('l'));
    CHECK(cache.has('m'));
    CHECK(cache.has('n'));
    CHECK(cache.has('o'));
    CHECK(cache.has('p'));
    CHECK(cache.has('q'));
    CHECK(cache.has('r'));
    CHECK(cache.has('s'));
    CHECK(cache.has('t'));
    CHECK(cache.has('u'));
    CHECK(cache.has('v'));
    CHECK(cache.has('x'));
    CHECK(cache.has('y'));
    CHECK(cache.has('z'));
  }

  SECTION("Uppercase latin alphabet")
  {
    CHECK(cache.has('A'));
    CHECK(cache.has('B'));
    CHECK(cache.has('C'));
    CHECK(cache.has('D'));
    CHECK(cache.has('E'));
    CHECK(cache.has('F'));
    CHECK(cache.has('G'));
    CHECK(cache.has('H'));
    CHECK(cache.has('I'));
    CHECK(cache.has('J'));
    CHECK(cache.has('K'));
    CHECK(cache.has('L'));
    CHECK(cache.has('M'));
    CHECK(cache.has('N'));
    CHECK(cache.has('O'));
    CHECK(cache.has('P'));
    CHECK(cache.has('Q'));
    CHECK(cache.has('R'));
    CHECK(cache.has('S'));
    CHECK(cache.has('T'));
    CHECK(cache.has('U'));
    CHECK(cache.has('V'));
    CHECK(cache.has('X'));
    CHECK(cache.has('Y'));
    CHECK(cache.has('Z'));
  }

  SECTION("ASCII digits")
  {
    CHECK(cache.has('0'));
    CHECK(cache.has('1'));
    CHECK(cache.has('2'));
    CHECK(cache.has('3'));
    CHECK(cache.has('4'));
    CHECK(cache.has('5'));
    CHECK(cache.has('6'));
    CHECK(cache.has('7'));
    CHECK(cache.has('8'));
    CHECK(cache.has('9'));
  }

  SECTION("ASCII punctuation and symbols")
  {
    CHECK(cache.has(' '));
    CHECK(cache.has('!'));
    CHECK(cache.has('"'));
    CHECK(cache.has('#'));
    CHECK(cache.has('$'));
    CHECK(cache.has('%'));
    CHECK(cache.has('&'));
    CHECK(cache.has('\''));
    CHECK(cache.has('('));
    CHECK(cache.has(')'));
    CHECK(cache.has('*'));
    CHECK(cache.has('+'));
    CHECK(cache.has(','));
    CHECK(cache.has('-'));
    CHECK(cache.has('.'));
    CHECK(cache.has('/'));
    CHECK(cache.has(':'));
    CHECK(cache.has(';'));
    CHECK(cache.has('<'));
    CHECK(cache.has('='));
    CHECK(cache.has('>'));
    CHECK(cache.has('?'));
    CHECK(cache.has('@'));
    CHECK(cache.has('['));
    CHECK(cache.has('\\'));
    CHECK(cache.has(']'));
    CHECK(cache.has('^'));
    CHECK(cache.has('_'));
    CHECK(cache.has('`'));
    CHECK(cache.has('{'));
    CHECK(cache.has('|'));
    CHECK(cache.has('}'));
    CHECK(cache.has('~'));
  }

  //  CHECK(cache.has(0x20));
}