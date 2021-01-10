/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

/**
 * \defgroup event Events
 *
 * \brief Contains entities related to events.
 */

#ifndef CENTURION_EVENT_HEADER
#define CENTURION_EVENT_HEADER

#include <SDL.h>

#include <algorithm>    // clamp
#include <optional>     // optional
#include <string_view>  // string_view
#include <utility>      // move
#include <variant>      // variant, holds_alternative, monostate, get, get_if

#include "centurion_cfg.hpp"
#include "controller.hpp"
#include "detail/clamp.hpp"
#include "event_type.hpp"
#include "joystick.hpp"
#include "key_code.hpp"
#include "key_modifier.hpp"
#include "mouse_button.hpp"
#include "scan_code.hpp"
#include "touch.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class common_event
 *
 * \brief The templated base class of all Centurion events.
 *
 * \details This class defines the common API of all events and provides the
 * storage of the SDL2 event.
 *
 * \tparam T an SDL event type.
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
template <typename T>
class common_event
{
 public:
  /**
   * \brief Creates a zero-initialized `common_event`.
   *
   * \deprecated Use `common_event(event_type)` instead.
   *
   * \since 4.0.0
   */
  [[deprecated]] common_event() noexcept = default;

  /**
   * \brief Creates a `common_event` and zero-initializes the internal event
   * except for the timestamp and the supplied type.
   *
   * \param type the type of the event.
   *
   * \since 5.1.0
   */
  explicit common_event(const event_type type) noexcept
  {
    set_time(SDL_GetTicks());
    set_type(type);
  }

  /**
   * \brief Creates a common_event and copies the supplied event.
   *
   * \param event the event that will be copied.
   *
   * \since 4.0.0
   */
  explicit common_event(const T& event) : m_event{event}
  {}

  /**
   * \brief Creates a common_event and moves the contents of the supplied event.
   *
   * \param event the event that will be moved.
   *
   * \since 4.0.0
   */
  explicit common_event(T&& event) : m_event{std::move(event)}
  {}

  /**
   * \brief Sets the timestamp that is associated with the creation of the
   * event.
   *
   * \param timestamp the timestamp that should be associated with the creation
   * of the event.
   *
   * \since 4.0.0
   */
  void set_time(const u32 timestamp) noexcept
  {
    m_event.timestamp = timestamp;
  }

  /**
   * \brief Sets the event type value associated with the event.
   *
   * \param type the event type value associated with the event.
   *
   * \since 4.0.0
   */
  void set_type(const event_type type) noexcept
  {
    m_event.type = static_cast<u32>(type);
  }

  /**
   * \brief Returns the timestamp associated with the creation of the event.
   *
   * \return the timestamp associated with the creation of the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto time() const noexcept -> u32
  {
    return m_event.timestamp;
  }

  /**
   * \brief Returns the event type value associated with the event.
   *
   * \return the event type value associated with the event.
   *
   * \see EventType
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto type() const noexcept -> event_type
  {
    return static_cast<event_type>(m_event.type);
  }

  /**
   * \brief Returns the internal event.
   *
   * \return the internal event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> const T&
  {
    return m_event;
  }

 protected:
  T m_event{};
};

template <typename T>
[[nodiscard]] auto as_sdl_event(const common_event<T>& event) -> SDL_Event;

/**
 * \class audio_device_event
 *
 * \brief Represents an event that is associated with some sort of audio
 * device, either capture of output.
 *
 * \see `SDL_AudioDeviceEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class audio_device_event final : public common_event<SDL_AudioDeviceEvent>
{
 public:
  /**
   * \brief Creates an audio device event of type `audio_device_added`.
   *
   * \since 4.0.0
   */
  audio_device_event() noexcept : common_event{event_type::audio_device_added}
  {}

  /**
   * \brief Creates a audio device event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit audio_device_event(const SDL_AudioDeviceEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the audio device ID that is associated with the event.
   *
   * \param which the audio device ID that is associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets whether or not the audio device event is associated with a
   * capture device.
   *
   * \param capture `true` if the event is associated with a capture device;
   * `false` indicates that the event is associated with an output device.
   *
   * \since 4.0.0
   */
  void set_capture(const bool capture) noexcept
  {
    m_event.iscapture = capture;
  }

  /**
   * \brief Returns the audio device ID associated with the event.
   *
   * \return the audio device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Indicates whether or not the audio device event is associated with
   * an audio output device.
   *
   * \return `true` if the event is associated with an output device; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto output() const noexcept -> bool
  {
    return !capture();
  }

  /**
   * \brief Indicates whether or not the audio device event is associated with
   * an audio capture device.
   *
   * \return `true` if the event is associated with a capture device; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto capture() const noexcept -> bool
  {
    return m_event.iscapture;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_AudioDeviceEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

/**
 * \class controller_axis_event
 *
 * \brief Represents an event triggered by game controller axis motion.
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class controller_axis_event final : public common_event<SDL_ControllerAxisEvent>
{
 public:
  /**
   * \brief Creates a controller axis event of type `controller_axis_motion`.
   *
   * \since 4.0.0
   */
  controller_axis_event() noexcept
      : common_event{cen::event_type::controller_axis_motion}
  {}

  /**
   * \brief Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_axis_event(const SDL_ControllerAxisEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the instance ID of the joystick that the event is
   * associated with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the game controller axis value associated with the event.
   *
   * \param axis the game controller axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const controller_axis axis) noexcept
  {
    m_event.axis = static_cast<u8>(axis);
  }

  /**
   * \brief Sets the axis value associated with the event.
   *
   * \param value the new axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_value(const i16 value) noexcept
  {
    m_event.value = value;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the game controller axis value associated with the event.
   *
   * \return the game controller axis value associated with the event.
   *
   * \see `GameControllerAxis`
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> controller_axis
  {
    return static_cast<controller_axis>(m_event.axis);
  }

  /**
   * \brief Returns the axis value associated with the event.
   *
   * \return the axis value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto value() const noexcept -> i16
  {
    return m_event.value;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerAxisEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

/**
 * \class controller_button_event
 *
 * \brief Represents events associated with the state of buttons of a game
 * controller.
 *
 * \see `SDL_ControllerButtonEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class controller_button_event final
    : public common_event<SDL_ControllerButtonEvent>
{
 public:
  /**
   * \brief Creates a controller button event of type `controller_button_down`.
   *
   * \since 4.0.0
   */
  controller_button_event() noexcept
      : common_event{event_type::controller_button_down}
  {}

  /**
   * \brief Creates a controller button event that is based on the supplied SDL
   * controller button event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_button_event(
      const SDL_ControllerButtonEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the game controller button associated with the event.
   *
   * \param button the game controller button associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const controller_button button) noexcept
  {
    m_event.button = static_cast<u8>(button);
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = static_cast<u8>(state);
  }

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param id the instance ID of the joystick that the event is associated
   * with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID id) noexcept
  {
    m_event.which = id;
  }

  /**
   * \brief Returns the game controller button associated with the event.
   *
   * \return the game controller button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> controller_button
  {
    return static_cast<controller_button>(m_event.button);
  }

  /**
   * \brief Returns the button state associated with the event.
   *
   * \return the button state associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the associated button is pressed.
   *
   * \return `true` if the associated button is pressed; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Indicates whether or not the associated button is released.
   *
   * \return `true` if the associated button is released; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerButtonEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.cbutton = event.get();
  return e;
}

/**
 * \class controller_device_event
 *
 * \brief Represents events related to game controller devices such as adding
 * or removing game controller devices.
 *
 * \see `SDL_ControllerDeviceEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class controller_device_event final
    : public common_event<SDL_ControllerDeviceEvent>
{
 public:
  /**
   * \brief Creates a controller device event of type `controller_device_added`.
   *
   * \since 4.0.0
   */
  controller_device_event() noexcept
      : common_event{event_type::controller_device_added}
  {}

  /**
   * \brief Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_device_event(
      const SDL_ControllerDeviceEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick device index or instance ID.
   *
   * \details If the event type is `Added`, then this value is the joystick
   * device index. If the type of the event is either `Removed` or
   * `Remapped`, then this value is the instance ID.
   *
   * \param which the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const i32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Returns the joystick device index or instance ID.
   *
   * \details Returns the joystick device index if the type of the event is
   * `Added`. Returns the instance ID if the type of the event is either
   * `Removed` or `Remapped`.
   *
   * \return the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> i32
  {
    return m_event.which;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerDeviceEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

/**
 * \class dollar_gesture_event
 *
 * \brief Provides information about dollar gestures from touch events.
 *
 * \see `SDL_DollarGestureEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class dollar_gesture_event final : public common_event<SDL_DollarGestureEvent>
{
 public:
  /**
   * \brief Creates a dollar gesture event of type `dollar_gesture`.
   *
   * \since 4.0.0
   */
  dollar_gesture_event() noexcept : common_event{event_type::dollar_gesture}
  {
    set_type(event_type::dollar_gesture);
  }

  /**
   * \brief Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the touch device ID associated with the event.
   *
   * \param id the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept
  {
    m_event.touchId = id;
  }

  /**
   * \brief Sets the gesture ID associated with the event.
   *
   * \param id the gesture ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_gesture_id(const SDL_GestureID id) noexcept
  {
    m_event.gestureId = id;
  }

  /**
   * \brief Sets the amount of fingers used to draw the stroke.
   *
   * \param fingers the amount of fingers used to draw the stroke.
   *
   * \since 4.0.0
   */
  void set_fingers(const u32 fingers) noexcept
  {
    m_event.numFingers = fingers;
  }

  /**
   * \brief Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * \since 4.0.0
   */
  void set_error(const float error) noexcept
  {
    m_event.error = error;
  }

  /**
   * \brief Sets the normalized x-coordinate of the center of the gesture.
   *
   * \param x the normalized x-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_x(const float x) noexcept
  {
    m_event.x = x;
  }

  /**
   * \brief Sets the normalized y-coordinate of the center of the gesture.
   *
   * \param y the normalized y-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_y(const float y) noexcept
  {
    m_event.y = y;
  }

  /**
   * \brief Returns the touch device ID associated with the event.
   *
   * \return the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID
  {
    return m_event.touchId;
  }

  /**
   * \brief Returns the unique ID of the closest gesture to the performed
   * stroke.
   *
   * \return the unique ID of the closest gesture to the performed stroke.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto gesture_id() const noexcept -> SDL_GestureID
  {
    return m_event.gestureId;
  }

  /**
   * \brief Returns the amount of fingers used to draw the stroke.
   *
   * \return the amount of fingers used to draw the stroke.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto fingers() const noexcept -> u32
  {
    return m_event.numFingers;
  }

  /**
   * \brief Returns the difference between the gesture template and the
   * performed gesture.
   *
   * \details The lower the error, the better the match.
   *
   * \return the difference between the gesture template and the performed
   * gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto error() const noexcept -> float
  {
    return m_event.error;
  }

  /**
   * \brief Returns the x-coordinate of the normalized center of the gesture.
   *
   * \return the x-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the normalized center of the gesture.
   *
   * \return the y-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> float
  {
    return m_event.y;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_DollarGestureEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.dgesture = event.get();
  return e;
}

/**
 * \class drop_event
 *
 * \brief Represents the event of requesting a file to be opened.
 *
 * \see `SDL_DropEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class drop_event final : public common_event<SDL_DropEvent>
{
 public:
  /**
   * \brief Creates a drop event of type `drop_file`.
   *
   * \since 4.0.0
   */
  drop_event() noexcept : common_event{event_type::drop_file}
  {}

  /**
   * \brief Creates a drop event based on the supplied event.
   *
   * \param event the SDL drop event that will be copied.
   *
   * \since 4.0.0
   */
  explicit drop_event(const SDL_DropEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Destroys the drop event.
   *
   * \details The associated file will be freed depending on the value
   * returned from the `will_free_file()` method.
   *
   * \since 4.0.0
   */
  ~drop_event() noexcept
  {
    if (m_event.file && m_willFreeFile) {
      SDL_free(m_event.file);
    }
  }

  /**
   * \brief Sets whether or not the associated file will be freed by this event.
   *
   * \details If you set this property to `false`, you **must** remember to
   * call `SDL_free` on the file pointer by yourself. Otherwise, you'll end
   * up with a memory leak!
   *
   * \param freeFile `true` if the associated file should be freed upon the
   * destruction of the event; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_will_free_file(const bool freeFile) noexcept
  {
    m_willFreeFile = freeFile;
  }

  /**
   * \brief Sets the file associated with the drop event.
   *
   * \details The ownership of the supplied pointer will, by default, not be
   * claimed by this event.
   *
   * \note The supplied pointer will be freed using `SDL_free` upon the
   * destruction of the event *if* the `will_free_file` property is set to
   * **true**.
   *
   * \note If the `will_free_file` property is `true`, then **the previously
   * set file pointer will be freed** by calling this method. However, if the
   * `will_free_file` property is `false`, then the old file pointer is
   * simply overridden. Of course, this may, if you're not careful, introduce a
   * memory leak in your program!
   *
   * \warning Make sure you know what you are doing when using this method.
   *
   * \param file a pointer to a file, can safely be null.
   *
   * \since 4.0.0
   */
  void set_file(char* file) noexcept
  {
    if (m_event.file && m_willFreeFile) {
      SDL_free(m_event.file);
    }
    m_event.file = file;
  }

  /**
   * \brief Sets the ID of the window that is the target of the drop event.
   *
   * \param id the ID of the window that is the target of the drop event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Indicates whether or not the associated file will be freed by
   * this event upon destruction.
   *
   * \details By default, this property is set to **false**.
   *
   * \return `true` if the associated file will be freed upon destruction;
   * `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto will_free_file() const noexcept -> bool
  {
    return m_willFreeFile;
  }

  /**
   * \brief Returns a pointer to the associated file.
   *
   * \warning Do **not** claim ownership of the returned pointer *without*
   * setting the `will_free_file` property to **false**.
   *
   * \note The returned pointer is always `nullptr` for `drop_begin` and
   * `drop_complete` drop events.
   *
   * \return a pointer to the file associated with the event, might be null.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto file() const noexcept -> char*
  {
    return m_event.file;
  }

  /**
   * \brief Returns the ID of the window that is the target of the drop
   * event, if there even is one.
   *
   * \return the ID of the window that is the target of the drop event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

 private:
  bool m_willFreeFile{false};
};

template <>
inline auto as_sdl_event(const common_event<SDL_DropEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.drop = event.get();
  return e;
}

/**
 * \class joy_axis_event
 *
 * \brief Represents an event that occurs whenever a user moves an axis on a
 * joystick.
 *
 * \see `SDL_JoyAxisEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class joy_axis_event final : public common_event<SDL_JoyAxisEvent>
{
 public:
  /**
   * \brief Creates a joy axis event.
   *
   * \since 4.0.0
   */
  joy_axis_event() noexcept : common_event{event_type::joystick_axis_motion}
  {}

  /**
   * \brief Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * \param event the SDL joy axis event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_axis_event(const SDL_JoyAxisEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the joystick axis index associated with the event.
   *
   * \param axis the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const u8 axis) noexcept
  {
    m_event.axis = axis;
  }

  /**
   * \brief Sets the joystick axis value associated with the event.
   *
   * \param value the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_value(const i16 value) noexcept
  {
    m_event.value = value;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the joystick axis index associated with the event.
   *
   * \return the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> u8
  {
    return m_event.axis;
  }

  /**
   * \brief Returns the joystick axis value associated with the event.
   *
   * \return the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto value() const noexcept -> i16
  {
    return m_event.value;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_JoyAxisEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

/**
 * \class joy_ball_event
 *
 * \brief Represents the event that is triggered when a user moves a
 * trackball on a joystick.
 *
 * \see `SDL_JoyBallEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class joy_ball_event final : public common_event<SDL_JoyBallEvent>
{
 public:
  /**
   * \brief Creates a joy ball event.
   *
   * \since 4.0.0
   */
  joy_ball_event() noexcept : common_event{event_type::joystick_ball_motion}
  {}

  /**
   * \brief Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * \param event the SDL joy ball event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_ball_event(const SDL_JoyBallEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the joystick trackball index associated with the event.
   *
   * \param ball the joystick trackball index.
   *
   * \since 4.0.0
   */
  void set_ball(const u8 ball) noexcept
  {
    m_event.ball = ball;
  }

  /**
   * \brief Sets the relative motion along the x-axis associated with the event.
   *
   * \param dx the relative motion along the x-axis.
   *
   * \since 4.0.0
   */
  void set_dx(const i16 dx) noexcept
  {
    m_event.xrel = dx;
  }

  /**
   * \brief Sets the relative motion along the y-axis associated with the event.
   *
   * \param dy the relative motion along the y-axis.
   *
   * \since 4.0.0
   */
  void set_dy(const i16 dy) noexcept
  {
    m_event.yrel = dy;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the joystick trackball index associated with the event.
   *
   * \return the joystick trackball index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto ball() const noexcept -> u8
  {
    return m_event.ball;
  }

  /**
   * \brief Returns the relative motion along the x-axis.
   *
   * \note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the x-axis since it was last updated.
   *
   * \return the relative motion along the x-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dx() const noexcept -> i16
  {
    return m_event.xrel;
  }

  /**
   * \brief Returns the relative motion along the y-axis.
   *
   * \note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the y-axis since it was last updated.
   *
   * \return the relative motion along the y-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dy() const noexcept -> i16
  {
    return m_event.yrel;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_JoyBallEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

/**
 * \class joy_button_event
 *
 * \brief Represents an event associated with the press or release of a
 * joystick button.
 *
 * \see `SDL_JoyButtonEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class joy_button_event final : public common_event<SDL_JoyButtonEvent>
{
 public:
  /**
   * \brief Creates a joystick button event of type `joystick_button_down`.
   *
   * \since 4.0.0
   */
  joy_button_event() noexcept : common_event{event_type::joystick_button_down}
  {}

  /**
   * \brief Creates a joy_button_event based on the supplied event.
   *
   * \param event the event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_button_event(const SDL_JoyButtonEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the button index associated with the event.
   *
   * \param button the button index associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const u8 button) noexcept
  {
    m_event.button = button;
  }

  /**
   * \brief Sets the button state that is associated with the button that
   * triggered the event.
   *
   * \param state the button state that is associated with the button that
   * triggered the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = static_cast<u8>(state);
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the index of the button that changed.
   *
   * \return the index of the button that changed.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> u8
  {
    return m_event.button;
  }

  /**
   * \brief Returns the state of the button associated with the event.
   *
   * \return the state of the button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the associated button is pressed.
   *
   * \return `true` if the associated button is pressed; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Indicates whether or not the associated button is released.
   *
   * \return `true` if the associated button is released; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_JoyButtonEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.jbutton = event.get();
  return e;
}

/**
 * \class joy_device_event
 *
 * \brief Represents an event triggered by adding or removing a joystick device.
 *
 * \see `SDL_JoyDeviceEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class joy_device_event final : public common_event<SDL_JoyDeviceEvent>
{
 public:
  /**
   * \brief Creates a joystick device event of type `joystick_device_added`.
   *
   * \since 4.0.0
   */
  joy_device_event() noexcept : common_event{event_type::joystick_device_added}
  {}

  /**
   * \brief Creates a joy_device_event that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_device_event(const SDL_JoyDeviceEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick device index or instance ID, depending on the type
   * of the event.
   *
   * \param which the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const i32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Returns the joystick device index or instance ID.
   *
   * \details The returned value is the joystick device index if the type is
   * `JoystickDeviceAdded`, or the joystick instance ID if the type is
   * `JoystickDeviceRemoved`.
   *
   * \return the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> i32
  {
    return m_event.which;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_JoyDeviceEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.jdevice = event.get();
  return e;
}

/**
 * \enum joy_hat_position
 *
 * \brief Serves as a wrapper for the `SDL_HAT_x` macro values.
 *
 * \since 4.0.0
 */
enum class joy_hat_position
{
  left_up = SDL_HAT_LEFTUP,
  left = SDL_HAT_LEFT,
  left_down = SDL_HAT_LEFTDOWN,
  up = SDL_HAT_UP,
  centered = SDL_HAT_CENTERED,
  down = SDL_HAT_DOWN,
  right_up = SDL_HAT_RIGHTUP,
  right = SDL_HAT_RIGHT,
  right_down = SDL_HAT_RIGHTDOWN
};

/**
 * \class joy_hat_event
 *
 * \brief Represents an event that is triggered whenever a user moves a hat
 * on a joystick.
 *
 * \see `SDL_JoyHatEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class joy_hat_event final : public common_event<SDL_JoyHatEvent>
{
 public:
  /**
   * \brief Creates a joy hat event.
   *
   * \since 4.0.0
   */
  joy_hat_event() noexcept : common_event{event_type::joystick_hat_motion}
  {}

  /**
   * \brief Creates a joy hat event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_hat_event(const SDL_JoyHatEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the hat index associated with the event.
   *
   * \param hat the hat index.
   *
   * \since 4.0.0
   */
  void set_hat(const u8 hat) noexcept
  {
    m_event.hat = hat;
  }

  /**
   * \brief Sets the joystick hat position associated with the event.
   *
   * \param value the joystick hat position associated with the event.
   *
   * \since 4.0.0
   */
  void set_position(const joy_hat_position value) noexcept
  {
    m_event.value = static_cast<u8>(value);
  }

  /**
   * \brief Returns the index of the hat that changed.
   *
   * \return the index of the hat that changed.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto hat() const noexcept -> u8
  {
    return m_event.hat;
  }

  /**
   * \brief Returns the position of the associated joystick hat.
   *
   * \return the position of the associated joystick hat.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto position() const noexcept -> joy_hat_position
  {
    return static_cast<joy_hat_position>(m_event.value);
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_JoyHatEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.jhat = event.get();
  return e;
}

/**
 * \class keyboard_event
 *
 * \brief Represents an event associated with some sort of key action, such
 * as the release or pressing of a key.
 *
 * \see `SDL_KeyboardEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class keyboard_event final : public common_event<SDL_KeyboardEvent>
{
 public:
  /**
   * \brief Creates a keyboard event of type `key_down`.
   *
   * \since 4.0.0
   */
  keyboard_event() noexcept : common_event{event_type::key_down}
  {}

  /**
   * \brief Creates a keyboard event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit keyboard_event(const SDL_KeyboardEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the scan code that is associated with the event.
   *
   * \param code the scan code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_scan_code(const scan_code& code) noexcept
  {
    m_event.keysym.scancode = code.get();
  }

  /**
   * \brief Sets the key code that is associated with the event.
   *
   * \param code the key code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_key_code(const key_code& code) noexcept
  {
    m_event.keysym.sym = code.get();
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state that will be associated with the event
   *
   * \since 5.0.0
   */
  void set_button_state(const button_state state) noexcept
  {
    m_event.state = static_cast<u8>(state);
  }

  /**
   * \brief Sets the status of a key modifier.
   *
   * \param modifier the key modifier that will be affected.
   * \param active `true` if the key modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_modifier(const key_modifier modifier, const bool active) noexcept
  {
    if (active) {
      m_event.keysym.mod |= static_cast<u16>(modifier);
    } else {
      m_event.keysym.mod &= ~static_cast<u16>(modifier);
    }
  }

  /**
   * \brief Sets the flag that indicates whether or not the key associated with
   * this key event was repeatedly triggered.
   *
   * \param repeated `true` if the key was repeatedly triggered; `false`
   * otherwise.
   *
   * \since 4.0.0
   */
  void set_repeated(const bool repeated) noexcept
  {
    m_event.repeat = repeated;
  }

  /**
   * \brief Sets the window ID that is associated with this key event.
   *
   * \param id the window ID that should be associated with the key event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Indicates whether or not the event is associated with the
   * specified scan code.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the supplied scan code is associated with the event;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_active(const scan_code& code) const noexcept -> bool
  {
    return m_event.keysym.scancode == code.get();
  }

  /**
   * \brief Indicates whether or not the event is associated with the
   * specified key code.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the supplied key code is associated with the event;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_active(const key_code& code) const noexcept -> bool
  {
    return static_cast<SDL_KeyCode>(m_event.keysym.sym) == code.get();
  }

  /**
   * \brief Indicates whether or not the specified key modifier is active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifier the key modifier that will be checked.
   *
   * \return `true` if the specified key modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto modifier_active(const key_modifier modifier) const noexcept
      -> bool
  {
    return m_event.keysym.mod & static_cast<u16>(modifier);
  }

  /**
   * \brief Indicates whether or not any of the SHIFT modifiers are active.
   *
   * \return `true` if any of the SHIFT modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto shift_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::left_shift) ||
           modifier_active(key_modifier::right_shift);
  }

  /**
   * \brief Indicates whether or not any of the CTRL modifiers are active.
   *
   * \return `true` if any of the CTRL modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto ctrl_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::left_ctrl) ||
           modifier_active(key_modifier::right_ctrl);
  }

  /**
   * \brief Indicates whether or not any of the ALT modifiers are active.
   *
   * \return `true` if any of the ALT modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto alt_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::left_alt) ||
           modifier_active(key_modifier::right_alt);
  }

  /**
   * \brief Indicates whether or not any of the GUI modifiers are active.
   *
   * \return `true` if any of the GUI modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto gui_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::left_gui) ||
           modifier_active(key_modifier::right_gui);
  }

  /**
   * \brief Indicates whether or not the CAPS modifier is active.
   *
   * \return `true` if the CAPS modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto caps_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::caps);
  }

  /**
   * \brief Indicates whether or not the NUM modifier is active.
   *
   * \return `true` if the NUM modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto num_active() const noexcept -> bool
  {
    return modifier_active(key_modifier::num);
  }

  /**
   * \brief Indicates whether or not the key associated with this key event has
   * been repeatedly triggered.
   *
   * \return `true` if the key associated with the event was repeated; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto repeated() const noexcept -> bool
  {
    return m_event.repeat;
  }

  /**
   * \brief Returns the button state of the key associated with the event.
   *
   * \return the button state of the key associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the event is associated with the release
   * of a key.
   *
   * \note This function is equivalent to `state() ==  button_state::released`.
   *
   * \return `true` if the event is a key released event; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  /**
   * \brief Indicates whether or not the event is associated with the press
   * of a key.
   *
   * \note This function is equivalent to `state() ==  button_state::pressed`.
   *
   * \return `true` if the event is a key pressed event; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Returns the scan code that is associated with the event.
   *
   * \return the scan code that is associated with the event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_scan_code() const noexcept -> scan_code
  {
    return m_event.keysym.scancode;
  }

  /**
   * \brief Returns the key code that is associated with the event.
   *
   * \return the key code that is associated with the event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_key_code() const noexcept -> key_code
  {
    return static_cast<SDL_KeyCode>(m_event.keysym.sym);
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_KeyboardEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

/**
 * \class mouse_button_event
 *
 * \brief Represents an event triggered by mouse button presses or releases.
 *
 * \see `SDL_MouseButtonEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class mouse_button_event final : public common_event<SDL_MouseButtonEvent>
{
 public:
  /**
   * \brief Creates a mouse button event of type `mouse_button_down`.
   *
   * \since 4.0.0
   */
  mouse_button_event() noexcept : common_event{event_type::mouse_button_down}
  {}

  /**
   * \brief Creates a mouse_button_event that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_button_event(const SDL_MouseButtonEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the mouse instance ID.
   *
   * \param which the mouse instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the mouse button associated with the event.
   *
   * \param button the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const mouse_button button) noexcept
  {
    m_event.button = static_cast<u8>(button);
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = static_cast<u8>(state);
  }

  /**
   * \brief Sets the amount of clicks associated with the event.
   *
   * \param clicks the amount of clicks associated with the event.
   *
   * \since 4.0.0
   */
  void set_clicks(const u8 clicks) noexcept
  {
    m_event.clicks = clicks;
  }

  /**
   * \brief Sets the x-coordinate of the mouse relative to the window.
   *
   * \param x the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_x(const i32 x) noexcept
  {
    m_event.x = x;
  }

  /**
   * \brief Sets the y-coordinate of the mouse relative to the window.
   *
   * \param y the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_y(const i32 y) noexcept
  {
    m_event.y = y;
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * \return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Returns the mouse button associated with the event.
   *
   * \return the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> mouse_button
  {
    return static_cast<mouse_button>(m_event.button);
  }

  /**
   * \brief Returns the state of the mouse button associated with the event.
   *
   * \return the state of the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the associated button is pressed.
   *
   * \return `true` if the associated button is pressed; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Indicates whether or not the associated button is released.
   *
   * \return `true` if the associated button is released; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  /**
   * \brief Returns the number of mouse clicks associated with the event.
   *
   * \return the number of mouse clicks associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto clicks() const noexcept -> u8
  {
    return m_event.clicks;
  }

  /**
   * \brief Returns the x-coordinate of the mouse relative to the window.
   *
   * \return the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> i32
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the mouse relative to the window.
   *
   * \return the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> i32
  {
    return m_event.y;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_MouseButtonEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

/**
 * \class mouse_motion_event
 *
 * \brief Represents events that are triggered by the movement of the mouse.
 *
 * \see `SDL_MouseMotionEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class mouse_motion_event final : public common_event<SDL_MouseMotionEvent>
{
 public:
  /**
   * \brief Creates a mouse motion event.
   *
   * \since 4.0.0
   */
  mouse_motion_event() noexcept : common_event{event_type::mouse_motion}
  {}

  /**
   * \brief Creates a `MouseMotionEvent` that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_motion_event(const SDL_MouseMotionEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the mouse instance ID.
   *
   * \param which the mouse instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the mouse button state associated with the event.
   *
   * \details The state could be any of `SDL_BUTTON_LMASK`, `SDL_BUTTON_MMASK`,
   * `SDL_BUTTON_RMASK`, `SDL_BUTTON_X1MASK` and `SDL_BUTTON_X2MASK` OR'd
   * together.
   *
   * \param state the mouse button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const u32 state) noexcept
  {
    m_event.state = state;
  }

  /**
   * \brief Sets the x-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * \param x the x-coordinate of the mouse.
   *
   * \since 4.0.0
   */
  void set_x(const i32 x) noexcept
  {
    m_event.x = x;
  }

  /**
   * \brief Sets the y-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * \param y the y-coordinate of the mouse.
   *
   * \since 4.0.0
   */
  void set_y(const i32 y) noexcept
  {
    m_event.y = y;
  }

  /**
   * \brief Sets the value of the relative motion of the mouse along the x-axis.
   *
   * \param dx the value of the relative motion of the mouse along the x-axis.
   *
   * \since 4.0.0
   */
  void set_dx(const i32 dx) noexcept
  {
    m_event.xrel = dx;
  }

  /**
   * \brief Sets the value of the relative motion of the mouse along the y-axis.
   *
   * \param dy the value of the relative motion of the mouse along the y-axis.
   *
   * \since 4.0.0
   */
  void set_dy(const i32 dy) noexcept
  {
    m_event.yrel = dy;
  }

  /**
   * \brief Returns the window ID associated with the event.
   *
   * \return the window ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * \details The returned value might be `SDL_TOUCH_MOUSEID` for events that
   * were generated by a touch input device.
   *
   * \return the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Returns a bitmask for the current mouse button state.
   *
   * \remark If you want to check if a specific mouse button is pressed or
   * released, a better alternative would be to use the `pressed(MouseButton)
   * ` method.
   *
   * \return a bitmask for the current mouse button state.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> u32
  {
    return m_event.state;
  }

  /**
   * \brief Indicates whether or not a mouse button is pressed.
   *
   * \param button the mouse button that will be checked.
   *
   * \return `true` if the specified mouse button is pressed; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pressed(const mouse_button button) const noexcept -> bool
  {
    return m_event.state & SDL_BUTTON(static_cast<u32>(button));
  }

  /**
   * \brief Returns the x-coordinate of the mouse relative to the window.
   *
   * \return the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> i32
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the mouse relative to the window.
   *
   * \return the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> i32
  {
    return m_event.y;
  }

  /**
   * \brief Returns the relative motion of the mouse along the x-axis.
   *
   * \return the relative motion of the mouse along the x-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dx() const noexcept -> i32
  {
    return m_event.xrel;
  }

  /**
   * \brief Returns the relative motion of the mouse along the y-axis.
   *
   * \return the relative motion of the mouse along the y-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dy() const noexcept -> i32
  {
    return m_event.yrel;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_MouseMotionEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.motion = event.get();
  return e;
}

/**
 * \enum mouse_wheel_direction
 *
 * \brief Mirrors the the `SDL_MouseWheelDirection` enum.
 *
 * \see `SDL_MouseWheelDirection`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
enum class mouse_wheel_direction
{
  normal = SDL_MOUSEWHEEL_NORMAL,   ///< The scroll direction is normal
  flipped = SDL_MOUSEWHEEL_FLIPPED  ///< The scroll direction is flipped natural
};

/**
 * \class mouse_wheel_event
 *
 * \brief Represents events triggered when a user moves the mouse wheel.
 *
 * \see `SDL_MouseWheelEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class mouse_wheel_event final : public common_event<SDL_MouseWheelEvent>
{
 public:
  /**
   * \brief Creates a mouse wheel event.
   *
   * \since 4.0.0
   */
  mouse_wheel_event() noexcept : common_event{event_type::mouse_wheel}
  {}

  /**
   * \brief Creates a `MouseMotionEvent` that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the mouse instance ID.
   *
   * \param which the mouse instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the horizontally scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \param xScroll the horizontally scrolled distance.
   *
   * \since 4.0.0
   */
  void set_x_scroll(const i32 xScroll) noexcept
  {
    m_event.x = xScroll;
  }

  /**
   * \brief Sets the vertically scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \param yScroll the vertically scrolled distance.
   *
   * \since 4.0.0
   */
  void set_y_scroll(const i32 yScroll) noexcept
  {
    m_event.y = yScroll;
  }

  /**
   * \brief Sets the mouse wheel direction mode associated with the event.
   *
   * \param direction the mouse wheel direction mode associated with the event.
   *
   * \since 4.0.0
   */
  void set_direction(const mouse_wheel_direction direction) noexcept
  {
    m_event.direction = static_cast<u32>(direction);
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the mouse instance ID, or `SDL_TOUCH_MOUSEID` if the event
   * was triggered by a touch input device.
   *
   * \return the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Returns the horizontally scrolled distance
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \return the horizontally scrolled distance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x_scroll() const noexcept -> i32
  {
    return m_event.x;
  }

  /**
   * \brief Returns the vertically scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \return the vertically scrolled distance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y_scroll() const noexcept -> i32
  {
    return m_event.y;
  }

  /**
   * \brief Returns the mouse wheel direction mode associated with the event.
   *
   * \return the mouse wheel direction mode associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto direction() const noexcept -> mouse_wheel_direction
  {
    return static_cast<mouse_wheel_direction>(m_event.direction);
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_MouseWheelEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.wheel = event.get();
  return e;
}

/**
 * \class multi_gesture_event
 *
 * \brief Provides information about events related to touch events triggered
 * by multiple fingers.
 *
 * \see `SDL_MultiGestureEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class multi_gesture_event final : public common_event<SDL_MultiGestureEvent>
{
 public:
  /**
   * \brief Creates a multi-gesture event.
   *
   * \since 4.0.0
   */
  multi_gesture_event() noexcept : common_event{event_type::multi_gesture}
  {}

  /**
   * \brief Creates a `MultiGestureEvent` that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit multi_gesture_event(const SDL_MultiGestureEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the touch device ID associated with the event.
   *
   * \param id the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept
  {
    m_event.touchId = id;
  }

  /**
   * \brief Sets the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * \param dTheta the amount that the fingers rotated.
   *
   * \since 4.0.0
   */
  void set_delta_theta(const float dTheta) noexcept
  {
    m_event.dTheta = dTheta;
  }

  /**
   * \brief Sets the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * \param dDistance the amount that the fingers pinched.
   *
   * \since 4.0.0
   */
  void set_delta_distance(const float dDistance) noexcept
  {
    m_event.dDist = dDistance;
  }

  /**
   * \brief Sets the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \param centerX the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \since 4.0.0
   */
  void set_center_x(const float centerX) noexcept
  {
    m_event.x = centerX;
  }

  /**
   * \brief Sets the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \param centerY the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \since 4.0.0
   */
  void set_center_y(const float centerY) noexcept
  {
    m_event.y = centerY;
  }

  /**
   * \brief Sets the number of fingers that was used in the gesture associated
   * with the event.
   *
   * \param nFingers the number of fingers that was used in the gesture.
   *
   * \since 4.0.0
   */
  void set_fingers(const u16 nFingers) noexcept
  {
    m_event.numFingers = nFingers;
  }

  /**
   * \brief Returns the touch device ID associated with the event.
   *
   * \return the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID
  {
    return m_event.touchId;
  }

  /**
   * \brief Returns the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * \return the amount that the fingers rotated.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto delta_theta() const noexcept -> float
  {
    return m_event.dTheta;
  }

  /**
   * \brief Returns the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * \return the amount that the fingers pinched.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto delta_distance() const noexcept -> float
  {
    return m_event.dDist;
  }

  /**
   * \brief Returns the x-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * \return the x-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto center_x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * \return the y-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto center_y() const noexcept -> float
  {
    return m_event.y;
  }

  /**
   * \brief Returns the amount of fingers used in the gesture associated with
   * the event.
   *
   * \return the amount of fingers used in the gesture associated with the
   * event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto fingers() const noexcept -> float
  {
    return m_event.numFingers;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_MultiGestureEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.mgesture = event.get();
  return e;
}

/**
 * \class quit_event
 *
 * \brief Represents the event of the user wanting to close the application,
 * usually by pressing the "X"-button on the window frame.
 *
 * \see `SDL_QuitEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class quit_event final : public common_event<SDL_QuitEvent>
{
 public:
  /**
   * \brief Creates a quit event.
   *
   * \since 4.0.0
   */
  quit_event() noexcept : common_event{event_type::quit}
  {}

  /**
   * \brief Creates a quit event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit quit_event(const SDL_QuitEvent& event) noexcept : common_event{event}
  {}
};

template <>
inline auto as_sdl_event(const common_event<SDL_QuitEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.quit = event.get();
  return e;
}

/**
 * \class text_editing_event
 *
 * \brief Represents an event triggered by keyboard text editing.
 *
 * \note This class doesn't provide a setter for the text, since it's
 * impossible to assign a value to a variable of type `char[32]` in C++.
 *
 * \see `SDL_TextEditingEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class text_editing_event final : public common_event<SDL_TextEditingEvent>
{
 public:
  /**
   * \brief Creates a text editing event.
   *
   * \since 4.0.0
   */
  text_editing_event() noexcept : common_event{event_type::text_editing}
  {
    check_length();
  }

  /**
   * \brief Creates a `TextEditingEvent` that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit text_editing_event(const SDL_TextEditingEvent& event) noexcept
      : common_event{event}
  {
    check_length();
  }

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the location to begin editing from.
   *
   * \param start the location to begin editing from.
   *
   * \since 4.0.0
   */
  void set_start(const i32 start) noexcept
  {
    m_event.start = start;
  }

  /**
   * \brief Sets the number of characters to edit from the start point.
   *
   * \details The supplied value will be clamped to the range [0, 32].
   *
   * \param length the number of characters to edit from the start point.
   *
   * \since 4.0.0
   */
  void set_length(const i32 length) noexcept
  {
    m_event.length = detail::clamp(length, 0, 32);
  }

  /**
   * \brief Returns the window ID associated with the event.
   *
   * \return the window ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the text that will be used, as a null-terminated string in
   * UTF-8 encoding.
   *
   * \return the text that will be used.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto text() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<czstring>(m_event.text)};
  }

  /**
   * \brief Returns the location to begin editing from.
   *
   * \return the location to begin editing from.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto start() const noexcept -> i32
  {
    return m_event.start;
  }

  /**
   * \brief Returns the number of characters to edit from the start point.
   *
   * \details The returned value will always be in the range [0, 32].
   *
   * \return the number of characters to edit from the start point.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto length() const noexcept -> i32
  {
    return m_event.length;
  }

 private:
  void check_length() noexcept
  {
    m_event.length = detail::clamp(m_event.length, 0, 32);
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_TextEditingEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.edit = event.get();
  return e;
}

/**
 * \class text_input_event
 *
 * \brief Provides information about keyboard text input events.
 *
 * \see `SDL_TextInputEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class text_input_event final : public common_event<SDL_TextInputEvent>
{
 public:
  /**
   * \brief Creates a text input event.
   *
   * \since 4.0.0
   */
  text_input_event() noexcept : common_event{event_type::text_input}
  {}

  /**
   * \brief Creates a `TextInputEvent` that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit text_input_event(const SDL_TextInputEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Returns the window ID associated with the event.
   *
   * \return the window ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * \return the text that will be used.
   * \since 4.0.0
   */
  [[nodiscard]] auto text_utf8() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<czstring>(m_event.text)};
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_TextInputEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.text = event.get();
  return e;
}

/**
 * \class touch_finger_event
 *
 * \brief Represents an event related to touch screen actions.
 *
 * \see `SDL_TouchFingerEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class touch_finger_event final : public common_event<SDL_TouchFingerEvent>
{
 public:
  /**
   * \brief Creates a touch finger event of type `touch_down`.
   *
   * \since 4.0.0
   */
  touch_finger_event() noexcept : common_event{event_type::touch_down}
  {}

  /**
   * \brief Creates a touch finger event that is based on the supplied SDL
   * ouch finger event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit touch_finger_event(const SDL_TouchFingerEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the ID of the associated touch device.
   *
   * \param id the ID of the associated touch device.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept
  {
    m_event.touchId = id;
  }

  /**
   * \brief Sets the finger ID associated with the event.
   *
   * \param id the finger ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_finger_id(const SDL_FingerID id) noexcept
  {
    m_event.fingerId = id;
  }

  /**
   * \brief Sets the window ID of the window under the finger.
   *
   * \param id the window ID of the window under the finger.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the normalized x-coordinate of the location of the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param x the normalized x-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_x(const float x) noexcept
  {
    m_event.x = detail::clamp(x, 0.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized y-coordinate of the location of the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param y the normalized y-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_y(const float y) noexcept
  {
    m_event.y = detail::clamp(y, 0.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized distance moved along the x-axis.
   *
   * \details The supplied value will be clamped to the range [-1, 1].
   *
   * \param dx the normalized distance moved along the x-axis, clamped to the
   * range [-1, 1].
   *
   * \since 4.0.0
   */
  void set_dx(const float dx) noexcept
  {
    m_event.dx = detail::clamp(dx, -1.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized distance moved along the y-axis.
   *
   * \details The supplied value will be clamped to the range [-1, 1].
   *
   * \param dy the normalized distance moved along the y-axis, clamped to the
   * range [-1, 1].
   *
   * \since 4.0.0
   */
  void set_dy(const float dy) noexcept
  {
    m_event.dy = detail::clamp(dy, -1.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized pressure associated with the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param pressure the normalized pressure associated with the event, clamped
   * in the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_pressure(const float pressure) noexcept
  {
    m_event.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  /**
   * \brief Returns the touch device ID associated with the event.
   *
   * \return the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID
  {
    return m_event.touchId;
  }

  /**
   * \brief Returns the finger ID associated with the event.
   *
   * \return the finger ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto finger_id() const noexcept -> SDL_FingerID
  {
    return m_event.fingerId;
  }

  /**
   * \brief Returns the window ID of the window under the finger.
   *
   * \return the window ID of the window under the finger.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the normalized x-coordinate of the location of the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized x-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the normalized y-coordinate of the location of the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized y-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> float
  {
    return m_event.y;
  }

  /**
   * \brief Returns the normalized distance moved along the x-axis.
   *
   * \details The returned value will be in the range [-1, 1].
   *
   * \return the normalized distance moved along the x-axis, in the range
   * [-1, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dx() const noexcept -> float
  {
    return m_event.dx;
  }

  /**
   * \brief Returns the normalized distance moved along the y-axis.
   *
   * \details The returned value will be in the range [-1, 1].
   *
   * \return the normalized distance moved along the y-axis, in the range
   * [-1, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dy() const noexcept -> float
  {
    return m_event.dy;
  }

  /**
   * \brief Returns the normalized pressure associated with the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized pressure associated with the event, in the range
   * [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pressure() const noexcept -> float
  {
    return m_event.pressure;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_TouchFingerEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.tfinger = event.get();
  return e;
}

/**
 * \enum window_event_id
 *
 * \brief Mirrors the `SDL_WindowEventID` enum.
 *
 * \details Depending on the event ID of a `window_event` instance, the
 * `window_event::data_1()` and `window_event::data_2()` methods have special
 * meanings.
 *
 * <table style="width:100%">
 *   <tr>
 *     <th>Value</th>
 *     <th>data_1</th>
 *     <th>data_2</th>
 *   </tr>
 *   <tr>
 *    <td><code>None</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Shown</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Hidden</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Exposed</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Moved</code></td>
 *    <td>X</td>
 *    <td>Y</td>
 *   </tr>
 *   <tr>
 *    <td><code>Resized</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>SizeChanged</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>Minimized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Maximized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Restored</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Enter</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Leave</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusGained</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusLost</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Close</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>TakeFocus</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>HitTest</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 * </table>
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
enum class window_event_id
{
  none = SDL_WINDOWEVENT_NONE,
  shown = SDL_WINDOWEVENT_SHOWN,
  hidden = SDL_WINDOWEVENT_HIDDEN,
  exposed = SDL_WINDOWEVENT_EXPOSED,
  moved = SDL_WINDOWEVENT_MOVED,
  resized = SDL_WINDOWEVENT_RESIZED,
  size_changed = SDL_WINDOWEVENT_SIZE_CHANGED,
  minimized = SDL_WINDOWEVENT_MINIMIZED,
  maximized = SDL_WINDOWEVENT_MAXIMIZED,
  restored = SDL_WINDOWEVENT_RESTORED,
  enter = SDL_WINDOWEVENT_ENTER,
  leave = SDL_WINDOWEVENT_LEAVE,
  focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
  focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,
  close = SDL_WINDOWEVENT_CLOSE,
  take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,
  hit_test = SDL_WINDOWEVENT_HIT_TEST
};

/**
 * \class window_event
 *
 * \brief Represents an event that is associated with an action related to a
 * window.
 *
 * \see `SDL_WindowEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class window_event final : public common_event<SDL_WindowEvent>
{
 public:
  /**
   * \brief Creates a window event.
   *
   * \since 4.0.0
   */
  window_event() noexcept : common_event{event_type::window}
  {}

  /**
   * \brief Creates a window event based on the supplied SDL window event.
   *
   * \param event the SDL window event that will be copied.
   *
   * \since 4.0.0
   */
  explicit window_event(const SDL_WindowEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Returns the event ID of this window event.
   *
   * \details There are many different kinds of window events, use this
   * method to check what kind of action that triggered this event.
   *
   * \return the event ID of this window event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto event_id() const noexcept -> window_event_id
  {
    return static_cast<window_event_id>(m_event.event);
  }

  /**
   * \brief Returns the value of the first data value.
   *
   * \details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
   *
   * \return the value of the first data value.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto data_1() const noexcept -> i32
  {
    return m_event.data1;
  }

  /**
   * \brief Returns the value of the second data value.
   *
   * \details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
   *
   * \return the value of the second data value.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto data_2() const noexcept -> i32
  {
    return m_event.data2;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_WindowEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

/**
 * \class event
 *
 * \brief Serves as the main interface for dealing with events.
 *
 * \see `SDL_Event`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class event final
{
 public:
  /**
   * \brief Creates an empty event.
   *
   * \since 4.0.0
   */
  event() noexcept = default;

  /**
   * \brief Creates an event based on the supplied event.
   *
   * \param event the event that will be copied.
   *
   * \since 4.0.0
   */
  explicit event(const SDL_Event& event) noexcept : m_event{event}
  {
    update_data(static_cast<event_type>(event.type));
  }

  template <typename T>
  explicit event(const common_event<T>& event) noexcept
      : m_event{as_sdl_event(event)}
  {
    update_data(event.type());
  }

  /**
   * \brief Refresh the event loop, gathering events from the input devices.
   *
   * \note You might not have to call this method by yourself.
   *
   * \see `SDL_PumpEvents`
   *
   * \since 3.1.0
   */
  static void refresh() noexcept
  {
    SDL_PumpEvents();
  }

  /**
   * \brief Pushes an event onto the event queue.
   *
   * \param event the event that will be added to the event queue.
   *
   * \since 3.1.0
   */
  static void push(event& event) noexcept
  {
    auto& sdlEvent = event.m_event;
    SDL_PushEvent(&sdlEvent);
  }

  /**
   * \brief Pushes an event onto the event queue.
   *
   * \tparam T the SDL event type.
   *
   * \param event the event that will be pushed onto the event queue.
   *
   * \return `true` if the event was successfully added; `false` otherwise.
   *
   * \since 5.1.0
   */
  template <typename T>
  static auto push(const common_event<T>& event) noexcept -> bool
  {
    auto sdlEvent = as_sdl_event(event);
    const auto result = SDL_PushEvent(&sdlEvent);
    return result >= 0;
  }

  /**
   * \brief Flushes all current events from the event queue.
   *
   * \see `SDL_FlushEvents`
   *
   * \since 3.1.0
   */
  static void flush() noexcept
  {
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
  }

  /**
   * Flushes all of the current events from the event queue, including pending
   * events.
   *
   * \since 3.1.0
   */
  static void flush_all() noexcept
  {
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
  }

  /**
   * \brief Polls the next available event, if there is one.
   *
   * \details This is meant to be called inside a while-loop.
   *
   * \return `true` if there are any pending events; `false` otherwise.
   *
   * \since 3.1.0
   */
  auto poll() noexcept -> bool
  {
    const bool result = SDL_PollEvent(&m_event);

    if (result) {
      update_data(static_cast<event_type>(m_event.type));
    } else {
      update_data(std::nullopt);
    }

    return result;
  }

  /**
   * \brief Returns the type of the event.
   *
   * \return the type of the event; `std::nullopt` if there is no internal
   * event.
   *
   * \since 3.1.0
   */
  [[nodiscard]] auto type() const noexcept -> std::optional<event_type>
  {
    if (is_empty()) {
      return std::nullopt;
    } else {
      return static_cast<event_type>(m_event.type);
    }
  }

  /**
   * \brief Returns the number of events in the event queue.
   *
   * \return the current number of events in the event queue; `std::nullopt`
   * if something goes wrong.
   *
   * \since 5.0.0
   */
  [[nodiscard]] static auto num_queued() noexcept -> std::optional<int>
  {
    const auto num = SDL_PeepEvents(nullptr,
                                    0,
                                    SDL_PEEKEVENT,
                                    SDL_FIRSTEVENT,
                                    SDL_LASTEVENT);
    if (num != -1) {
      return num;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the number of events of a particular type that are in the
   * event queue.
   *
   * \param type the type of event to count.
   *
   * \return the current number of events of the specified type that are in
   * the event queue; `std::nullopt` if something goes wrong.
   *
   * \since 5.0.0
   */
  [[nodiscard]] static auto num_queued(const event_type type) noexcept
      -> std::optional<int>
  {
    const auto id = static_cast<u32>(type);
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, id, id);
    if (num != -1) {
      return num;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether or not the event is of a particular type.
   *
   * \details This method is useful for checking the event type before
   * calling `get<T>`, to avoid exceptions being thrown.
   *
   * \tparam T the event type that will be checked, e.g. `window_event`.
   *
   * \return `true` if the event is of the specified type; `false` otherwise.
   *
   * \see `get`
   * \see `try_get`
   *
   * \since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_data);
  }

  /**
   * \brief Attempts to return the internal event instance.
   *
   * \details If you're certain about the internal type, then you could use this
   * method to simply extract the internal event.
   *
   * \note This functions throws if the internal event isn't of the specified
   * type! You might want to make sure that the internal type is `T` with the
   * `is()` method before calling this method, or use `try_get()`.
   *
   * \tparam T the event type to obtain.
   *
   * \return a reference to the internal event type.
   *
   * \throws bad_variant_access if the internal event type isn't `T`.
   *
   * \see `is`
   * \see `try_get`
   *
   * \since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto get() -> T&
  {
    return std::get<T>(m_data);
  }

  /**
   * \copydoc get()
   */
  template <typename T>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(m_data);
  }

  /**
   * \brief Attempts to return the internal event instance.
   *
   * \details This method returns a null pointer if the internal event
   * doesn't match the specified type.
   *
   * \tparam T the event type to obtain.
   *
   * \return a pointer to the internal event type, might be null.
   *
   * \see `is`
   * \see `get`
   *
   * \since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto try_get() noexcept -> T*
  {
    return std::get_if<T>(&m_data);
  }

  /**
   * \copybrief try_get
   *
   * \details This function returns a null pointer if the internal event
   * doesn't match the specified type.
   *
   * \tparam T the event type to obtain.
   *
   * \return a pointer to the internal event type, might be null.
   *
   * \see `is`
   * \see `get`
   *
   * \since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto try_get() const noexcept -> const T*
  {
    return std::get_if<T>(&m_data);
  }

  /**
   * \brief Indicates whether or not there is an internal event stored in the
   * instance.
   *
   * \return `true` if there is no internal event; `false` otherwise.
   *
   * \deprecated Use `is_empty()` instead.
   *
   * \since 5.0.0
   */
  [[nodiscard, deprecated]] auto empty() const noexcept -> bool
  {
    return is_empty();
  }

  /**
   * \brief Indicates whether or not there is an internal event stored in the
   * instance.
   *
   * \return `true` if there is no internal event; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_empty() const noexcept -> bool
  {
    return is<std::monostate>();
  }

 private:
  SDL_Event m_event{};

  // behold, the beast!
  std::variant<std::monostate,
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
               window_event>
      m_data{};

  void update_data(const std::optional<event_type> t) noexcept
  {
    using et = event_type;

    if (t == et::quit) {
      m_data.emplace<quit_event>(m_event.quit);

    } else if (t == et::audio_device_added || t == et::audio_device_removed) {
      m_data.emplace<audio_device_event>(m_event.adevice);

    } else if (t == et::controller_axis_motion) {
      m_data.emplace<controller_axis_event>(m_event.caxis);

    } else if (t == et::controller_button_down ||
               t == et::controller_button_up) {
      m_data.emplace<controller_button_event>(m_event.cbutton);

    } else if (t == et::controller_device_added ||
               t == et::controller_device_removed ||
               t == et::controller_device_remapped) {
      m_data.emplace<controller_device_event>(m_event.cdevice);

    } else if (t == et::dollar_gesture || t == et::dollar_record) {
      m_data.emplace<dollar_gesture_event>(m_event.dgesture);

    } else if (t == et::drop_begin || t == et::drop_complete ||
               t == et::drop_file || t == et::drop_text) {
      m_data.emplace<drop_event>(m_event.drop);

    } else if (t == et::joystick_axis_motion) {
      m_data.emplace<joy_axis_event>(m_event.jaxis);

    } else if (t == et::joystick_ball_motion) {
      m_data.emplace<joy_ball_event>(m_event.jball);

    } else if (t == et::joystick_button_up || t == et::joystick_button_down) {
      m_data.emplace<joy_button_event>(m_event.jbutton);

    } else if (t == et::joystick_device_added ||
               t == et::joystick_device_removed) {
      m_data.emplace<joy_device_event>(m_event.jdevice);

    } else if (t == event_type::joystick_hat_motion) {
      m_data.emplace<joy_hat_event>(m_event.jhat);

    } else if (t == et::key_down || t == et::key_up) {
      m_data.emplace<keyboard_event>(m_event.key);

    } else if (t == et::mouse_button_up || t == et::mouse_button_down) {
      m_data.emplace<mouse_button_event>(m_event.button);

    } else if (t == et::mouse_motion) {
      m_data.emplace<mouse_motion_event>(m_event.motion);

    } else if (t == et::mouse_wheel) {
      m_data.emplace<mouse_wheel_event>(m_event.wheel);

    } else if (t == et::multi_gesture) {
      m_data.emplace<multi_gesture_event>(m_event.mgesture);

    } else if (t == et::text_editing) {
      m_data.emplace<text_editing_event>(m_event.edit);

    } else if (t == et::text_input) {
      m_data.emplace<text_input_event>(m_event.text);

    } else if (t == et::touch_motion || t == et::touch_down ||
               t == et::touch_up) {
      m_data.emplace<touch_finger_event>(m_event.tfinger);

    } else if (t == et::window) {
      m_data.emplace<window_event>(m_event.window);

    } else {
      m_data.emplace<std::monostate>();
    }
  }
};

/**
 * \brief Indicates whether or not two mouse wheel direction values are equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values are equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(
    const mouse_wheel_direction lhs,
    const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return lhs == static_cast<mouse_wheel_direction>(rhs);
}

/**
 * \copydoc operator==(mouse_wheel_direction, SDL_MouseWheelDirection)
 *
 */
[[nodiscard]] constexpr auto operator==(
    const SDL_MouseWheelDirection lhs,
    const mouse_wheel_direction rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two mouse wheel direction values aren't
 * equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values aren't equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(
    const mouse_wheel_direction lhs,
    const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(mouse_wheel_direction, SDL_MouseWheelDirection)
 */
[[nodiscard]] constexpr auto operator!=(
    const SDL_MouseWheelDirection lhs,
    const mouse_wheel_direction rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two window event ID values are the same.
 *
 * \param lhs the left-hand side window event ID value.
 * \param rhs the right-hand side window event ID value.
 *
 * \return `true` if the window event ID values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const window_event_id lhs,
                                        const SDL_WindowEventID rhs) noexcept
    -> bool
{
  return static_cast<SDL_WindowEventID>(lhs) == rhs;
}

/**
 * \copydoc operator==(window_event_id, SDL_WindowEventID)
 */
[[nodiscard]] constexpr auto operator==(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two window event ID values aren't the same.
 *
 * \param lhs the left-hand side window event ID value.
 * \param rhs the right-hand side window event ID value.
 *
 * \return `true` if the window event ID values aren't the same; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const window_event_id lhs,
                                        const SDL_WindowEventID rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(window_event_id, SDL_WindowEventID)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_EVENT_HEADER