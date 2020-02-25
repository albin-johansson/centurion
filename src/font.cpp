#ifndef CENTURION_FONT_SOURCE
#define CENTURION_FONT_SOURCE

#include "font.h"

namespace centurion {
namespace video {

CENTURION_DEF
Font::Font(const std::string& file, int size) : size{size}
{
  if (size <= 0) {
    throw CenturionException{"Bad font size!"};
  }

  font = TTF_OpenFont(file.c_str(), size);
  if (!font) {
    throw CenturionException{"Failed to open font! " + Error::msg()};
  }

  style = TTF_GetFontStyle(font);
}

CENTURION_DEF
Font::Font(Font&& other) noexcept
{
  TTF_CloseFont(font);

  font = other.font;
  other.font = nullptr;

  style = other.style;
  size = other.size;
}

CENTURION_DEF
Font::~Font() noexcept
{
  if (font) {
    TTF_CloseFont(font);
  }
}

CENTURION_DEF
Font& Font::operator=(Font&& other) noexcept
{
  TTF_CloseFont(font);

  font = other.font;
  other.font = nullptr;

  style = other.style;
  size = other.size;

  return *this;
}

CENTURION_DEF
std::unique_ptr<Font> Font::unique(const std::string& file, int size)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Font>(file, size);
#else
  return centurion::make_unique<Font>(file, size);
#endif
}

CENTURION_DEF
std::shared_ptr<Font> Font::shared(const std::string& file, int size)
{
  return std::make_shared<Font>(file, size);
}

CENTURION_DEF
void Font::reset() noexcept
{
  style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(font, style);
}

CENTURION_DEF
void Font::add_style(int mask) noexcept
{
  style |= mask;
  TTF_SetFontStyle(font, style);
}

CENTURION_DEF
void Font::remove_style(int mask) noexcept
{
  style &= ~mask;
  TTF_SetFontStyle(font, style);
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
  TTF_SetFontOutline(font, outlined ? 1 : 0);
}

CENTURION_DEF
void Font::set_font_hinting(FontHint hint) noexcept
{
  TTF_SetFontHinting(font, static_cast<int>(hint));
}

CENTURION_DEF
bool Font::is_bold() const noexcept
{
  return style & TTF_STYLE_BOLD;
}

CENTURION_DEF
bool Font::is_italic() const noexcept
{
  return style & TTF_STYLE_ITALIC;
}

CENTURION_DEF
bool Font::is_underlined() const noexcept
{
  return style & TTF_STYLE_UNDERLINE;
}

CENTURION_DEF
bool Font::is_strikethrough() const noexcept
{
  return style & TTF_STYLE_STRIKETHROUGH;
}

CENTURION_DEF
bool Font::is_outlined() const noexcept
{
  return TTF_GetFontOutline(font);
}

CENTURION_DEF
bool Font::is_fixed_width() const noexcept
{
  return TTF_FontFaceIsFixedWidth(font);
}

CENTURION_DEF
int Font::get_string_width(const std::string& s) const noexcept
{
  int width = 0;
  TTF_SizeText(font, s.c_str(), &width, nullptr);
  return width;
}

CENTURION_DEF
int Font::get_string_height(const std::string& s) const noexcept
{
  int height = 0;
  TTF_SizeText(font, s.c_str(), nullptr, &height);
  return height;
}

CENTURION_DEF
int Font::get_size() const noexcept
{
  return size;
}

CENTURION_DEF
int Font::get_height() const noexcept
{
  return TTF_FontHeight(font);
}

CENTURION_DEF
int Font::get_descent() const noexcept
{
  return TTF_FontDescent(font);
}

CENTURION_DEF
int Font::get_ascent() const noexcept
{
  return TTF_FontAscent(font);
}

CENTURION_DEF
int Font::get_line_skip() const noexcept
{
  return TTF_FontLineSkip(font);
}

CENTURION_DEF
int Font::get_font_faces() const noexcept
{
  return static_cast<int>(TTF_FontFaces(font));
}

CENTURION_DEF
FontHint Font::get_font_hinting() const noexcept
{
  return static_cast<FontHint>(TTF_GetFontHinting(font));
}

CENTURION_DEF
std::string Font::get_family_name() const noexcept
{
  return TTF_FontFaceFamilyName(font);
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF
std::optional<std::string> Font::get_style_name() const noexcept
{
  const auto* name = TTF_FontFaceStyleName(font);
  if (name) {
    return name;
  } else {
    return std::nullopt;
  }
}

#endif

CENTURION_DEF
std::string Font::to_string() const
{
  const auto idStr = "Font@" + address_of(this);
  const auto nameStr = " | Name: " + get_family_name();
  const auto sizeStr = ", Size: " + std::to_string(get_size());
  return "[" + idStr + nameStr + sizeStr + "]";
}

CENTURION_DEF
Font::operator TTF_Font*() const noexcept
{
  return font;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_FONT_SOURCE