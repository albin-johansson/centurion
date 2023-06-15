/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/fonts/font_cache.hpp"

#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "centurion/video/renderer.hpp"
#include "centurion/video/window.hpp"

class FontCacheTest : public testing::Test {
 protected:
  FontCacheTest() : mCache {"resources/jetbrains_mono.ttf", 12} {}

  static void SetUpTestSuite()
  {
    mWindow = std::make_unique<cen::window>();
    mRenderer = std::make_unique<cen::renderer>(mWindow->make_renderer());
  }

  static void TearDownTestSuite()
  {
    mRenderer.reset();
    mWindow.reset();
  }

  const char* kUTF8String = "UTF-8_<!?+=";
  const char* kLatin1String = "latin1_<!?+=";
  const cen::unicode_string kUnicodeString {'b', 'a', 'r'};

  inline static std::unique_ptr<cen::window> mWindow;
  inline static std::unique_ptr<cen::renderer> mRenderer;
  cen::font_cache mCache;
};

TEST_F(FontCacheTest, Constructors)
{
  using namespace std::string_literals;
  EXPECT_ANY_THROW(cen::font_cache("foo.ttf"s, 12));
  EXPECT_ANY_THROW(cen::font_cache("foo.ttf", 12));
}

TEST_F(FontCacheTest, HasGlyph)
{
  mCache.store_latin1_glyphs(*mRenderer);

  /* Basic latin range */
  ASSERT_TRUE(mCache.has_glyph(0x20));
  ASSERT_FALSE(mCache.has_glyph(0x1F));

  ASSERT_TRUE(mCache.has_glyph(0x7E));
  ASSERT_FALSE(mCache.has_glyph(0x7F));

  /* Latin-1 supplement range */
  ASSERT_TRUE(mCache.has_glyph(0xA0));
  ASSERT_FALSE(mCache.has_glyph(0x9F));

  ASSERT_TRUE(mCache.has_glyph(0xFF));
  ASSERT_FALSE(mCache.has_glyph(0x100));

  /* Lowercase latin alphabet */
  ASSERT_TRUE(mCache.has_glyph('a'));
  ASSERT_TRUE(mCache.has_glyph('b'));
  ASSERT_TRUE(mCache.has_glyph('c'));
  ASSERT_TRUE(mCache.has_glyph('d'));
  ASSERT_TRUE(mCache.has_glyph('e'));
  ASSERT_TRUE(mCache.has_glyph('f'));
  ASSERT_TRUE(mCache.has_glyph('g'));
  ASSERT_TRUE(mCache.has_glyph('h'));
  ASSERT_TRUE(mCache.has_glyph('i'));
  ASSERT_TRUE(mCache.has_glyph('j'));
  ASSERT_TRUE(mCache.has_glyph('k'));
  ASSERT_TRUE(mCache.has_glyph('l'));
  ASSERT_TRUE(mCache.has_glyph('m'));
  ASSERT_TRUE(mCache.has_glyph('n'));
  ASSERT_TRUE(mCache.has_glyph('o'));
  ASSERT_TRUE(mCache.has_glyph('p'));
  ASSERT_TRUE(mCache.has_glyph('q'));
  ASSERT_TRUE(mCache.has_glyph('r'));
  ASSERT_TRUE(mCache.has_glyph('s'));
  ASSERT_TRUE(mCache.has_glyph('t'));
  ASSERT_TRUE(mCache.has_glyph('u'));
  ASSERT_TRUE(mCache.has_glyph('v'));
  ASSERT_TRUE(mCache.has_glyph('x'));
  ASSERT_TRUE(mCache.has_glyph('y'));
  ASSERT_TRUE(mCache.has_glyph('z'));

  /* Uppercase latin alphabet */
  ASSERT_TRUE(mCache.has_glyph('A'));
  ASSERT_TRUE(mCache.has_glyph('B'));
  ASSERT_TRUE(mCache.has_glyph('C'));
  ASSERT_TRUE(mCache.has_glyph('D'));
  ASSERT_TRUE(mCache.has_glyph('E'));
  ASSERT_TRUE(mCache.has_glyph('F'));
  ASSERT_TRUE(mCache.has_glyph('G'));
  ASSERT_TRUE(mCache.has_glyph('H'));
  ASSERT_TRUE(mCache.has_glyph('I'));
  ASSERT_TRUE(mCache.has_glyph('J'));
  ASSERT_TRUE(mCache.has_glyph('K'));
  ASSERT_TRUE(mCache.has_glyph('L'));
  ASSERT_TRUE(mCache.has_glyph('M'));
  ASSERT_TRUE(mCache.has_glyph('N'));
  ASSERT_TRUE(mCache.has_glyph('O'));
  ASSERT_TRUE(mCache.has_glyph('P'));
  ASSERT_TRUE(mCache.has_glyph('Q'));
  ASSERT_TRUE(mCache.has_glyph('R'));
  ASSERT_TRUE(mCache.has_glyph('S'));
  ASSERT_TRUE(mCache.has_glyph('T'));
  ASSERT_TRUE(mCache.has_glyph('U'));
  ASSERT_TRUE(mCache.has_glyph('V'));
  ASSERT_TRUE(mCache.has_glyph('X'));
  ASSERT_TRUE(mCache.has_glyph('Y'));
  ASSERT_TRUE(mCache.has_glyph('Z'));

  /* ASCII digits */
  ASSERT_TRUE(mCache.has_glyph('0'));
  ASSERT_TRUE(mCache.has_glyph('1'));
  ASSERT_TRUE(mCache.has_glyph('2'));
  ASSERT_TRUE(mCache.has_glyph('3'));
  ASSERT_TRUE(mCache.has_glyph('4'));
  ASSERT_TRUE(mCache.has_glyph('5'));
  ASSERT_TRUE(mCache.has_glyph('6'));
  ASSERT_TRUE(mCache.has_glyph('7'));
  ASSERT_TRUE(mCache.has_glyph('8'));
  ASSERT_TRUE(mCache.has_glyph('9'));

  /* ASCII punctuation and symbols */
  ASSERT_TRUE(mCache.has_glyph(' '));
  ASSERT_TRUE(mCache.has_glyph('!'));
  ASSERT_TRUE(mCache.has_glyph('"'));
  ASSERT_TRUE(mCache.has_glyph('#'));
  ASSERT_TRUE(mCache.has_glyph('$'));
  ASSERT_TRUE(mCache.has_glyph('%'));
  ASSERT_TRUE(mCache.has_glyph('&'));
  ASSERT_TRUE(mCache.has_glyph('\''));
  ASSERT_TRUE(mCache.has_glyph('('));
  ASSERT_TRUE(mCache.has_glyph(')'));
  ASSERT_TRUE(mCache.has_glyph('*'));
  ASSERT_TRUE(mCache.has_glyph('+'));
  ASSERT_TRUE(mCache.has_glyph(','));
  ASSERT_TRUE(mCache.has_glyph('-'));
  ASSERT_TRUE(mCache.has_glyph('.'));
  ASSERT_TRUE(mCache.has_glyph('/'));
  ASSERT_TRUE(mCache.has_glyph(':'));
  ASSERT_TRUE(mCache.has_glyph(';'));
  ASSERT_TRUE(mCache.has_glyph('<'));
  ASSERT_TRUE(mCache.has_glyph('='));
  ASSERT_TRUE(mCache.has_glyph('>'));
  ASSERT_TRUE(mCache.has_glyph('?'));
  ASSERT_TRUE(mCache.has_glyph('@'));
  ASSERT_TRUE(mCache.has_glyph('['));
  ASSERT_TRUE(mCache.has_glyph('\\'));
  ASSERT_TRUE(mCache.has_glyph(']'));
  ASSERT_TRUE(mCache.has_glyph('^'));
  ASSERT_TRUE(mCache.has_glyph('_'));
  ASSERT_TRUE(mCache.has_glyph('`'));
  ASSERT_TRUE(mCache.has_glyph('{'));
  ASSERT_TRUE(mCache.has_glyph('|'));
  ASSERT_TRUE(mCache.has_glyph('}'));
  ASSERT_TRUE(mCache.has_glyph('~'));
}

TEST_F(FontCacheTest, GetGlyph)
{
  mCache.store_basic_latin_glyphs(*mRenderer);

  const auto& [texture, metrics] = mCache.get_glyph('a');
  ASSERT_TRUE(texture.get());

  ASSERT_THROW(mCache.get_glyph(256), cen::exception);
}

TEST_F(FontCacheTest, FindGlyph)
{
  mCache.store_basic_latin_glyphs(*mRenderer);
  ASSERT_TRUE(mCache.find_glyph('a'));
  ASSERT_TRUE(mCache.find_glyph(0x20));
  ASSERT_TRUE(mCache.find_glyph(0x7E));
  ASSERT_FALSE(mCache.find_glyph(0x7F));
}

TEST_F(FontCacheTest, GetString)
{
  mCache.store_latin1_glyphs(*mRenderer);

  const auto& font = mCache.get_font();
  const auto id =
      mCache.store(*mRenderer, font.render_blended("bar!?<,.", cen::colors::white));
  ASSERT_TRUE(mCache.has_string(id));

  ASSERT_TRUE(mCache.get_string(id).get());
  ASSERT_THROW(mCache.get_string(id + 1), cen::exception);
}

TEST_F(FontCacheTest, FindString)
{
  mCache.store_basic_latin_glyphs(*mRenderer);

  const auto& font = mCache.get_font();
  const auto id =
      mCache.store(*mRenderer, font.render_blended("bar!?<,.", cen::colors::white));

  ASSERT_NE(mCache.find_string(id), nullptr);
  ASSERT_EQ(mCache.find_string(id + 1), nullptr);
}

TEST_F(FontCacheTest, GetFont)
{
  const auto& font = mCache.get_font();
  ASSERT_STREQ("JetBrains Mono", font.family_name());
}

TEST_F(FontCacheTest, ToString)
{
  ASSERT_EQ("font_cache(font: 'JetBrains Mono', size: 12)", cen::to_string(mCache));
}