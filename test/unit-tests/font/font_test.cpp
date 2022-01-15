#include "font.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <type_traits>

#include "core/logging.hpp"

using namespace std::string_literals;

namespace {

inline constexpr auto typeWriterPath = "resources/type_writer.ttf";
inline constexpr auto firaCodePath = "resources/fira_code.ttf";
inline constexpr auto danielPath = "resources/daniel.ttf";

}  // namespace

static_assert(std::is_final_v<cen::font>);

static_assert(std::is_nothrow_move_constructible_v<cen::font>);
static_assert(std::is_nothrow_move_assignable_v<cen::font>);

static_assert(!std::is_copy_constructible_v<cen::font>);
static_assert(!std::is_copy_assignable_v<cen::font>);

TEST(Font, Constructor)
{
  ASSERT_THROW(cen::font("", 1), cen::TTFError);
  ASSERT_THROW(cen::font(danielPath, 0), cen::Error);

  ASSERT_THROW(cen::font(""s, 1), cen::TTFError);
  ASSERT_THROW(cen::font(std::string{danielPath}, 0), cen::Error);
}

TEST(Font, ResetStyle)
{
  // We use the std::string constructor here to make sure it works
  cen::font font{std::string{typeWriterPath}, 12};

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
  cen::font font{typeWriterPath, 12};

  ASSERT_FALSE(font.is_bold());

  font.set_bold(true);
  ASSERT_TRUE(font.is_bold());

  font.set_bold(false);
  ASSERT_FALSE(font.is_bold());
}

TEST(Font, SetItalic)
{
  cen::font font{typeWriterPath, 12};

  ASSERT_FALSE(font.is_italic());

  font.set_italic(true);
  ASSERT_TRUE(font.is_italic());

  font.set_italic(false);
  ASSERT_FALSE(font.is_italic());
}

TEST(Font, SetUnderlined)
{
  cen::font font{typeWriterPath, 12};

  ASSERT_FALSE(font.is_underlined());

  font.set_underlined(true);
  ASSERT_TRUE(font.is_underlined());

  font.set_underlined(false);
  ASSERT_FALSE(font.is_underlined());
}

TEST(Font, SetStrikethrough)
{
  cen::font font{typeWriterPath, 12};

  ASSERT_FALSE(font.is_strikethrough());

  font.set_strikethrough(true);
  ASSERT_TRUE(font.is_strikethrough());

  font.set_strikethrough(false);
  ASSERT_FALSE(font.is_strikethrough());
}

TEST(Font, SetOutline)
{
  cen::font font{typeWriterPath, 12};

  ASSERT_FALSE(font.is_outlined());

  font.set_outline(2);
  ASSERT_EQ(font.outline(), 2);
  ASSERT_TRUE(font.is_outlined());

  font.set_outline(0);
  ASSERT_EQ(font.outline(), 0);
  ASSERT_FALSE(font.is_outlined());
}

TEST(Font, SetFontHinting)
{
  cen::font font{typeWriterPath, 12};

  font.set_font_hinting(cen::font_hint::mono);
  ASSERT_EQ(font.font_hinting(), cen::font_hint::mono);

  font.set_font_hinting(cen::font_hint::none);
  ASSERT_EQ(font.font_hinting(), cen::font_hint::none);

  font.set_font_hinting(cen::font_hint::light);
  ASSERT_EQ(font.font_hinting(), cen::font_hint::light);

  font.set_font_hinting(cen::font_hint::normal);
  ASSERT_EQ(font.font_hinting(), cen::font_hint::normal);
}

TEST(Font, SetKerning)
{
  cen::font font{danielPath, 12};

  font.set_kerning(true);
  ASSERT_TRUE(font.has_kerning());

  font.set_kerning(false);
  ASSERT_FALSE(font.has_kerning());
}

TEST(Font, Size)
{
  constexpr auto size = 12;
  const cen::font font{typeWriterPath, size};

  ASSERT_EQ(font.size(), size);
}

TEST(Font, Height)
{
  constexpr auto size = 16;
  const cen::font font{typeWriterPath, size};

  // doesn't have to be equal, but should be close
  ASSERT_EQ(font.height(), size);
}

TEST(Font, IsFixedWidth)
{
  const cen::font firaCode{firaCodePath, 12};  // Fixed width
  const cen::font daniel{danielPath, 12};      // Not fixed width

  ASSERT_TRUE(firaCode.is_fixed_width());
  ASSERT_FALSE(daniel.is_fixed_width());
}

TEST(Font, GetKerning)
{
  cen::font font{danielPath, 36};
  font.set_kerning(true);

  const auto amount = font.get_kerning('A', 'A');
  ASSERT_EQ(amount, 0);

  // TODO test font with heavier kerning
}

TEST(Font, GetMetrics)
{
  const cen::font font{danielPath, 12};

  const auto metrics = font.get_metrics('A');
  ASSERT_TRUE(metrics.has_value());
}

TEST(Font, IsGlyphAvailable)
{
  const cen::font font{firaCodePath, 12};

  ASSERT_TRUE(font.is_glyph_provided('A'));
  ASSERT_TRUE(font.is_glyph_provided(0x003D));  // U+003D is an equal sign
}

TEST(Font, FamilyName)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_STREQ(font.family_name(), "Type Writer");
}

TEST(Font, StyleName)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_STREQ(font.style_name(), "Regular");
}

TEST(Font, CalcSize)
{
  const cen::font font{typeWriterPath, 12};
  const auto size = font.calc_size("foo"s).value();
  ASSERT_GT(size.width, 0);
  ASSERT_GT(size.height, 0);
}

TEST(Font, FontFaceCount)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_GE(font.font_face_count(), 1);
}

TEST(Font, FontHinting)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_EQ(font.font_hinting(), cen::font_hint::normal);
}

TEST(Font, HasKerning)
{
  const cen::font font{danielPath, 12};
  ASSERT_TRUE(font.has_kerning());
}

TEST(Font, LineSkip)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_GT(font.line_skip(), 0);
}

TEST(Font, Ascent)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_GT(font.ascent(), 0);
}

TEST(Font, Descent)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_LT(font.descent(), 0);
}

TEST(Font, Get)
{
  const cen::font font{typeWriterPath, 12};
  ASSERT_TRUE(font.get());
}

TEST(Font, ToString)
{
  const cen::font font{typeWriterPath, 12};
  cen::log_info_raw(cen::to_string(font));
}

TEST(Font, StreamOperator)
{
  const cen::font font{typeWriterPath, 12};
  std::clog << font << '\n';
}