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

#ifndef CENTURION_CONTROLLER_AXIS_EVENT_HEADER
#define CENTURION_CONTROLLER_AXIS_EVENT_HEADER

#include <SDL_events.h>

#include <type_traits>

#include "centurion_api.h"
#include "common_event.h"
#include "game_controller.h"

namespace centurion {
namespace event {

/**
 * The ControllerAxisEvent represents an event triggered by game controller
 * axis motion.
 *
 * @since 4.0.0
 */
class ControllerAxisEvent : public CommonEvent<SDL_ControllerAxisEvent> {
 public:
  /**
   * Creates a default-initialized controller axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent() noexcept;

  /**
   * Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent(
      const SDL_ControllerAxisEvent& event) noexcept;

  /**
   * Creates a controller axis event by moving the supplied SDL controller
   * axis event.
   *
   * @param event the SDL controller axis event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent(SDL_ControllerAxisEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the instance ID of the joystick that the event is
   * associated with.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID which) noexcept;

  /**
   * Sets the game controller axis value associated with the event.
   *
   * @param axis the game controller axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_axis(GameControllerAxis axis) noexcept;

  /**
   * Sets the axis value associated with the event.
   *
   * @param value the new axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_value(Sint16 value) noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoystickID which() const noexcept;

  /**
   * Returns the game controller axis value associated with the event.
   *
   * @return the game controller axis value associated with the event.
   * @since 4.0.0
   * @see GameControllerAxis
   */
  CENTURION_NODISCARD
  CENTURION_API GameControllerAxis axis() const noexcept;

  /**
   * Returns the axis value associated with the event.
   *
   * @return the axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint16 value() const noexcept;
};

static_assert(validate_event<ControllerAxisEvent, SDL_ControllerAxisEvent>(),
              "ControllerAxisEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "controller_axis_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_HEADER
