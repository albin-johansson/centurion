#include "ctn_font.h"
#include <stdexcept>

namespace centurion {
namespace visuals {

Font::Font(const std::string &path, const int size) {
  font = TTF_OpenFont(path.c_str(), size);
  if (font == nullptr) {
    throw std::exception();
  } else {
    this->size = size;
    styleMask = 0;
    ResetStyle();
    SetOutlined(false);
  }
}

Font::~Font() { TTF_CloseFont(font); }

void Font::ApplyStyle(int style) noexcept {
  styleMask |= style;
  SetStyle(styleMask);
}

void Font::RemoveStyle(int style) noexcept {
  styleMask &= ~style;
  SetStyle(styleMask);
}

void Font::ResetStyle() noexcept { SetStyle(TTF_STYLE_NORMAL); }

void Font::SetStyle(int style) noexcept {
  if (IsValidStyle(style)) {
    styleMask = style;
    TTF_SetFontStyle(font, style);
  }
}

void Font::SetOutlined(bool isOutlined) noexcept {
  if (isOutlined) {
    TTF_SetFontOutline(font, 1);
  } else {
    TTF_SetFontOutline(font, 0);
  }
}

void Font::SetBold(bool isBold) noexcept {
  if (isBold) {
    ApplyStyle(TTF_STYLE_BOLD);
  } else {
    RemoveStyle(TTF_STYLE_BOLD);
  }
}

void Font::SetItalic(bool isItalic) noexcept {
  if (isItalic) {
    ApplyStyle(TTF_STYLE_ITALIC);
  } else {
    RemoveStyle(TTF_STYLE_ITALIC);
  }
}

void Font::SetUnderlined(bool isUnderlined) noexcept {
  if (isUnderlined) {
    ApplyStyle(TTF_STYLE_UNDERLINE);
  } else {
    RemoveStyle(TTF_STYLE_UNDERLINE);
  }
}

void Font::SetStrikethrough(bool isStrikethrough) noexcept {
  if (isStrikethrough) {
    ApplyStyle(TTF_STYLE_STRIKETHROUGH);
  } else {
    RemoveStyle(TTF_STYLE_STRIKETHROUGH);
  }
}

bool Font::IsValidStyle(int style) noexcept {
  return (style & TTF_STYLE_BOLD) || (style & TTF_STYLE_ITALIC) ||
      (style & TTF_STYLE_NORMAL) || (style & TTF_STYLE_STRIKETHROUGH) ||
      (style & TTF_STYLE_UNDERLINE);
}

int Font::GetStringWidth(const std::string &str) const noexcept {
  int w = 0;
  TTF_SizeText(font, str.c_str(), &w, NULL);
  return w;
}

int Font::GetStringHeight(const std::string &str) const noexcept {
  int h = 0;
  TTF_SizeText(font, str.c_str(), NULL, &h);
  return h;
}

Font_sptr Font::CreateShared(const std::string &path, int size) {
  return std::make_shared<Font>(path, size);
}

Font_uptr Font::CreateUnique(const std::string &path, int size) {
  return std::make_unique<Font>(path, size);
}

}  // namespace visuals
}  // namespace centurion