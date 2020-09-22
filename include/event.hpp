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

/**
 * @file event.hpp
 *
 * @brief Provides the event API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

/**
 * @defgroup event Events
 *
 * @brief Contains entities related to events.
 */

#ifndef CENTURION_EVENT_HEADER
#define CENTURION_EVENT_HEADER

#include <SDL_events.h>

#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

#include "centurion_api.hpp"
#include "controller.hpp"
#include "detail/utils.hpp"
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

/**
 * @class common_event
 *
 * @ingroup event
 *
 * @brief The templated base class of all Centurion events.
 *
 * @details This class defines the common API of all events and provides the
 * storage of the SDL2 event.
 *
 * @tparam T an SDL event type.
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
template <typename T>
class common_event
{
 public:
  /**
   * @brief Creates a `CommonEvent` and default-initializes the internal event.
   *
   * @since 4.0.0
   */
  common_event() noexcept = default;

  /**
   * @brief Creates a CommonEvent and copies the supplied event.
   *
   * @param event the event that will be copied.
   *
   * @since 4.0.0
   */
  explicit common_event(const T& event) : m_event{event} {}

  /**
   * @brief Creates a CommonEvent and moves the contents of the supplied event.
   *
   * @param event the event that will be moved.
   *
   * @since 4.0.0
   */
  explicit common_event(T&& event) : m_event{std::move(event)} {}

  /**
   * @brief Default virtual destructor.
   *
   * @since 4.0.0
   */
  ~common_event() noexcept = default;

  /**
   * @brief Sets the timestamp that is associated with the creation of the
   * event.
   *
   * @param timestamp the timestamp that should be associated with the creation
   * of the event.
   *
   * @since 4.0.0
   */
  void set_time(u32 timestamp) noexcept { m_event.timestamp = timestamp; }

  /**
   * @brief Sets the event type value associated with the event.
   *
   * @param type the event type value associated with the event.
   *
   * @since 4.0.0
   */
  void set_type(event_type type) noexcept
  {
    m_event.type = static_cast<u32>(type);
  }

  /**
   * @brief Returns the timestamp associated with the creation of the event.
   *
   * @return the timestamp associated with the creation of the event.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto time() const noexcept -> u32 { return m_event.timestamp; }

  /**
   * @brief Returns the event type value associated with the event.
   *
   * @return the event type value associated with the event.
   *
   * @see EventType
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto type() const noexcept -> event_type
  {
    return static_cast<event_type>(m_event.type);
  }

  /**
   * @brief Returns the internal event.
   *
   * @return the internal event.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> const T& { return m_event; }

 protected:
  T m_event{};
};

/**
 * @brief Indicates whether or not a Centurion event type fulfills the event
 * type specification.
 *
 * @ingroup event
 *
 * @tparam T the Centurion event type that will be checked.
 * @tparam E the SDL event type that the Centurion event is mirroring.
 *
 * @return `true` if the supplied event type passed the requirements; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
template <typename T, typename E>
[[nodiscard]] inline constexpr auto validate_event() noexcept -> bool
{
  return !std::has_virtual_destructor_v<T> &&
         std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> &&
         std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> &&
         std::is_nothrow_constructible_v<T, E> && std::is_final_v<T>;
}

/**
 * @class audio_device_event
 *
 * @ingroup event
 *
 * @brief Represents an event that is associated with some sort of audio
 * device, either capture of output.
 *
 * @see `SDL_AudioDeviceEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class audio_device_event final : public common_event<SDL_AudioDeviceEvent>
{
 public:
  /**
   * @brief Creates a default-initialized audio device event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  audio_device_event() noexcept;

  /**
   * @brief Creates a audio device event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  audio_device_event(const SDL_AudioDeviceEvent& event) noexcept;

  /**
   * @brief Sets the audio device ID that is associated with the event.
   *
   * @param which the audio device ID that is associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(u32 which) noexcept;

  /**
   * @brief Sets whether or not the audio device event is associated with a
   * capture device.
   *
   * @param capture `true` if the event is associated with a capture device;
   * `false` indicates that the event is associated with an output device.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_capture(bool capture) noexcept;

  /**
   * @brief Returns the audio device ID associated with the event.
   *
   * @return the audio device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> u32;

  /**
   * @brief Indicates whether or not the audio device event is associated with
   * an audio output device.
   *
   * @return `true` if the event is associated with an output device; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto output() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the audio device event is associated with
   * an audio capture device.
   *
   * @return `true` if the event is associated with a capture device; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto capture() const noexcept -> bool;
};

static_assert(validate_event<audio_device_event, SDL_AudioDeviceEvent>());

/**
 * @class controller_axis_event
 *
 * @ingroup event
 *
 * @brief Represents an event triggered by game controller axis motion.
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class controller_axis_event final : public common_event<SDL_ControllerAxisEvent>
{
 public:
  /**
   * @brief Creates a default-initialized controller axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_axis_event() noexcept;

  /**
   * @brief Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_axis_event(const SDL_ControllerAxisEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the instance ID of the joystick that the event is
   * associated with.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(SDL_JoystickID which) noexcept;

  /**
   * @brief Sets the game controller axis value associated with the event.
   *
   * @param axis the game controller axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_axis(controller_axis axis) noexcept;

  /**
   * @brief Sets the axis value associated with the event.
   *
   * @param value the new axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_value(i16 value) noexcept;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> SDL_JoystickID;

  /**
   * @brief Returns the game controller axis value associated with the event.
   *
   * @return the game controller axis value associated with the event.
   *
   * @see `GameControllerAxis`
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto axis() const noexcept -> controller_axis;

  /**
   * @brief Returns the axis value associated with the event.
   *
   * @return the axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto value() const noexcept -> i16;
};

static_assert(validate_event<controller_axis_event, SDL_ControllerAxisEvent>());

/**
 * @class controller_button_event
 *
 * @ingroup event
 *
 * @brief Represents events associated with the state of buttons of a game
 * controller.
 *
 * @see `SDL_ControllerButtonEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class controller_button_event final
    : public common_event<SDL_ControllerButtonEvent>
{
 public:
  /**
   * @brief Creates a default-initialized controller button event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_button_event() noexcept;

  /**
   * @brief Creates a controller button event that is based on the supplied SDL
   * controller button event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_button_event(const SDL_ControllerButtonEvent& event) noexcept;

  /**
   * @brief Sets the game controller button associated with the event.
   *
   * @param button the game controller button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(controller_button button) noexcept;

  /**
   * @brief Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(button_state state) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param id the instance ID of the joystick that the event is associated
   * with.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(SDL_JoystickID id) noexcept;

  /**
   * @brief Returns the game controller button associated with the event.
   *
   * @return the game controller button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto button() const noexcept -> controller_button;

  /**
   * @brief Returns the button state associated with the event.
   *
   * @return the button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> button_state;

  /**
   * @brief Indicates whether or not the associated button is pressed.
   *
   * @return `true` if the associated button is pressed; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto pressed() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the associated button is released.
   *
   * @return `true` if the associated button is released; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto released() const noexcept -> bool;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> SDL_JoystickID;
};

static_assert(
    validate_event<controller_button_event, SDL_ControllerButtonEvent>());

/**
 * @class controller_device_event
 *
 * @ingroup event
 *
 * @brief Represents events related to game controller devices such as adding
 * or removing game controller devices.
 *
 * @see `SDL_ControllerDeviceEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class controller_device_event final
    : public common_event<SDL_ControllerDeviceEvent>
{
 public:
  /**
   * @brief Creates a default-initialized controller device event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_device_event() noexcept;

  /**
   * @brief Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  controller_device_event(const SDL_ControllerDeviceEvent& event) noexcept;

  /**
   * @brief Sets the joystick device index or instance ID.
   *
   * @details If the event type is `Added`, then this value is the joystick
   * device index. If the type of the event is either `Removed` or
   * `Remapped`, then this value is the instance ID.
   *
   * @param which the joystick device index or instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(i32 which) noexcept;

  /**
   * @brief Returns the joystick device index or instance ID.
   *
   * @details Returns the joystick device index if the type of the event is
   * `Added`. Returns the instance ID if the type of the event is either
   * `Removed` or `Remapped`.
   *
   * @return the joystick device index or instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> i32;
};

static_assert(
    validate_event<controller_device_event, SDL_ControllerDeviceEvent>());

/**
 * @class dollar_gesture_event
 *
 * @ingroup event
 *
 * @brief Provides information about dollar gestures from touch events.
 *
 * @see `SDL_DollarGestureEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class dollar_gesture_event final : public common_event<SDL_DollarGestureEvent>
{
 public:
  /**
   * @brief Creates a default-initialized dollar gesture event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  dollar_gesture_event() noexcept;

  /**
   * @brief Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept;

  /**
   * @brief Sets the touch device ID associated with the event.
   *
   * @param id the touch device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_touch_id(SDL_TouchID id) noexcept;

  /**
   * @brief Sets the gesture ID associated with the event.
   *
   * @param id the gesture ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_gesture_id(SDL_GestureID id) noexcept;

  /**
   * @brief Sets the amount of fingers used to draw the stroke.
   *
   * @param fingers the amount of fingers used to draw the stroke.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_fingers(u32 fingers) noexcept;

  /**
   * @brief Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_error(float error) noexcept;

  /**
   * @brief Sets the normalized x-coordinate of the center of the gesture.
   *
   * @param x the normalized x-coordinate of the center of the gesture.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(float x) noexcept;

  /**
   * @brief Sets the normalized y-coordinate of the center of the gesture.
   *
   * @param y the normalized y-coordinate of the center of the gesture.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(float y) noexcept;

  /**
   * @brief Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto touch_id() const noexcept -> SDL_TouchID;

  /**
   * @brief Returns the unique ID of the closest gesture to the performed
   * stroke.
   *
   * @return the unique ID of the closest gesture to the performed stroke.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto gesture_id() const noexcept -> SDL_GestureID;

  /**
   * @brief Returns the amount of fingers used to draw the stroke.
   *
   * @return the amount of fingers used to draw the stroke.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto fingers() const noexcept -> u32;

  /**
   * @brief Returns the difference between the gesture template and the
   * performed gesture.
   *
   * @details The lower the error, the better the match.
   *
   * @return the difference between the gesture template and the performed
   * gesture.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto error() const noexcept -> float;

  /**
   * @brief Returns the x-coordinate of the normalized center of the gesture.
   *
   * @return the x-coordinate of the normalized center of the gesture.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto x() const noexcept -> float;

  /**
   * @brief Returns the y-coordinate of the normalized center of the gesture.
   *
   * @return the y-coordinate of the normalized center of the gesture.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto y() const noexcept -> float;
};

static_assert(validate_event<dollar_gesture_event, SDL_DollarGestureEvent>());

/**
 * @class drop_event
 *
 * @ingroup event
 *
 * @brief Represents the event of requesting a file to be opened.
 *
 * @see `SDL_DropEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class drop_event final : public common_event<SDL_DropEvent>
{
 public:
  /**
   * @brief Creates a default-initialized drop event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  drop_event() noexcept;

  /**
   * @brief Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  drop_event(const SDL_DropEvent& event) noexcept;

  /**
   * @brief Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  drop_event(SDL_DropEvent&& event) noexcept;

  /**
   * @brief Destroys the drop event.
   *
   * @details The associated file will be freed depending on the value
   * returned from the `will_free_file()` method.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ~drop_event() noexcept;

  /**
   * @brief Sets whether or not the associated file will be freed by this event.
   *
   * @details If you set this property to `false`, you **must** remember to
   * call `SDL_free` on the file pointer by yourself. Otherwise, you'll end
   * up with a memory leak!
   *
   * @param freeFile `true` if the associated file should be freed upon the
   * destruction of the event; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_will_free_file(bool freeFile) noexcept;

  /**
   * @brief Sets the file associated with the drop event.
   *
   * @details The ownership of the supplied pointer will, by default, not be
   * claimed by this event.
   *
   * @note The supplied pointer will be freed using `SDL_free` upon the
   * destruction of the event *if* the `will_free_file` property is set to
   * **true**.
   *
   * @note If the `will_free_file` property is `true`, then **the previously
   * set file pointer will be freed** by calling this method. However, if the
   * `will_free_file` property is `false`, then the old file pointer is
   * simply overridden. Of course, this may, if you're not careful, introduce a
   * memory leak in your program!
   *
   * @warning Make sure you know what you are doing when using this method.
   *
   * @param file a pointer to a file, can safely be null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_file(char* file) noexcept;

  /**
   * @brief Sets the ID of the window that is the target of the drop event.
   *
   * @param id the ID of the window that is the target of the drop event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Indicates whether or not the associated file will be freed by
   * this event upon destruction.
   *
   * @details By default, this property is set to **false**.
   *
   * @return `true` if the associated file will be freed upon destruction;
   * `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto will_free_file() const noexcept -> bool;

  /**
   * @brief Returns a pointer to the associated file.
   *
   * @warning Do **not** claim ownership of the returned pointer *without*
   * setting the `will_free_file` property to **false**.
   *
   * @note The returned pointer is always `nullptr` for `DropBegin` and
   * `DropComplete` drop events.
   *
   * @return a pointer to the file associated with the event, might be null.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto file() const noexcept -> char*;

  /**
   * @brief Returns the ID of the window that is the target of the drop
   * event, if there even is one.
   *
   * @return the ID of the window that is the target of the drop event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

 private:
  bool m_willFreeFile{false};
};

static_assert(validate_event<drop_event, SDL_DropEvent>());

/**
 * @class joy_axis_event
 *
 * @ingroup event
 *
 * @brief Represents an event that occurs whenever a user moves an axis on a
 * joystick.
 *
 * @see `SDL_JoyAxisEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class joy_axis_event final : public common_event<SDL_JoyAxisEvent>
{
 public:
  /**
   * @brief Creates a default-initialized joy axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_axis_event() noexcept;

  /**
   * @brief Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * @param event the SDL joy axis event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_axis_event(const SDL_JoyAxisEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(SDL_JoystickID which) noexcept;

  /**
   * @brief Sets the joystick axis index associated with the event.
   *
   * @param axis the joystick axis index associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_axis(u8 axis) noexcept;

  /**
   * @brief Sets the joystick axis value associated with the event.
   *
   * @param value the joystick axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_value(i16 value) noexcept;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> SDL_JoystickID;

  /**
   * @brief Returns the joystick axis index associated with the event.
   *
   * @return the joystick axis index associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto axis() const noexcept -> u8;

  /**
   * @brief Returns the joystick axis value associated with the event.
   *
   * @return the joystick axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto value() const noexcept -> i16;
};

static_assert(validate_event<joy_axis_event, SDL_JoyAxisEvent>());

/**
 * @class joy_ball_event
 *
 * @ingroup event
 *
 * @brief Represents the event that is triggered when a user moves a
 * trackball on a joystick.
 *
 * @see `SDL_JoyBallEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class joy_ball_event final : public common_event<SDL_JoyBallEvent>
{
 public:
  /**
   * @brief Creates a default-initialized joy ball event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_ball_event() noexcept;

  /**
   * @brief Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * @param event the SDL joy ball event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_ball_event(const SDL_JoyBallEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(SDL_JoystickID which) noexcept;

  /**
   * @brief Sets the joystick trackball index associated with the event.
   *
   * @param ball the joystick trackball index.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_ball(u8 ball) noexcept;

  /**
   * @brief Sets the relative motion along the x-axis associated with the event.
   *
   * @param dx the relative motion along the x-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(i16 dx) noexcept;

  /**
   * @brief Sets the relative motion along the y-axis associated with the event.
   *
   * @param dy the relative motion along the y-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(i16 dy) noexcept;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> SDL_JoystickID;

  /**
   * @brief Returns the joystick trackball index associated with the event.
   *
   * @return the joystick trackball index associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto ball() const noexcept -> u8;

  /**
   * @brief Returns the relative motion along the x-axis.
   *
   * @note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the x-axis since it was last updated.
   *
   * @return the relative motion along the x-axis.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dx() const noexcept -> i16;

  /**
   * @brief Returns the relative motion along the y-axis.
   *
   * @note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the y-axis since it was last updated.
   *
   * @return the relative motion along the y-axis.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dy() const noexcept -> i16;
};

static_assert(validate_event<joy_ball_event, SDL_JoyBallEvent>());

/**
 * @class joy_button_event
 *
 * @ingroup event
 *
 * @brief Represents an event associated with the press or release of a
 * joystick button.
 *
 * @see `SDL_JoyButtonEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class joy_button_event final : public common_event<SDL_JoyButtonEvent>
{
 public:
  /**
   * @brief Creates a default-initialized JoyButtonEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_button_event() noexcept;

  /**
   * @brief Creates a JoyButtonEvent based on the supplied event.
   *
   * @param event the event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_button_event(const SDL_JoyButtonEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(SDL_JoystickID which) noexcept;

  /**
   * @brief Sets the button index associated with the event.
   *
   * @param button the button index associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(u8 button) noexcept;

  /**
   * @brief Sets the button state that is associated with the button that
   * triggered the event.
   *
   * @param state the button state that is associated with the button that
   * triggered the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(button_state state) noexcept;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> SDL_JoystickID;

  /**
   * @brief Returns the index of the button that changed.
   *
   * @return the index of the button that changed.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto button() const noexcept -> u8;

  /**
   * @brief Returns the state of the button associated with the event.
   *
   * @return the state of the button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> button_state;

  /**
   * @brief Indicates whether or not the associated button is pressed.
   *
   * @return `true` if the associated button is pressed; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto pressed() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the associated button is released.
   *
   * @return `true` if the associated button is released; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto released() const noexcept -> bool;
};

static_assert(validate_event<joy_button_event, SDL_JoyButtonEvent>());

/**
 * @class joy_device_event
 *
 * @ingroup event
 *
 * @brief Represents an event triggered by adding or removing a joystick device.
 *
 * @see `SDL_JoyDeviceEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class joy_device_event final : public common_event<SDL_JoyDeviceEvent>
{
 public:
  /**
   * @brief Creates a default-initialized JoyDeviceEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_device_event() noexcept;

  /**
   * @brief Creates a JoyDeviceEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_device_event(const SDL_JoyDeviceEvent& event) noexcept;

  /**
   * @brief Sets the joystick device index or instance ID, depending on the type
   * of the event.
   *
   * @param which the joystick device index or instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(i32 which) noexcept;

  /**
   * @brief Returns the joystick device index or instance ID.
   *
   * @details The returned value is the joystick device index if the type is
   * `JoystickDeviceAdded`, or the joystick instance ID if the type is
   * `JoystickDeviceRemoved`.
   *
   * @return the joystick device index or instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> i32;
};

static_assert(validate_event<joy_device_event, SDL_JoyDeviceEvent>());

/**
 * @enum joy_hat_position
 *
 * @ingroup event
 *
 * @brief Serves as a wrapper for the `SDL_HAT_x` macro values.
 *
 * @since 4.0.0
 */
enum class joy_hat_position {
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
 * @class joy_hat_event
 *
 * @ingroup event
 *
 * @brief Represents an event that is triggered whenever a user moves a hat
 * on a joystick.
 *
 * @see `SDL_JoyHatEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class joy_hat_event final : public common_event<SDL_JoyHatEvent>
{
 public:
  /**
   * @brief Creates a default-initialized joy hat event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_hat_event() noexcept;

  /**
   * @brief Creates a joy hat event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  joy_hat_event(const SDL_JoyHatEvent& event) noexcept;

  /**
   * @brief Sets the hat index associated with the event.
   *
   * @param hat the hat index.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_hat(u8 hat) noexcept;

  /**
   * @brief Sets the joystick hat position associated with the event.
   *
   * @param value the joystick hat position associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_position(joy_hat_position value) noexcept;

  /**
   * @brief Returns the index of the hat that changed.
   *
   * @return the index of the hat that changed.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto hat() const noexcept -> u8;

  /**
   * @brief Returns the position of the associated joystick hat.
   *
   * @return the position of the associated joystick hat.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto position() const noexcept -> joy_hat_position;
};

static_assert(validate_event<joy_hat_event, SDL_JoyHatEvent>());

/**
 * @class keyboard_event
 *
 * @ingroup event
 *
 * @brief Represents an event associated with some sort of key action, such
 * as the release or pressing of a key.
 *
 * @see `SDL_KeyboardEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class keyboard_event final : public common_event<SDL_KeyboardEvent>
{
 public:
  /**
   * @brief Creates a default-initialized keyboard event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  keyboard_event() noexcept;

  /**
   * @brief Creates a keyboard event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  keyboard_event(const SDL_KeyboardEvent& event) noexcept;

  /**
   * @brief Sets the scan code that is associated with the event.
   *
   * @param code the scan code that will be associated with the event.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void set_scan_code(const scan_code& code) noexcept;

  /**
   * @brief Sets the key code that is associated with the event.
   *
   * @param code the key code that will be associated with the event.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void set_key_code(const key_code& code) noexcept;

  /**
   * @brief Sets the button state associated with the event.
   *
   * @param state the button state that will be associated with the event
   *
   * @since 5.0.0
   */
  CENTURION_API
  void set_button_state(button_state state) noexcept;

  /**
   * @brief Sets the status of a key modifier.
   *
   * @param modifier the key modifier that will be affected.
   * @param active `true` if the key modifier is active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_modifier(key_modifier modifier, bool active) noexcept;

  /**
   * @brief Sets the flag that indicates whether or not the key associated with
   * this key event was repeatedly triggered.
   *
   * @param repeated `true` if the key was repeatedly triggered; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_repeated(bool repeated) noexcept;

  /**
   * @brief Sets the window ID that is associated with this key event.
   *
   * @param id the window ID that should be associated with the key event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Indicates whether or not the event is associated with the
   * specified scan code.
   *
   * @param code the scan code that will be checked.
   *
   * @return `true` if the supplied scan code is associated with the event;
   * `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto is_active(const scan_code& code) const noexcept -> bool;

  /**
   * @brief Indicates whether or not the event is associated with the
   * specified key code.
   *
   * @param code the key code that will be checked.
   *
   * @return `true` if the supplied key code is associated with the event;
   * `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto is_active(const key_code& code) const noexcept -> bool;

  /**
   * @brief Indicates whether or not the specified key modifier is active.
   *
   * @note Multiple key modifiers can be active at the same time.
   *
   * @param modifier the key modifier that will be checked.
   *
   * @return `true` if the specified key modifier is active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto modifier_active(key_modifier modifier) const noexcept -> bool;

  /**
   * @brief Indicates whether or not any of the SHIFT modifiers are active.
   *
   * @return `true` if any of the SHIFT modifiers are active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto shift_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not any of the CTRL modifiers are active.
   *
   * @return `true` if any of the CTRL modifiers are active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto ctrl_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not any of the ALT modifiers are active.
   *
   * @return `true` if any of the ALT modifiers are active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto alt_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not any of the GUI modifiers are active.
   *
   * @return `true` if any of the GUI modifiers are active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto gui_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the CAPS modifier is active.
   *
   * @return `true` if the CAPS modifier is active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto caps_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the NUM modifier is active.
   *
   * @return `true` if the NUM modifier is active; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto num_active() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the key associated with this key event has
   * been repeatedly triggered.
   *
   * @return `true` if the key associated with the event was repeated; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto repeated() const noexcept -> bool;

  /**
   * @brief Returns the button state of the key associated with the event.
   *
   * @return the button state of the key associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> button_state;

  /**
   * @brief Indicates whether or not the event is associated with the release
   * of a key.
   *
   * @note This function is equivalent to `state() ==  button_state::released`.
   *
   * @return `true` if the event is a key released event; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto released() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the event is associated with the press
   * of a key.
   *
   * @note This function is equivalent to `state() ==  button_state::pressed`.
   *
   * @return `true` if the event is a key pressed event; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto pressed() const noexcept -> bool;

  /**
   * @brief Returns the scan code that is associated with the event.
   *
   * @return the scan code that is associated with the event.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto get_scan_code() const noexcept -> scan_code;

  /**
   * @brief Returns the key code that is associated with the event.
   *
   * @return the key code that is associated with the event.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto get_key_code() const noexcept -> key_code;

  /**
   * @brief Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;
};

static_assert(validate_event<keyboard_event, SDL_KeyboardEvent>());

/**
 * @class mouse_button_event
 *
 * @ingroup event
 *
 * @brief Represents an event triggered by mouse button presses or releases.
 *
 * @see `SDL_MouseButtonEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class mouse_button_event final : public common_event<SDL_MouseButtonEvent>
{
 public:
  /**
   * @brief Creates a default-initialized `MouseButtonEvent`.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_button_event() noexcept;

  /**
   * @brief Creates a MouseButtonEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_button_event(const SDL_MouseButtonEvent& event) noexcept;

  /**
   * @brief Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Sets the mouse instance ID.
   *
   * @param which the mouse instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(u32 which) noexcept;

  /**
   * @brief Sets the mouse button associated with the event.
   *
   * @param button the mouse button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(mouse_button button) noexcept;

  /**
   * @brief Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(button_state state) noexcept;

  /**
   * @brief Sets the amount of clicks associated with the event.
   *
   * @param clicks the amount of clicks associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_clicks(u8 clicks) noexcept;

  /**
   * @brief Sets the x-coordinate of the mouse relative to the window.
   *
   * @param x the x-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(i32 x) noexcept;

  /**
   * @brief Sets the y-coordinate of the mouse relative to the window.
   *
   * @param y the y-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(i32 y) noexcept;

  /**
   * @brief Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * @brief Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> u32;

  /**
   * @brief Returns the mouse button associated with the event.
   *
   * @return the mouse button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto button() const noexcept -> mouse_button;

  /**
   * @brief Returns the state of the mouse button associated with the event.
   *
   * @return the state of the mouse button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> button_state;

  /**
   * @brief Indicates whether or not the associated button is pressed.
   *
   * @return `true` if the associated button is pressed; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto pressed() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the associated button is released.
   *
   * @return `true` if the associated button is released; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto released() const noexcept -> bool;

  /**
   * @brief Returns the number of mouse clicks associated with the event.
   *
   * @return the number of mouse clicks associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto clicks() const noexcept -> u8;

  /**
   * @brief Returns the x-coordinate of the mouse relative to the window.
   *
   * @return the x-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto x() const noexcept -> i32;

  /**
   * @brief Returns the y-coordinate of the mouse relative to the window.
   *
   * @return the y-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto y() const noexcept -> i32;
};

static_assert(validate_event<mouse_button_event, SDL_MouseButtonEvent>());

/**
 * @class mouse_motion_event
 *
 * @ingroup event
 *
 * @brief Represents events that are triggered by the movement of the mouse.
 *
 * @see `SDL_MouseMotionEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class mouse_motion_event final : public common_event<SDL_MouseMotionEvent>
{
 public:
  /**
   * @brief Creates a default-initialized MouseMotionEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_motion_event() noexcept;

  /**
   * @brief Creates a `MouseMotionEvent` that is based on the supplied SDL
   * event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_motion_event(const SDL_MouseMotionEvent& event) noexcept;

  /**
   * @brief Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Sets the mouse instance ID.
   *
   * @param which the mouse instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(u32 which) noexcept;

  /**
   * @brief Sets the mouse button state associated with the event.
   *
   * @details The state could be any of `SDL_BUTTON_LMASK`, `SDL_BUTTON_MMASK`,
   * `SDL_BUTTON_RMASK`, `SDL_BUTTON_X1MASK` and `SDL_BUTTON_X2MASK` OR'd
   * together.
   *
   * @param state the mouse button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(u32 state) noexcept;

  /**
   * @brief Sets the x-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * @param x the x-coordinate of the mouse.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(i32 x) noexcept;

  /**
   * @brief Sets the y-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * @param y the y-coordinate of the mouse.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(i32 y) noexcept;

  /**
   * @brief Sets the value of the relative motion of the mouse along the x-axis.
   *
   * @param dx the value of the relative motion of the mouse along the x-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(i32 dx) noexcept;

  /**
   * @brief Sets the value of the relative motion of the mouse along the y-axis.
   *
   * @param dy the value of the relative motion of the mouse along the y-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(i32 dy) noexcept;

  /**
   * @brief Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * @brief Returns the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * @details The returned value might be `SDL_TOUCH_MOUSEID` for events that
   * were generated by a touch input device.
   *
   * @return the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> u32;

  /**
   * @brief Returns a bitmask for the current mouse button state.
   *
   * @remark If you want to check if a specific mouse button is pressed or
   * released, a better alternative would be to use the `pressed(MouseButton)
   * ` method.
   *
   * @return a bitmask for the current mouse button state.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> u32;

  /**
   * @brief Indicates whether or not a mouse button is pressed.
   *
   * @param button the mouse button that will be checked.
   *
   * @return `true` if the specified mouse button is pressed; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto pressed(mouse_button button) const noexcept -> bool;

  /**
   * @brief Returns the x-coordinate of the mouse relative to the window.
   *
   * @return the x-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto x() const noexcept -> i32;

  /**
   * @brief Returns the y-coordinate of the mouse relative to the window.
   *
   * @return the y-coordinate of the mouse relative to the window.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto y() const noexcept -> i32;

  /**
   * @brief Returns the relative motion of the mouse along the x-axis.
   *
   * @return the relative motion of the mouse along the x-axis.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dx() const noexcept -> i32;

  /**
   * @brief Returns the relative motion of the mouse along the y-axis.
   *
   * @return the relative motion of the mouse along the y-axis.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dy() const noexcept -> i32;
};

static_assert(validate_event<mouse_motion_event, SDL_MouseMotionEvent>());

/**
 * @enum mouse_wheel_direction
 *
 * @ingroup event
 *
 * @brief Mirrors the the `SDL_MouseWheelDirection` enum.
 *
 * @see `SDL_MouseWheelDirection`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
enum class mouse_wheel_direction {
  normal = SDL_MOUSEWHEEL_NORMAL,  /**< The scroll direction is normal */
  flipped = SDL_MOUSEWHEEL_FLIPPED /**< The scroll direction is flipped /
                                    * natural */
};

/**
 * @brief Indicates whether or not two mouse wheel direction values are equal.
 *
 * @ingroup event
 *
 * @param lhs the left-hand side mouse wheel direction value.
 * @param rhs the right-hand side mouse wheel direction value.
 *
 * @return `true` if the two values are equal; `false` otherwise.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto operator==(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool;

/**
 * @copydoc operator==(mouse_wheel_direction, SDL_MouseWheelDirection)
 *
 * @ingroup event
 */
CENTURION_QUERY
auto operator==(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool;

/**
 * @brief Indicates whether or not two mouse wheel direction values aren't
 * equal.
 *
 * @ingroup event
 *
 * @param lhs the left-hand side mouse wheel direction value.
 * @param rhs the right-hand side mouse wheel direction value.
 *
 * @return `true` if the two values aren't equal; `false` otherwise.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto operator!=(mouse_wheel_direction lhs, SDL_MouseWheelDirection rhs) noexcept
    -> bool;

/**
 * @copydoc operator!=(mouse_wheel_direction, SDL_MouseWheelDirection)
 *
 * @ingroup event
 */
CENTURION_QUERY
auto operator!=(SDL_MouseWheelDirection lhs, mouse_wheel_direction rhs) noexcept
    -> bool;

/**
 * @class mouse_wheel_event
 *
 * @ingroup event
 *
 * @brief Represents events triggered when a user moves the mouse wheel.
 *
 * @see `SDL_MouseWheelEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class mouse_wheel_event final : public common_event<SDL_MouseWheelEvent>
{
 public:
  /**
   * @brief Creates a default-initialized MouseWheelEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_wheel_event() noexcept;

  /**
   * @brief Creates a `MouseMotionEvent` that is based on the supplied SDL
   * event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept;

  /**
   * @brief Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Sets the mouse instance ID.
   *
   * @param which the mouse instance ID.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(u32 which) noexcept;

  /**
   * @brief Sets the horizontally scrolled distance.
   *
   * @details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * @param xScroll the horizontally scrolled distance.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_x_scroll(i32 xScroll) noexcept;

  /**
   * @brief Sets the vertically scrolled distance.
   *
   * @details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * @param yScroll the vertically scrolled distance.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_y_scroll(i32 yScroll) noexcept;

  /**
   * @brief Sets the mouse wheel direction mode associated with the event.
   *
   * @param direction the mouse wheel direction mode associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_direction(mouse_wheel_direction direction) noexcept;

  /**
   * @brief Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * @brief Returns the mouse instance ID, or `SDL_TOUCH_MOUSEID` if the event
   * was triggered by a touch input device.
   *
   * @return the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> u32;

  /**
   * @brief Returns the horizontally scrolled distance
   *
   * @details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * @return the horizontally scrolled distance.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto x_scroll() const noexcept -> i32;

  /**
   * @brief Returns the vertically scrolled distance.
   *
   * @details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * @return the vertically scrolled distance.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto y_scroll() const noexcept -> i32;

  /**
   * @brief Returns the mouse wheel direction mode associated with the event.
   *
   * @return the mouse wheel direction mode associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto direction() const noexcept -> mouse_wheel_direction;
};

static_assert(validate_event<mouse_wheel_event, SDL_MouseWheelEvent>());

/**
 * @class multi_gesture_event
 *
 * @ingroup event
 *
 * @brief Provides information about events related to touch events triggered
 * by multiple fingers.
 *
 * @see `SDL_MultiGestureEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class multi_gesture_event final : public common_event<SDL_MultiGestureEvent>
{
 public:
  /**
   * @brief Creates a default-initialized `MultiGestureEvent`.
   *
   * @since 4.0.0
   */
  CENTURION_API
  multi_gesture_event() noexcept;

  /**
   * @brief Creates a `MultiGestureEvent` that is based on the supplied SDL
   * event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  multi_gesture_event(const SDL_MultiGestureEvent& event) noexcept;

  /**
   * @brief Sets the touch device ID associated with the event.
   *
   * @param id the touch device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_touch_id(SDL_TouchID id) noexcept;

  /**
   * @brief Sets the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * @param dTheta the amount that the fingers rotated.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_delta_theta(float dTheta) noexcept;

  /**
   * @brief Sets the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * @param dDistance the amount that the fingers pinched.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_delta_distance(float dDistance) noexcept;

  /**
   * @brief Sets the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * @param centerX the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_center_x(float centerX) noexcept;

  /**
   * @brief Sets the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * @param centerY the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_center_y(float centerY) noexcept;

  /**
   * @brief Sets the number of fingers that was used in the gesture associated
   * with the event.
   *
   * @param nFingers the number of fingers that was used in the gesture.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_fingers(u16 nFingers) noexcept;

  /**
   * @brief Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto touch_id() const noexcept -> SDL_TouchID;

  /**
   * @brief Returns the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers rotated.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto delta_theta() const noexcept -> float;

  /**
   * @brief Returns the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers pinched.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto delta_distance() const noexcept -> float;

  /**
   * @brief Returns the x-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * @return the x-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto center_x() const noexcept -> float;

  /**
   * @brief Returns the y-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * @return the y-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto center_y() const noexcept -> float;

  /**
   * @brief Returns the amount of fingers used in the gesture associated with
   * the event.
   *
   * @return the amount of fingers used in the gesture associated with the
   * event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto fingers() const noexcept -> float;
};

static_assert(validate_event<multi_gesture_event, SDL_MultiGestureEvent>());

/**
 * @class quit_event
 *
 * @ingroup event
 *
 * @brief Represents the event of the user wanting to close the application,
 * usually by pressing the "X"-button on the window frame.
 *
 * @see `SDL_QuitEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class quit_event final : public common_event<SDL_QuitEvent>
{
 public:
  /**
   * @brief Creates a default-initialized quit event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  quit_event() noexcept;

  /**
   * @brief Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  quit_event(const SDL_QuitEvent& event) noexcept;
};

static_assert(validate_event<quit_event, SDL_QuitEvent>());

/**
 * @class text_editing_event
 *
 * @ingroup event
 *
 * @brief Represents an event triggered by keyboard text editing.
 *
 * @note This class doesn't provide a setter for the text, since it's
 * impossible to assign a value to a variable of type `char[32]` in C++.
 *
 * @see `SDL_TextEditingEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class text_editing_event final : public common_event<SDL_TextEditingEvent>
{
 public:
  /**
   * @brief Creates a default-initialized `TextEditingEvent`.
   *
   * @since 4.0.0
   */
  CENTURION_API
  text_editing_event() noexcept;

  /**
   * @brief Creates a `TextEditingEvent` that is based on the supplied SDL
   * event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  text_editing_event(const SDL_TextEditingEvent& event) noexcept;

  /**
   * @brief Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Sets the location to begin editing from.
   *
   * @param start the location to begin editing from.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_start(i32 start) noexcept;

  /**
   * @brief Sets the number of characters to edit from the start point.
   *
   * @details The supplied value will be clamped to the range [0, 32].
   *
   * @param length the number of characters to edit from the start point.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_length(i32 length) noexcept;

  /**
   * @brief Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * @brief Returns the text that will be used, as a null-terminated string in
   * UTF-8 encoding.
   *
   * @return the text that will be used.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto text() const noexcept -> std::string_view;

  /**
   * @brief Returns the location to begin editing from.
   *
   * @return the location to begin editing from.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto start() const noexcept -> i32;

  /**
   * @brief Returns the number of characters to edit from the start point.
   *
   * @details The returned value will always be in the range [0, 32].
   *
   * @return the number of characters to edit from the start point.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto length() const noexcept -> i32;

 private:
  void check_length() noexcept;
};

static_assert(validate_event<text_editing_event, SDL_TextEditingEvent>());

/**
 * @class text_input_event
 *
 * @ingroup event
 *
 * @brief Provides information about keyboard text input events.
 *
 * @see `SDL_TextInputEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class text_input_event final : public common_event<SDL_TextInputEvent>
{
 public:
  /**
   * @brief Creates a default-initialized TextInputEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  text_input_event() noexcept;

  /**
   * @brief Creates a `TextInputEvent` that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  text_input_event(const SDL_TextInputEvent& event) noexcept;

  /**
   * @brief Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * @return the text that will be used.
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto text_utf8() const noexcept -> std::string_view;
};

static_assert(validate_event<text_input_event, SDL_TextInputEvent>());

/**
 * @class touch_finger_event
 *
 * @ingroup event
 *
 * @brief Represents an event related to touch screen actions.
 *
 * @see `SDL_TouchFingerEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class touch_finger_event final : public common_event<SDL_TouchFingerEvent>
{
 public:
  /**
   * @brief Creates a default-initialized touch finger event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  touch_finger_event() noexcept;

  /**
   * @brief Creates a touch finger event that is based on the supplied SDL
   * ouch finger event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  touch_finger_event(const SDL_TouchFingerEvent& event) noexcept;

  /**
   * @brief Sets the ID of the associated touch device.
   *
   * @param id the ID of the associated touch device.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_touch_id(SDL_TouchID id) noexcept;

  /**
   * @brief Sets the finger ID associated with the event.
   *
   * @param id the finger ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_finger_id(SDL_FingerID id) noexcept;

  /**
   * @brief Sets the window ID of the window under the finger.
   *
   * @param id the window ID of the window under the finger.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(u32 id) noexcept;

  /**
   * @brief Sets the normalized x-coordinate of the location of the event.
   *
   * @details The supplied value will be clamped to the range [0, 1].
   *
   * @param x the normalized x-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(float x) noexcept;

  /**
   * @brief Sets the normalized y-coordinate of the location of the event.
   *
   * @details The supplied value will be clamped to the range [0, 1].
   *
   * @param y the normalized y-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(float y) noexcept;

  /**
   * @brief Sets the normalized distance moved along the x-axis.
   *
   * @details The supplied value will be clamped to the range [-1, 1].
   *
   * @param dx the normalized distance moved along the x-axis, clamped to the
   * range [-1, 1].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(float dx) noexcept;

  /**
   * @brief Sets the normalized distance moved along the y-axis.
   *
   * @details The supplied value will be clamped to the range [-1, 1].
   *
   * @param dy the normalized distance moved along the y-axis, clamped to the
   * range [-1, 1].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(float dy) noexcept;

  /**
   * @brief Sets the normalized pressure associated with the event.
   *
   * @details The supplied value will be clamped to the range [0, 1].
   *
   * @param pressure the normalized pressure associated with the event, clamped
   * in the range [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_pressure(float pressure) noexcept;

  /**
   * @brief Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto touch_id() const noexcept -> SDL_TouchID;

  /**
   * @brief Returns the finger ID associated with the event.
   *
   * @return the finger ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto finger_id() const noexcept -> SDL_FingerID;

  /**
   * @brief Returns the window ID of the window under the finger.
   *
   * @return the window ID of the window under the finger.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto window_id() const noexcept -> u32;

  /**
   * @brief Returns the normalized x-coordinate of the location of the event.
   *
   * @details The returned value will be in the range [0, 1].
   *
   * @return the normalized x-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto x() const noexcept -> float;

  /**
   * @brief Returns the normalized y-coordinate of the location of the event.
   *
   * @details The returned value will be in the range [0, 1].
   *
   * @return the normalized y-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto y() const noexcept -> float;

  /**
   * @brief Returns the normalized distance moved along the x-axis.
   *
   * @details The returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the x-axis, in the range
   * [-1, 1].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dx() const noexcept -> float;

  /**
   * @brief Returns the normalized distance moved along the y-axis.
   *
   * @details The returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the y-axis, in the range
   * [-1, 1].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto dy() const noexcept -> float;

  /**
   * @brief Returns the normalized pressure associated with the event.
   *
   * @details The returned value will be in the range [0, 1].
   *
   * @return the normalized pressure associated with the event, in the range
   * [0, 1].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto pressure() const noexcept -> float;
};

static_assert(validate_event<touch_finger_event, SDL_TouchFingerEvent>());

/**
 * @enum window_event_id
 *
 * @ingroup event
 *
 * @brief Mirrors the `SDL_WindowEventID` enum.
 *
 * @details Depending on the event ID of a `WindowEvent` instance, the
 * `WindowEvent::data_1()` and `WindowEvent::data_2()` methods have special
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
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
enum class window_event_id {
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
 * @brief Indicates whether or not two window event ID values are the same.
 *
 * @ingroup event
 *
 * @param lhs the left-hand side window event ID value.
 * @param rhs the right-hand side window event ID value.
 *
 * @return `true` if the window event ID values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(window_event_id lhs,
                                               SDL_WindowEventID rhs) noexcept
    -> bool
{
  return static_cast<SDL_WindowEventID>(lhs) == rhs;
}

/**
 * @copydoc operator==(window_event_id, SDL_WindowEventID)
 *
 * @ingroup event
 */
[[nodiscard]] inline constexpr auto operator==(SDL_WindowEventID lhs,
                                               window_event_id rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two window event ID values aren't the same.
 *
 * @ingroup event
 *
 * @param lhs the left-hand side window event ID value.
 * @param rhs the right-hand side window event ID value.
 *
 * @return `true` if the window event ID values aren't the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(window_event_id lhs,
                                               SDL_WindowEventID rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(window_event_id, SDL_WindowEventID)
 *
 * @ingroup event
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_WindowEventID lhs,
                                               window_event_id rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @class window_event
 *
 * @ingroup event
 *
 * @brief Represents an event that is associated with an action related to a
 * window.
 *
 * @see `SDL_WindowEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class window_event final : public common_event<SDL_WindowEvent>
{
 public:
  /**
   * @brief Creates a default-initialized window event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  window_event() noexcept;

  /**
   * @brief Creates a window event based on the supplied SDL window event.
   *
   * @param event the SDL window event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  window_event(const SDL_WindowEvent& event) noexcept;

  /**
   * @brief Returns the event ID of this window event.
   *
   * @details There are many different kinds of window events, use this
   * method to check what kind of action that triggered this event.
   *
   * @return the event ID of this window event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto event_id() const noexcept -> window_event_id;

  /**
   * @brief Returns the value of the first data value.
   *
   * @details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
   *
   * @return the value of the first data value.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto data_1() const noexcept -> i32;

  /**
   * @brief Returns the value of the second data value.
   *
   * @details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
   *
   * @return the value of the second data value.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto data_2() const noexcept -> i32;
};

static_assert(validate_event<window_event, SDL_WindowEvent>());

/**
 * @class event
 *
 * @ingroup event
 *
 * @brief Serves as the main interface for dealing with events.
 *
 * @see `SDL_Event`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class event final
{
 public:
  /**
   * @brief Creates an empty event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  event() noexcept;

  /**
   * @brief Creates an event based on the supplied event.
   *
   * @param event the event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  event(const SDL_Event& event) noexcept;

  /**
   * @brief Creates an event based on the supplied event.
   *
   * @param event the event that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  event(SDL_Event&& event) noexcept;

  /**
   * @brief Refresh the event loop, gathering events from the input devices.
   *
   * @note You might not have to call this method by yourself.
   *
   * @see `SDL_PumpEvents`
   *
   * @since 3.1.0
   */
  CENTURION_API
  static void refresh() noexcept;

  /**
   * @brief Pushes an event onto the event queue.
   *
   * @param event the event that will be added to the event queue.
   *
   * @since 3.1.0
   */
  CENTURION_API
  static void push(event& event) noexcept;

  /**
   * @brief Flushes all current events from the event queue.
   *
   * @see `SDL_FlushEvents`
   *
   * @since 3.1.0
   */
  CENTURION_API
  static void flush() noexcept;

  /**
   * Flushes all of the current events from the event queue, including pending
   * events.
   *
   * @since 3.1.0
   */
  CENTURION_API
  static void flush_all() noexcept;

  /**
   * @brief Polls the next available event, if there is one.
   *
   * @details This is meant to be called inside a while-loop.
   *
   * @return `true` if there are any pending events; `false` otherwise.
   *
   * @since 3.1.0
   */
  CENTURION_QUERY
  auto poll() noexcept -> bool;

  /**
   * @brief Returns the type of the event.
   *
   * @details This method can always be safely called on an event instance.
   *
   * @return the type of the event.
   *
   * @since 3.1.0
   */
  CENTURION_QUERY
  auto type() const noexcept -> event_type;

  /**
   * @brief Indicates whether or not the event is of a particular type.
   *
   * @details This method is useful for checking the event type before
   * calling `get<T>`, to avoid exceptions being thrown.
   *
   * @tparam T the event type that will be checked, e.g. `WindowEvent`.
   *
   * @return `true` if the event is of the specified type; `false` otherwise.
   *
   * @see `get`
   * @see `try_get`
   *
   * @since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_data);
  }

  /**
   * @brief Attempts to return the internal event instance.
   *
   * @details If you're certain about the internal type, then you could use this
   * method to simply extract the internal event.
   *
   * @note This functions throws if the internal event isn't of the specified
   * type! You might want to make sure that the internal type is `T` with the
   * `is()` method before calling this method, or use `try_get()`.
   *
   * @tparam T the event type to obtain.
   *
   * @return a reference to the internal event type.
   *
   * @throws bad_variant_access if the internal event type isn't `T`.
   *
   * @see `is`
   * @see `try_get`
   *
   * @since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto get() -> T&
  {
    return std::get<T>(m_data);
  }

  /**
   * @copydoc get()
   */
  template <typename T>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(m_data);
  }

  /**
   * @brief Attempts to return the internal event instance.
   *
   * @details This method returns a null pointer if the internal event
   * doesn't match the specified type.
   *
   * @tparam T the event type to obtain.
   *
   * @return a pointer to the internal event type, might be null.
   *
   * @see `is`
   * @see `get`
   *
   * @since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto try_get() noexcept -> T*
  {
    return std::get_if<T>(&m_data);
  }

  /**
   * @copybrief try_get
   *
   * @details This function returns a null pointer if the internal event
   * doesn't match the specified type.
   *
   * @tparam T the event type to obtain.
   *
   * @return a pointer to the internal event type, might be null.
   *
   * @see `is`
   * @see `get`
   *
   * @since 5.0.0
   */
  template <typename T>
  [[nodiscard]] auto try_get() const noexcept -> const T*
  {
    return std::get_if<T>(&m_data);
  }

  /**
   * @brief Indicates whether or not there is an internal event stored in the
   * instance.
   *
   * @return `true` if there is no internal event; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto empty() const noexcept -> bool
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

  void update_data() noexcept;
};

}  // namespace cen

#endif  // CENTURION_EVENT_HEADER