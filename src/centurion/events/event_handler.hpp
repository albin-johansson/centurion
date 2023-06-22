/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_EVENTS_EVENT_HANDLER_HPP_
#define CENTURION_EVENTS_EVENT_HANDLER_HPP_

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string, to_string
#include <variant>  // variant, monostate, get, get_if, holds_alternative

#include "../common/primitives.hpp"
#include "../features.hpp"
#include "audio_events.hpp"
#include "controller_events.hpp"
#include "event_base.hpp"
#include "joystick_events.hpp"
#include "misc_events.hpp"
#include "mouse_events.hpp"
#include "window_events.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// The main API for dealing with events.
class event_handler final {
 public:
  static void update() noexcept { SDL_PumpEvents(); }

  template <typename T>
  static auto push(const event_base<T>& event) noexcept -> result
  {
    auto underlying = as_sdl_event(event);
    return SDL_PushEvent(&underlying) >= 0;
  }

  static void flush() noexcept { SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT); }

  static void flush_all() noexcept
  {
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
  }

  // Waits until an event is available
  void wait()
  {
    SDL_Event event {};
    if (SDL_WaitEvent(&event)) {
      store(event);
    }
    else {
      throw sdl_error {};
    }
  }

  // Waits until an event is available or timeout
  auto wait(int timeout) noexcept -> bool
  {
    SDL_Event event {};
    if (SDL_WaitEventTimeout(&event, timeout)) {
      store(event);
      return true;
    }
    else {
      reset_state();
      return false;
    }
  }

  /// Polls the next available event, if there is one.
  auto poll() noexcept -> bool
  {
    SDL_Event event {};
    if (SDL_PollEvent(&event)) {
      store(event);
      return true;
    }
    else {
      reset_state();
      return false;
    }
  }

  /**
   * Indicates whether the currently stored event is of a particular type.
   *
   * Note, not all event types have dedicated event classes, so you might want to use
   * the overload taking a event type as a parameter to perform more fine-grained type checks.
   *
   * \tparam T the event type to check for, e.g. window_event.
   *
   * \return true if the stored event is of the specified type; false otherwise.
   *
   * \see is(event_type)
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(mData);
  }

  /// Indicates whether the current event is of a specific type.
  [[nodiscard]] auto is(const event_type type) const noexcept -> bool
  {
    if (type == event_type::user && is_user_event(mType)) {
      return true;
    }
    else {
      return mType == type;
    }
  }

  /// Returns the type of the internal event.
  [[nodiscard]] auto type() const noexcept -> maybe<event_type>
  {
    if (mType != event_type::last_event) {
      return mType;
    }
    else {
      return nothing;
    }
  }

  /// Returns the raw integral value of the event type.
  [[nodiscard]] auto raw_type() const noexcept -> maybe<uint32>
  {
    if (mType != event_type::last_event) {
      return to_underlying(mType);
    }
    else {
      return nothing;
    }
  }

  /**
   * Indicates whether there is no internal event instance.
   *
   * There may still be information about the event type, this function just checks whether
   * there is additional information about the event, i.e. a dedicated event type.
   *
   * \return true if there is no internal event; false otherwise.
   */
  [[nodiscard]] auto empty() const noexcept -> bool { return is<std::monostate>(); }

  /**
   * Returns the current event representation.
   *
   * Use this function if you're certain about the current event type.
   *
   * An exception is thrown if there is a mismatch between the requested type and the actual
   * current event type. Use the try_get function for a non-throwing alternative to this
   * function.
   *
   * \tparam T the type of the event to obtain.
   *
   * \return a reference to the internal event type.
   */
  template <typename T>
  [[nodiscard]] auto get() -> T&
  {
    return std::get<T>(mData);
  }

  template <typename T>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(mData);
  }

  /**
   * Attempts to return the current event representation.
   *
   * \tparam T the type of the event to obtain.
   *
   * \return a potentially null pointer to the internal event type.
   */
  template <typename T>
  [[nodiscard]] auto try_get() noexcept -> T*
  {
    return std::get_if<T>(&mData);
  }

  template <typename T>
  [[nodiscard]] auto try_get() const noexcept -> const T*
  {
    return std::get_if<T>(&mData);
  }

  /// Returns the current amount of events in the event queue.
  [[nodiscard]] static auto queue_count() noexcept -> maybe<int>
  {
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (num != -1) {
      return num;
    }
    else {
      return nothing;
    }
  }

  /// Returns the number of events of a particular type in the event queue.
  [[nodiscard]] static auto queue_count(const event_type type) noexcept -> maybe<int>
  {
    const auto id = to_underlying(type);
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, id, id);
    if (num != -1) {
      return num;
    }
    else {
      return nothing;
    }
  }

  /// Indicates whether any events of the specified type are in the event queue.
  [[nodiscard]] static auto in_queue(const event_type type) noexcept -> bool
  {
    return queue_count(type) > 0;
  }

  [[nodiscard]] auto data() const noexcept -> const SDL_Event* { return &mEvent; }

 private:
  // Behold, the beast!
  using data_type = std::variant<std::monostate,
                                 audio_device_event,
                                 controller_axis_event,
                                 controller_button_event,
                                 controller_device_event,
                                 dollar_gesture_event,
                                 drop_event,
                                 joy_axis_event,
                                 joy_ball_event,
                                 joy_button_event,
                                 joy_device_event,
                                 joy_hat_event,
                                 keyboard_event,
                                 mouse_button_event,
                                 mouse_motion_event,
                                 mouse_wheel_event,
                                 multi_gesture_event,
                                 quit_event,
                                 text_editing_event,
                                 text_input_event,
                                 touch_finger_event,
                                 sensor_event,
                                 user_event,

#if SDL_VERSION_ATLEAST(2, 0, 14)
                                 display_event,
                                 controller_touchpad_event,
                                 controller_sensor_event,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 22)
                                 text_editing_ext_event,
#endif  // SDL_VERSION_ATLEAST(2, 0, 22)

#if SDL_VERSION_ATLEAST(2, 24, 0)
                                 joy_battery_event,
#endif  // SDL_VERSION_ATLEAST(2, 24,0)

                                 window_event>;

  SDL_Event mEvent {};  // Only needed to support the data member function
  event_type mType {event_type::last_event};
  data_type mData {};

  void reset_state()
  {
    mEvent = {};
    mType = event_type::last_event;
    mData.emplace<std::monostate>();
  }

  void store(const SDL_Event& event) noexcept
  {
    mEvent = event;

    const auto type = static_cast<SDL_EventType>(event.type);
    mType = static_cast<event_type>(type);

    // Special case for user events with custom types
    if (is_user_event(mType)) {
      mData.emplace<user_event>(event.user);
      return;
    }

    /* Use the SDL event type in the switch, so that we get hopefully get warnings if we were
       to miss new event types. */
    switch (type) {
      case SDL_FIRSTEVENT:
      case SDL_LASTEVENT:
#if SDL_VERSION_ATLEAST(2, 0, 18)
      case SDL_POLLSENTINEL:
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
        reset_state();
        break;

      case SDL_QUIT:
        mData.emplace<quit_event>(event.quit);
        break;

      case SDL_APP_TERMINATING:
      case SDL_APP_LOWMEMORY:
      case SDL_APP_WILLENTERBACKGROUND:
      case SDL_APP_DIDENTERBACKGROUND:
      case SDL_APP_WILLENTERFOREGROUND:
      case SDL_APP_DIDENTERFOREGROUND:
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_LOCALECHANGED:
        break;

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_DISPLAYEVENT:
        mData.emplace<display_event>(event.display);
        break;

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_WINDOWEVENT:
        mData.emplace<window_event>(event.window);
        break;

      case SDL_SYSWMEVENT:
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        mData.emplace<keyboard_event>(event.key);
        break;

      case SDL_TEXTEDITING:
        mData.emplace<text_editing_event>(event.edit);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 22)

      case SDL_TEXTEDITING_EXT:
        mData.emplace<text_editing_ext_event>(event.editExt);
        break;

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)

      case SDL_TEXTINPUT:
        mData.emplace<text_input_event>(event.text);
        break;

      case SDL_KEYMAPCHANGED:
        break;

      case SDL_MOUSEMOTION:
        mData.emplace<mouse_motion_event>(event.motion);
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        mData.emplace<mouse_button_event>(event.button);
        break;

      case SDL_MOUSEWHEEL:
        mData.emplace<mouse_wheel_event>(event.wheel);
        break;

      case SDL_JOYAXISMOTION:
        mData.emplace<joy_axis_event>(event.jaxis);
        break;

      case SDL_JOYBALLMOTION:
        mData.emplace<joy_ball_event>(event.jball);
        break;

      case SDL_JOYHATMOTION:
        mData.emplace<joy_hat_event>(event.jhat);
        break;

      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        mData.emplace<joy_button_event>(event.jbutton);
        break;

      case SDL_JOYDEVICEADDED:
      case SDL_JOYDEVICEREMOVED:
        mData.emplace<joy_device_event>(event.jdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 24, 0)

      case SDL_JOYBATTERYUPDATED:
        mData.emplace<joy_battery_event>(event.jbattery);
        break;

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

      case SDL_CONTROLLERAXISMOTION:
        mData.emplace<controller_axis_event>(event.caxis);
        break;

      case SDL_CONTROLLERBUTTONDOWN:
      case SDL_CONTROLLERBUTTONUP:
        mData.emplace<controller_button_event>(event.cbutton);
        break;

      case SDL_CONTROLLERDEVICEADDED:
      case SDL_CONTROLLERDEVICEREMOVED:
      case SDL_CONTROLLERDEVICEREMAPPED:
        mData.emplace<controller_device_event>(event.cdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_CONTROLLERTOUCHPADDOWN:
      case SDL_CONTROLLERTOUCHPADMOTION:
      case SDL_CONTROLLERTOUCHPADUP:
        mData.emplace<controller_touchpad_event>(event.ctouchpad);
        break;

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_CONTROLLERSENSORUPDATE:
        mData.emplace<controller_sensor_event>(event.csensor);
        break;

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case SDL_FINGERDOWN:
      case SDL_FINGERUP:
      case SDL_FINGERMOTION:
        mData.emplace<touch_finger_event>(event.tfinger);
        break;

      case SDL_DOLLARGESTURE:
      case SDL_DOLLARRECORD:
        mData.emplace<dollar_gesture_event>(event.dgesture);
        break;

      case SDL_MULTIGESTURE:
        mData.emplace<multi_gesture_event>(event.mgesture);
        break;

      case SDL_CLIPBOARDUPDATE:
        break;

      case SDL_DROPFILE:
      case SDL_DROPTEXT:
      case SDL_DROPBEGIN:
      case SDL_DROPCOMPLETE:
        mData.emplace<drop_event>(event.drop);
        break;

      case SDL_AUDIODEVICEADDED:
      case SDL_AUDIODEVICEREMOVED:
        mData.emplace<audio_device_event>(event.adevice);
        break;

      case SDL_SENSORUPDATE:
        mData.emplace<sensor_event>(event.sensor);
        break;

      case SDL_RENDER_TARGETS_RESET:
      case SDL_RENDER_DEVICE_RESET:
        break;

      case SDL_USEREVENT:
        mData.emplace<user_event>(event.user);
        break;

      default:
        reset_state();
        break;
    }
  }
};

}  // namespace cen

#endif  // CENTURION_EVENTS_EVENT_HANDLER_HPP_
