/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#include "centurion/render.hpp"
#include "centurion/video/window.hpp"

class FontCacheTest : public testing::Test {
 protected:
  FontCacheTest() : testing::Test {}, cache {"resources/jetbrains_mono.ttf", 12} {}

  static void SetUpTestSuite()
  {
    window = std::make_unique<cen::window>();
    renderer = std::make_unique<cen::renderer>(window->make_renderer());
  }

  static void TearDownTestSuite()
  {
    renderer.reset();
    window.reset();
  }

  const char* utf8_string = "UTF-8_<!?+=";
  const char* latin1_string = "latin1_<!?+=";
  const cen::unicode_string unicode_string {'b', 'a', 'r'};

  inline static std::unique_ptr<cen::window> window;
  inline static std::unique_ptr<cen::renderer> renderer;
  cen::font_cache cache;
};

TEST_F(FontCacheTest, Constructors)
{
  using namespace std::string_literals;
  EXPECT_ANY_THROW(cen::font_cache("foo.ttf"s, 12));
  EXPECT_ANY_THROW(cen::font_cache("foo.ttf", 12));
}

TEST_F(FontCacheTest, HasGlyph)
{
  cache.store_latin1_glyphs(*renderer);

  /* Basic latin range */
  ASSERT_TRUE(cache.has_glyph(0x20));
  ASSERT_FALSE(cache.has_glyph(0x1F));

  ASSERT_TRUE(cache.has_glyph(0x7E));
  ASSERT_FALSE(cache.has_glyph(0x7F));

  /* Latin-1 supplement range */
  ASSERT_TRUE(cache.has_glyph(0xA0));
  ASSERT_FALSE(cache.has_glyph(0x9F));

  ASSERT_TRUE(cache.has_glyph(0xFF));
  ASSERT_FALSE(cache.has_glyph(0x100));

  /* Lowercase latin alphabet */
  ASSERT_TRUE(cache.has_glyph('a'));
  ASSERT_TRUE(cache.has_glyph('b'));
  ASSERT_TRUE(cache.has_glyph('c'));
  ASSERT_TRUE(cache.has_glyph('d'));
  ASSERT_TRUE(cache.has_glyph('e'));
  ASSERT_TRUE(cache.has_glyph('f'));
  ASSERT_TRUE(cache.has_glyph('g'));
  ASSERT_TRUE(cache.has_glyph('h'));
  ASSERT_TRUE(cache.has_glyph('i'));
  ASSERT_TRUE(cache.has_glyph('j'));
  ASSERT_TRUE(cache.has_glyph('k'));
  ASSERT_TRUE(cache.has_glyph('l'));
  ASSERT_TRUE(cache.has_glyph('m'));
  ASSERT_TRUE(cache.has_glyph('n'));
  ASSERT_TRUE(cache.has_glyph('o'));
  ASSERT_TRUE(cache.has_glyph('p'));
  ASSERT_TRUE(cache.has_glyph('q'));
  ASSERT_TRUE(cache.has_glyph('r'));
  ASSERT_TRUE(cache.has_glyph('s'));
  ASSERT_TRUE(cache.has_glyph('t'));
  ASSERT_TRUE(cache.has_glyph('u'));
  ASSERT_TRUE(cache.has_glyph('v'));
  ASSERT_TRUE(cache.has_glyph('x'));
  ASSERT_TRUE(cache.has_glyph('y'));
  ASSERT_TRUE(cache.has_glyph('z'));

  /* Uppercase latin alphabet */
  ASSERT_TRUE(cache.has_glyph('A'));
  ASSERT_TRUE(cache.has_glyph('B'));
  ASSERT_TRUE(cache.has_glyph('C'));
  ASSERT_TRUE(cache.has_glyph('D'));
  ASSERT_TRUE(cache.has_glyph('E'));
  ASSERT_TRUE(cache.has_glyph('F'));
  ASSERT_TRUE(cache.has_glyph('G'));
  ASSERT_TRUE(cache.has_glyph('H'));
  ASSERT_TRUE(cache.has_glyph('I'));
  ASSERT_TRUE(cache.has_glyph('J'));
  ASSERT_TRUE(cache.has_glyph('K'));
  ASSERT_TRUE(cache.has_glyph('L'));
  ASSERT_TRUE(cache.has_glyph('M'));
  ASSERT_TRUE(cache.has_glyph('N'));
  ASSERT_TRUE(cache.has_glyph('O'));
  ASSERT_TRUE(cache.has_glyph('P'));
  ASSERT_TRUE(cache.has_glyph('Q'));
  ASSERT_TRUE(cache.has_glyph('R'));
  ASSERT_TRUE(cache.has_glyph('S'));
  ASSERT_TRUE(cache.has_glyph('T'));
  ASSERT_TRUE(cache.has_glyph('U'));
  ASSERT_TRUE(cache.has_glyph('V'));
  ASSERT_TRUE(cache.has_glyph('X'));
  ASSERT_TRUE(cache.has_glyph('Y'));
  ASSERT_TRUE(cache.has_glyph('Z'));

  /* ASCII digits */
  ASSERT_TRUE(cache.has_glyph('0'));
  ASSERT_TRUE(cache.has_glyph('1'));
  ASSERT_TRUE(cache.has_glyph('2'));
  ASSERT_TRUE(cache.has_glyph('3'));
  ASSERT_TRUE(cache.has_glyph('4'));
  ASSERT_TRUE(cache.has_glyph('5'));
  ASSERT_TRUE(cache.has_glyph('6'));
  ASSERT_TRUE(cache.has_glyph('7'));
  ASSERT_TRUE(cache.has_glyph('8'));
  ASSERT_TRUE(cache.has_glyph('9'));

  /* ASCII punctuation and symbols */
  ASSERT_TRUE(cache.has_glyph(' '));
  ASSERT_TRUE(cache.has_glyph('!'));
  ASSERT_TRUE(cache.has_glyph('"'));
  ASSERT_TRUE(cache.has_glyph('#'));
  ASSERT_TRUE(cache.has_glyph('$'));
  ASSERT_TRUE(cache.has_glyph('%'));
  ASSERT_TRUE(cache.has_glyph('&'));
  ASSERT_TRUE(cache.has_glyph('\''));
  ASSERT_TRUE(cache.has_glyph('('));
  ASSERT_TRUE(cache.has_glyph(')'));
  ASSERT_TRUE(cache.has_glyph('*'));
  ASSERT_TRUE(cache.has_glyph('+'));
  ASSERT_TRUE(cache.has_glyph(','));
  ASSERT_TRUE(cache.has_glyph('-'));
  ASSERT_TRUE(cache.has_glyph('.'));
  ASSERT_TRUE(cache.has_glyph('/'));
  ASSERT_TRUE(cache.has_glyph(':'));
  ASSERT_TRUE(cache.has_glyph(';'));
  ASSERT_TRUE(cache.has_glyph('<'));
  ASSERT_TRUE(cache.has_glyph('='));
  ASSERT_TRUE(cache.has_glyph('>'));
  ASSERT_TRUE(cache.has_glyph('?'));
  ASSERT_TRUE(cache.has_glyph('@'));
  ASSERT_TRUE(cache.has_glyph('['));
  ASSERT_TRUE(cache.has_glyph('\\'));
  ASSERT_TRUE(cache.has_glyph(']'));
  ASSERT_TRUE(cache.has_glyph('^'));
  ASSERT_TRUE(cache.has_glyph('_'));
  ASSERT_TRUE(cache.has_glyph('`'));
  ASSERT_TRUE(cache.has_glyph('{'));
  ASSERT_TRUE(cache.has_glyph('|'));
  ASSERT_TRUE(cache.has_glyph('}'));
  ASSERT_TRUE(cache.has_glyph('~'));
}

TEST_F(FontCacheTest, GetGlyph)
{
  cache.store_basic_latin_glyphs(*renderer);

  const auto& [texture, metrics] = cache.get_glyph('a');
  ASSERT_TRUE(texture.get());

  ASSERT_THROW(cache.get_glyph(256), cen::exception);
}

TEST_F(FontCacheTest, FindGlyph)
{
  cache.store_basic_latin_glyphs(*renderer);
  ASSERT_TRUE(cache.find_glyph('a'));
  ASSERT_TRUE(cache.find_glyph(0x20));
  ASSERT_TRUE(cache.find_glyph(0x7E));
  ASSERT_FALSE(cache.find_glyph(0x7F));
}

TEST_F(FontCacheTest, GetString)
{
  cache.store_latin1_glyphs(*renderer);

  const auto& font = cache.get_font();
  const auto id = cache.store(*renderer, font.render_blended("bar!?<,.", cen::colors::white));
  ASSERT_TRUE(cache.has_string(id));

  ASSERT_TRUE(cache.get_string(id).get());
  ASSERT_THROW(cache.get_string(id + 1), cen::exception);
}

TEST_F(FontCacheTest, FindString)
{
  cache.store_basic_latin_glyphs(*renderer);

  const auto& font = cache.get_font();
  const auto id = cache.store(*renderer, font.render_blended("bar!?<,.", cen::colors::white));

  ASSERT_NE(cache.find_string(id), nullptr);
  ASSERT_EQ(cache.find_string(id + 1), nullptr);
}

TEST_F(FontCacheTest, GetFont)
{
  const auto& font = cache.get_font();
  ASSERT_STREQ("JetBrains Mono", font.family_name());
}

TEST_F(FontCacheTest, ToString)
{
  ASSERT_EQ("font_cache(font: 'JetBrains Mono', size: 12)", cen::to_string(cache));
}