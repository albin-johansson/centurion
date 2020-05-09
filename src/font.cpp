#ifndef CENTURION_FONT_SOURCE
#define CENTURION_FONT_SOURCE

#include "font.h"

#include "centurion_utils.h"

namespace centurion {

/* Any sufficiently advanced technology is indistinguishable from magic. */

CENTURION_DEF
Font::Font(const std::string& file, int size) : m_size{size}
{
  if (size <= 0) {
    throw CenturionException{"Bad font size!"};
  }

  m_font = TTF_OpenFont(file.c_str(), size);
  if (!m_font) {
    throw CenturionException{"Failed to open font! " + Error::msg()};
  }

  m_style = TTF_GetFontStyle(m_font);
}

CENTURION_DEF
Font::Font(Font&& other) noexcept
{
  TTF_CloseFont(m_font);

  m_font = other.m_font;
  other.m_font = nullptr;

  m_style = other.m_style;
  m_size = other.m_size;
}

CENTURION_DEF
Font::~Font() noexcept
{
  if (m_font) {
    TTF_CloseFont(m_font);
  }
}

CENTURION_DEF
Font& Font::operator=(Font&& other) noexcept
{
  TTF_CloseFont(m_font);

  m_font = other.m_font;
  other.m_font = nullptr;

  m_style = other.m_style;
  m_size = other.m_size;

  return *this;
}

CENTURION_DEF
std::unique_ptr<Font> Font::unique(const std::string& file, int size)
{
  return centurion::detail::make_unique<Font>(file, size);
}

CENTURION_DEF
std::shared_ptr<Font> Font::shared(const std::string& file, int size)
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
int Font::string_width(const std::string& s) const noexcept
{
  int width = 0;
  TTF_SizeText(m_font, s.c_str(), &width, nullptr);
  return width;
}

CENTURION_DEF
int Font::string_height(const std::string& s) const noexcept
{
  int height = 0;
  TTF_SizeText(m_font, s.c_str(), nullptr, &height);
  return height;
}

CENTURION_DEF
int Font::size() const noexcept
{
  return m_size;
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
std::string Font::family_name() const noexcept
{
  return TTF_FontFaceFamilyName(m_font);
}

CENTURION_DEF
Optional<std::string> Font::style_name() const noexcept
{
  const auto* name = TTF_FontFaceStyleName(m_font);
  if (name) {
    return name;
  } else {
    return nothing;
  }
}

CENTURION_DEF
std::string Font::to_string() const
{
  const auto idStr = "Font@" + detail::address_of(this);
  const auto nameStr = " | Name: " + family_name();
  const auto sizeStr = ", Size: " + std::to_string(size());
  return "[" + idStr + nameStr + sizeStr + "]";
}

CENTURION_DEF
Font::operator TTF_Font*() const noexcept
{
  return m_font;
}

}  // namespace centurion

#endif  // CENTURION_FONT_SOURCE