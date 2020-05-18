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

#ifndef CENTURION_DOLLAR_GESTURE_HEADER
#define CENTURION_DOLLAR_GESTURE_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"
#include "touch.h"

namespace centurion {
namespace event {

/**
 * The DollarGestureEvent provides information about dollar gestures from
 * touch events.
 *
 * @see SDL_DollarGestureEvent
 * @since 4.0.0
 */
class DollarGestureEvent : public CommonEvent<SDL_DollarGestureEvent> {
 public:
  /**
   * Creates a default-initialized dollar gesture event.
   *
   * @since 4.0.0
   */
  CENTURION_API DollarGestureEvent() noexcept;

  /**
   * Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API DollarGestureEvent(
      const SDL_DollarGestureEvent& event) noexcept;

  /**
   * Creates a dollar gesture event by moving the supplied SDL dollar gesture
   * event.
   *
   * @param event the SDL dollar gesture event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API DollarGestureEvent(SDL_DollarGestureEvent&& event) noexcept;

  /**
   * Sets the touch device ID associated with the event.
   *
   * @param id the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_touch_id(TouchID id) noexcept;

  /**
   * Sets the gesture ID associated with the event.
   *
   * @param id the gesture ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_gesture_id(GestureID id) noexcept;

  /**
   * Sets the amount of fingers used to draw the stroke.
   *
   * @param fingers the amount of fingers used to draw the stroke.
   * @since 4.0.0
   */
  CENTURION_API void set_fingers(Uint32 fingers) noexcept;

  /**
   * Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * @return the error value for the performed stroke.
   * @since 4.0.0
   */
  CENTURION_API void set_error(float error) noexcept;

  /**
   * Sets the normalized x-coordinate of the center of the gesture.
   *
   * @param x the normalized x-coordinate of the center of the gesture.
   * @since 4.0.0
   */
  CENTURION_API void set_x(float x) noexcept;

  /**
   * Sets the normalized y-coordinate of the center of the gesture.
   *
   * @param y the normalized y-coordinate of the center of the gesture.
   * @since 4.0.0
   */
  CENTURION_API void set_y(float y) noexcept;

  /**
   * Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API TouchID touch_id() const noexcept;

  /**
   * Returns the unique ID of the closest gesture to the performed stroke.
   *
   * @return the unique ID of the closest gesture to the performed stroke.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API GestureID gesture_id() const noexcept;

  /**
   * Returns the amount of fingers used to draw the stroke.
   *
   * @return the amount of fingers used to draw the stroke.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 fingers() const noexcept;

  /**
   * Returns the difference between the gesture template and the performed
   * gesture. The lower the error, the better of a match.
   *
   * @return the difference between the gesture template and the performed
   * gesture.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float error() const noexcept;

  /**
   * Returns the x-coordinate of the normalized center of the gesture.
   *
   * @return the x-coordinate of the normalized center of the gesture.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float x() const noexcept;

  /**
   * Returns the y-coordinate of the normalized center of the gesture.
   *
   * @return the y-coordinate of the normalized center of the gesture.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float y() const noexcept;
};

static_assert(validate_event<DollarGestureEvent, SDL_DollarGestureEvent>(),
              "DollarGestureEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "dollar_gesture_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_DOLLAR_GESTURE_HEADER