#include "font_cache.hpp"

#include <gtest/gtest.h>

#include <functional>   // function
#include <memory>       // unique_ptr
#include <string>       // string
#include <string_view>  // string_view

#include "event.hpp"
#include "font.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace {
inline constexpr auto fontPath = "resources/daniel.ttf";
}

TEST(FontCache, FontConstructor)
{
  cen::font font{fontPath, 12};
  EXPECT_NO_THROW(cen::font_cache{std::move(font)});
}

TEST(FontCache, InPlaceConstructor)
{
  EXPECT_NO_THROW(cen::font_cache(fontPath, 12));

  // Font constructor exceptions
  EXPECT_THROW(cen::font_cache("", 12), cen::ttf_error);
  EXPECT_THROW(cen::font_cache(fontPath, 0), cen::exception);
}

class FontCacheTest : public testing::Test
{
 protected:
  using id_type = cen::font_cache::id_type;

  using unicode_signature = void(id_type,
                                 const cen::unicode_string&,
                                 cen::renderer&);
  using unicode_store_fn = std::function<unicode_signature>;

  using normal_signature = void(id_type, cen::czstring, cen::renderer&);
  using normal_store_fn = std::function<normal_signature>;

  FontCacheTest() : testing::Test{}, m_cache{fontPath, 12}
  {}

  static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
    m_renderer = std::make_unique<cen::renderer>(*m_window);
  }

  void test_store_utf_8(const normal_store_fn& store)
  {
    test_store(store, 54, "UTF-8_<!?+=");
  }

  void test_store_latin_1(const normal_store_fn& store)
  {
    test_store(store, 27, "latin1_<!?+=");
  }

  void test_store_unicode(const unicode_store_fn& store)
  {
    test_store(store, 77, cen::unicode_string{'b', 'a', 'r'});
  }

  inline static std::unique_ptr<cen::window> m_window;
  inline static std::unique_ptr<cen::renderer> m_renderer;
  cen::font_cache m_cache;

 private:
  template <typename T, typename S>
  void test_store(const T& store, const id_type id, const S& str)
  {
    EXPECT_FALSE(m_cache.has_stored(id));

    store(id, str, *m_renderer);
    EXPECT_TRUE(m_cache.has_stored(id));

    EXPECT_NO_THROW(store(id, str, *m_renderer));
  }
};

TEST_F(FontCacheTest, StoreBlendedUnicode)
{
  test_store_unicode([this](const id_type id,
                            const cen::unicode_string& str,
                            cen::renderer& renderer) {
    m_cache.store_blended_unicode(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreBlendedWrappedUnicode)
{
  test_store_unicode([this](const id_type id,
                            const cen::unicode_string& str,
                            cen::renderer& renderer) {
    m_cache.store_blended_wrapped_unicode(id, str, *m_renderer, 100);
  });
}

TEST_F(FontCacheTest, StoreSolidUnicode)
{
  test_store_unicode([this](const id_type id,
                            const cen::unicode_string& str,
                            cen::renderer& renderer) {
    m_cache.store_solid_unicode(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreShadedUnicode)
{
  test_store_unicode([this](const id_type id,
                            const cen::unicode_string& str,
                            cen::renderer& renderer) {
    m_cache.store_shaded_unicode(id, str, *m_renderer, cen::colors::pink);
  });
}

TEST_F(FontCacheTest, StoreBlendedUTF8)
{
  test_store_utf_8(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_blended_utf8(id, str, *m_renderer);
      });
}

TEST_F(FontCacheTest, StoreBlendedWrappedUTF8)
{
  test_store_utf_8(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_blended_wrapped_utf8(id, str, *m_renderer, 80);
      });
}

TEST_F(FontCacheTest, StoreSolidUTF8)
{
  test_store_utf_8(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_solid_utf8(id, str, *m_renderer);
      });
}

TEST_F(FontCacheTest, StoreShadedUTF8)
{
  test_store_utf_8(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_shaded_utf8(id, str, *m_renderer, cen::colors::cyan);
      });
}

TEST_F(FontCacheTest, StoreBlendedLatin1)
{
  test_store_latin_1(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_blended_latin1(id, str, *m_renderer);
      });
}

TEST_F(FontCacheTest, StoreBlendedWrappedLatin1)
{
  test_store_latin_1(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_blended_wrapped_latin1(id, str, *m_renderer, 120);
      });
}

TEST_F(FontCacheTest, StoreSolidLatin1)
{
  test_store_latin_1(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_solid_latin1(id, str, *m_renderer);
      });
}

TEST_F(FontCacheTest, StoreShadedLatin1)
{
  test_store_latin_1(
      [this](const id_type id, cen::czstring str, cen::renderer& renderer) {
        m_cache.store_shaded_latin1(id, str, *m_renderer, cen::colors::aqua);
      });
}

TEST_F(FontCacheTest, Has)
{
  m_cache.add_basic_latin(*m_renderer);

  {  // Lowercase latin alphabet
    EXPECT_TRUE(m_cache.has('a'));
    EXPECT_TRUE(m_cache.has('b'));
    EXPECT_TRUE(m_cache.has('c'));
    EXPECT_TRUE(m_cache.has('d'));
    EXPECT_TRUE(m_cache.has('e'));
    EXPECT_TRUE(m_cache.has('f'));
    EXPECT_TRUE(m_cache.has('g'));
    EXPECT_TRUE(m_cache.has('h'));
    EXPECT_TRUE(m_cache.has('i'));
    EXPECT_TRUE(m_cache.has('j'));
    EXPECT_TRUE(m_cache.has('k'));
    EXPECT_TRUE(m_cache.has('l'));
    EXPECT_TRUE(m_cache.has('m'));
    EXPECT_TRUE(m_cache.has('n'));
    EXPECT_TRUE(m_cache.has('o'));
    EXPECT_TRUE(m_cache.has('p'));
    EXPECT_TRUE(m_cache.has('q'));
    EXPECT_TRUE(m_cache.has('r'));
    EXPECT_TRUE(m_cache.has('s'));
    EXPECT_TRUE(m_cache.has('t'));
    EXPECT_TRUE(m_cache.has('u'));
    EXPECT_TRUE(m_cache.has('v'));
    EXPECT_TRUE(m_cache.has('x'));
    EXPECT_TRUE(m_cache.has('y'));
    EXPECT_TRUE(m_cache.has('z'));
  }

  {  // Uppercase latin alphabet
    EXPECT_TRUE(m_cache.has('A'));
    EXPECT_TRUE(m_cache.has('B'));
    EXPECT_TRUE(m_cache.has('C'));
    EXPECT_TRUE(m_cache.has('D'));
    EXPECT_TRUE(m_cache.has('E'));
    EXPECT_TRUE(m_cache.has('F'));
    EXPECT_TRUE(m_cache.has('G'));
    EXPECT_TRUE(m_cache.has('H'));
    EXPECT_TRUE(m_cache.has('I'));
    EXPECT_TRUE(m_cache.has('J'));
    EXPECT_TRUE(m_cache.has('K'));
    EXPECT_TRUE(m_cache.has('L'));
    EXPECT_TRUE(m_cache.has('M'));
    EXPECT_TRUE(m_cache.has('N'));
    EXPECT_TRUE(m_cache.has('O'));
    EXPECT_TRUE(m_cache.has('P'));
    EXPECT_TRUE(m_cache.has('Q'));
    EXPECT_TRUE(m_cache.has('R'));
    EXPECT_TRUE(m_cache.has('S'));
    EXPECT_TRUE(m_cache.has('T'));
    EXPECT_TRUE(m_cache.has('U'));
    EXPECT_TRUE(m_cache.has('V'));
    EXPECT_TRUE(m_cache.has('X'));
    EXPECT_TRUE(m_cache.has('Y'));
    EXPECT_TRUE(m_cache.has('Z'));
  }

  {  // ASCII digits
    EXPECT_TRUE(m_cache.has('0'));
    EXPECT_TRUE(m_cache.has('1'));
    EXPECT_TRUE(m_cache.has('2'));
    EXPECT_TRUE(m_cache.has('3'));
    EXPECT_TRUE(m_cache.has('4'));
    EXPECT_TRUE(m_cache.has('5'));
    EXPECT_TRUE(m_cache.has('6'));
    EXPECT_TRUE(m_cache.has('7'));
    EXPECT_TRUE(m_cache.has('8'));
    EXPECT_TRUE(m_cache.has('9'));
  }

  {  // ASCII punctuation and symbols
    EXPECT_TRUE(m_cache.has(' '));
    EXPECT_TRUE(m_cache.has('!'));
    EXPECT_TRUE(m_cache.has('"'));
    EXPECT_TRUE(m_cache.has('#'));
    EXPECT_TRUE(m_cache.has('$'));
    EXPECT_TRUE(m_cache.has('%'));
    EXPECT_TRUE(m_cache.has('&'));
    EXPECT_TRUE(m_cache.has('\''));
    EXPECT_TRUE(m_cache.has('('));
    EXPECT_TRUE(m_cache.has(')'));
    EXPECT_TRUE(m_cache.has('*'));
    EXPECT_TRUE(m_cache.has('+'));
    EXPECT_TRUE(m_cache.has(','));
    EXPECT_TRUE(m_cache.has('-'));
    EXPECT_TRUE(m_cache.has('.'));
    EXPECT_TRUE(m_cache.has('/'));
    EXPECT_TRUE(m_cache.has(':'));
    EXPECT_TRUE(m_cache.has(';'));
    EXPECT_TRUE(m_cache.has('<'));
    EXPECT_TRUE(m_cache.has('='));
    EXPECT_TRUE(m_cache.has('>'));
    EXPECT_TRUE(m_cache.has('?'));
    EXPECT_TRUE(m_cache.has('@'));
    EXPECT_TRUE(m_cache.has('['));
    EXPECT_TRUE(m_cache.has('\\'));
    EXPECT_TRUE(m_cache.has(']'));
    EXPECT_TRUE(m_cache.has('^'));
    EXPECT_TRUE(m_cache.has('_'));
    EXPECT_TRUE(m_cache.has('`'));
    EXPECT_TRUE(m_cache.has('{'));
    EXPECT_TRUE(m_cache.has('|'));
    EXPECT_TRUE(m_cache.has('}'));
    EXPECT_TRUE(m_cache.has('~'));
  }
}

TEST_F(FontCacheTest, At)
{
  m_cache.add_basic_latin(*m_renderer);

  const auto& [texture, metrics] = m_cache.at('a');
  EXPECT_TRUE(texture.get());

  EXPECT_ANY_THROW(m_cache.at(256));
}

TEST_F(FontCacheTest, SubscriptOperator)
{
  m_cache.add_basic_latin(*m_renderer);

  const auto& [texture, metrics] = m_cache['t'];
  EXPECT_TRUE(texture.get());

  EXPECT_ANY_THROW(m_cache[256]);
}

TEST_F(FontCacheTest, TryGetStored)
{
  m_cache.add_basic_latin(*m_renderer);

  constexpr auto id = 12;
  m_cache.store_blended_latin1(id, "bar!?<,.", *m_renderer);

  EXPECT_TRUE(m_cache.try_get_stored(id));
  EXPECT_FALSE(m_cache.try_get_stored(id + 1));
}

TEST_F(FontCacheTest, GetStored)
{
  m_cache.add_latin1(*m_renderer);

  constexpr auto id = 42;

  m_cache.store_blended_latin1(id, "bar!?<,.", *m_renderer);

  EXPECT_TRUE(m_cache.get_stored(id).get());
  EXPECT_ANY_THROW(m_cache.get_stored(id + 1));
}

TEST_F(FontCacheTest, GetFont)
{
  const auto& font = m_cache.get_font();
  EXPECT_EQ(font.family_name(), std::string("Daniel"));
}

TEST_F(FontCacheTest, DISABLED_Interactive)
{
  using cen::unicode;

  constexpr auto id1 = 72;
  constexpr auto id2 = 23;

  {
    m_renderer->set_color(cen::colors::white);
    m_cache.add_latin1(*m_renderer);

    m_renderer->set_color(cen::colors::magenta);
    m_cache.store_blended_latin1(id1, "cool string! <|>", *m_renderer);

    const cen::unicode_string cool = {0x2192, 0x2665, 0x2190, 0x263A};
    m_cache.store_blended_unicode(id2, cool, *m_renderer);
  }

  const cen::unicode_string str = {'c',
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

  cen::event event;
  bool running = true;

  m_window->show();
  while (running) {
    while (event.poll()) {
      if (event.is<cen::quit_event>()) {
        running = false;
        break;
      } else if (const auto* key = event.try_get<cen::keyboard_event>(); key) {
        if (key->state() == cen::button_state::released) {
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

      } else if (const auto* text = event.try_get<cen::text_input_event>();
                 text) {
        changingStr += text->text_utf8();
      }
    }

    m_renderer->clear_with(cen::colors::black);

    using namespace std::string_view_literals;

    m_renderer->render_text(m_cache, "abcdefghijklmnopqrstuvwxyz"sv, {50, 10});
    m_renderer->render_text(m_cache, changingStr, {50, 150});
    m_renderer->render_text(m_cache, str, {50, 100});

    m_renderer->render(m_cache.get_stored(id1), cen::ipoint{50, 200});
    m_renderer->render(m_cache.get_stored(id2), cen::ipoint{300, 400});

    m_renderer->present();
  }
  m_window->hide();
}
