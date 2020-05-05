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

#ifndef CENTURION_JOY_DEVICE_EVENT_HEADER
#define CENTURION_JOY_DEVICE_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The JoyDeviceEvent class represents an event triggered by adding or
 * removing a joystick device.
 *
 * @see SDL_JoyDeviceEvent
 * @since 4.0.0
 */
class JoyDeviceEvent : public CommonEvent<SDL_JoyDeviceEvent> {
 public:
  /**
   * Creates a default-initialized JoyDeviceEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API JoyDeviceEvent() noexcept;

  /**
   * Creates a JoyDeviceEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept;

  /**
   * Creates a JoyDeviceEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API JoyDeviceEvent(SDL_JoyDeviceEvent&& event) noexcept;

  /**
   * Sets the joystick device index or instance ID, depending on the type of
   * the event.
   *
   * @param which the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_API void set_which(Sint32 which) noexcept;

  /**
   * Returns the joystick device index if the type is JoystickDeviceAdded
   * or the joystick instance ID if the type is JoystickDeviceRemoved.
   *
   * @return the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 which() const noexcept;
};

static_assert(validate_event<JoyDeviceEvent, SDL_JoyDeviceEvent>(),
              "JoyDeviceEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joy_device_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOY_DEVICE_EVENT_HEADER