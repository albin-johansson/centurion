#include "font_cache.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"
#include "font.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("font_cache(font_cache&&)", "[font_cache]")
{
  ctn::font f{"resources/daniel.ttf", 12};
  CHECK_NOTHROW(ctn::font_cache{std::move(f)});
}

TEST_CASE("font_cache(Args&&...)", "[font_cache]")
{
  CHECK_NOTHROW(ctn::font_cache{"resources/daniel.ttf", 12});
}

TEST_CASE("font_cache smart pointer factory methods", "[font_cache]")
{
  CHECK(ctn::font_cache::unique("resources/daniel.ttf", 12));
  CHECK(ctn::font_cache::unique(ctn::font{"resources/daniel.ttf", 12}));

  CHECK(ctn::font_cache::shared("resources/daniel.ttf", 12));
  CHECK(ctn::font_cache::shared(ctn::font{"resources/daniel.ttf", 12}));
}

template <class Callable>
void test_unicode_cache(Callable&& callable)
{
  ctn::window window;
  ctn::renderer renderer{window};

  constexpr auto id = "foo"_hs;

  ctn::font_cache cache{"resources/fira_code.ttf", 12};
  ctn::unicode_string str = {'b', 'a', 'r'};

  callable(renderer, cache, id, str);
}

template <class Callable>
void test_latin1_cache(Callable&& callable)
{
  ctn::window window;
  ctn::renderer renderer{window};

  constexpr auto id = "foo"_hs;

  ctn::font_cache cache{"resources/fira_code.ttf", 12};
  ctn::nn_czstring str = "latin1_<!?+=";

  callable(renderer, cache, id, str);
}

template <class Callable>
void test_utf8_cache(Callable&& callable)
{
  ctn::window window;
  ctn::renderer renderer{window};

  constexpr auto id = "foo"_hs;

  ctn::font_cache cache{"resources/fira_code.ttf", 12};
  ctn::nn_czstring str = "UTF-8_<!?+=";

  callable(renderer, cache, id, str);
}

TEST_CASE("font_cache::store", "[font_cache]")
{
  test_unicode_cache([](ctn::renderer& renderer,
                        ctn::font_cache& cache,
                        entt::id_type id,
                        const ctn::unicode_string& str) {
    CHECK(!cache.has_stored(id));

    cache.store("foo"_hs,
                renderer.render_blended_unicode(str, cache.get_font()));

    CHECK(cache.has_stored(id));

    CHECK_NOTHROW(cache.store(
        "foo"_hs, renderer.render_blended_unicode(str, cache.get_font())));
    CHECK_NOTHROW(cache.get_stored(id));
  });
}

TEST_CASE("font_cache::has", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::font_cache cache{"resources/daniel.ttf", 12};

  cache.add_basic_latin(renderer);

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

TEST_CASE("font_cache::at", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::font_cache cache{"resources/daniel.ttf", 12};
  cache.add_latin1(renderer);

  const auto& [cachedTexture, glyphMetrics] = cache.at('a');

  CHECK(cachedTexture.get());
}

TEST_CASE("font_cache::operator[]", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::font_cache cache{"resources/daniel.ttf", 12};
  cache.add_latin1(renderer);

  const auto& [cachedTexture, glyphMetrics] = cache['t'];

  CHECK(cachedTexture.get());
}

TEST_CASE("font_cache::try_get_stored", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::font_cache cache{"resources/fira_code.ttf", 12};
  cache.add_latin1(renderer);

  cache.store("foo"_hs,
              renderer.render_blended_latin1("bar!?<,.", cache.get_font()));

  CHECK(cache.try_get_stored("foo"_hs));
  CHECK_NOTHROW(cache.try_get_stored("bad"_hs));
}

TEST_CASE("font_cache::get_stored", "[font_cache]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::font_cache cache{"resources/fira_code.ttf", 12};
  cache.add_latin1(renderer);
  cache.store("foo"_hs,
              renderer.render_blended_latin1("bar!?<,.", cache.get_font()));

  CHECK(cache.get_stored("foo"_hs).get());
}

TEST_CASE("font_cache::get_font", "[font_cache]")
{
  SECTION("Non-const")
  {
    ctn::font_cache cache{"resources/daniel.ttf", 12};
    auto& font = cache.get_font();

    CHECK(font.get());
    CHECK(font.family_name() == std::string{"Daniel"});
  }

  SECTION("Const")
  {
    const ctn::font_cache cache{"resources/daniel.ttf", 12};
    const auto& font = cache.get_font();

    CHECK(font.get());
    CHECK(font.family_name() == std::string{"Daniel"});
  }
}

TEST_CASE("Interactive font cache", "[.font_cache]")
{
  using ctn::unicode;

  ctn::window window;
  ctn::renderer renderer{window};
  ctn::font_cache cache{"resources/daniel.ttf", 32};

  {
    renderer.set_color(ctn::colors::white);
    cache.add_latin1(renderer);

    renderer.set_color(ctn::colors::magenta);
    cache.store(
        "foo"_hs,
        renderer.render_blended_latin1("cool string! <|>", cache.get_font()));

    ctn::unicode_string cool = {0x2192, 0x2665, 0x2190, 0x263A};

    cache.store("cool"_hs,
                renderer.render_blended_unicode(cool, cache.get_font()));
  }

  ctn::unicode_string str = {'c',
                             'o',
                             'o',
                             'l',
                             ' ',
                             's',
                             't',
                             'r',
                             'i',
                             'n',
                             'g',
                             '!',
                             ' ',
                             '<',
                             '|',
                             '>'};

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
        if (key->state() == ctn::button_state::released) {
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
        changingStr += text->text_utf8();
      }
    }

    renderer.clear_with(ctn::colors::black);

    using namespace std::string_view_literals;

    renderer.render_text(cache, "abcdefghijklmnopqrstuvwxyz"sv, {50, 10});
    renderer.render_text(cache, changingStr, {50, 150});
    renderer.render_text(cache, str, {50, 100});

    renderer.render(cache.get_stored("foo"_hs), ctn::ipoint{50, 200});
    renderer.render(cache.get_stored("cool"_hs), ctn::ipoint{300, 400});

    renderer.present();
  }
  window.hide();
}
