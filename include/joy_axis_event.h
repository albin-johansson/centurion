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

#ifndef CENTURION_JOY_AXIS_EVENT_HEADER
#define CENTURION_JOY_AXIS_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"
#include "game_controller.h"

namespace centurion {
namespace event {

/**
 * The JoyAxisEvent class represents an event that occurs whenever a user
 * moves an axis on a joystick.
 *
 * @see SDL_JoyAxisEvent
 * @since 4.0.0
 */
class JoyAxisEvent : public CommonEvent<SDL_JoyAxisEvent> {
 public:
  /**
   * Creates a default-initialized joy axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API JoyAxisEvent() noexcept;

  /**
   * Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * @param event the SDL joy axis event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept;

  /**
   * Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * @param event the SDL joy axis event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API JoyAxisEvent(SDL_JoyAxisEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID which) noexcept;

  /**
   * Sets the joystick axis index associated with the event.
   *
   * @param axis the joystick axis index associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_axis(Uint8 axis) noexcept;

  /**
   * Sets the joystick axis value associated with the event.
   *
   * @param value the joystick axis value associated with the event.
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
   * Returns the joystick axis index associated with the event.
   *
   * @return the joystick axis index associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 axis() const noexcept;

  /**
   * Returns the joystick axis value associated with the event.
   *
   * @return the joystick axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint16 value() const noexcept;
};

static_assert(validate_event<JoyAxisEvent, SDL_JoyAxisEvent>(),
              "JoyAxisEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joy_axis_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOY_AXIS_EVENT_HEADER