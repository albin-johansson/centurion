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

/**
 * @file mouse_state.hpp
 *
 * @brief Provides the `mouse_state` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_MOUSE_STATE_HEADER
#define CENTURION_MOUSE_STATE_HEADER

#include "centurion_api.hpp"
#include "detail/utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class mouse_state
 *
 * @ingroup input
 *
 * @brief Provides information about the mouse state, which is an
 * alternative to dealing with mouse events.
 *
 * @since 3.0.0
 *
 * @headerfile mouse_state.hpp
 */
class mouse_state final
{
 public:
  /**
   * @brief Creates a `mouse_state` instance.
   *
   * @since 3.0.0
   */
  CENTURION_API
  mouse_state() noexcept;

  /**
   * @brief Updates the mouse state. The window width and height will be
   * adjusted to be at least 1.
   *
   * @param windowWidth the current window width, set to 1 by default.
   * @param windowHeight the current window height, set to 1 by default.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void update(int windowWidth = 1, int windowHeight = 1) noexcept;

  /**
   * @brief Resets the screen and logical dimensions of the mouse state
   * instance.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void reset() noexcept;

  /**
   * @brief Sets the logical width that will be used to determine the mouse
   * position.
   *
   * @details The supplied value will be adjusted to be at least 1.
   *
   * @param logicalWidth the logical width that will be used to determine the
   * mouse position.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_logical_width(int logicalWidth) noexcept;

  /**
   * @brief Sets the logical height that will be used to determine the mouse
   * position.
   *
   * @details The supplied value will be adjusted to be at least 1.
   *
   * @param logicalHeight the logical height that will be used to determine the
   * mouse position.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_logical_height(int logicalHeight) noexcept;

  /**
   * @brief Indicates whether or not the left mouse button was released.
   *
   * @return `true` if the left mouse button was released; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto was_left_button_released() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the right mouse button was released.
   *
   * @return `true` if the right mouse button was released; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto was_right_button_released() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the mouse was moved.
   *
   * @return `true` if the mouse was moved; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto was_mouse_moved() const noexcept -> bool;

  /**
   * @brief Returns the x-coordinate of the mouse.
   *
   * @return the x-coordinate of the mouse.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto mouse_x() const noexcept -> int { return m_mouseX; }

  /**
   * @brief Returns the y-coordinate of the mouse.
   *
   * @return the y-coordinate of the mouse.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto mouse_y() const noexcept -> int { return m_mouseY; }

  /**
   * @brief Returns the logical width used by the mouse state instance.
   *
   * @return the logical width used by the mouse state instance, 1 is used by
   * default.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int
  {
    return m_logicalWidth;
  }

  /**
   * @brief Returns the logical height used by the mouse state instance.
   *
   * @return the logical height used by the mouse state instance, 1 is used by
   * default.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int
  {
    return m_logicalHeight;
  }

  /**
   * @brief Indicates whether or not the left mouse button is currently pressed.
   *
   * @return `true` if the left mouse button is pressed; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_left_button_pressed() const noexcept -> bool
  {
    return m_leftPressed;
  }

  /**
   * @brief Indicates whether or not the right mouse button is currently
   * pressed.
   *
   * @return `true` if the right mouse button is pressed; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_right_button_pressed() const noexcept -> bool
  {
    return m_rightPressed;
  }

 private:
  int m_mouseX{0};
  int m_mouseY{0};
  int m_oldX{0};
  int m_oldY{0};
  int m_logicalWidth{1};
  int m_logicalHeight{1};
  bool m_leftPressed{false};
  bool m_rightPressed{false};
  bool m_prevLeftPressed{false};
  bool m_prevRightPressed{false};
};

}  // namespace cen

#endif  // CENTURION_MOUSE_STATE_HEADER