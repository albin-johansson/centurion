#pragma once
#include <memory>
#include "centurion_api.h"
#include "window_listener.h"

namespace centurion {

/**
 * The MouseState class provides information about the mouse state, which is an alternative to
 * dealing with mouse events. This class implements the IWindowListener interface. Important
 * note! If you register a MouseState instance as a window listener, you'll need to set the
 * logical size of the window manually, otherwise you'll end up with unexpected behaviour.
 *
 * @see IWindowListener
 * @since 3.0.0
 */
class CENTURION_API MouseState final : public IWindowListener {
 private:
  int mouseX = 0;
  int mouseY = 0;
  int oldX = 0;
  int oldY = 0;

  int logicalWidth = 1;
  int logicalHeight = 1;
  int windowWidth = 1;
  int windowHeight = 1;

  bool leftPressed = false;
  bool rightPressed = false;
  bool prevLeftPressed = false;
  bool prevRightPressed = false;

 public:
  /**
   * @since 3.0.0
   */
  CENTURION_API MouseState() noexcept;

  ~MouseState() override = default;

  /**
   * Creates and returns a unique pointer to a MouseState instance.
   *
   * @return a unique pointer to a MouseState instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<MouseState> unique();

  /**
   * Creates and returns a shared pointer to a MouseState instance.
   *
   * @return a shared pointer to a MouseState instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<MouseState> shared();

  void window_updated(const Window& window) noexcept override;

  /**
   * Updates the mouse state.
   *
   * @since 3.0.0
   */
  CENTURION_API void update() noexcept;

  /**
   * Resets the screen and logical dimensions of the mouse state instance.
   *
   * @since 3.0.0
   */
  CENTURION_API void reset() noexcept;

  /**
   * Sets the logical width that will be used to determine the mouse position. This method will
   * use the default logical width when the supplied value is <= 0.
   *
   * @param logicalWidth the logical width that will be used to determine the mouse position.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_width(int logicalWidth) noexcept;

  /**
   * Sets the logical height that will be used to determine the mouse position. This method will
   * use the default logical height when the supplied value is <= 0.
   *
   * @param logicalHeight the logical height that will be used to determine the mouse position.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_height(int logicalHeight) noexcept;

  /**
   * Sets the screen width that the mouse state instance will use when calculating the mouse
   * position. This method will use the default window width when the supplied value is <= 0.
   *
   * @param screenWidth the width of the screen.
   * @since 3.0.0
   */
  CENTURION_API void set_window_width(int windowWidth) noexcept;

  /**
   * Sets the screen height that the mouse state instance will use when calculating the mouse
   * position. This method will use the default window height when the supplied value is <= 0.
   *
   * @param windowHeight the height of the screen.
   * @since 3.0.0
   */
  CENTURION_API void set_window_height(int windowHeight) noexcept;

  /**
   * Returns the x-coordinate of the mouse.
   *
   * @return the x-coordinate of the mouse.
   * @since 3.0.0
   */
  CENTURION_API int get_mouse_x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse.
   *
   * @return the y-coordinate of the mouse.
   * @since 3.0.0
   */
  CENTURION_API int get_mouse_y() const noexcept;

  /**
   * Returns the window width used by the mouse state instance.
   *
   * @return the window width used by the mouse state instance, 1 is used by default.
   * @since 3.0.0
   */
  CENTURION_API int get_window_width() const noexcept;

  /**
   * Returns the window height used by the mouse state instance.
   *
   * @return the window height used by the mouse state instance, 1 is used by default.
   * @since 3.0.0
   */
  CENTURION_API int get_window_height() const noexcept;

  /**
   * Returns the logical width used by the mouse state instance.
   *
   * @return the logical width used by the mouse state instance, 1 is used by default.
   * @since 3.0.0
   */
  CENTURION_API int get_logical_width() const noexcept;

  /**
   * Returns the logical height used by the mouse state instance.
   *
   * @return the logical height used by the mouse state instance, 1 is used by default.
   * @since 3.0.0
   */
  CENTURION_API int get_logical_height() const noexcept;

  /**
   * Indicates whether or not the left mouse button is currently pressed.
   *
   * @return true if the left mouse button is pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API bool is_left_button_pressed() const noexcept;

  /**
   * Indicates whether or not the right mouse button is currently pressed.
   *
   * @return true if the right mouse button is pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API bool is_right_button_pressed() const noexcept;

  /**
   * Indicates whether or not the left mouse button was released.
   *
   * @return true if the left mouse button was released; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API bool was_left_button_released() const noexcept;

  /**
   * Indicates whether or not the right mouse button was released.
   *
   * @return true if the right mouse button was released; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API bool was_right_button_released() const noexcept;

  /**
   * Indicates whether or not the mouse was moved.
   *
   * @return true if the mouse was moved; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API bool was_mouse_moved() const noexcept;

};

}
