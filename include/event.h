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

#ifndef CENTURION_EVENT_HEADER
#define CENTURION_EVENT_HEADER

#include <SDL_events.h>

#include "audio_device_event.h"
#include "centurion_api.h"
#include "centurion_utils.h"
#include "common_event.h"
#include "controller_axis_event.h"
#include "controller_button_event.h"
#include "controller_device_event.h"
#include "dollar_gesture_event.h"
#include "drop_event.h"
#include "event_type.h"
#include "joy_axis_event.h"
#include "joy_ball_event.h"
#include "joy_button_event.h"
#include "joy_device_event.h"
#include "joy_hat_event.h"
#include "keyboard_event.h"
#include "mouse_button_event.h"
#include "mouse_motion_event.h"
#include "mouse_wheel_event.h"
#include "multi_gesture_event.h"
#include "quit_event.h"
// #include "syswm_event.h"
#include "text_editing_event.h"
#include "text_input_event.h"
#include "touch_finger_event.h"
#include "window_event.h"

namespace centurion {
namespace event {

/**
 * The Event class serves as the main interface for dealing with events in
 * the Centurion library.
 *
 * @see SDL_Event
 * @since 4.0.0
 */
class Event final {
 public:
  /**
   * Creates an empty event.
   *
   * @since 4.0.0
   */
  CENTURION_API Event() noexcept;

  /**
   * Creates an event based on the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API Event(const SDL_Event& event) noexcept;

  /**
   * Creates an event based on the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API Event(SDL_Event&& event) noexcept;

  /**
   * Refresh the event loop, gathering events from the input devices. Note that
   * you might not have to call this method by yourself.
   *
   * @see SDL_PumpEvents
   * @since 3.1.0
   */
  CENTURION_API static void refresh() noexcept;

  /**
   * Pushes an event onto the event queue.
   *
   * @param event the event that will be added to the event queue.
   * @since 3.1.0
   */
  CENTURION_API static void push(Event& event) noexcept;

  /**
   * Flushes all current events from the event queue.
   *
   * @see
   * @since 3.1.0
   */
  CENTURION_API static void flush() noexcept;

  /**
   * Flushes all of the current events from the event queue, including pending
   * events.
   *
   * @since 3.1.0
   */
  CENTURION_API static void flush_all() noexcept;

  /**
   * Polls the next available event, if there is one. This is meant to be
   * called inside a while-loop.
   *
   * @return true if there are any pending events; false otherwise.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool poll() noexcept;

  /**
   * Returns the type of the event. This method can always be safely called on
   * an event instance.
   *
   * @return the type of the event.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API EventType type() const noexcept;

  /**
   * Returns an AudioDeviceEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return an AudioDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<AudioDeviceEvent> as_audio_device_event() const noexcept;

  /**
   * Returns a ControllerAxisEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a ControllerAxisEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<ControllerAxisEvent> as_controller_axis_event() const noexcept;

  /**
   * Returns a ControllerButtonEvent or nothing if the type of the event
   * doesn't match.
   *
   * @return a ControllerButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<ControllerButtonEvent> as_controller_button_event() const noexcept;

  /**
   * Returns a ControllerDeviceEvent or nothing if the type of the event
   * doesn't match.
   *
   * @return a ControllerDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<ControllerDeviceEvent> as_controller_device_event() const noexcept;

  /**
   * Returns a DollarGestureEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a DollarGestureEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<DollarGestureEvent> as_dollar_gesture_event() const noexcept;

  /**
   * Returns a DropEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a DropEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<DropEvent> as_drop_event() const noexcept;

  /**
   * Returns a JoyAxisEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyAxisEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<JoyAxisEvent> as_joy_axis_event() const noexcept;

  /**
   * Returns a JoyBallEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyBallEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<JoyBallEvent> as_joy_ball_event() const noexcept;

  /**
   * Returns a JoyButtonEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<JoyButtonEvent> as_joy_button_event() const noexcept;

  /**
   * Returns a JoyDeviceEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<JoyDeviceEvent> as_joy_device_event() const noexcept;

  /**
   * Returns a JoyHatEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyHatEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<JoyHatEvent> as_joy_hat_event() const noexcept;

  /**
   * Returns a KeyboardEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a KeyboardEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<KeyboardEvent> as_keyboard_event() const noexcept;

  /**
   * Returns a MouseButtonEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<MouseButtonEvent> as_mouse_button_event() const noexcept;

  /**
   * Returns a MouseMotionEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseMotionEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<MouseMotionEvent> as_mouse_motion_event() const noexcept;

  /**
   * Returns a MouseWheelEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseWheelEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<MouseWheelEvent> as_mouse_wheel_event() const noexcept;

  /**
   * Returns a MultiGestureEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MultiGestureEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<MultiGestureEvent> as_multi_gesture_event() const noexcept;

  /**
   * Returns a QuitEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a QuitEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<QuitEvent> as_quit_event() const noexcept;

  /**
   * Returns a TextEditingEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TextEditingEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<TextEditingEvent> as_text_editing_event() const noexcept;

  /**
   * Returns a TextInputEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TextInputEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<TextInputEvent> as_text_input_event() const noexcept;

  /**
   * Returns a TouchFingerEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TouchFingerEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<TouchFingerEvent> as_touch_finger_event() const noexcept;

  /**
   * Returns a WindowEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a WindowEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<WindowEvent> as_window_event() const noexcept;

  // FIXME Not available, there is something fishy about the SysWMEvent includes
  //  /**
  //   * Returns a SysWMEvent or nothing if the type of the event doesn't
  //   * match.
  //   *
  //   * @return a SysWMEvent or nothing.
  //   * @since 4.0.0
  //   */
  //  CENTURION_NODISCARD
  //  CENTURION_API
  //  Optional<SysWMEvent> as_syswm_event() const noexcept;

  /**
   * Implicitly converts the event to a reference to the internal SDL_Event.
   *
   * @return a reference to the internal SDL_Event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Event&() noexcept { return m_event; }

  /**
   * Implicitly converts the event to a const reference to the internal
   * SDL_Event.
   *
   * @return a const reference to the internal SDL_Event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator const SDL_Event&() const noexcept { return m_event; }

 private:
  SDL_Event m_event;
};

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EVENT_HEADER