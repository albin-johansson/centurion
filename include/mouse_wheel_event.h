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

#ifndef CENTURION_MOUSE_WHEEL_EVENT_HEADER
#define CENTURION_MOUSE_WHEEL_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The MouseWheelDirection enum class mirrors the values of the
 * SDL_MouseWheelDirection enum.
 *
 * @see SDL_MouseWheelDirection
 * @since 4.0.0
 */
enum class MouseWheelDirection {
  Normal = SDL_MOUSEWHEEL_NORMAL,
  Flipped = SDL_MOUSEWHEEL_FLIPPED
};

/**
 * Indicates whether or not the two mouse wheel direction values are the same.
 *
 * @param lhs the left-hand side Centurion mouse wheel direction.
 * @param rhs the right-hand side SDL mouse wheel direction.
 * @return true if the two mouse wheel direction values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(MouseWheelDirection lhs,
                              SDL_MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values are the same.
 *
 * @param lhs the left-hand side SDL mouse wheel direction.
 * @param rhs the right-hand side Centurion mouse wheel direction.
 * @return true if the two mouse wheel direction values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_MouseWheelDirection lhs,
                              MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values aren't the
 * same.
 *
 * @param lhs the left-hand side Centurion mouse wheel direction.
 * @param rhs the right-hand side SDL mouse wheel direction.
 * @return true if the two mouse wheel direction values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(MouseWheelDirection lhs,
                              SDL_MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values aren't the
 * same.
 *
 * @param lhs the left-hand side SDL mouse wheel direction.
 * @param rhs the right-hand side Centurion mouse wheel direction.
 * @return true if the two mouse wheel direction values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_MouseWheelDirection lhs,
                              MouseWheelDirection rhs) noexcept;

/**
 * The MouseWheelEvent class represents events triggered when a user moves
 * the mouse wheel.
 *
 * @see SDL_MouseWheelEvent
 * @since 4.0.0
 */
class MouseWheelEvent : public CommonEvent<SDL_MouseWheelEvent> {
 public:
  /**
   * Creates a default-initialized MouseWheelEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API MouseWheelEvent() noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API MouseWheelEvent(const SDL_MouseWheelEvent& event) noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API MouseWheelEvent(SDL_MouseWheelEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @param which the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_API void set_which(Uint32 which) noexcept;

  /**
   * Returns the horizontally scrolled distance, a positive value indicates that
   * the user scrolled to the right and a negative value indicates that the
   * user scrolled to the left.
   *
   * @param xScroll the horizontally scrolled distance.
   * @since 4.0.0
   */
  CENTURION_API void set_x_scroll(Sint32 xScroll) noexcept;

  /**
   * Returns the vertically scrolled distance, a positive value indicates that
   * the user scrolled away from the user and a negative value indicates that
   * the user scrolled towards the user.
   *
   * @param yScroll the vertically scrolled distance.
   * @since 4.0.0
   */
  CENTURION_API void set_y_scroll(Sint32 yScroll) noexcept;

  /**
   * Sets the mouse wheel direction mode associated with the event.
   *
   * @param direction the mouse wheel direction mode associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_direction(MouseWheelDirection direction) noexcept;

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 window_id() const noexcept;

  /**
   * Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 which() const noexcept;

  /**
   * Returns the horizontally scrolled distance, a positive value indicates that
   * the user scrolled to the right and a negative value indicates that the
   * user scrolled to the left.
   *
   * @return the horizontally scrolled distance.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 x_scroll() const noexcept;

  /**
   * Returns the vertically scrolled distance, a positive value indicates that
   * the user scrolled away from the user and a negative value indicates that
   * the user scrolled towards the user.
   *
   * @return the vertically scrolled distance.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 y_scroll() const noexcept;

  /**
   * Returns the mouse wheel direction mode associated with the event.
   *
   * @return the mouse wheel direction mode associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API MouseWheelDirection direction() const noexcept;
};

static_assert(validate_event<MouseWheelEvent, SDL_MouseWheelEvent>(),
              "MouseWheelEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "mouse_wheel_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_MOUSE_WHEEL_EVENT_HEADER