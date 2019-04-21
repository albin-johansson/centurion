#pragma once

namespace centurion {
namespace tools {

/**
\brief The Screen class represents the system display.
\since 1.0.0
*/
class Screen final {
 private:
  Screen() = delete;

 public:
  ~Screen() = default;

  /**
  \brief Assigns whether the screen saver is enabled.
  \param enabled - true if the screen saver should be enabled, false otherwise.
  \since 1.1.0
  */
  static void SetScreenSaverEnabled(bool enabled) noexcept;

  /**
  \brief Returns the width of the screen.
  \since 1.0.0
  */
  static int GetWidth();

  /**
  \brief Returns the height of the screen.
  \since 1.0.0
  */
  static int GetHeight();
};

}  // namespace tools
}  // namespace centurion