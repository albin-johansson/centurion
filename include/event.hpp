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

#ifndef CENTURION_EVENT_HEADER
#define CENTURION_EVENT_HEADER

#include <SDL_events.h>

#include <type_traits>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "event_type.hpp"
#include "game_controller.hpp"
#include "joystick.hpp"
#include "key.hpp"
#include "key_modifier.hpp"
#include "mouse_button.hpp"
#include "touch.hpp"

/**
 * @namespace centurion::event
 *
 * @brief Contains the event components.
 *
 * @headerfile event.hpp
 */
namespace centurion::event {

/**
 * @brief The templated base class of all Centurion events.
 *
 * @details This class defines the common API of all events and provides the
 * storage of the SDL2 event.
 *
 * @tparam T an SDL event type.
 *
 * @since 4.0.0
 */
template <typename T>
class CommonEvent {
 public:
  /**
   * @brief Creates a `CommonEvent` and default-initializes the internal event.
   *
   * @since 4.0.0
   */
  CommonEvent() noexcept : m_event{} {}

  /**
   * @brief Creates a CommonEvent and copies the supplied event.
   *
   * @param event the event that will be copied.
   *
   * @since 4.0.0
   */
  explicit CommonEvent(const T& event) : m_event{event} {}

  /**
   * @brief Creates a CommonEvent and moves the contents of the supplied event.
   *
   * @param event the event that will be moved.
   *
   * @since 4.0.0
   */
  explicit CommonEvent(T&& event) : m_event{std::move(event)} {}

  /**
   * @brief Default virtual destructor.
   *
   * @since 4.0.0
   */
  virtual ~CommonEvent() noexcept = default;

  /**
   * @brief Sets the timestamp that is associated with the creation of the
   * event.
   *
   * @param timestamp the timestamp that should be associated with the creation
   * of the event.
   *
   * @since 4.0.0
   */
  void set_time(Uint32 timestamp) noexcept { m_event.timestamp = timestamp; }

  /**
   * @brief Sets the event type value associated with the event.
   *
   * @param type the event type value associated with the event.
   *
   * @since 4.0.0
   */
  void set_type(EventType type) noexcept
  {
    m_event.type = static_cast<Uint32>(type);
  }

  /**
   * @brief Returns the timestamp associated with the creation of the event.
   *
   * @return the timestamp associated with the creation of the event.
   *
   * @since 4.0.0
   */
  [[nodiscard]] Uint32 time() const noexcept { return m_event.timestamp; }

  /**
   * @brief Returns the event type value associated with the event.
   *
   * @return the event type value associated with the event.
   *
   * @see EventType
   *
   * @since 4.0.0
   */
  [[nodiscard]] EventType type() const noexcept
  {
    return static_cast<EventType>(m_event.type);
  }

  /**
   * @brief Returns the internal event.
   *
   * @return the internal event.
   *
   * @since 5.0.0
   */
  [[nodiscard]] const T& get() const noexcept { return m_event; }

 protected:
  T m_event{};
};

/**
 * @brief Indicates whether or not a Centurion event type fulfills the event
 * type specification.
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
  return std::has_virtual_destructor_v<T> &&
         std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> &&
         std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> &&
         std::is_nothrow_constructible_v<T, E> && !std::is_final_v<T>;
}

/**
 * @class AudioDeviceEvent
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
class AudioDeviceEvent : public CommonEvent<SDL_AudioDeviceEvent> {
 public:
  /**
   * @brief Creates a default-initialized audio device event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  AudioDeviceEvent() noexcept;

  /**
   * @brief Creates a audio device event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept;

  /**
   * @brief Sets the audio device ID that is associated with the event.
   *
   * @param which the audio device ID that is associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(Uint32 which) noexcept;

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
  auto which() const noexcept -> Uint32;

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

static_assert(validate_event<AudioDeviceEvent, SDL_AudioDeviceEvent>());

/**
 * @class ControllerAxisEvent
 *
 * @brief Represents an event triggered by game controller axis motion.
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class ControllerAxisEvent : public CommonEvent<SDL_ControllerAxisEvent> {
 public:
  /**
   * @brief Creates a default-initialized controller axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerAxisEvent() noexcept;

  /**
   * @brief Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerAxisEvent(const SDL_ControllerAxisEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the instance ID of the joystick that the event is
   * associated with.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(JoystickID which) noexcept;

  /**
   * @brief Sets the game controller axis value associated with the event.
   *
   * @param axis the game controller axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_axis(GameControllerAxis axis) noexcept;

  /**
   * @brief Sets the axis value associated with the event.
   *
   * @param value the new axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_value(Sint16 value) noexcept;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> JoystickID;

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
  auto axis() const noexcept -> GameControllerAxis;

  /**
   * @brief Returns the axis value associated with the event.
   *
   * @return the axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto value() const noexcept -> Sint16;
};

static_assert(validate_event<ControllerAxisEvent, SDL_ControllerAxisEvent>());

/**
 * @class ControllerButtonEvent
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
class ControllerButtonEvent : public CommonEvent<SDL_ControllerButtonEvent> {
 public:
  /**
   * @brief Creates a default-initialized controller button event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerButtonEvent() noexcept;

  /**
   * @brief Creates a controller button event that is based on the supplied SDL
   * controller button event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerButtonEvent(const SDL_ControllerButtonEvent& event) noexcept;

  /**
   * @brief Sets the game controller button associated with the event.
   *
   * @param button the game controller button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(GameControllerButton button) noexcept;

  /**
   * @brief Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(ButtonState state) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param id the instance ID of the joystick that the event is associated
   * with.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(JoystickID id) noexcept;

  /**
   * @brief Returns the game controller button associated with the event.
   *
   * @return the game controller button associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto button() const noexcept -> GameControllerButton;

  /**
   * @brief Returns the button state associated with the event.
   *
   * @return the button state associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto state() const noexcept -> ButtonState;

  /**
   * @brief Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto which() const noexcept -> JoystickID;
};

static_assert(
    validate_event<ControllerButtonEvent, SDL_ControllerButtonEvent>());

/**
 * @class ControllerDeviceEvent
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
class ControllerDeviceEvent : public CommonEvent<SDL_ControllerDeviceEvent> {
 public:
  /**
   * @brief Creates a default-initialized controller device event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerDeviceEvent() noexcept;

  /**
   * @brief Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ControllerDeviceEvent(const SDL_ControllerDeviceEvent& event) noexcept;

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
  void set_which(Sint32 which) noexcept;

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
  auto which() const noexcept -> Sint32;
};

static_assert(
    validate_event<ControllerDeviceEvent, SDL_ControllerDeviceEvent>());

/**
 * @class DollarGestureEvent
 *
 * @brief Provides information about dollar gestures from touch events.
 *
 * @see `SDL_DollarGestureEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class DollarGestureEvent : public CommonEvent<SDL_DollarGestureEvent> {
 public:
  /**
   * @brief Creates a default-initialized dollar gesture event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  DollarGestureEvent() noexcept;

  /**
   * @brief Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * @param event the SDL event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  DollarGestureEvent(const SDL_DollarGestureEvent& event) noexcept;

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
  void set_fingers(Uint32 fingers) noexcept;

  /**
   * @brief Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * @return the error value for the performed stroke.
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
  auto fingers() const noexcept -> Uint32;

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

static_assert(validate_event<DollarGestureEvent, SDL_DollarGestureEvent>());

/**
 * @class DropEvent
 *
 * @brief Represents the event of requesting a file to be opened.
 *
 * @see `SDL_DropEvent`
 *
 * @since 4.0.0
 *
 * @headerfile event.hpp
 */
class DropEvent : public CommonEvent<SDL_DropEvent> {
 public:
  /**
   * @brief Creates a default-initialized drop event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  DropEvent() noexcept;

  /**
   * @brief Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  DropEvent(const SDL_DropEvent& event) noexcept;

  /**
   * @brief Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be moved.
   *
   * @since 4.0.0
   */
  CENTURION_API
  DropEvent(SDL_DropEvent&& event) noexcept;

  /**
   * @brief Destroys the drop event.
   *
   * @details The associated file will be freed depending on the value
   * returned from the `will_free_file()` method.
   *
   * @since 4.0.0
   */
  CENTURION_API
  ~DropEvent() noexcept;

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
  void set_window_id(Uint32 id) noexcept;

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
  auto window_id() const noexcept -> Uint32;

 private:
  bool m_willFreeFile{false};
};

static_assert(validate_event<DropEvent, SDL_DropEvent>());

/**
 * @class JoyAxisEvent
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
class JoyAxisEvent : public CommonEvent<SDL_JoyAxisEvent> {
 public:
  /**
   * @brief Creates a default-initialized joy axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  JoyAxisEvent() noexcept;

  /**
   * @brief Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * @param event the SDL joy axis event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept;

  /**
   * @brief Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(JoystickID which) noexcept;

  /**
   * @brief Sets the joystick axis index associated with the event.
   *
   * @param axis the joystick axis index associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_axis(Uint8 axis) noexcept;

  /**
   * @brief Sets the joystick axis value associated with the event.
   *
   * @param value the joystick axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_value(Sint16 value) noexcept;

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
  auto axis() const noexcept -> Uint8;

  /**
   * @brief Returns the joystick axis value associated with the event.
   *
   * @return the joystick axis value associated with the event.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto value() const noexcept -> Sint16;
};

static_assert(validate_event<JoyAxisEvent, SDL_JoyAxisEvent>());

/**
 * @class JoyBallEvent
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
class JoyBallEvent : public CommonEvent<SDL_JoyBallEvent> {
 public:
  /**
   * @brief Creates a default-initialized joy ball event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  JoyBallEvent() noexcept;

  /**
   * @brief Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * @param event the SDL joy ball event that will be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  JoyBallEvent(const SDL_JoyBallEvent& event) noexcept;

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
  void set_ball(Uint8 ball) noexcept;

  /**
   * @brief Sets the relative motion along the x-axis associated with the event.
   *
   * @param dx the relative motion along the x-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(Sint16 dx) noexcept;

  /**
   * @brief Sets the relative motion along the y-axis associated with the event.
   *
   * @param dy the relative motion along the y-axis.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(Sint16 dy) noexcept;

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
  auto ball() const noexcept -> Uint8;

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
  auto dx() const noexcept -> Sint16;

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
  auto dy() const noexcept -> Sint16;
};

static_assert(validate_event<JoyBallEvent, SDL_JoyBallEvent>());

/**
 * The JoyButtonEvent class represents an event associated with the press or
 * release of a joystick button.
 *
 * @see SDL_JoyButtonEvent
 * @since 4.0.0
 */
class JoyButtonEvent : public CommonEvent<SDL_JoyButtonEvent> {
 public:
  /**
   * Creates a default-initialized JoyButtonEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  JoyButtonEvent() noexcept;

  /**
   * Creates a JoyButtonEvent based on the supplied SDL_JoyButtonEvent.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept;

  /**
   * Creates a JoyButtonEvent based on the supplied SDL_JoyButtonEvent.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  JoyButtonEvent(SDL_JoyButtonEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(JoystickID which) noexcept;

  /**
   * Sets the button index associated with the event.
   *
   * @param button the button index associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(Uint8 button) noexcept;

  /**
   * Sets the button state that is associated with the button that triggered
   * the event.
   *
   * @param state the button state that is associated with the button that
   * triggered the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(ButtonState state) noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY JoystickID which() const noexcept;

  /**
   * Returns the index of the button that changed.
   *
   * @return the index of the button that changed.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint8 button() const noexcept;

  /**
   * Returns the state of the button associated with the event.
   *
   * @return the state of the button associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY ButtonState state() const noexcept;
};

static_assert(validate_event<JoyButtonEvent, SDL_JoyButtonEvent>());

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
  CENTURION_API
  JoyDeviceEvent() noexcept;

  /**
   * Creates a JoyDeviceEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept;

  /**
   * Creates a JoyDeviceEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  JoyDeviceEvent(SDL_JoyDeviceEvent&& event) noexcept;

  /**
   * Sets the joystick device index or instance ID, depending on the type of
   * the event.
   *
   * @param which the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(Sint32 which) noexcept;

  /**
   * Returns the joystick device index if the type is JoystickDeviceAdded
   * or the joystick instance ID if the type is JoystickDeviceRemoved.
   *
   * @return the joystick device index or instance ID.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 which() const noexcept;
};

static_assert(validate_event<JoyDeviceEvent, SDL_JoyDeviceEvent>());

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
  CENTURION_API
  JoyHatEvent() noexcept;

  /**
   * Creates a joy hat event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  JoyHatEvent(const SDL_JoyHatEvent& event) noexcept;

  /**
   * Creates a joy hat event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  JoyHatEvent(SDL_JoyHatEvent&& event) noexcept;

  /**
   * Sets the hat index associated with the event.
   *
   * @param hat the hat index.
   * @since 4.0.0
   */
  CENTURION_API
  void set_hat(Uint8 hat) noexcept;

  /**
   * Sets the joystick hat position associated with the event.
   *
   * @param value the joystick hat position associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_position(JoyHatPosition value) noexcept;

  /**
   * Returns the index of the hat that changed.
   *
   * @return the index of the hat that changed.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint8 hat() const noexcept;

  /**
   * Returns the position of the associated joystick hat.
   *
   * @return the position of the associated joystick hat.
   * @since 4.0.0
   */
  CENTURION_QUERY JoyHatPosition position() const noexcept;
};

static_assert(validate_event<JoyHatEvent, SDL_JoyHatEvent>());

/**
 * The KeyboardEvent class represents an event associated with some sort of
 * key action, such as the release or pressing of a key.
 *
 * @see SDL_KeyboardEvent
 * @since 4.0.0
 */
class KeyboardEvent : public CommonEvent<SDL_KeyboardEvent> {
 public:
  /**
   * Creates a default-initialized keyboard event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  KeyboardEvent() noexcept;

  /**
   * Creates a keyboard event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  explicit KeyboardEvent(const SDL_KeyboardEvent& event) noexcept;

  /**
   * Creates a keyboard event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  explicit KeyboardEvent(SDL_KeyboardEvent&& event) noexcept;

  /**
   * Sets the button state associated with a key.
   *
   * @param key the key to set the button state of.
   * @param state the new button state of the key.
   * @since 4.0.0
   */
  CENTURION_API
  void set_key(const Key& key, ButtonState state) noexcept;

  /**
   * Sets the status of a key modifier.
   *
   * @param modifier the key modifier that will be affected.
   * @param active `true` if the key modifier is active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_API
  void set_modifier(KeyModifier modifier, bool active) noexcept;

  /**
   * Sets the flag that indicates whether or not the key associated with this
   * key event was repeatedly triggered.
   *
   * @param repeated `true` if the key was repeatedly triggered; `false`
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_API
  void set_repeated(bool repeated) noexcept;

  /**
   * Sets the window ID that is associated with this key event.
   *
   * @param id the window ID that should be associated with the key event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Indicates whether or not the supplied key represents the same key that
   * triggered this keyboard event.
   *
   * @param key the key that will be checked.
   * @return `true` if the supplied key caused this keyboard event; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool is_active(const Key& key) const noexcept;

  /**
   * Indicates whether or not the specified key modifier is active. Multiple key
   * modifiers can be active at the same time.
   *
   * @param modifier the key modifier that will be checked.
   * @return `true` if the specified key modifier is active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool modifier_active(KeyModifier modifier) const noexcept;

  /**
   * Indicates whether or not any of the SHIFT modifiers are active.
   *
   * @return `true` if any of the SHIFT modifiers are active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool shift_active() const noexcept;

  /**
   * Indicates whether or not any of the CTRL modifiers are active.
   *
   * @return `true` if any of the CTRL modifiers are active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool ctrl_active() const noexcept;

  /**
   * Indicates whether or not any of the ALT modifiers are active.
   *
   * @return `true` if any of the ALT modifiers are active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool alt_active() const noexcept;

  /**
   * Indicates whether or not any of the GUI modifiers are active.
   *
   * @return `true` if any of the GUI modifiers are active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool gui_active() const noexcept;

  /**
   * Indicates whether or not the CAPS modifier is active.
   *
   * @return `true` if the CAPS modifier is active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool caps_active() const noexcept;

  /**
   * Indicates whether or not the NUM modifier is active.
   *
   * @return `true` if the NUM modifier is active; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool num_active() const noexcept;

  /**
   * Indicates whether or not the key associated with this key event has been
   * repeatedly triggered.
   *
   * @return `true` if the key associated with the event was repeated; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool repeated() const noexcept;

  /**
   * Returns the button state of the key associated with the event.
   *
   * @return the button state of the key associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY ButtonState state() const noexcept;

  /**
   * Returns the key that triggered this keyboard event.
   *
   * @return the key that triggered this keyboard event.
   * @since 4.0.0
   */
  CENTURION_QUERY Key key() const noexcept;

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;
};

static_assert(validate_event<KeyboardEvent, SDL_KeyboardEvent>());

/**
 * The MouseButtonEvent class represents an event triggered by mouse button
 * presses or releases.
 *
 * @see SDL_MouseButtonEvent
 * @since 4.0.0
 */
class MouseButtonEvent : public CommonEvent<SDL_MouseButtonEvent> {
 public:
  /**
   * Creates a default-initialized MouseButtonEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  MouseButtonEvent() noexcept;

  /**
   * Creates a MouseButtonEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  MouseButtonEvent(const SDL_MouseButtonEvent& event) noexcept;

  /**
   * Creates a MouseButtonEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  MouseButtonEvent(SDL_MouseButtonEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @param which the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(Uint32 which) noexcept;

  /**
   * Sets the mouse button associated with the event.
   *
   * @param button the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_button(MouseButton button) noexcept;

  /**
   * Sets the button state associated with the event.
   *
   * @param state the button state associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(ButtonState state) noexcept;

  /**
   * Sets the amount of clicks associated with the event.
   *
   * @param clicks the amount of clicks associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_clicks(Uint8 clicks) noexcept;

  /**
   * Sets the x-coordinate of the mouse relative to the window.
   *
   * @param x the x-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(Sint32 x) noexcept;

  /**
   * Sets the y-coordinate of the mouse relative to the window.
   *
   * @param y the y-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(Sint32 y) noexcept;

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 which() const noexcept;

  /**
   * Returns the mouse button associated with the event.
   *
   * @return the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY MouseButton button() const noexcept;

  /**
   * Returns the state of the mouse button associated with the event.
   *
   * @return the state of the mouse button associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY ButtonState state() const noexcept;

  /**
   * Returns the number of mouse clicks associated with the event.
   *
   * @return the number of mouse clicks associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint8 clicks() const noexcept;

  /**
   * Returns the x-coordinate of the mouse relative to the window.
   *
   * @return the x-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse relative to the window.
   *
   * @return the y-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 y() const noexcept;
};

static_assert(validate_event<MouseButtonEvent, SDL_MouseButtonEvent>());

/**
 * The MouseMotionEvent class represents events that are triggered by the
 * movement of the mouse.
 *
 * @see SDL_MouseMotionEvent
 * @since 4.0.0
 */
class MouseMotionEvent : public CommonEvent<SDL_MouseMotionEvent> {
 public:
  /**
   * Creates a default-initialized MouseMotionEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  MouseMotionEvent() noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  MouseMotionEvent(const SDL_MouseMotionEvent& event) noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  MouseMotionEvent(SDL_MouseMotionEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the mouse instance ID, or SDL_TOUCH_MOUSEID depending on the type
   * of the event.
   *
   * @param which the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(Uint32 which) noexcept;

  /**
   * Sets the mouse button state associated with the event. The value could
   * be any of SDL_BUTTON_LMASK, SDL_BUTTON_MMASK, SDL_BUTTON_RMASK,
   * SDL_BUTTON_X1MASK and SDL_BUTTON_X2MASK OR'd together.
   *
   * @param state the mouse button state associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_state(Uint32 state) noexcept;

  /**
   * Sets the x-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * @param x the x-coordinate of the mouse.
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(Sint32 x) noexcept;

  /**
   * Sets the y-coordinate of the mouse relative to the mouse that is
   * associated with the event.
   *
   * @param y the y-coordinate of the mouse.
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(Sint32 y) noexcept;

  /**
   * Sets the value of the relative motion of the mouse along the x-axis.
   *
   * @param dx the value of the relative motion of the mouse along the x-axis.
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(Sint32 dx) noexcept;

  /**
   * Sets the value of the relative motion of the mouse along the y-axis.
   *
   * @param dy the value of the relative motion of the mouse along the y-axis.
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(Sint32 dy) noexcept;

  /**
   * Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the mouse instance ID, or SDL_TOUCH_MOUSEID. The returned value
   * might be SDL_TOUCH_MOUSEID for events that were generated by a touch
   * input device.
   *
   * @return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 which() const noexcept;

  /**
   * Returns a bitmask for the current mouse button state. If you want to
   * check if a specific mouse button is pressed or released, a better
   * alternative would be to use the <code>pressed(MouseButton)</code> method.
   *
   * @return  a bitmask for the current mouse button state.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 state() const noexcept;

  /**
   * Indicate whether or not a mouse button is pressed.
   *
   * @param button the mouse button that will be checked.
   * @return `true` if the specified mouse button is pressed; `false` otherwise.
   * @since 4.0.0
   */
  CENTURION_QUERY bool pressed(MouseButton button) const noexcept;

  /**
   * Returns the x-coordinate of the mouse relative to the window.
   *
   * @return the x-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse relative to the window.
   *
   * @return the y-coordinate of the mouse relative to the window.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 y() const noexcept;

  /**
   * Returns the relative motion of the mouse along the x-axis.
   *
   * @return the relative motion of the mouse along the x-axis.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 dx() const noexcept;

  /**
   * Returns the relative motion of the mouse along the y-axis.
   *
   * @return the relative motion of the mouse along the y-axis.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 dy() const noexcept;
};

static_assert(validate_event<MouseMotionEvent, SDL_MouseMotionEvent>());

/**
 * The MouseWheelDirection enum class mirrors the values of the
 * SDL_MouseWheelDirection enum.
 *
 * @see SDL_MouseWheelDirection
 * @since 4.0.0
 */
enum class MouseWheelDirection {
  Normal = SDL_MOUSEWHEEL_NORMAL,
  Flipped = SDL_MOUSEWHEEL_FLIPPED
};

/**
 * Indicates whether or not the two mouse wheel direction values are the same.
 *
 * @param lhs the left-hand side Centurion mouse wheel direction.
 * @param rhs the right-hand side SDL mouse wheel direction.
 * @return `true` if the two mouse wheel direction values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator==(MouseWheelDirection lhs,
                                SDL_MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values are the same.
 *
 * @param lhs the left-hand side SDL mouse wheel direction.
 * @param rhs the right-hand side Centurion mouse wheel direction.
 * @return `true` if the two mouse wheel direction values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator==(SDL_MouseWheelDirection lhs,
                                MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values aren't the
 * same.
 *
 * @param lhs the left-hand side Centurion mouse wheel direction.
 * @param rhs the right-hand side SDL mouse wheel direction.
 * @return `true` if the two mouse wheel direction values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator!=(MouseWheelDirection lhs,
                                SDL_MouseWheelDirection rhs) noexcept;

/**
 * Indicates whether or not the two mouse wheel direction values aren't the
 * same.
 *
 * @param lhs the left-hand side SDL mouse wheel direction.
 * @param rhs the right-hand side Centurion mouse wheel direction.
 * @return `true` if the two mouse wheel direction values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator!=(SDL_MouseWheelDirection lhs,
                                MouseWheelDirection rhs) noexcept;

/**
 * The MouseWheelEvent class represents events triggered when a user moves
 * the mouse wheel.
 *
 * @see SDL_MouseWheelEvent
 * @since 4.0.0
 */
class MouseWheelEvent : public CommonEvent<SDL_MouseWheelEvent> {
 public:
  /**
   * Creates a default-initialized MouseWheelEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  MouseWheelEvent() noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  MouseWheelEvent(const SDL_MouseWheelEvent& event) noexcept;

  /**
   * Creates a MouseMotionEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  MouseWheelEvent(SDL_MouseWheelEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @param which the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_API
  void set_which(Uint32 which) noexcept;

  /**
   * Returns the horizontally scrolled distance, a positive value indicates that
   * the user scrolled to the right and a negative value indicates that the
   * user scrolled to the left.
   *
   * @param xScroll the horizontally scrolled distance.
   * @since 4.0.0
   */
  CENTURION_API
  void set_x_scroll(Sint32 xScroll) noexcept;

  /**
   * Returns the vertically scrolled distance, a positive value indicates that
   * the user scrolled away from the user and a negative value indicates that
   * the user scrolled towards the user.
   *
   * @param yScroll the vertically scrolled distance.
   * @since 4.0.0
   */
  CENTURION_API
  void set_y_scroll(Sint32 yScroll) noexcept;

  /**
   * Sets the mouse wheel direction mode associated with the event.
   *
   * @param direction the mouse wheel direction mode associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_direction(MouseWheelDirection direction) noexcept;

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * @return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 which() const noexcept;

  /**
   * Returns the horizontally scrolled distance, a positive value indicates that
   * the user scrolled to the right and a negative value indicates that the
   * user scrolled to the left.
   *
   * @return the horizontally scrolled distance.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 x_scroll() const noexcept;

  /**
   * Returns the vertically scrolled distance, a positive value indicates that
   * the user scrolled away from the user and a negative value indicates that
   * the user scrolled towards the user.
   *
   * @return the vertically scrolled distance.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 y_scroll() const noexcept;

  /**
   * Returns the mouse wheel direction mode associated with the event.
   *
   * @return the mouse wheel direction mode associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY MouseWheelDirection direction() const noexcept;
};

static_assert(validate_event<MouseWheelEvent, SDL_MouseWheelEvent>());

/**
 * The MultiGestureEvent class provides information about events related to
 * touch events triggered by multiple fingers.
 *
 * @see SDL_MultiGestureEvent
 * @since 4.0.0
 */
class MultiGestureEvent : public CommonEvent<SDL_MultiGestureEvent> {
 public:
  /**
   * Creates a default-initialized MultiGestureEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  MultiGestureEvent() noexcept;

  /**
   * Creates a MultiGestureEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  MultiGestureEvent(const SDL_MultiGestureEvent& event) noexcept;

  /**
   * Creates a MultiGestureEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  MultiGestureEvent(SDL_MultiGestureEvent&& event) noexcept;

  /**
   * Sets the touch device ID associated with the event.
   *
   * @param id the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_touch_id(TouchID id) noexcept;

  /**
   * Sets the amount that the fingers rotated during the gesture associated
   * with the event.
   *
   * @param dTheta the amount that the fingers rotated.
   * @since 4.0.0
   */
  CENTURION_API
  void set_delta_theta(float dTheta) noexcept;

  /**
   * Sets the amount that the fingers pinched during the gesture associated
   * with the event.
   *
   * @param dDistance the amount that the fingers pinched.
   * @since 4.0.0
   */
  CENTURION_API
  void set_delta_distance(float dDistance) noexcept;

  /**
   * Sets the x-coordinate of the normalized center of the gesture associated
   * with the event.
   *
   * @param centerX the x-coordinate of the normalized center of the gesture
   * associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_center_x(float centerX) noexcept;

  /**
   * Sets the y-coordinate of the normalized center of the gesture associated
   * with the event.
   *
   * @param centerY the y-coordinate of the normalized center of the gesture
   * associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_center_y(float centerY) noexcept;

  /**
   * Sets the number of fingers that was used in the gesture associated with
   * the event.
   *
   * @param nFingers the number of fingers that was used in the gesture.
   * @since 4.0.0
   */
  CENTURION_API
  void set_fingers(Uint16 nFingers) noexcept;

  /**
   * Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY TouchID touch_id() const noexcept;

  /**
   * Returns the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers rotated.
   * @since 4.0.0
   */
  CENTURION_QUERY float delta_theta() const noexcept;

  /**
   * Returns the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * @return the amount that the fingers pinched.
   * @since 4.0.0
   */
  CENTURION_QUERY float delta_distance() const noexcept;

  /**
   * Returns the x-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @return the x-coordinate of the normalized center of gesture associated
   * with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY float center_x() const noexcept;

  /**
   * Returns the y-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * @return the y-coordinate of the normalized center of gesture associated
   * with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY float center_y() const noexcept;

  /**
   * Returns the amount of fingers used in the gesture associated with the
   * event.
   *
   * @return the amount of fingers used in the gesture associated with the
   * event.
   * @since 4.0.0
   */
  CENTURION_QUERY float fingers() const noexcept;
};

static_assert(validate_event<MultiGestureEvent, SDL_MultiGestureEvent>());

/**
 * The QuitEvent class represents the event of the user wanting to close the
 * application, usually by pressing the "X"-button on the window frame.
 *
 * @see SDL_QuitEvent
 * @since 4.0.0
 */
class QuitEvent : public CommonEvent<SDL_QuitEvent> {
 public:
  /**
   * Creates a default-initialized quit event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  QuitEvent() noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  explicit QuitEvent(const SDL_QuitEvent& event) noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  explicit QuitEvent(SDL_QuitEvent&& event) noexcept;
};

static_assert(validate_event<QuitEvent, SDL_QuitEvent>());

/**
 * The TextEditingEvent class represents an event triggered by keyboard text
 * editing. Note that this class doesn't provide a setter for the text, since
 * it's impossible to assign a value to a variable of type char[32] in C++.
 *
 * @see SDL_TextEditingEvent
 * @since 4.0.0
 */
class TextEditingEvent : public CommonEvent<SDL_TextEditingEvent> {
 public:
  /**
   * Creates a default-initialized TextEditingEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  TextEditingEvent() noexcept;

  /**
   * Creates a TextEditingEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  TextEditingEvent(const SDL_TextEditingEvent& event) noexcept;

  /**
   * Creates a TextEditingEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  TextEditingEvent(SDL_TextEditingEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the location to begin editing from.
   *
   * @param start the location to begin editing from.
   * @since 4.0.0
   */
  CENTURION_API
  void set_start(Sint32 start) noexcept;

  /**
   * Sets the number of characters to edit from the start point. The supplied
   * value will be capped to always be in the range [0, 32].
   *
   * @param length the number of characters to edit from the start point.
   * @since 4.0.0
   */
  CENTURION_API
  void set_length(Sint32 length) noexcept;

  /**
   * Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * @return the text that will be used.
   * @since 4.0.0
   */
  CENTURION_QUERY CZString text() const noexcept;

  /**
   * Returns the location to begin editing from.
   *
   * @return the location to begin editing from.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 start() const noexcept;

  /**
   * Returns the number of characters to edit from the start point. The
   * returned value will always be in the range [0, 32].
   *
   * @return the number of characters to edit from the start point.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 length() const noexcept;

 private:
  void check_length() noexcept;
};

static_assert(validate_event<TextEditingEvent, SDL_TextEditingEvent>());

/**
 * The TextInputEvent class contains information about keyboard text input
 * events.
 *
 * @see SDL_TextInputEvent
 * @since 4.0.0
 */
class TextInputEvent : public CommonEvent<SDL_TextInputEvent> {
 public:
  /**
   * Creates a default-initialized TextInputEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  TextInputEvent() noexcept;

  /**
   * Creates a TextInputEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  TextInputEvent(const SDL_TextInputEvent& event) noexcept;

  /**
   * Creates a TextInputEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  TextInputEvent(SDL_TextInputEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * @return the text that will be used.
   * @since 4.0.0
   */
  CENTURION_QUERY CZString text() const noexcept;
};

static_assert(validate_event<TextInputEvent, SDL_TextInputEvent>());

/**
 * The TouchFingerEvent class represents an event related to touch screen
 * actions.
 *
 * @see SDL_TouchFingerEvent
 * @since 4.0.0
 */
class TouchFingerEvent : public CommonEvent<SDL_TouchFingerEvent> {
 public:
  /**
   * Creates a default-initialized touch finger event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  TouchFingerEvent() noexcept;

  /**
   * Creates a touch finger event that is based on the supplied SDL
   * ouch finger event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  TouchFingerEvent(const SDL_TouchFingerEvent& event) noexcept;

  /**
   * Creates a touch finger event by moving the supplied SDL touch finger
   * event.
   *
   * @param event the SDL touch finger event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  TouchFingerEvent(SDL_TouchFingerEvent&& event) noexcept;

  /**
   * Sets the ID of the associated touch device.
   *
   * @param id the ID of the associated touch device.
   * @since 4.0.0
   */
  CENTURION_API
  void set_touch_id(TouchID id) noexcept;

  /**
   * Sets the finger ID associated with the event.
   *
   * @param id the finger ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API
  void set_finger_id(FingerID id) noexcept;

  /**
   * Sets the window ID of the window under the finger.
   *
   * @param id the window ID of the window under the finger.
   * @since 4.0.0
   */
  CENTURION_API
  void set_window_id(Uint32 id) noexcept;

  /**
   * Sets the normalized x-coordinate of the location of the event. The
   * supplied value will be clamped in the range [0, 1].
   *
   * @param x the normalized x-coordinate of the location of the event,
   * clamped to the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API
  void set_x(float x) noexcept;

  /**
   * Sets the normalized y-coordinate of the location of the event. The
   * supplied value will be clamped in the range [0, 1].
   *
   * @param y the normalized y-coordinate of the location of the event,
   * clamped to the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API
  void set_y(float y) noexcept;

  /**
   * Sets the normalized distance moved along the x-axis. The
   * supplied value will be clamped in the range [-1, 1].
   *
   * @param dx the normalized distance moved along the x-axis, clamped to the
   * range [-1, 1].
   * @since 4.0.0
   */
  CENTURION_API
  void set_dx(float dx) noexcept;

  /**
   * Sets the normalized distance moved along the y-axis. The
   * supplied value will be clamped in the range [-1, 1].
   *
   * @param dy the normalized distance moved along the y-axis, clamped to the
   * range [-1, 1].
   * @since 4.0.0
   */
  CENTURION_API
  void set_dy(float dy) noexcept;

  /**
   * Sets the normalized pressure associated with the event. The supplied
   * value will be clamped in the range [0, 1].
   *
   * @param pressure the normalized pressure associated with the event, clamped
   * in the range [0, 1].
   * @since 4.0.0
   */
  CENTURION_API
  void set_pressure(float pressure) noexcept;

  /**
   * Returns the touch device ID associated with the event.
   *
   * @return the touch device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY TouchID touch_id() const noexcept;

  /**
   * Returns the finger ID associated with the event.
   *
   * @return the finger ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_QUERY FingerID finger_id() const noexcept;

  /**
   * Returns the window ID of the window under the finger.
   *
   * @return the window ID of the window under the finger.
   * @since 4.0.0
   */
  CENTURION_QUERY Uint32 window_id() const noexcept;

  /**
   * Returns the normalized x-coordinate of the location of the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized x-coordinate of the location of the event, in the
   * range [0, 1].
   * @since 4.0.0
   */
  CENTURION_QUERY float x() const noexcept;

  /**
   * Returns the normalized y-coordinate of the location of the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized y-coordinate of the location of the event, in the
   * range [0, 1].
   * @since 4.0.0
   */
  CENTURION_QUERY float y() const noexcept;

  /**
   * Returns the normalized distance moved along the x-axis. The
   * returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the x-axis, in the range
   * [-1, 1].
   * @since 4.0.0
   */
  CENTURION_QUERY float dx() const noexcept;

  /**
   * Returns the normalized distance moved along the y-axis. The
   * returned value will be in the range [-1, 1].
   *
   * @return the normalized distance moved along the y-axis, in the range
   * [-1, 1].
   * @since 4.0.0
   */
  CENTURION_QUERY float dy() const noexcept;

  /**
   * Returns the normalized pressure associated with the event. The
   * returned value will be in the range [0, 1].
   *
   * @return the normalized pressure associated with the event, in the range
   * [0, 1].
   * @since 4.0.0
   */
  CENTURION_QUERY float pressure() const noexcept;
};

static_assert(validate_event<TouchFingerEvent, SDL_TouchFingerEvent>());

/**
 *
 * The WindowEventID enum class mirrors the SDL_WindowEventID enum. Depending
 * on the event ID of a WindowEvent instance, the <code>data_1()</code> and
 * <code>data_2()</code> methods have special meanings.
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
 */
enum class WindowEventID {
  None = SDL_WINDOWEVENT_NONE,
  Shown = SDL_WINDOWEVENT_SHOWN,
  Hidden = SDL_WINDOWEVENT_HIDDEN,
  Exposed = SDL_WINDOWEVENT_EXPOSED,
  Moved = SDL_WINDOWEVENT_MOVED,
  Resized = SDL_WINDOWEVENT_RESIZED,
  SizeChanged = SDL_WINDOWEVENT_SIZE_CHANGED,
  Minimized = SDL_WINDOWEVENT_MINIMIZED,
  Maximized = SDL_WINDOWEVENT_MAXIMIZED,
  Restored = SDL_WINDOWEVENT_RESTORED,
  Enter = SDL_WINDOWEVENT_ENTER,
  Leave = SDL_WINDOWEVENT_LEAVE,
  FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
  FocusLost = SDL_WINDOWEVENT_FOCUS_LOST,
  Close = SDL_WINDOWEVENT_CLOSE,
  TakeFocus = SDL_WINDOWEVENT_TAKE_FOCUS,
  HitTest = SDL_WINDOWEVENT_HIT_TEST
};

/**
 * Indicates whether or not two window event ID values are the same.
 *
 * @param eventId the Centurion window event ID.
 * @param sdlEventId the SDL window event ID.
 * @return `true` if the window event ID values are the same; `false` otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator==(WindowEventID eventId,
                                SDL_WindowEventID sdlEventId) noexcept;

/**
 * Indicates whether or not two window event ID values are the same.
 *
 * @param eventId the SDL window event ID.
 * @param sdlEventId the Centurion window event ID.
 * @return `true` if the window event ID values are the same; `false` otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator==(SDL_WindowEventID sdlEventId,
                                WindowEventID eventId) noexcept;

/**
 * Indicates whether or not two window event ID values aren't the same.
 *
 * @param eventId the Centurion window event ID.
 * @param sdlEventId the SDL window event ID.
 * @return `true` if the window event ID values aren't the same; `false`
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator!=(WindowEventID eventId,
                                SDL_WindowEventID sdlEventId) noexcept;

/**
 * Indicates whether or not two window event ID values aren't the same.
 *
 * @param eventId the SDL window event ID.
 * @param sdlEventId the Centurion window event ID.
 * @return `true` if the window event ID values aren't the same; `false`
 * otherwise.
 * @since 4.0.0
 */
CENTURION_QUERY bool operator!=(SDL_WindowEventID sdlEventId,
                                WindowEventID eventId) noexcept;

/**
 * The WindowEvent class represents an event that is associated with an
 * action related to a window. This class is a subclass of
 * BaseEvent&lt;SDL_WindowEvent&gt;.
 *
 * @see SDL_WindowEvent
 * @since 4.0.0
 */
class WindowEvent : public CommonEvent<SDL_WindowEvent> {
 public:
  /**
   * Creates a default-initialized window event.
   *
   * @since 4.0.0
   */
  CENTURION_API
  WindowEvent() noexcept;

  /**
   * Creates a window event based on the supplied SDL window event.
   *
   * @param event the SDL window event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  explicit WindowEvent(const SDL_WindowEvent& event) noexcept;

  /**
   * Creates a window event based on the supplied SDL window event.
   *
   * @param event the SDL window event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  explicit WindowEvent(SDL_WindowEvent&& event) noexcept;

  /**
   * Returns the event ID of this window event. There are many different
   * kinds of window events, use this method to check what kind of action
   * that triggered this event.
   *
   * @return the event ID of this window event.
   * @since 4.0.0
   */
  CENTURION_QUERY WindowEventID event_id() const noexcept;

  /**
   * Returns the value of the first data value. The meaning of this value is
   * dependent on the window event ID of this window event.
   *
   * <p> For instance, if the event ID is <code>SizeChanged</code>, then
   * data1 and data2 represent the new width and height of the window
   * respectively. See the <code>WindowEventID</code> documentation for more
   * details about whether the value returned from this method is meaningful
   * in regard to the window event ID.
   *
   * @return the value of the first data value.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 data_1() const noexcept;

  /**
   * Returns the value of the second data value. The meaning of this value is
   * dependent on the window event ID of this window event.
   *
   * <p> For instance, if the event ID is <code>SizeChanged</code>, then
   * data1 and data2 represent the new width and height of the window
   * respectively. See the <code>WindowEventID</code> documentation for more
   * details about whether the value returned from this method is meaningful
   * in regard to the window event ID.
   *
   * @return the value of the second data value.
   * @since 4.0.0
   */
  CENTURION_QUERY Sint32 data_2() const noexcept;
};

static_assert(validate_event<WindowEvent, SDL_WindowEvent>());

/**
 * The Event class serves as the main interface for dealing with events in
 * the Centurion library.
 *
 * @todo Look into `SysWMEvent` breaking includes on Travis.
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
  CENTURION_API
  Event() noexcept;

  /**
   * Creates an event based on the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API
  Event(const SDL_Event& event) noexcept;

  /**
   * Creates an event based on the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  Event(SDL_Event&& event) noexcept;

  /**
   * Refresh the event loop, gathering events from the input devices. Note that
   * you might not have to call this method by yourself.
   *
   * @see SDL_PumpEvents
   * @since 3.1.0
   */
  CENTURION_API
  static void refresh() noexcept;

  /**
   * Pushes an event onto the event queue.
   *
   * @param event the event that will be added to the event queue.
   * @since 3.1.0
   */
  CENTURION_API
  static void push(Event& event) noexcept;

  /**
   * Flushes all current events from the event queue.
   *
   * @see
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
   * Polls the next available event, if there is one. This is meant to be
   * called inside a while-loop.
   *
   * @return `true` if there are any pending events; `false` otherwise.
   * @since 3.1.0
   */
  CENTURION_QUERY bool poll() noexcept;

  /**
   * Returns the type of the event. This method can always be safely called on
   * an event instance.
   *
   * @return the type of the event.
   * @since 3.1.0
   */
  CENTURION_QUERY EventType type() const noexcept;

  /**
   * Returns an AudioDeviceEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return an AudioDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<AudioDeviceEvent> as_audio_device_event()
      const noexcept;

  /**
   * Returns a ControllerAxisEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a ControllerAxisEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<ControllerAxisEvent> as_controller_axis_event()
      const noexcept;

  /**
   * Returns a ControllerButtonEvent or nothing if the type of the event
   * doesn't match.
   *
   * @return a ControllerButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<ControllerButtonEvent> as_controller_button_event()
      const noexcept;

  /**
   * Returns a ControllerDeviceEvent or nothing if the type of the event
   * doesn't match.
   *
   * @return a ControllerDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<ControllerDeviceEvent> as_controller_device_event()
      const noexcept;

  /**
   * Returns a DollarGestureEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a DollarGestureEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<DollarGestureEvent> as_dollar_gesture_event()
      const noexcept;

  /**
   * Returns a DropEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a DropEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<DropEvent> as_drop_event() const noexcept;

  /**
   * Returns a JoyAxisEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyAxisEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<JoyAxisEvent> as_joy_axis_event() const noexcept;

  /**
   * Returns a JoyBallEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyBallEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<JoyBallEvent> as_joy_ball_event() const noexcept;

  /**
   * Returns a JoyButtonEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<JoyButtonEvent> as_joy_button_event() const noexcept;

  /**
   * Returns a JoyDeviceEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyDeviceEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<JoyDeviceEvent> as_joy_device_event() const noexcept;

  /**
   * Returns a JoyHatEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a JoyHatEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<JoyHatEvent> as_joy_hat_event() const noexcept;

  /**
   * Returns a KeyboardEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a KeyboardEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<KeyboardEvent> as_keyboard_event() const noexcept;

  /**
   * Returns a MouseButtonEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseButtonEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<MouseButtonEvent> as_mouse_button_event()
      const noexcept;

  /**
   * Returns a MouseMotionEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseMotionEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<MouseMotionEvent> as_mouse_motion_event()
      const noexcept;

  /**
   * Returns a MouseWheelEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MouseWheelEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<MouseWheelEvent> as_mouse_wheel_event()
      const noexcept;

  /**
   * Returns a MultiGestureEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a MultiGestureEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<MultiGestureEvent> as_multi_gesture_event()
      const noexcept;

  /**
   * Returns a QuitEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a QuitEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<QuitEvent> as_quit_event() const noexcept;

  /**
   * Returns a TextEditingEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TextEditingEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<TextEditingEvent> as_text_editing_event()
      const noexcept;

  /**
   * Returns a TextInputEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TextInputEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<TextInputEvent> as_text_input_event() const noexcept;

  /**
   * Returns a TouchFingerEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a TouchFingerEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<TouchFingerEvent> as_touch_finger_event()
      const noexcept;

  /**
   * Returns a WindowEvent or nothing if the type of the event doesn't
   * match.
   *
   * @return a WindowEvent or nothing.
   * @since 4.0.0
   */
  CENTURION_QUERY Optional<WindowEvent> as_window_event() const noexcept;

  /**
   * Implicitly converts the event to a reference to the internal SDL_Event.
   *
   * @return a reference to the internal SDL_Event.
   * @since 4.0.0
   */
  [[nodiscard]] operator SDL_Event&() noexcept { return m_event; }

  /**
   * Implicitly converts the event to a const reference to the internal
   * SDL_Event.
   *
   * @return a const reference to the internal SDL_Event.
   * @since 4.0.0
   */
  [[nodiscard]] operator const SDL_Event&() const noexcept { return m_event; }

 private:
  SDL_Event m_event;
};

}  // namespace centurion::event

#ifdef CENTURION_HEADER_ONLY
#include "audio_device_event.cpp"
#include "controller_axis_event.cpp"
#include "controller_button_event.cpp"
#include "controller_device_event.cpp"
#include "dollar_gesture_event.cpp"
#include "drop_event.cpp"
#include "event.cpp"
#include "joy_axis_event.cpp"
#include "joy_ball_event.cpp"
#include "joy_button_event.cpp"
#include "joy_device_event.cpp"
#include "joy_hat_event.cpp"
#include "keyboard_event.cpp"
#include "mouse_button_event.cpp"
#include "mouse_motion_event.cpp"
#include "mouse_wheel_event.cpp"
#include "multi_gesture_event.cpp"
#include "quit_event.cpp"
#include "text_editing_event.cpp"
#include "text_input_event.cpp"
#include "touch_finger_event.cpp"
#include "window_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EVENT_HEADER