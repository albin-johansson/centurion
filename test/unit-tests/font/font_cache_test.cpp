#include <gtest/gtest.h>

#include <functional>   // function
#include <memory>       // unique_ptr
#include <string_view>  // string_view

#include "font.hpp"
#include "render.hpp"
#include "video/window.hpp"

class FontCacheTest : public testing::Test {
 protected:
  FontCacheTest() : testing::Test{}, cache{"resources/daniel.ttf", 12} {}

  static void SetUpTestSuite()
  {
    window = std::make_unique<cen::Window>();
    renderer = std::make_unique<cen::Renderer>(*window);
  }

  static void TearDownTestSuite()
  {
    renderer.reset();
    window.reset();
  }

  const char* utf8_string = "UTF-8_<!?+=";
  const char* latin1_string = "latin1_<!?+=";
  const cen::UnicodeString unicode_string{'b', 'a', 'r'};

  inline static std::unique_ptr<cen::Window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
  cen::FontCache cache;
};

TEST_F(FontCacheTest, Constructors)
{
  using namespace std::string_literals;
  EXPECT_ANY_THROW(cen::FontCache("foo.ttf"s, 12));
  EXPECT_ANY_THROW(cen::FontCache("foo.ttf", 12));
}

TEST_F(FontCacheTest, StoreBlendedUnicode)
{
  // TODO
}

TEST_F(FontCacheTest, StoreWrappedUnicode)
{
  // TODO
}

TEST_F(FontCacheTest, StoreSolidUnicode)
{
  // TODO
}

TEST_F(FontCacheTest, StoreShadedUnicode)
{
  // TODO
}

TEST_F(FontCacheTest, StoreBlendedUTF8)
{
  // TODO
}

TEST_F(FontCacheTest, StoreWrappedUTF8)
{
  // TODO
}

TEST_F(FontCacheTest, StoreSolidUTF8)
{
  // TODO
}

TEST_F(FontCacheTest, StoreShadedUTF8)
{
  // TODO
}

TEST_F(FontCacheTest, StoreBlendedLatin1)
{
  // TODO
}

TEST_F(FontCacheTest, StoreWrappedLatin1)
{
  // TODO
}

TEST_F(FontCacheTest, StoreSolidLatin1)
{
  // TODO
}

TEST_F(FontCacheTest, StoreShadedLatin1)
{
  // TODO
}

TEST_F(FontCacheTest, HasGlyph)
{
  cache.StoreBasicLatinGlyphs(*renderer);

  /* Lowercase latin alphabet */
  ASSERT_TRUE(cache.HasGlyph('a'));
  ASSERT_TRUE(cache.HasGlyph('b'));
  ASSERT_TRUE(cache.HasGlyph('c'));
  ASSERT_TRUE(cache.HasGlyph('d'));
  ASSERT_TRUE(cache.HasGlyph('e'));
  ASSERT_TRUE(cache.HasGlyph('f'));
  ASSERT_TRUE(cache.HasGlyph('g'));
  ASSERT_TRUE(cache.HasGlyph('h'));
  ASSERT_TRUE(cache.HasGlyph('i'));
  ASSERT_TRUE(cache.HasGlyph('j'));
  ASSERT_TRUE(cache.HasGlyph('k'));
  ASSERT_TRUE(cache.HasGlyph('l'));
  ASSERT_TRUE(cache.HasGlyph('m'));
  ASSERT_TRUE(cache.HasGlyph('n'));
  ASSERT_TRUE(cache.HasGlyph('o'));
  ASSERT_TRUE(cache.HasGlyph('p'));
  ASSERT_TRUE(cache.HasGlyph('q'));
  ASSERT_TRUE(cache.HasGlyph('r'));
  ASSERT_TRUE(cache.HasGlyph('s'));
  ASSERT_TRUE(cache.HasGlyph('t'));
  ASSERT_TRUE(cache.HasGlyph('u'));
  ASSERT_TRUE(cache.HasGlyph('v'));
  ASSERT_TRUE(cache.HasGlyph('x'));
  ASSERT_TRUE(cache.HasGlyph('y'));
  ASSERT_TRUE(cache.HasGlyph('z'));

  /* Uppercase latin alphabet */
  ASSERT_TRUE(cache.HasGlyph('A'));
  ASSERT_TRUE(cache.HasGlyph('B'));
  ASSERT_TRUE(cache.HasGlyph('C'));
  ASSERT_TRUE(cache.HasGlyph('D'));
  ASSERT_TRUE(cache.HasGlyph('E'));
  ASSERT_TRUE(cache.HasGlyph('F'));
  ASSERT_TRUE(cache.HasGlyph('G'));
  ASSERT_TRUE(cache.HasGlyph('H'));
  ASSERT_TRUE(cache.HasGlyph('I'));
  ASSERT_TRUE(cache.HasGlyph('J'));
  ASSERT_TRUE(cache.HasGlyph('K'));
  ASSERT_TRUE(cache.HasGlyph('L'));
  ASSERT_TRUE(cache.HasGlyph('M'));
  ASSERT_TRUE(cache.HasGlyph('N'));
  ASSERT_TRUE(cache.HasGlyph('O'));
  ASSERT_TRUE(cache.HasGlyph('P'));
  ASSERT_TRUE(cache.HasGlyph('Q'));
  ASSERT_TRUE(cache.HasGlyph('R'));
  ASSERT_TRUE(cache.HasGlyph('S'));
  ASSERT_TRUE(cache.HasGlyph('T'));
  ASSERT_TRUE(cache.HasGlyph('U'));
  ASSERT_TRUE(cache.HasGlyph('V'));
  ASSERT_TRUE(cache.HasGlyph('X'));
  ASSERT_TRUE(cache.HasGlyph('Y'));
  ASSERT_TRUE(cache.HasGlyph('Z'));

  /* ASCII digits */
  ASSERT_TRUE(cache.HasGlyph('0'));
  ASSERT_TRUE(cache.HasGlyph('1'));
  ASSERT_TRUE(cache.HasGlyph('2'));
  ASSERT_TRUE(cache.HasGlyph('3'));
  ASSERT_TRUE(cache.HasGlyph('4'));
  ASSERT_TRUE(cache.HasGlyph('5'));
  ASSERT_TRUE(cache.HasGlyph('6'));
  ASSERT_TRUE(cache.HasGlyph('7'));
  ASSERT_TRUE(cache.HasGlyph('8'));
  ASSERT_TRUE(cache.HasGlyph('9'));

  /* ASCII punctuation and symbols */
  ASSERT_TRUE(cache.HasGlyph(' '));
  ASSERT_TRUE(cache.HasGlyph('!'));
  ASSERT_TRUE(cache.HasGlyph('"'));
  ASSERT_TRUE(cache.HasGlyph('#'));
  ASSERT_TRUE(cache.HasGlyph('$'));
  ASSERT_TRUE(cache.HasGlyph('%'));
  ASSERT_TRUE(cache.HasGlyph('&'));
  ASSERT_TRUE(cache.HasGlyph('\''));
  ASSERT_TRUE(cache.HasGlyph('('));
  ASSERT_TRUE(cache.HasGlyph(')'));
  ASSERT_TRUE(cache.HasGlyph('*'));
  ASSERT_TRUE(cache.HasGlyph('+'));
  ASSERT_TRUE(cache.HasGlyph(','));
  ASSERT_TRUE(cache.HasGlyph('-'));
  ASSERT_TRUE(cache.HasGlyph('.'));
  ASSERT_TRUE(cache.HasGlyph('/'));
  ASSERT_TRUE(cache.HasGlyph(':'));
  ASSERT_TRUE(cache.HasGlyph(';'));
  ASSERT_TRUE(cache.HasGlyph('<'));
  ASSERT_TRUE(cache.HasGlyph('='));
  ASSERT_TRUE(cache.HasGlyph('>'));
  ASSERT_TRUE(cache.HasGlyph('?'));
  ASSERT_TRUE(cache.HasGlyph('@'));
  ASSERT_TRUE(cache.HasGlyph('['));
  ASSERT_TRUE(cache.HasGlyph('\\'));
  ASSERT_TRUE(cache.HasGlyph(']'));
  ASSERT_TRUE(cache.HasGlyph('^'));
  ASSERT_TRUE(cache.HasGlyph('_'));
  ASSERT_TRUE(cache.HasGlyph('`'));
  ASSERT_TRUE(cache.HasGlyph('{'));
  ASSERT_TRUE(cache.HasGlyph('|'));
  ASSERT_TRUE(cache.HasGlyph('}'));
  ASSERT_TRUE(cache.HasGlyph('~'));
}

TEST_F(FontCacheTest, GetGlyph)
{
  cache.StoreBasicLatinGlyphs(*renderer);

  const auto& [texture, metrics] = cache.GetGlyph('a');
  ASSERT_TRUE(texture.get());

  ASSERT_ANY_THROW(cache.GetGlyph(256));
}

TEST_F(FontCacheTest, TryGetGlyph)
{
  cache.StoreBasicLatinGlyphs(*renderer);
  ASSERT_TRUE(cache.TryGetGlyph('a'));
  ASSERT_TRUE(cache.TryGetGlyph(0x20));
  ASSERT_TRUE(cache.TryGetGlyph(0x7E));
  ASSERT_FALSE(cache.TryGetGlyph(0x7F));
}

TEST_F(FontCacheTest, GetString)
{
  cache.StoreLatin1Glyphs(*renderer);

  const auto id = cache.StoreBlendedLatin1(*renderer, "bar!?<,.", cen::colors::white);
  ASSERT_TRUE(cache.HasString(id));

  ASSERT_TRUE(cache.GetString(id).get());
  ASSERT_ANY_THROW(cache.GetString(id + 1));
}

TEST_F(FontCacheTest, TryGetString)
{
  cache.StoreBasicLatinGlyphs(*renderer);

  const auto id = cache.StoreBlendedLatin1(*renderer, "bar!?<,.", cen::colors::white);

  ASSERT_NE(cache.TryGetString(id), nullptr);
  ASSERT_EQ(cache.TryGetString(id + 1), nullptr);
}

TEST_F(FontCacheTest, GetFont)
{
  const auto& font = cache.GetFont();
  ASSERT_STREQ("Daniel", font.GetFamilyName());
}
