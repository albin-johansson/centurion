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

#ifndef CENTURION_MOUSE_BUTTON_EVENT_HEADER
#define CENTURION_MOUSE_BUTTON_EVENT_HEADER

#include <SDL_events.h>

#include "button_state.h"
#include "centurion_api.h"
#include "common_event.h"
#include "mouse_button.h"

namespace centurion {
namespace event {

/**
 * The MouseButtonEvent class represents an event triggered by mouse button
 * presses or releases.
 *
 * @see SDL_MouseButtonEvent
 * @since 4.0.0
 */
class MouseButtonEvent : public CommonEvent<SDL_MouseButtonEvent> {
 public:
  /**
   * Creates a default-initialized MouseButtonEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API MouseButtonEvent() noexcept;

  /**
   * Creates a MouseButtonEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API MouseButtonEvent(const SDL_MouseButtonEvent& event) noexcept;

  /**
   * Creates a MouseButtonEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API MouseButtonEvent(SDL_MouseButtonEvent&& event) noexcept;

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
   * Sets the mouse button associated with the event.
   *
   * @param button the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_button(MouseButton button) noexcept;

  /**
   * Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_state(ButtonState state) noexcept;

  /**
   * Sets the amount of clicks associated with the event.
   *
   * @param clicks the amount of clicks associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_clicks(Uint8 clicks) noexcept;

  /**
   * Sets the x-coordinate of the mouse relative to the window.
   *
   * @param x the x-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_API void set_x(Sint32 x) noexcept;

  /**
   * Sets the y-coordinate of the mouse relative to the window.
   *
   * @param y the y-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_API void set_y(Sint32 y) noexcept;

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
   * Returns the mouse button associated with the event.
   *
   * @return the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API MouseButton button() const noexcept;

  /**
   * Returns the state of the mouse button associated with the event.
   *
   * @return the state of the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API ButtonState state() const noexcept;

  /**
   * Returns the number of mouse clicks associated with the event.
   *
   * @return the number of mouse clicks associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 clicks() const noexcept;

  /**
   * Returns the x-coordinate of the mouse relative to the window.
   *
   * @return the x-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse relative to the window.
   *
   * @return the y-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 y() const noexcept;
};

static_assert(validate_event<MouseButtonEvent, SDL_MouseButtonEvent>(),
              "MouseButtonEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "mouse_button_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_MOUSE_BUTTON_EVENT_HEADER