#pragma once
#include <SDL.h>
#include "centurion.h"

/**
\brief The BooleanConverter class is a conversion tool between values of bool
and SDL_bool.
*/
class centurion::tools::BooleanConverter final {
 private:
  BooleanConverter() = delete;

 public:
  ~BooleanConverter() = default;

  /**
  \brief Converts an SDL_bool value and returns the corresponding default C++
  bool value. \param b - the SDL_bool value that will be converted.
  */
  static bool Convert(SDL_bool b) { return (b) ? true : false; }

  /**
  \brief Converts a bool value and returns the corresponding SDL_bool value.
  \param b - the bool value that will be converted.
  */
  static SDL_bool Convert(bool b) {
    return (b) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE;
  }
};