/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MOUSE_STATE_HEADER
#define CENTURION_MOUSE_STATE_HEADER

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {
namespace input {

/**
 * The MouseState class provides information about the mouse state, which is an
 * alternative to dealing with mouse events.
 *
 * @since 3.0.0
 */
class MouseState final {
 public:
  /**
   * @since 3.0.0
   */
  CENTURION_API MouseState() noexcept;

  /**
   * Creates and returns a unique pointer to a MouseState instance.
   *
   * @return a unique pointer to a MouseState instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<MouseState> unique();

  /**
   * Creates and returns a shared pointer to a MouseState instance.
   *
   * @return a shared pointer to a MouseState instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<MouseState> shared();

  /**
   * Updates the mouse state. The window width and height will be adjusted to
   * be at least 1.
   *
   * @param windowWidth the current window width, set to 1 by default.
   * @param windowHeight the current window height, set to 1 by default.
   * @since 3.0.0
   */
  CENTURION_API void update(int windowWidth = 1, int windowHeight = 1) noexcept;

  /**
   * Resets the screen and logical dimensions of the mouse state instance.
   *
   * @since 3.0.0
   */
  CENTURION_API void reset() noexcept;

  /**
   * Sets the logical width that will be used to determine the mouse position.
   * The supplied value will be adjusted to be at least 1.
   *
   * @param logicalWidth the logical width that will be used to determine the
   * mouse position.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_width(int logicalWidth) noexcept;

  /**
   * Sets the logical height that will be used to determine the mouse position.
   * The supplied value will be adjusted to be at least 1.
   *
   * @param logicalHeight the logical height that will be used to determine the
   * mouse position.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_height(int logicalHeight) noexcept;

  /**
   * Indicates whether or not the left mouse button was released.
   *
   * @return true if the left mouse button was released; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool was_left_button_released() const noexcept;

  /**
   * Indicates whether or not the right mouse button was released.
   *
   * @return true if the right mouse button was released; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool was_right_button_released() const noexcept;

  /**
   * Indicates whether or not the mouse was moved.
   *
   * @return true if the mouse was moved; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool was_mouse_moved() const noexcept;

  /**
   * Returns the x-coordinate of the mouse.
   *
   * @return the x-coordinate of the mouse.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int mouse_x() const noexcept { return m_mouseX; }

  /**
   * Returns the y-coordinate of the mouse.
   *
   * @return the y-coordinate of the mouse.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int mouse_y() const noexcept { return m_mouseY; }

  /**
   * Returns the logical width used by the mouse state instance.
   *
   * @return the logical width used by the mouse state instance, 1 is used by
   * default.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int logical_width() const noexcept { return m_logicalWidth; }

  /**
   * Returns the logical height used by the mouse state instance.
   *
   * @return the logical height used by the mouse state instance, 1 is used by
   * default.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int logical_height() const noexcept { return m_logicalHeight; }

  /**
   * Indicates whether or not the left mouse button is currently pressed.
   *
   * @return true if the left mouse button is pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  bool is_left_button_pressed() const noexcept { return m_leftPressed; }

  /**
   * Indicates whether or not the right mouse button is currently pressed.
   *
   * @return true if the right mouse button is pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  bool is_right_button_pressed() const noexcept { return m_rightPressed; }

 private:
  int m_mouseX = 0;
  int m_mouseY = 0;
  int m_oldX = 0;
  int m_oldY = 0;
  int m_logicalWidth = 1;
  int m_logicalHeight = 1;
  bool m_leftPressed = false;
  bool m_rightPressed = false;
  bool m_prevLeftPressed = false;
  bool m_prevRightPressed = false;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<MouseState>::value, "MouseState isn't final!");
#endif

static_assert(std::is_nothrow_move_constructible<MouseState>::value,
              "MouseState isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<MouseState>::value,
              "MouseState isn't nothrow move assignable!");

static_assert(std::is_nothrow_copy_constructible<MouseState>::value,
              "MouseState isn't nothrow copy constructible!");

static_assert(std::is_nothrow_copy_assignable<MouseState>::value,
              "MouseState isn't nothrow copy assignable!");

}  // namespace input
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "mouse_state.cpp"
#endif

#endif  // CENTURION_MOUSE_STATE_HEADER