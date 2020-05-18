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

#ifndef CENTURION_MULTI_GESTURE_EVENT_HEADER
#define CENTURION_MULTI_GESTURE_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"
#include "touch.h"

namespace centurion {
namespace event {

/**
 * The MultiGestureEvent class provides information about events related to
 * touch events triggered by multiple fingers.
 *
 * @see SDL_MultiGestureEvent
 * @since 4.0.0
 */
class MultiGestureEvent : public CommonEvent<SDL_MultiGestureEvent> {
 public:
  /**
   * Creates a default-initialized MultiGestureEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API MultiGestureEvent() noexcept;

  /**
   * Creates a MultiGestureEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API MultiGestureEvent(const SDL_MultiGestureEvent& event) noexcept;

  /**
   * Creates a MultiGestureEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API MultiGestureEvent(SDL_MultiGestureEvent&& event) noexcept;

  /**
   * Sets the touch device ID associated with the event.
   *
   * @param id the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_touch_id(TouchID id) noexcept;

  /**
   * Sets the amount that the fingers rotated during the gesture associated
   * with the event.
   *
   * @param dTheta the amount that the fingers rotated.
   * @since 4.0.0
   */
  CENTURION_API void set_delta_theta(float dTheta) noexcept;

  /**
   * Sets the amount that the fingers pinched during the gesture associated
   * with the event.
   *
   * @param dDistance the amount that the fingers pinched.
   * @since 4.0.0
   */
  CENTURION_API void set_delta_distance(float dDistance) noexcept;

  /**
   * Sets the x-coordinate of the normalized center of the gesture associated
   * with the event.
   *
   * @param centerX the x-coordinate of the normalized center of the gesture
   * associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_center_x(float centerX) noexcept;

  /**
   * Sets the y-coordinate of the normalized center of the gesture associated
   * with the event.
   *
   * @param centerY the y-coordinate of the normalized center of the gesture
   * associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_center_y(float centerY) noexcept;

  /**
   * Sets the number of fingers that was used in the gesture associated with
   * the event.
   *
   * @param nFingers the number of fingers that was used in the gesture.
   * @since 4.0.0
   */
  CENTURION_API void set_fingers(Uint16 nFingers) noexcept;

  /**
   * Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API TouchID touch_id() const noexcept;

  /**
   * Returns the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers rotated.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float delta_theta() const noexcept;

  /**
   * Returns the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers pinched.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float delta_distance() const noexcept;

  /**
   * Returns the x-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @return the x-coordinate of the normalized center of gesture associated
   * with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float center_x() const noexcept;

  /**
   * Returns the y-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @return the y-coordinate of the normalized center of gesture associated
   * with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float center_y() const noexcept;

  /**
   * Returns the amount of fingers used in the gesture associated with the
   * event.
   *
   * @return the amount of fingers used in the gesture associated with the
   * event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float fingers() const noexcept;
};

static_assert(validate_event<MultiGestureEvent, SDL_MultiGestureEvent>(),
              "MultiGestureEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "multi_gesture_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_MULTI_GESTURE_EVENT_HEADER