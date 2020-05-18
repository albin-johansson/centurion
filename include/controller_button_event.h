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

#ifndef CENTURION_CONTROLLER_BUTTON_EVENT_HEADER
#define CENTURION_CONTROLLER_BUTTON_EVENT_HEADER

#include <SDL_events.h>

#include "button_state.h"
#include "centurion_api.h"
#include "common_event.h"
#include "game_controller.h"

namespace centurion {
namespace event {

/**
 * The ControllerButtonEvent class represents events associated with the
 * state of buttons of a game controller.
 *
 * @see SDL_ControllerButtonEvent
 * @since 4.0.0
 */
class ControllerButtonEvent : public CommonEvent<SDL_ControllerButtonEvent> {
 public:
  /**
   * Creates a default-initialized controller button event.
   *
   * @since 4.0.0
   */
  CENTURION_API ControllerButtonEvent() noexcept;

  /**
   * Creates a controller button event that is based on the supplied SDL
   * controller button event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API ControllerButtonEvent(
      const SDL_ControllerButtonEvent& event) noexcept;

  /**
   * Creates a controller button event by moving the supplied SDL controller
   * button event.
   *
   * @param event the SDL controller button event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API ControllerButtonEvent(
      SDL_ControllerButtonEvent&& event) noexcept;

  /**
   * Sets the game controller button associated with the event.
   *
   * param button the game controller button associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_button(GameControllerButton button) noexcept;

  /**
   * Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_state(ButtonState state) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param id the instance ID of the joystick that the event is associated
   * with.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID id) noexcept;

  /**
   * Returns the game controller button associated with the event.
   *
   * @return the game controller button associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API GameControllerButton button() const noexcept;

  /**
   * Returns the button state associated with the event.
   *
   * @return the button state associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API ButtonState state() const noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoystickID which() const noexcept;
};

static_assert(
    validate_event<ControllerButtonEvent, SDL_ControllerButtonEvent>(),
    "ControllerButtonEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "controller_button_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_CONTROLLER_BUTTON_EVENT_HEADER
