#pragma once
#include <SDL_ttf.h>
#include <string>
#include "centurion.h"

/**
\brief The Font class serves as a representation of a True Type font.
*/
class centurion::visuals::Font {
 private:
  TTF_Font* font;
  int size;

 public:
  /**
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  */
  Font(const std::string& path, int size);

  ~Font();

  /**
  \brief Returns a raw pointer to the SDL_font which this Font object
  represents. DO NOT use the returned pointer to call TTF_CloseFont().
  */
  TTF_Font* GetSDLVersion() { return font; }  // FIXME avoid raw pointers

  /**
  \brief Returns the point size of the font that this Font instacne represents.
  */
  int GetSize() const { return size; }
};