#ifndef CENTURION_FONT_SOURCE
#define CENTURION_FONT_SOURCE

#include "font.h"

#include "centurion_utils.h"
#include "error.h"

namespace centurion {

/* Any sufficiently advanced technology is indistinguishable from magic. */

CENTURION_DEF
Font::Font(CZString file, int size) : m_size{size}
{
  if (!file) {
    throw CenturionException{"Cannot create Font from null path!"};
  }

  if (size <= 0) {
    throw CenturionException{"Bad font size!"};
  }

  m_font = TTF_OpenFont(file, size);
  if (!m_font) {
    throw detail::Error::from_ttf("Failed to open font!");
  }

  m_style = TTF_GetFontStyle(m_font);
}

CENTURION_DEF
Font::Font(Font&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Font::~Font() noexcept
{
  destroy();
}

CENTURION_DEF
Font& Font::operator=(Font&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void Font::destroy() noexcept
{
  if (m_font) {
    TTF_CloseFont(m_font);
  }
}

CENTURION_DEF
void Font::move(Font&& other) noexcept
{
  destroy();

  m_font = other.m_font;
  m_style = other.m_style;
  m_size = other.m_size;

  other.m_font = nullptr;
}

CENTURION_DEF
UniquePtr<Font> Font::unique(CZString file, int size)
{
  return centurion::detail::make_unique<Font>(file, size);
}

CENTURION_DEF
SharedPtr<Font> Font::shared(CZString file, int size)
{
  return std::make_shared<Font>(file, size);
}

CENTURION_DEF
void Font::reset() noexcept
{
  m_style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void Font::add_style(int mask) noexcept
{
  m_style |= mask;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void Font::remove_style(int mask) noexcept
{
  m_style &= ~mask;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void Font::set_bold(bool bold) noexcept
{
  if (bold) {
    add_style(TTF_STYLE_BOLD);
  } else {
    remove_style(TTF_STYLE_BOLD);
  }
}

CENTURION_DEF
void Font::set_italic(bool italic) noexcept
{
  if (italic) {
    add_style(TTF_STYLE_ITALIC);
  } else {
    remove_style(TTF_STYLE_ITALIC);
  }
}

CENTURION_DEF
void Font::set_underlined(bool underlined) noexcept
{
  if (underlined) {
    add_style(TTF_STYLE_UNDERLINE);
  } else {
    remove_style(TTF_STYLE_UNDERLINE);
  }
}

CENTURION_DEF
void Font::set_strikethrough(bool strikethrough) noexcept
{
  if (strikethrough) {
    add_style(TTF_STYLE_STRIKETHROUGH);
  } else {
    remove_style(TTF_STYLE_STRIKETHROUGH);
  }
}

CENTURION_DEF
void Font::set_outlined(bool outlined) noexcept
{
  TTF_SetFontOutline(m_font, outlined ? 1 : 0);
}

CENTURION_DEF
void Font::set_font_hinting(FontHint hint) noexcept
{
  TTF_SetFontHinting(m_font, static_cast<int>(hint));
}

CENTURION_DEF
bool Font::bold() const noexcept
{
  return m_style & TTF_STYLE_BOLD;
}

CENTURION_DEF
bool Font::italic() const noexcept
{
  return m_style & TTF_STYLE_ITALIC;
}

CENTURION_DEF
bool Font::underlined() const noexcept
{
  return m_style & TTF_STYLE_UNDERLINE;
}

CENTURION_DEF
bool Font::strikethrough() const noexcept
{
  return m_style & TTF_STYLE_STRIKETHROUGH;
}

CENTURION_DEF
bool Font::outlined() const noexcept
{
  return TTF_GetFontOutline(m_font);
}

CENTURION_DEF
bool Font::is_fixed_width() const noexcept
{
  return TTF_FontFaceIsFixedWidth(m_font);
}

CENTURION_DEF
int Font::string_width(CZString s) const noexcept
{
  int width = 0;
  TTF_SizeText(m_font, s, &width, nullptr);
  return width;
}

CENTURION_DEF
int Font::string_height(CZString s) const noexcept
{
  int height = 0;
  TTF_SizeText(m_font, s, nullptr, &height);
  return height;
}

CENTURION_DEF
int Font::height() const noexcept
{
  return TTF_FontHeight(m_font);
}

CENTURION_DEF
int Font::descent() const noexcept
{
  return TTF_FontDescent(m_font);
}

CENTURION_DEF
int Font::ascent() const noexcept
{
  return TTF_FontAscent(m_font);
}

CENTURION_DEF
int Font::line_skip() const noexcept
{
  return TTF_FontLineSkip(m_font);
}

CENTURION_DEF
int Font::font_faces() const noexcept
{
  return static_cast<int>(TTF_FontFaces(m_font));
}

CENTURION_DEF
FontHint Font::font_hinting() const noexcept
{
  return static_cast<FontHint>(TTF_GetFontHinting(m_font));
}

CENTURION_DEF
CZString Font::family_name() const noexcept
{
  return TTF_FontFaceFamilyName(m_font);
}

CENTURION_DEF
CZString Font::style_name() const noexcept
{
  return TTF_FontFaceStyleName(m_font);
}

CENTURION_DEF
std::string Font::to_string() const
{
  const auto idStr = "Font@" + detail::address_of(this);
  const auto nameStr = " | Name: " + std::string{family_name()};
  const auto sizeStr = ", Size: " + std::to_string(size());
  return "[" + idStr + nameStr + sizeStr + "]";
}

}  // namespace centurion

#endif  // CENTURION_FONT_SOURCE