#pragma once
#include "centurion.h"

/**
\brief The Screen class provides information about the system display.
*/
class centurion::Screen final {
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