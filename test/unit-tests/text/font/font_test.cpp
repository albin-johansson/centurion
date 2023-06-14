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

#include "centurion/fonts/font.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // ...

using namespace std::string_literals;

namespace {

constexpr auto type_writer = "resources/type_writer.ttf";
constexpr auto fira_code = "resources/fira_code.ttf";
constexpr auto daniel = "resources/daniel.ttf";

}  // namespace

static_assert(std::is_final_v<cen::font>);

static_assert(std::is_nothrow_move_constructible_v<cen::font>);
static_assert(std::is_nothrow_move_assignable_v<cen::font>);

static_assert(!std::is_copy_constructible_v<cen::font>);
static_assert(!std::is_copy_assignable_v<cen::font>);

TEST(Font, Constructor)
{
  ASSERT_THROW(cen::font("", 1), cen::ttf_error);
  ASSERT_THROW(cen::font(daniel, 0), cen::exception);

  ASSERT_THROW(cen::font(""s, 1), cen::ttf_error);
  ASSERT_THROW(cen::font(std::string {daniel}, 0), cen::exception);

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)
  cen::font_dpi dpi;
  ASSERT_THROW(cen::font("", 0, dpi), cen::exception);
  ASSERT_THROW(cen::font("", 1, dpi), cen::ttf_error);
#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)
}

TEST(Font, ResetStyle)
{
  // We use the std::string constructor here to make sure it works
  cen::font font {std::string {type_writer}, 12};

  font.set_bold(true);
  font.set_italic(true);
  font.set_underlined(true);
  font.set_strikethrough(true);

  font.reset_style();
  ASSERT_FALSE(font.is_bold());
  ASSERT_FALSE(font.is_italic());
  ASSERT_FALSE(font.is_underlined());
  ASSERT_FALSE(font.is_strikethrough());
}

TEST(Font, SetBold)
{
  cen::font font {type_writer, 12};

  ASSERT_FALSE(font.is_bold());

  font.set_bold(true);
  ASSERT_TRUE(font.is_bold());

  font.set_bold(false);
  ASSERT_FALSE(font.is_bold());
}

TEST(Font, SetItalic)
{
  cen::font font {type_writer, 12};

  ASSERT_FALSE(font.is_italic());

  font.set_italic(true);
  ASSERT_TRUE(font.is_italic());

  font.set_italic(false);
  ASSERT_FALSE(font.is_italic());
}

TEST(Font, SetUnderlined)
{
  cen::font font {type_writer, 12};

  ASSERT_FALSE(font.is_underlined());

  font.set_underlined(true);
  ASSERT_TRUE(font.is_underlined());

  font.set_underlined(false);
  ASSERT_FALSE(font.is_underlined());
}

TEST(Font, SetStrikethrough)
{
  cen::font font {type_writer, 12};

  ASSERT_FALSE(font.is_strikethrough());

  font.set_strikethrough(true);
  ASSERT_TRUE(font.is_strikethrough());

  font.set_strikethrough(false);
  ASSERT_FALSE(font.is_strikethrough());
}

TEST(Font, SetOutline)
{
  cen::font font {type_writer, 12};

  ASSERT_FALSE(font.is_outlined());

  font.set_outline(2);
  ASSERT_EQ(font.outline(), 2);
  ASSERT_TRUE(font.is_outlined());

  font.set_outline(0);
  ASSERT_EQ(font.outline(), 0);
  ASSERT_FALSE(font.is_outlined());
}

TEST(Font, SetHinting)
{
  cen::font font {type_writer, 12};

  font.set_hinting(cen::font_hint::mono);
  ASSERT_EQ(font.hinting(), cen::font_hint::mono);

  font.set_hinting(cen::font_hint::none);
  ASSERT_EQ(font.hinting(), cen::font_hint::none);

  font.set_hinting(cen::font_hint::light);
  ASSERT_EQ(font.hinting(), cen::font_hint::light);

  font.set_hinting(cen::font_hint::normal);
  ASSERT_EQ(font.hinting(), cen::font_hint::normal);
}

TEST(Font, SetKerning)
{
  cen::font font {daniel, 12};

  font.set_kerning(true);
  ASSERT_TRUE(font.has_kerning());

  font.set_kerning(false);
  ASSERT_FALSE(font.has_kerning());
}

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

TEST(Font, SetSize)
{
  cen::font font {daniel, 12};
  ASSERT_EQ(12, font.size());

  ASSERT_EQ(cen::success, font.set_size(16));
  ASSERT_EQ(16, font.size());
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

TEST(Font, Size)
{
  constexpr auto size = 12;
  const cen::font font {type_writer, size};

  ASSERT_EQ(font.size(), size);
}

TEST(Font, Height)
{
  constexpr auto size = 16;
  const cen::font font {type_writer, size};

  // doesn't have to be equal, but should be close
  ASSERT_EQ(font.height(), size);
}

TEST(Font, IsFixedWidth)
{
  const cen::font fixed {fira_code, 12};
  ASSERT_TRUE(fixed.is_fixed_width());

  const cen::font proportional {daniel, 12};
  ASSERT_FALSE(proportional.is_fixed_width());
}

TEST(Font, GetKerning)
{
  cen::font font {daniel, 36};
  font.set_kerning(true);

  const auto amount = font.get_kerning('A', 'A');
  ASSERT_EQ(amount, 0);

  // TODO test font with heavier kerning
}

TEST(Font, GetMetrics)
{
  const cen::font font {daniel, 12};

  const auto metrics = font.get_metrics('A');
  ASSERT_TRUE(metrics.has_value());
}

TEST(Font, IsGlyphAvailable)
{
  const cen::font font {fira_code, 12};

  ASSERT_TRUE(font.is_glyph_provided('A'));
  ASSERT_TRUE(font.is_glyph_provided(0x003D));  // U+003D is an equal sign
}

TEST(Font, FamilyName)
{
  const cen::font font {type_writer, 12};
  ASSERT_STREQ(font.family_name(), "Type Writer");
}

TEST(Font, StyleName)
{
  const cen::font font {type_writer, 12};
  ASSERT_STREQ(font.style_name(), "Regular");
}

TEST(Font, CalcSize)
{
  const cen::font font {type_writer, 12};
  const auto size = font.calc_size("foo"s).value();
  ASSERT_GT(size.width, 0);
  ASSERT_GT(size.height, 0);
}

TEST(Font, FaceCount)
{
  const cen::font font {type_writer, 12};
  ASSERT_GE(font.face_count(), 1);
}

TEST(Font, Hinting)
{
  const cen::font font {type_writer, 12};
  ASSERT_EQ(font.hinting(), cen::font_hint::normal);
}

TEST(Font, HasKerning)
{
  const cen::font font {daniel, 12};
  ASSERT_TRUE(font.has_kerning());
}

TEST(Font, LineSkip)
{
  const cen::font font {type_writer, 12};
  ASSERT_GT(font.line_skip(), 0);
}

TEST(Font, Ascent)
{
  const cen::font font {type_writer, 12};
  ASSERT_GT(font.ascent(), 0);
}

TEST(Font, Descent)
{
  const cen::font font {type_writer, 12};
  ASSERT_LT(font.descent(), 0);
}

TEST(Font, Get)
{
  const cen::font font {type_writer, 12};
  ASSERT_TRUE(font.get());
}

TEST(Font, StreamOperator)
{
  const cen::font font {type_writer, 12};
  std::cout << font << '\n';
}

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

TEST(Font, TTFHarfBuzzVersion)
{
  int major {};
  int minor {};
  int patch {};
  TTF_GetHarfBuzzVersion(&major, &minor, &patch);

  const auto ver = cen::ttf_harf_buzz_version();
  ASSERT_EQ(major, ver.major);
  ASSERT_EQ(minor, ver.minor);
  ASSERT_EQ(patch, ver.patch);
}

TEST(Font, TTFFreeTypeVersion)
{
  int major {};
  int minor {};
  int patch {};
  TTF_GetFreeTypeVersion(&major, &minor, &patch);

  const auto ver = cen::ttf_free_type_version();
  ASSERT_EQ(major, ver.major);
  ASSERT_EQ(minor, ver.minor);
  ASSERT_EQ(patch, ver.patch);
}

TEST(Font, MeasureText)
{
  const cen::font font {type_writer, 12};

  const auto measurement = font.measure_text("foobar", 1000);
  ASSERT_TRUE(measurement.has_value());

  const auto size = font.calc_size("foobar");
  ASSERT_TRUE(size.has_value());

  ASSERT_EQ(6, measurement->count);
  ASSERT_EQ(size->width, measurement->extent);
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

TEST(Font, SetWrapAlign)
{
  cen::font font {type_writer, 12};

  font.set_wrap_align(cen::wrap_alignment::left);
  ASSERT_EQ(cen::wrap_alignment::left, font.wrap_align());

  font.set_wrap_align(cen::wrap_alignment::center);
  ASSERT_EQ(cen::wrap_alignment::center, font.wrap_align());

  font.set_wrap_align(cen::wrap_alignment::right);
  ASSERT_EQ(cen::wrap_alignment::right, font.wrap_align());
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)
