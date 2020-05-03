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

#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_HEADER
#define CENTURION_CONTROLLER_DEVICE_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The ControllerDeviceEvent class represents events related to game
 * controller devices such as adding or removing game controller devices.
 *
 * @see SDL_ControllerDeviceEvent
 * @since 4.0.0
 */
class ControllerDeviceEvent : public CommonEvent<SDL_ControllerDeviceEvent> {
 public:
  /**
   * Creates a default-initialized controller device event.
   *
   * @since 4.0.0
   */
  CENTURION_API ControllerDeviceEvent() noexcept;

  /**
   * Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API ControllerDeviceEvent(
      const SDL_ControllerDeviceEvent& event) noexcept;

  /**
   * Creates a controller device event by moving the supplied SDL controller
   * device event.
   *
   * @param event the SDL controller device event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API ControllerDeviceEvent(
      SDL_ControllerDeviceEvent&& event) noexcept;

  /**
   * If the event type is <code>Added</code>, then this value is the joystick
   * device index. If the type of the event is either <code>Removed</code> or
   * <code>Remapped</code>, then this value is the instance ID.
   *
   * @param which the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_API void set_which(Sint32 which) noexcept;

  /**
   * Returns the joystick device index if the type of the event is
   * <code>Added</code>. Returns the instance ID if the type of the event is
   * either <code>Removed</code> or <code>Remapped</code>.
   *
   * @return the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 which() const noexcept;
};

static_assert(
    validate_event<ControllerDeviceEvent, SDL_ControllerDeviceEvent>(),
    "ControllerDeviceEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "controller_device_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_HEADER