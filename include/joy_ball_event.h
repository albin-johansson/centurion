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

#ifndef CENTURION_JOY_BALL_EVENT_HEADER
#define CENTURION_JOY_BALL_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"
#include "game_controller.h"

namespace centurion {
namespace event {

/**
 * The JoyBallEvent class represents the event that is triggered when a user
 * moves a trackball on a joystick.
 *
 * @see SDL_JoyBallEvent
 * @since 4.0.0
 */
class JoyBallEvent : public CommonEvent<SDL_JoyBallEvent> {
 public:
  /**
   * Creates a default-initialized joy ball event.
   *
   * @since 4.0.0
   */
  CENTURION_API JoyBallEvent() noexcept;

  /**
   * Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * @param event the SDL joy ball event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API JoyBallEvent(const SDL_JoyBallEvent& event) noexcept;

  /**
   * Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * @param event the SDL joy ball event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API JoyBallEvent(SDL_JoyBallEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID which) noexcept;

  /**
   * Sets the joystick trackball index associated with the event.
   *
   * @param ball the joystick trackball index.
   * @since 4.0.0
   */
  CENTURION_API void set_ball(Uint8 ball) noexcept;

  /**
   * Sets the relative motion along the x-axis associated with the event.
   *
   * @param dx the relative motion along the x-axis.
   * @since 4.0.0
   */
  CENTURION_API void set_dx(Sint16 dx) noexcept;

  /**
   * Sets the relative motion along the y-axis associated with the event.
   *
   * @param dy the relative motion along the y-axis.
   * @since 4.0.0
   */
  CENTURION_API void set_dy(Sint16 dy) noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoystickID which() const noexcept;

  /**
   * Returns the joystick trackball index associated with the event.
   *
   * @return the joystick trackball index associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 ball() const noexcept;

  /**
   * Returns the relative motion along the x-axis. Note that trackballs only
   * return relative motion, i.e this is the change in position of the ball
   * along the x-axis since it was last updated.
   *
   * @return the relative motion along the x-axis.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint16 dx() const noexcept;

  /**
   * Returns the relative motion along the y-axis. Note that trackballs only
   * return relative motion, i.e this is the change in position of the ball
   * along the y-axis since it was last updated.
   *
   * @return the relative motion along the y-axis.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint16 dy() const noexcept;
};

static_assert(validate_event<JoyBallEvent, SDL_JoyBallEvent>(),
              "JoyBallEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joy_ball_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOY_BALL_EVENT_HEADER