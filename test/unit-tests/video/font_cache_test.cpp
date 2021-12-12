#include "video/font_cache.hpp"

#include <gtest/gtest.h>

#include <functional>   // function
#include <memory>       // unique_ptr
#include <string_view>  // string_view

#include "video/font.hpp"
#include "video/renderer.hpp"
#include "video/window.hpp"

namespace {
inline constexpr auto fontPath = "resources/daniel.ttf";
}

TEST(FontCache, FontConstructor)
{
  cen::font font{fontPath, 12};
  ASSERT_NO_THROW(cen::font_cache{std::move(font)});
}

TEST(FontCache, InPlaceConstructor)
{
  ASSERT_NO_THROW(cen::font_cache(fontPath, 12));

  // Font constructor exceptions
  ASSERT_THROW(cen::font_cache("", 12), cen::TTFError);
  ASSERT_THROW(cen::font_cache(fontPath, 0), cen::Error);
}

class FontCacheTest : public testing::Test
{
 protected:
  using id_type = cen::font_cache::id_type;

  using unicode_signature = void(id_type, const cen::unicode_string&);
  using unicode_store_fn = std::function<unicode_signature>;

  using normal_signature = void(id_type, cen::cstr);
  using normal_store_fn = std::function<normal_signature>;

  FontCacheTest() : testing::Test{}, m_cache{fontPath, 12}
  {}

  static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
    m_renderer = std::make_unique<cen::renderer>(*m_window);
  }

  static void TearDownTestSuite()
  {
    m_renderer.reset();
    m_window.reset();
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
    ASSERT_FALSE(m_cache.has_stored(id));

    store(id, str);
    ASSERT_TRUE(m_cache.has_stored(id));

    ASSERT_NO_THROW(store(id, str));
  }
};

TEST_F(FontCacheTest, StoreBlendedUnicode)
{
  test_store_unicode([this](const id_type id, const cen::unicode_string& str) {
    m_cache.store_blended_unicode(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreBlendedWrappedUnicode)
{
  test_store_unicode([this](const id_type id, const cen::unicode_string& str) {
    m_cache.store_blended_wrapped_unicode(id, str, *m_renderer, 100);
  });
}

TEST_F(FontCacheTest, StoreSolidUnicode)
{
  test_store_unicode([this](const id_type id, const cen::unicode_string& str) {
    m_cache.store_solid_unicode(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreShadedUnicode)
{
  test_store_unicode([this](const id_type id, const cen::unicode_string& str) {
    m_cache.store_shaded_unicode(id, str, *m_renderer, cen::colors::pink);
  });
}

TEST_F(FontCacheTest, StoreBlendedUTF8)
{
  test_store_utf_8([this](const id_type id, cen::cstr str) {
    m_cache.store_blended_utf8(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreBlendedWrappedUTF8)
{
  test_store_utf_8([this](const id_type id, cen::cstr str) {
    m_cache.store_blended_wrapped_utf8(id, str, *m_renderer, 80);
  });
}

TEST_F(FontCacheTest, StoreSolidUTF8)
{
  test_store_utf_8([this](const id_type id, cen::cstr str) {
    m_cache.store_solid_utf8(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreShadedUTF8)
{
  test_store_utf_8([this](const id_type id, cen::cstr str) {
    m_cache.store_shaded_utf8(id, str, *m_renderer, cen::colors::cyan);
  });
}

TEST_F(FontCacheTest, StoreBlendedLatin1)
{
  test_store_latin_1([this](const id_type id, cen::cstr str) {
    m_cache.store_blended_latin1(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreBlendedWrappedLatin1)
{
  test_store_latin_1([this](const id_type id, cen::cstr str) {
    m_cache.store_blended_wrapped_latin1(id, str, *m_renderer, 120);
  });
}

TEST_F(FontCacheTest, StoreSolidLatin1)
{
  test_store_latin_1([this](const id_type id, cen::cstr str) {
    m_cache.store_solid_latin1(id, str, *m_renderer);
  });
}

TEST_F(FontCacheTest, StoreShadedLatin1)
{
  test_store_latin_1([this](const id_type id, cen::cstr str) {
    m_cache.store_shaded_latin1(id, str, *m_renderer, cen::colors::aqua);
  });
}

TEST_F(FontCacheTest, Has)
{
  m_cache.add_basic_latin(*m_renderer);

  {  // Lowercase latin alphabet
    ASSERT_TRUE(m_cache.has('a'));
    ASSERT_TRUE(m_cache.has('b'));
    ASSERT_TRUE(m_cache.has('c'));
    ASSERT_TRUE(m_cache.has('d'));
    ASSERT_TRUE(m_cache.has('e'));
    ASSERT_TRUE(m_cache.has('f'));
    ASSERT_TRUE(m_cache.has('g'));
    ASSERT_TRUE(m_cache.has('h'));
    ASSERT_TRUE(m_cache.has('i'));
    ASSERT_TRUE(m_cache.has('j'));
    ASSERT_TRUE(m_cache.has('k'));
    ASSERT_TRUE(m_cache.has('l'));
    ASSERT_TRUE(m_cache.has('m'));
    ASSERT_TRUE(m_cache.has('n'));
    ASSERT_TRUE(m_cache.has('o'));
    ASSERT_TRUE(m_cache.has('p'));
    ASSERT_TRUE(m_cache.has('q'));
    ASSERT_TRUE(m_cache.has('r'));
    ASSERT_TRUE(m_cache.has('s'));
    ASSERT_TRUE(m_cache.has('t'));
    ASSERT_TRUE(m_cache.has('u'));
    ASSERT_TRUE(m_cache.has('v'));
    ASSERT_TRUE(m_cache.has('x'));
    ASSERT_TRUE(m_cache.has('y'));
    ASSERT_TRUE(m_cache.has('z'));
  }

  {  // Uppercase latin alphabet
    ASSERT_TRUE(m_cache.has('A'));
    ASSERT_TRUE(m_cache.has('B'));
    ASSERT_TRUE(m_cache.has('C'));
    ASSERT_TRUE(m_cache.has('D'));
    ASSERT_TRUE(m_cache.has('E'));
    ASSERT_TRUE(m_cache.has('F'));
    ASSERT_TRUE(m_cache.has('G'));
    ASSERT_TRUE(m_cache.has('H'));
    ASSERT_TRUE(m_cache.has('I'));
    ASSERT_TRUE(m_cache.has('J'));
    ASSERT_TRUE(m_cache.has('K'));
    ASSERT_TRUE(m_cache.has('L'));
    ASSERT_TRUE(m_cache.has('M'));
    ASSERT_TRUE(m_cache.has('N'));
    ASSERT_TRUE(m_cache.has('O'));
    ASSERT_TRUE(m_cache.has('P'));
    ASSERT_TRUE(m_cache.has('Q'));
    ASSERT_TRUE(m_cache.has('R'));
    ASSERT_TRUE(m_cache.has('S'));
    ASSERT_TRUE(m_cache.has('T'));
    ASSERT_TRUE(m_cache.has('U'));
    ASSERT_TRUE(m_cache.has('V'));
    ASSERT_TRUE(m_cache.has('X'));
    ASSERT_TRUE(m_cache.has('Y'));
    ASSERT_TRUE(m_cache.has('Z'));
  }

  {  // ASCII digits
    ASSERT_TRUE(m_cache.has('0'));
    ASSERT_TRUE(m_cache.has('1'));
    ASSERT_TRUE(m_cache.has('2'));
    ASSERT_TRUE(m_cache.has('3'));
    ASSERT_TRUE(m_cache.has('4'));
    ASSERT_TRUE(m_cache.has('5'));
    ASSERT_TRUE(m_cache.has('6'));
    ASSERT_TRUE(m_cache.has('7'));
    ASSERT_TRUE(m_cache.has('8'));
    ASSERT_TRUE(m_cache.has('9'));
  }

  {  // ASCII punctuation and symbols
    ASSERT_TRUE(m_cache.has(' '));
    ASSERT_TRUE(m_cache.has('!'));
    ASSERT_TRUE(m_cache.has('"'));
    ASSERT_TRUE(m_cache.has('#'));
    ASSERT_TRUE(m_cache.has('$'));
    ASSERT_TRUE(m_cache.has('%'));
    ASSERT_TRUE(m_cache.has('&'));
    ASSERT_TRUE(m_cache.has('\''));
    ASSERT_TRUE(m_cache.has('('));
    ASSERT_TRUE(m_cache.has(')'));
    ASSERT_TRUE(m_cache.has('*'));
    ASSERT_TRUE(m_cache.has('+'));
    ASSERT_TRUE(m_cache.has(','));
    ASSERT_TRUE(m_cache.has('-'));
    ASSERT_TRUE(m_cache.has('.'));
    ASSERT_TRUE(m_cache.has('/'));
    ASSERT_TRUE(m_cache.has(':'));
    ASSERT_TRUE(m_cache.has(';'));
    ASSERT_TRUE(m_cache.has('<'));
    ASSERT_TRUE(m_cache.has('='));
    ASSERT_TRUE(m_cache.has('>'));
    ASSERT_TRUE(m_cache.has('?'));
    ASSERT_TRUE(m_cache.has('@'));
    ASSERT_TRUE(m_cache.has('['));
    ASSERT_TRUE(m_cache.has('\\'));
    ASSERT_TRUE(m_cache.has(']'));
    ASSERT_TRUE(m_cache.has('^'));
    ASSERT_TRUE(m_cache.has('_'));
    ASSERT_TRUE(m_cache.has('`'));
    ASSERT_TRUE(m_cache.has('{'));
    ASSERT_TRUE(m_cache.has('|'));
    ASSERT_TRUE(m_cache.has('}'));
    ASSERT_TRUE(m_cache.has('~'));
  }
}

TEST_F(FontCacheTest, At)
{
  m_cache.add_basic_latin(*m_renderer);

  const auto& [texture, metrics] = m_cache.at('a');
  ASSERT_TRUE(texture.get());

  ASSERT_ANY_THROW(m_cache.at(256));
}

TEST_F(FontCacheTest, TryAt)
{
  m_cache.add_basic_latin(*m_renderer);
  ASSERT_TRUE(m_cache.try_at('a'));
  ASSERT_TRUE(m_cache.try_at(0x20));
  ASSERT_TRUE(m_cache.try_at(0x7E));
  ASSERT_FALSE(m_cache.try_at(0x7F));
}

TEST_F(FontCacheTest, SubscriptOperator)
{
  m_cache.add_basic_latin(*m_renderer);

  const auto& [texture, metrics] = m_cache['t'];
  ASSERT_TRUE(texture.get());

  ASSERT_ANY_THROW(m_cache[256]);
}

TEST_F(FontCacheTest, TryGetStored)
{
  m_cache.add_basic_latin(*m_renderer);

  constexpr auto id = 12;
  m_cache.store_blended_latin1(id, "bar!?<,.", *m_renderer);

  ASSERT_TRUE(m_cache.try_get_stored(id));
  ASSERT_FALSE(m_cache.try_get_stored(id + 1));
}

TEST_F(FontCacheTest, GetStored)
{
  m_cache.add_latin1(*m_renderer);

  constexpr auto id = 42;

  m_cache.store_blended_latin1(id, "bar!?<,.", *m_renderer);

  ASSERT_TRUE(m_cache.get_stored(id).get());
  ASSERT_ANY_THROW(m_cache.get_stored(id + 1));
}

TEST_F(FontCacheTest, GetFont)
{
  const auto& font = m_cache.get_font();
  ASSERT_EQ(font.family_name(), std::string("Daniel"));
}
