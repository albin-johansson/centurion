#include "font.h"

using centurion::visuals::Font;

Font::Font(const std::string& path, const int size) {
  font = TTF_OpenFont(path.c_str(), size);
  this->size = size;
}

Font::~Font() { TTF_CloseFont(font); }