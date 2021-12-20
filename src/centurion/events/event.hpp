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
    UpdateData(static_cast<EventType>(event.type));
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
      UpdateData(static_cast<EventType>(mEvent.type));
    }
    else {
      mData.emplace<std::monostate>();
    }

    return result;
  }

  [[nodiscard]] auto GetType() const noexcept -> std::optional<EventType>
  {
    if (IsEmpty()) {
      return std::nullopt;
    }
    else {
      return static_cast<EventType>(mEvent.type);
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
  [[nodiscard]] static auto GetQueueSize(const EventType type) noexcept -> std::optional<int>
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
  [[nodiscard]] static auto InQueue(const EventType type) noexcept -> bool
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

  void UpdateData(const EventType type) noexcept
  {
    switch (type) {
      case EventType::Quit:
        mData.emplace<quit_event>(mEvent.quit);
        break;

      case EventType::AppTerminating:
      case EventType::AppLowMemory:
      case EventType::AppWillEnterBackground:
      case EventType::AppDidEnterBackground:
      case EventType::AppWillEnterForeground:
      case EventType::AppDidEnterForeground:
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case EventType::LocaleChanged:
        break;

      case EventType::Display:
        mData.emplace<display_event>(mEvent.display);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case EventType::Window:
        mData.emplace<window_event>(mEvent.window);
        break;

      case EventType::System:
        break;

      case EventType::KeyDown:
      case EventType::KeyUp:
        mData.emplace<keyboard_event>(mEvent.key);
        break;

      case EventType::TextEditing:
        mData.emplace<text_editing_event>(mEvent.edit);
        break;

      case EventType::TextInput:
        mData.emplace<text_input_event>(mEvent.text);
        break;

      case EventType::KeymapChanged:
        break;

      case EventType::MouseMotion:
        mData.emplace<mouse_motion_event>(mEvent.motion);
        break;

      case EventType::MouseButtonDown:
      case EventType::MouseButtonUp:
        mData.emplace<mouse_button_event>(mEvent.button);
        break;

      case EventType::MouseWheel:
        mData.emplace<mouse_wheel_event>(mEvent.wheel);
        break;

      case EventType::JoyAxisMotion:
        mData.emplace<joy_axis_event>(mEvent.jaxis);
        break;

      case EventType::JoyBallMotion:
        mData.emplace<joy_ball_event>(mEvent.jball);
        break;

      case EventType::JoyHatMotion:
        mData.emplace<joy_hat_event>(mEvent.jhat);
        break;

      case EventType::JoyButtonDown:
      case EventType::JoyButtonUp:
        mData.emplace<joy_button_event>(mEvent.jbutton);
        break;

      case EventType::JoyDeviceAdded:
      case EventType::JoyDeviceRemoved:
        mData.emplace<joy_device_event>(mEvent.jdevice);
        break;

      case EventType::ControllerAxisMotion:
        mData.emplace<controller_axis_event>(mEvent.caxis);
        break;

      case EventType::ControllerButtonDown:
      case EventType::ControllerButtonUp:
        mData.emplace<controller_button_event>(mEvent.cbutton);
        break;

      case EventType::ControllerDeviceAdded:
      case EventType::ControllerDeviceRemoved:
      case EventType::ControllerDeviceRemapped:
        mData.emplace<controller_device_event>(mEvent.cdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case EventType::ControllerTouchpadDown:
      case EventType::ControllerTouchpadUp:
      case EventType::ControllerTouchpadMotion:
        mData.emplace<controller_touchpad_event>(mEvent.ctouchpad);
        break;

      case EventType::ControllerSensorUpdate:
        mData.emplace<controller_sensor_event>(mEvent.csensor);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case EventType::FingerDown:
      case EventType::FingerUp:
      case EventType::FingerMotion:
        mData.emplace<touch_finger_event>(mEvent.tfinger);
        break;

      case EventType::DollarGesture:
      case EventType::DollarRecord:
        mData.emplace<dollar_gesture_event>(mEvent.dgesture);
        break;

      case EventType::MultiGesture:
        mData.emplace<multi_gesture_event>(mEvent.mgesture);
        break;

      case EventType::ClipboardUpdate:
        break;

      case EventType::DropFile:
      case EventType::DropText:
      case EventType::DropBegin:
      case EventType::DropComplete:
        mData.emplace<drop_event>(mEvent.drop);
        break;

      case EventType::AudioDeviceAdded:
      case EventType::AudioDeviceRemoved:
        mData.emplace<audio_device_event>(mEvent.adevice);
        break;

      case EventType::SensorUpdate:
        mData.emplace<sensor_event>(mEvent.sensor);
        break;

      case EventType::RenderTargetsReset:
      case EventType::RenderDeviceReset:
        break;

      case EventType::User:
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