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

#ifndef CENTURION_JOY_HAT_EVENT_HEADER
#define CENTURION_JOY_HAT_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The JoyHatPosition enum class provides a wrapper for the SDL_HAT_x macro
 * values.
 *
 * @since 4.0.0
 */
enum class JoyHatPosition {
  LeftUp = SDL_HAT_LEFTUP,
  Left = SDL_HAT_LEFT,
  LeftDown = SDL_HAT_LEFTDOWN,
  Up = SDL_HAT_UP,
  Centered = SDL_HAT_CENTERED,
  Down = SDL_HAT_DOWN,
  RightUp = SDL_HAT_RIGHTUP,
  Right = SDL_HAT_RIGHT,
  RightDown = SDL_HAT_RIGHTDOWN
};

/**
 * The JoyHatEvent class represents an event that is triggered whenever a  user
 * moves a hat on a joystick.
 *
 * @see SDL_JoyHatEvent
 * @since 4.0.0
 */
class JoyHatEvent : public CommonEvent<SDL_JoyHatEvent> {
 public:
  /**
   * Creates a default-initialized joy hat event.
   *
   * @since 4.0.0
   */
  CENTURION_API JoyHatEvent() noexcept;

  /**
   * Creates a joy hat event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API JoyHatEvent(const SDL_JoyHatEvent& event) noexcept;

  /**
   * Creates a joy hat event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API JoyHatEvent(SDL_JoyHatEvent&& event) noexcept;

  /**
   * Sets the hat index associated with the event.
   *
   * @param hat the hat index.
   * @since 4.0.0
   */
  CENTURION_API void set_hat(Uint8 hat) noexcept;

  /**
   * Sets the joystick hat position associated with the event.
   *
   * @param value the joystick hat position associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_position(JoyHatPosition value) noexcept;

  /**
   * Returns the index of the hat that changed.
   *
   * @return the index of the hat that changed.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 hat() const noexcept;

  /**
   * Returns the position of the associated joystick hat.
   *
   * @return the position of the associated joystick hat.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoyHatPosition position() const noexcept;
};

static_assert(validate_event<JoyHatEvent, SDL_JoyHatEvent>(),
              "JoyHatEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joy_hat_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOY_HAT_EVENT_HEADER