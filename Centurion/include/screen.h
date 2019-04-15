#pragma once

namespace centurion {
namespace tools {

/**
\brief The Screen class provides information about the system display.
\since 1.0.0
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