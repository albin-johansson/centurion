#pragma once
#include <SDL_types.h>

namespace centurion {
namespace tools {

class BooleanConverter final {
 private:
  BooleanConverter() = delete;

 public:
  ~BooleanConverter() = default;

  /**
  \brief Converts an SDL_bool value and returns the corresponding default C++
  bool value.
  \param b - the SDL_bool value that will be converted.
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

class NullChecker {
 public:
  template <class T>
  static bool IsNull(T* arg) {
    return arg == nullptr || arg == NULL;
  }
};

/**
\brief The Screen class provides information about the system display.
*/
class Screen final {
 private:
  Screen() = delete;

 public:
  ~Screen() = default;

  /**
  \brief Returns the width of the screen.
  */
  static int GetWidth();

  /**
  \brief Returns the height of the screen.
  */
  static int GetHeight();
};

}  // namespace tools
}  // namespace centurion