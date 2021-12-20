#ifndef CENTURION_EVENTS_EVENT_HPP_
#define CENTURION_EVENTS_EVENT_HPP_

#include <SDL.h>

#include <optional>  // optional
#include <utility>   // move
#include <variant>   // variant, holds_alternative, monostate, get, get_if

#include "../common.hpp"
#include "audio_device_event.hpp"
#include "common_event.hpp"
#include "controller_axis_event.hpp"
#include "controller_button_event.hpp"
#include "controller_device_event.hpp"
#include "controller_sensor_event.hpp"
#include "controller_touchpad_event.hpp"
#include "display_event.hpp"
#include "dollar_gesture_event.hpp"
#include "drop_event.hpp"
#include "event_type.hpp"
#include "joy_axis_event.hpp"
#include "joy_ball_event.hpp"
#include "joy_button_event.hpp"
#include "joy_device_event.hpp"
#include "joy_hat_event.hpp"
#include "keyboard_event.hpp"
#include "mouse_button_event.hpp"
#include "mouse_motion_event.hpp"
#include "mouse_wheel_event.hpp"
#include "multi_gesture_event.hpp"
#include "quit_event.hpp"
#include "sensor_event.hpp"
#include "text_editing_event.hpp"
#include "text_input_event.hpp"
#include "touch_finger_event.hpp"
#include "user_event.hpp"
#include "window_event.hpp"

namespace cen {

/// The main interface for dealing with events.
class Event final {
 public:
  /// Creates an empty event.
  Event() noexcept = default;

  explicit Event(const SDL_Event& event) noexcept : mEvent{event}
  {
    UpdateData(static_cast<event_type>(event.type));
  }

  template <typename T>
  explicit Event(const common_event<T>& event) noexcept : mEvent{as_sdl_event(event)}
  {
    UpdateData(event.type());
  }

  /// Updates the event loop, gathering events from the input devices.
  static void Update() noexcept { SDL_PumpEvents(); }

  static void Push(Event& event) noexcept
  {
    auto& sdlEvent = event.mEvent;
    SDL_PushEvent(&sdlEvent);
  }

  template <typename T>
  static auto Push(const common_event<T>& event) noexcept -> Result
  {
    auto sdlEvent = as_sdl_event(event);
    return SDL_PushEvent(&sdlEvent) >= 0;
  }

  /// Flushes all current events from the event queue.
  static void Flush() noexcept { SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT); }

  /// Flushes all of the current and pending events from the event queue.
  static void FlushAll() noexcept
  {
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
  }

  /// Polls the next available event, if there is one.
  /// \return `true` if there are any pending events; `false` otherwise.
  auto Poll() noexcept -> bool
  {
    const bool result = SDL_PollEvent(&mEvent);

    if (result) {
      UpdateData(static_cast<event_type>(mEvent.type));
    }
    else {
      mData.emplace<std::monostate>();
    }

    return result;
  }

  [[nodiscard]] auto GetType() const noexcept -> std::optional<event_type>
  {
    if (IsEmpty()) {
      return std::nullopt;
    }
    else {
      return static_cast<event_type>(mEvent.type);
    }
  }

  /// Returns the amount of events in the event queue.
  [[nodiscard]] static auto GetQueueSize() noexcept -> std::optional<int>
  {
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (num != -1) {
      return num;
    }
    else {
      return std::nullopt;
    }
  }

  /// Returns the amount of events of a particular type in the event queue.
  [[nodiscard]] static auto GetQueueSize(const event_type type) noexcept -> std::optional<int>
  {
    const auto id = ToUnderlying(type);
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, id, id);
    if (num != -1) {
      return num;
    }
    else {
      return std::nullopt;
    }
  }

  /// Indicates whether there is an event of a specific type in the event queue.
  [[nodiscard]] static auto InQueue(const event_type type) noexcept -> bool
  {
    return GetQueueSize(type) > 0;
  }

  /// Indicates whether the current event is of a particular type.
  template <typename T>
  [[nodiscard]] auto Is() const noexcept -> bool
  {
    return std::holds_alternative<T>(mData);
  }

  /// Returns the current event representation.
  ///
  /// Use this function if you're certain about the current event type.
  ///
  /// An exception is thrown if there is a mismatch between the requested type and the actual
  /// current event type. Use `TryGet()` for a non-throwing alternative to this function.
  ///
  /// \tparam T the type of the event to obtain.
  template <typename T>
  [[nodiscard]] auto Get() -> T&
  {
    return std::get<T>(mData);
  }

  /// \copydoc Get()
  template <typename T>
  [[nodiscard]] auto Get() const -> const T&
  {
    return std::get<T>(mData);
  }

  /// Attempts to return the current event representation.
  ///
  /// This function returns a null pointer if there is a mismatch between the requested type
  /// and the current event type.
  ///
  /// \tparam T the type of the event to obtain.
  template <typename T>
  [[nodiscard]] auto TryGet() noexcept -> T*
  {
    return std::get_if<T>(&mData);
  }

  /// \copydoc TryGet()
  template <typename T>
  [[nodiscard]] auto TryGet() const noexcept -> const T*
  {
    return std::get_if<T>(&mData);
  }

  /// Indicates whether there is no current event stored in the handler.
  [[nodiscard]] auto IsEmpty() const noexcept -> bool { return Is<std::monostate>(); }

  [[nodiscard]] auto data() const noexcept -> const SDL_Event* { return &mEvent; }

 private:
  /* Behold, the beast! */
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

                                 window_event>;

  SDL_Event mEvent{};
  data_type mData{};

  void UpdateData(const event_type type) noexcept
  {
    switch (type) {
      case event_type::quit:
        mData.emplace<quit_event>(mEvent.quit);
        break;

      case event_type::app_terminating:
      case event_type::app_low_memory:
      case event_type::app_will_enter_background:
      case event_type::app_did_enter_background:
      case event_type::app_will_enter_foreground:
      case event_type::app_did_enter_foreground:
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case event_type::locale_changed:
        break;

      case event_type::display:
        mData.emplace<display_event>(mEvent.display);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case event_type::window:
        mData.emplace<window_event>(mEvent.window);
        break;

      case event_type::system:
        break;

      case event_type::key_down:
      case event_type::key_up:
        mData.emplace<keyboard_event>(mEvent.key);
        break;

      case event_type::text_editing:
        mData.emplace<text_editing_event>(mEvent.edit);
        break;

      case event_type::text_input:
        mData.emplace<text_input_event>(mEvent.text);
        break;

      case event_type::keymap_changed:
        break;

      case event_type::mouse_motion:
        mData.emplace<mouse_motion_event>(mEvent.motion);
        break;

      case event_type::mouse_button_down:
      case event_type::mouse_button_up:
        mData.emplace<mouse_button_event>(mEvent.button);
        break;

      case event_type::mouse_wheel:
        mData.emplace<mouse_wheel_event>(mEvent.wheel);
        break;

      case event_type::joystick_axis_motion:
        mData.emplace<joy_axis_event>(mEvent.jaxis);
        break;

      case event_type::joystick_ball_motion:
        mData.emplace<joy_ball_event>(mEvent.jball);
        break;

      case event_type::joystick_hat_motion:
        mData.emplace<joy_hat_event>(mEvent.jhat);
        break;

      case event_type::joystick_button_down:
      case event_type::joystick_button_up:
        mData.emplace<joy_button_event>(mEvent.jbutton);
        break;

      case event_type::joystick_device_added:
      case event_type::joystick_device_removed:
        mData.emplace<joy_device_event>(mEvent.jdevice);
        break;

      case event_type::controller_axis_motion:
        mData.emplace<controller_axis_event>(mEvent.caxis);
        break;

      case event_type::controller_button_down:
      case event_type::controller_button_up:
        mData.emplace<controller_button_event>(mEvent.cbutton);
        break;

      case event_type::controller_device_added:
      case event_type::controller_device_removed:
      case event_type::controller_device_remapped:
        mData.emplace<controller_device_event>(mEvent.cdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case event_type::controller_touchpad_down:
      case event_type::controller_touchpad_up:
      case event_type::controller_touchpad_motion:
        mData.emplace<controller_touchpad_event>(mEvent.ctouchpad);
        break;

      case event_type::controller_sensor_update:
        mData.emplace<controller_sensor_event>(mEvent.csensor);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case event_type::touch_down:
      case event_type::touch_up:
      case event_type::touch_motion:
        mData.emplace<touch_finger_event>(mEvent.tfinger);
        break;

      case event_type::dollar_gesture:
      case event_type::dollar_record:
        mData.emplace<dollar_gesture_event>(mEvent.dgesture);
        break;

      case event_type::multi_gesture:
        mData.emplace<multi_gesture_event>(mEvent.mgesture);
        break;

      case event_type::clipboard_update:
        break;

      case event_type::drop_file:
      case event_type::drop_text:
      case event_type::drop_begin:
      case event_type::drop_complete:
        mData.emplace<drop_event>(mEvent.drop);
        break;

      case event_type::audio_device_added:
      case event_type::audio_device_removed:
        mData.emplace<audio_device_event>(mEvent.adevice);
        break;

      case event_type::sensor_update:
        mData.emplace<sensor_event>(mEvent.sensor);
        break;

      case event_type::render_targets_reset:
      case event_type::render_device_reset:
        break;

      case event_type::user:
        mData.emplace<user_event>(mEvent.user);
        break;

      default:
        mData.emplace<std::monostate>();
        break;
    }
  }
};

}  // namespace cen

#endif  // CENTURION_EVENT_HPP_