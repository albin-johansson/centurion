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

#ifndef CENTURION_JOY_BUTTON_EVENT_HEADER
#define CENTURION_JOY_BUTTON_EVENT_HEADER

#include <SDL_events.h>

#include "button_state.h"
#include "centurion_api.h"
#include "common_event.h"
#include "game_controller.h"

namespace centurion {
namespace event {

/**
 * The JoyButtonEvent class represents an event associated with the press or
 * release of a joystick button.
 *
 * @see SDL_JoyButtonEvent
 * @since 4.0.0
 */
class JoyButtonEvent : public CommonEvent<SDL_JoyButtonEvent> {
 public:
  /**
   * Creates a default-initialized JoyButtonEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API JoyButtonEvent() noexcept;

  /**
   * Creates a JoyButtonEvent based on the supplied SDL_JoyButtonEvent.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept;

  /**
   * Creates a JoyButtonEvent based on the supplied SDL_JoyButtonEvent.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API JoyButtonEvent(SDL_JoyButtonEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID which) noexcept;

  /**
   * Sets the button index associated with the event.
   *
   * @param button the button index associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_button(Uint8 button) noexcept;

  /**
   * Sets the button state that is associated with the button that triggered
   * the event.
   *
   * @param state the button state that is associated with the button that
   * triggered the event.
   * @since 4.0.0
   */
  CENTURION_API void set_state(ButtonState state) noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoystickID which() const noexcept;

  /**
   * Returns the index of the button that changed.
   *
   * @return the index of the button that changed.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 button() const noexcept;

  /**
   * Returns the state of the button associated with the event.
   *
   * @return the state of the button associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API ButtonState state() const noexcept;
};

static_assert(validate_event<JoyButtonEvent, SDL_JoyButtonEvent>(),
              "JoyButtonEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joy_button_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOY_BUTTON_EVENT_HEADER