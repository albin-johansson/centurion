#include "video/font.hpp"

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

static_assert(std::is_final_v<cen::Font>);

static_assert(std::is_nothrow_move_constructible_v<cen::Font>);
static_assert(std::is_nothrow_move_assignable_v<cen::Font>);

static_assert(!std::is_copy_constructible_v<cen::Font>);
static_assert(!std::is_copy_assignable_v<cen::Font>);

TEST(Font, Constructor)
{
  ASSERT_THROW(cen::Font("", 1), cen::TTFError);
  ASSERT_THROW(cen::Font(danielPath, 0), cen::Error);

  ASSERT_THROW(cen::Font(""s, 1), cen::TTFError);
  ASSERT_THROW(cen::Font(std::string{danielPath}, 0), cen::Error);
}

TEST(Font, ResetStyle)
{
  // We use the std::string constructor here to make sure it works
  cen::Font font{std::string{typeWriterPath}, 12};

  font.SetBold(true);
  font.SetItalic(true);
  font.SetUnderlined(true);
  font.SetStrikethrough(true);

  font.ResetStyle();
  ASSERT_FALSE(font.IsBold());
  ASSERT_FALSE(font.IsItalic());
  ASSERT_FALSE(font.IsUnderlined());
  ASSERT_FALSE(font.IsStrikethrough());
}

TEST(Font, SetBold)
{
  cen::Font font{typeWriterPath, 12};

  ASSERT_FALSE(font.IsBold());

  font.SetBold(true);
  ASSERT_TRUE(font.IsBold());

  font.SetBold(false);
  ASSERT_FALSE(font.IsBold());
}

TEST(Font, SetItalic)
{
  cen::Font font{typeWriterPath, 12};

  ASSERT_FALSE(font.IsItalic());

  font.SetItalic(true);
  ASSERT_TRUE(font.IsItalic());

  font.SetItalic(false);
  ASSERT_FALSE(font.IsItalic());
}

TEST(Font, SetUnderlined)
{
  cen::Font font{typeWriterPath, 12};

  ASSERT_FALSE(font.IsUnderlined());

  font.SetUnderlined(true);
  ASSERT_TRUE(font.IsUnderlined());

  font.SetUnderlined(false);
  ASSERT_FALSE(font.IsUnderlined());
}

TEST(Font, SetStrikethrough)
{
  cen::Font font{typeWriterPath, 12};

  ASSERT_FALSE(font.IsStrikethrough());

  font.SetStrikethrough(true);
  ASSERT_TRUE(font.IsStrikethrough());

  font.SetStrikethrough(false);
  ASSERT_FALSE(font.IsStrikethrough());
}

TEST(Font, SetOutline)
{
  cen::Font font{typeWriterPath, 12};

  ASSERT_FALSE(font.IsOutlined());

  font.SetOutline(2);
  ASSERT_EQ(font.GetOutline(), 2);
  ASSERT_TRUE(font.IsOutlined());

  font.SetOutline(0);
  ASSERT_EQ(font.GetOutline(), 0);
  ASSERT_FALSE(font.IsOutlined());
}

TEST(Font, SetFontHinting)
{
  cen::Font font{typeWriterPath, 12};

  font.SetFontHinting(cen::FontHint::Mono);
  ASSERT_EQ(font.GetFontHinting(), cen::FontHint::Mono);

  font.SetFontHinting(cen::FontHint::None);
  ASSERT_EQ(font.GetFontHinting(), cen::FontHint::None);

  font.SetFontHinting(cen::FontHint::Light);
  ASSERT_EQ(font.GetFontHinting(), cen::FontHint::Light);

  font.SetFontHinting(cen::FontHint::Normal);
  ASSERT_EQ(font.GetFontHinting(), cen::FontHint::Normal);
}

TEST(Font, SetKerning)
{
  cen::Font font{danielPath, 12};

  font.SetKerning(true);
  ASSERT_TRUE(font.HasKerning());

  font.SetKerning(false);
  ASSERT_FALSE(font.HasKerning());
}

TEST(Font, GetSize)
{
  constexpr auto size = 12;
  const cen::Font font{typeWriterPath, size};

  ASSERT_EQ(font.GetSize(), size);
}

TEST(Font, GetHeight)
{
  constexpr auto size = 16;
  const cen::Font font{typeWriterPath, size};

  // doesn't have to be equal, but should be close
  ASSERT_EQ(font.GetHeight(), size);
}

TEST(Font, IsFixedWidth)
{
  const cen::Font firaCode{firaCodePath, 12};  // Fixed width
  const cen::Font daniel{danielPath, 12};      // Not fixed width

  ASSERT_TRUE(firaCode.IsFixedWidth());
  ASSERT_FALSE(daniel.IsFixedWidth());
}

TEST(Font, GetKerning)
{
  cen::Font font{danielPath, 36};
  font.SetKerning(true);

  const auto amount = font.GetKerning('A', 'A');
  ASSERT_EQ(amount, 0);

  // TODO test font with heavier kerning
}

TEST(Font, GetMetrics)
{
  const cen::Font font{danielPath, 12};

  const auto metrics = font.GetMetrics('A');
  ASSERT_TRUE(metrics.has_value());
}

TEST(Font, IsGlyphAvailable)
{
  const cen::Font font{firaCodePath, 12};

  ASSERT_TRUE(font.IsGlyphProvided('A'));
  ASSERT_TRUE(font.IsGlyphProvided(0x003D));  // U+003D is an equal sign
}

TEST(Font, GetFamilyName)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_STREQ(font.GetFamilyName(), "Type Writer");
}

TEST(Font, GetStyleName)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_STREQ(font.GetStyleName(), "Regular");
}

TEST(Font, CalcSize)
{
  const cen::Font font{typeWriterPath, 12};
  const auto size = font.CalcSize("foo"s).value();
  ASSERT_GT(size.width, 0);
  ASSERT_GT(size.height, 0);
}

TEST(Font, GetFontFaces)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_GE(font.GetFontFaces(), 1);
}

TEST(Font, GetFontHinting)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_EQ(font.GetFontHinting(), cen::FontHint::Normal);
}

TEST(Font, HasKerning)
{
  const cen::Font font{danielPath, 12};
  ASSERT_TRUE(font.HasKerning());
}

TEST(Font, GetLineSkip)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_GT(font.GetLineSkip(), 0);
}

TEST(Font, GetAscent)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_GT(font.GetAscent(), 0);
}

TEST(Font, GetDescent)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_LT(font.GetDescent(), 0);
}

TEST(Font, Get)
{
  const cen::Font font{typeWriterPath, 12};
  ASSERT_TRUE(font.get());
}

TEST(Font, ToString)
{
  const cen::Font font{typeWriterPath, 12};
  cen::log_info_raw(cen::to_string(font));
}

TEST(Font, StreamOperator)
{
  const cen::Font font{typeWriterPath, 12};
  std::clog << font << '\n';
}