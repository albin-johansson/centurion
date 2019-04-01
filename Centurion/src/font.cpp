#include "font.h"
#include <stdexcept>

using centurion::visuals::Font;

Font::Font(const std::string& path, const int size) {
  font = TTF_OpenFont(path.c_str(), size);
  if (font == nullptr) {
    throw std::exception("Failed to located font!");
  } else {
    this->size = size;
  }
}

Font::~Font() { TTF_CloseFont(font); }