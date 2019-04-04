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
  }
}

Font::~Font() { TTF_CloseFont(font); }

void Font::SetStyle(int style) {
  if (IsValidStyle(style)) {
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

bool Font::IsValidStyle(int style) {
  return (style | TTF_STYLE_BOLD) || (style | TTF_STYLE_ITALIC) ||
         (style | TTF_STYLE_NORMAL) || (style | TTF_STYLE_STRIKETHROUGH) ||
         (style | TTF_STYLE_UNDERLINE);
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