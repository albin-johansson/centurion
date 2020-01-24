#include "font.h"
#include <stdexcept>
#include <type_traits>
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {

static_assert(std::is_final_v<Font>);

static_assert(std::is_nothrow_move_constructible_v<Font>);
static_assert(std::is_nothrow_move_assignable_v<Font>);

static_assert(!std::is_copy_constructible_v<Font>);
static_assert(!std::is_copy_assignable_v<Font>);

static_assert(std::is_convertible_v<Font, TTF_Font*>);

Font::Font(const std::string& file, int size) : size{size} {
  if (size <= 0) {
    throw std::invalid_argument{"Bad font size!"};
  }

  font = TTF_OpenFont(file.c_str(), size);
  if (!font) {
    throw CenturionException{"Failed to open font! " + Error::msg()};
  }

  style = TTF_GetFontStyle(font);
}

Font::Font(Font&& other) noexcept
    : font{other.font},
      style{other.style},
      size{other.size} {
  other.font = nullptr;
}

Font::~Font() noexcept {
  if (font) {
    TTF_CloseFont(font);
  }
}

Font& Font::operator=(Font&& other) noexcept {
  font = other.font;
  style = other.style;
  size = other.size;

  other.font = nullptr;

  return *this;
}

std::unique_ptr<Font> Font::unique(const std::string& file, int size) {
  return std::make_unique<Font>(file, size);
}

std::shared_ptr<Font> Font::shared(const std::string& file, int size) {
  return std::make_shared<Font>(file, size);
}

void Font::reset() noexcept {
  style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(font, style);
}

void Font::add_style(int mask) noexcept {
  style |= mask;
  TTF_SetFontStyle(font, style);
}

void Font::remove_style(int mask) noexcept {
  style &= ~mask;
  TTF_SetFontStyle(font, style);
}

void Font::set_bold(bool bold) noexcept {
  if (bold) {
    add_style(TTF_STYLE_BOLD);
  } else {
    remove_style(TTF_STYLE_BOLD);
  }
}

void Font::set_italic(bool italic) noexcept {
  if (italic) {
    add_style(TTF_STYLE_ITALIC);
  } else {
    remove_style(TTF_STYLE_ITALIC);
  }
}

void Font::set_underlined(bool underlined) noexcept {
  if (underlined) {
    add_style(TTF_STYLE_UNDERLINE);
  } else {
    remove_style(TTF_STYLE_UNDERLINE);
  }
}

void Font::set_strikethrough(bool strikethrough) noexcept {
  if (strikethrough) {
    add_style(TTF_STYLE_STRIKETHROUGH);
  } else {
    remove_style(TTF_STYLE_STRIKETHROUGH);
  }
}

void Font::set_outlined(bool outlined) noexcept {
  TTF_SetFontOutline(font, outlined ? 1 : 0);
}

bool Font::is_bold() const noexcept {
  return style & TTF_STYLE_BOLD;
}

bool Font::is_italic() const noexcept {
  return style & TTF_STYLE_ITALIC;
}

bool Font::is_underlined() const noexcept {
  return style & TTF_STYLE_UNDERLINE;
}

bool Font::is_strikethrough() const noexcept {
  return style & TTF_STYLE_STRIKETHROUGH;
}

bool Font::is_outlined() const noexcept {
  return TTF_GetFontOutline(font);
}

bool Font::is_fixed_width() const noexcept {
  return TTF_FontFaceIsFixedWidth(font);
}

int Font::get_string_width(const std::string& s) const noexcept {
  int width = 0;
  TTF_SizeText(font, s.c_str(), &width, nullptr);
  return width;
}

int Font::get_string_height(const std::string& s) const noexcept {
  int height = 0;
  TTF_SizeText(font, s.c_str(), nullptr, &height);
  return height;
}

int Font::get_size() const noexcept {
  return size;
}

int Font::get_height() const noexcept {
  return TTF_FontHeight(font);
}

int Font::get_descent() const noexcept {
  return TTF_FontDescent(font);
}

int Font::get_ascent() const noexcept {
  return TTF_FontAscent(font);
}

int Font::get_line_skip() const noexcept {
  return TTF_FontLineSkip(font);
}

int Font::get_font_faces() const noexcept {
  return TTF_FontFaces(font);
}

std::string Font::get_family_name() const noexcept {
  return TTF_FontFaceFamilyName(font);
}

std::optional<std::string> Font::get_style_name() const noexcept {
  const auto* name = TTF_FontFaceStyleName(font);
  if (name) {
    return name;
  } else {
    return std::nullopt;
  }
}

Font::operator TTF_Font*() const noexcept {
  return font;
}

std::ostream& operator<<(std::ostream& stream, const Font& font) {
  stream << "(Font@" << CenturionUtils::address(&font) << ")";
  return stream;
}

}
