#include "font.h"
#include <stdexcept>

namespace centurion {
namespace visuals {

Font::Font(const std::string& path, const int size) {
  font = TTF_OpenFont(path.c_str(), size);
  if (font == nullptr) {
    throw std::exception("Failed to located font!");
  } else {
    this->size = size;
    styleMask = 0;
    ResetStyle();
    SetOutlined(false);
  }
}

Font::~Font() { TTF_CloseFont(font); }

std::shared_ptr<Font> Font::Create(const std::string& path, int size) {
  return std::make_shared<Font>(path, size);
}

void Font::ApplyStyle(int style) { styleMask |= style; }

void Font::RemoveStyle(int style) { styleMask &= ~style; }

void Font::ResetStyle() { SetStyle(TTF_STYLE_NORMAL); }

void Font::SetStyle(int style) {
  if (IsValidStyle(style)) {
    styleMask = style;
    TTF_SetFontStyle(font, style);
  }
}

void Font::SetOutlined(bool isOutlined) {
  if (isOutlined) {
    TTF_SetFontOutline(font, 1);
  } else {
    TTF_SetFontOutline(font, 0);
  }
}

// TODO implement
void Font::SetBold(bool isBold) {
  if (isBold) {
    ApplyStyle(TTF_STYLE_BOLD);
  } else {
    RemoveStyle(TTF_STYLE_BOLD);
  }
}

void Font::SetItalic(bool isItalic) {
  if (isItalic) {
    ApplyStyle(TTF_STYLE_ITALIC);
  } else {
    RemoveStyle(TTF_STYLE_ITALIC);
  }
}

void Font::SetUnderlined(bool isUnderlined) {
  if (isUnderlined) {
    ApplyStyle(TTF_STYLE_UNDERLINE);
  } else {
    RemoveStyle(TTF_STYLE_UNDERLINE);
  }
}

void Font::SetStrikethrough(bool isStrikethrough) {
  if (isStrikethrough) {
    ApplyStyle(TTF_STYLE_STRIKETHROUGH);
  } else {
    RemoveStyle(TTF_STYLE_STRIKETHROUGH);
  }
}

bool Font::IsValidStyle(int style) {
  return (style | TTF_STYLE_BOLD) || (style | TTF_STYLE_ITALIC) ||
         (style | TTF_STYLE_NORMAL) || (style | TTF_STYLE_STRIKETHROUGH) ||
         (style | TTF_STYLE_UNDERLINE);
}

bool Font::IsBold() const { return styleMask | TTF_STYLE_BOLD; }

bool Font::IsItalic() const { return styleMask | TTF_STYLE_ITALIC; }

bool Font::IsUnderlined() const { return styleMask | TTF_STYLE_UNDERLINE; }

bool Font::IsStrikethrough() const {
  return styleMask | TTF_STYLE_STRIKETHROUGH;
}

int Font::GetStringWidth(const std::string& text) const {
  int w = 0;
  int h = 0;
  TTF_SizeText(font, text.c_str(), &w, &h);
  return w;
}

int Font::GetStringHeight(const std::string& text) const {
  int w = 0;
  int h = 0;
  TTF_SizeText(font, text.c_str(), &w, &h);
  return h;
}

}  // namespace visuals
}  // namespace centurion