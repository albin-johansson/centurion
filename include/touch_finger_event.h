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

#ifndef CENTURION_TOUCH_FINGER_EVENT_HEADER
#define CENTURION_TOUCH_FINGER_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"
#include "touch.h"

namespace centurion {
namespace event {

/**
 * The TouchFingerEvent class represents an event related to touch screen
 * actions.
 *
 * @see SDL_TouchFingerEvent
 * @since 4.0.0
 */
class TouchFingerEvent : public CommonEvent<SDL_TouchFingerEvent> {
 public:
  /**
   * Creates a default-initialized touch finger event.
   *
   * @since 4.0.0
   */
  CENTURION_API TouchFingerEvent() noexcept;

  /**
   * Creates a touch finger event that is based on the supplied SDL
   * ouch finger event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API TouchFingerEvent(const SDL_TouchFingerEvent& event) noexcept;

  /**
   * Creates a touch finger event by moving the supplied SDL touch finger
   * event.
   *
   * @param event the SDL touch finger event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API TouchFingerEvent(SDL_TouchFingerEvent&& event) noexcept;

  /**
   * Sets the ID of the associated touch device.
   *
   * @param id the ID of the associated touch device.
   * @since 4.0.0
   */
  CENTURION_API void set_touch_id(TouchID id) noexcept;

  /**
   * Sets the finger ID associated with the event.
   *
   * @param id the finger ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_finger_id(FingerID id) noexcept;

  /**
   * Sets the window ID of the window under the finger.
   *
   * @param id the window ID of the window under the finger.
   * @since 4.0.0
   */
  CENTURION_API void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the normalized x-coordinate of the location of the event. The
   * supplied value will be clamped in the range [0, 1].
   *
   * @param x the normalized x-coordinate of the location of the event,
   * clamped to the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API void set_x(float x) noexcept;

  /**
   * Sets the normalized y-coordinate of the location of the event. The
   * supplied value will be clamped in the range [0, 1].
   *
   * @param y the normalized y-coordinate of the location of the event,
   * clamped to the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API void set_y(float y) noexcept;

  /**
   * Sets the normalized distance moved along the x-axis. The
   * supplied value will be clamped in the range [-1, 1].
   *
   * @param dx the normalized distance moved along the x-axis, clamped to the
   * range [-1, 1].
   * @since 4.0.0
   */
  CENTURION_API void set_dx(float dx) noexcept;

  /**
   * Sets the normalized distance moved along the y-axis. The
   * supplied value will be clamped in the range [-1, 1].
   *
   * @param dy the normalized distance moved along the y-axis, clamped to the
   * range [-1, 1].
   * @since 4.0.0
   */
  CENTURION_API void set_dy(float dy) noexcept;

  /**
   * Sets the normalized pressure associated with the event. The supplied
   * value will be clamped in the range [0, 1].
   *
   * @param pressure the normalized pressure associated with the event, clamped
   * in the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API void set_pressure(float pressure) noexcept;

  /**
   * Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API TouchID touch_id() const noexcept;

  /**
   * Returns the finger ID associated with the event.
   *
   * @return the finger ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API FingerID finger_id() const noexcept;

  /**
   * Returns the window ID of the window under the finger.
   *
   * @return the window ID of the window under the finger.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 window_id() const noexcept;

  /**
   * Returns the normalized x-coordinate of the location of the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized x-coordinate of the location of the event, in the
   * range [0, 1].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float x() const noexcept;

  /**
   * Returns the normalized y-coordinate of the location of the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized y-coordinate of the location of the event, in the
   * range [0, 1].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float y() const noexcept;

  /**
   * Returns the normalized distance moved along the x-axis. The
   * returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the x-axis, in the range
   * [-1, 1].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float dx() const noexcept;

  /**
   * Returns the normalized distance moved along the y-axis. The
   * returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the y-axis, in the range
   * [-1, 1].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float dy() const noexcept;

  /**
   * Returns the normalized pressure associated with the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized pressure associated with the event, in the range
   * [0, 1].
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float pressure() const noexcept;
};

static_assert(validate_event<TouchFingerEvent, SDL_TouchFingerEvent>(),
              "TouchFingerEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "touch_finger_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_TOUCH_FINGER_EVENT_HEADER