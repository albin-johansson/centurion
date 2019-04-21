#pragma once
#include <SDL_stdinc.h>

namespace centurion {
namespace tools {

/**
\brief The BoolConverter class is a conversion tool between values of bool
and SDL_bool.
\since 1.0.0
*/
class BoolConverter final {
 private:
  BoolConverter() = delete;

 public:
  ~BoolConverter() = default;

  /**
  \brief Converts an SDL_bool value and returns the corresponding default C++
  bool value.
  \param b - the SDL_bool value that will be converted.
  \since 1.0.0
  */
  inline static bool Convert(SDL_bool b) noexcept { return (b) ? true : false; }

  /**
  \brief Converts a bool value and returns the corresponding SDL_bool value.
  \param b - the bool value that will be converted.
  \since 1.0.0
  */
  inline static SDL_bool Convert(bool b) noexcept {
    return (b) ? (SDL_bool::SDL_TRUE) : (SDL_bool::SDL_FALSE);
  }
};

}  // namespace tools
}  // namespace centurion