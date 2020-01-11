#pragma once

namespace centurion {

class Window;

/**
 * The IWindowListener interface is a one-method interface that specifies objects that can listen
 * for window updates.
 *
 * @since 0.1.0
 */
class IWindowListener {
 public:
  virtual ~IWindowListener() = default;

  /**
   * Invoked when the window is updated.
   *
   * @param window the window that was updated.
   * @since 0.1.0
   */
  virtual void window_updated(const Window& window) noexcept = 0;
};

}