#ifndef CENTURION_EVENT_HEADER
#define CENTURION_EVENT_HEADER

#include <SDL.h>

#include <optional>  // optional
#include <utility>   // move
#include <variant>   // variant, holds_alternative, monostate, get, get_if

#include "../core/result.hpp"
#include "../core/to_underlying.hpp"
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

/// \addtogroup event
/// \{

/**
 * \class event
 *
 * \brief Serves as the main interface for dealing with events.
 *
 * \see `SDL_Event`
 *
 * \since 4.0.0
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
  explicit event(const common_event<T>& event) noexcept : m_event{as_sdl_event(event)}
  {
    update_data(event.type());
  }

  /**
   * \brief Updates the event loop, gathering events from the input devices.
   *
   * \note You might not have to call this function by yourself.
   *
   * \see `SDL_PumpEvents`
   *
   * \since 3.1.0
   */
  static void update() noexcept
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
   * \return `success` if the event was successfully added; `failure` otherwise.
   *
   * \since 5.1.0
   */
  template <typename T>
  static auto push(const common_event<T>& event) noexcept -> result
  {
    auto sdlEvent = as_sdl_event(event);
    return SDL_PushEvent(&sdlEvent) >= 0;
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
    }
    else {
      m_data.emplace<std::monostate>();
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
    }
    else {
      return static_cast<event_type>(m_event.type);
    }
  }

  /**
   * \brief Returns the current amount of events in the event queue.
   *
   * \return the current number of events in the event queue; `std::nullopt`
   * if something goes wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] static auto queue_count() noexcept -> std::optional<int>
  {
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    if (num != -1) {
      return num;
    }
    else {
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
   * \since 5.3.0
   */
  [[nodiscard]] static auto queue_count(const event_type type) noexcept -> std::optional<int>
  {
    const auto id = to_underlying(type);
    const auto num = SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, id, id);
    if (num != -1) {
      return num;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether or not any events of the specified type is in the
   * event queue.
   *
   * \param type the event type to look for in the event queue.
   *
   * \return `true` if there are events of the specified type in the event
   * queue; `false` otherwise.
   *
   * \since 5.3.0
   */
  [[nodiscard]] static auto in_queue(const event_type type) noexcept -> bool
  {
    return queue_count(type) > 0;
  }

  /**
   * \brief Indicates whether or not the event is of a particular type.
   *
   * \details This function is useful for checking the event type before
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
   * function to simply extract the internal event.
   *
   * \note This functions throws if the internal event isn't of the specified
   * type! You might want to make sure that the internal type is `T` with the
   * `is()` function before calling this function, or use `try_get()`.
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
   * \brief Returns a pointer to the internal event representation.
   *
   * \return a pointer to the internal event instance.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto data() const noexcept -> const SDL_Event*
  {
    return &m_event;
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

  SDL_Event m_event{};
  data_type m_data{};

  void update_data(const event_type type) noexcept
  {
    switch (type) {
      case event_type::quit:
        m_data.emplace<quit_event>(m_event.quit);
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
        m_data.emplace<display_event>(m_event.display);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case event_type::window:
        m_data.emplace<window_event>(m_event.window);
        break;

      case event_type::system:
        break;

      case event_type::key_down:
      case event_type::key_up:
        m_data.emplace<keyboard_event>(m_event.key);
        break;

      case event_type::text_editing:
        m_data.emplace<text_editing_event>(m_event.edit);
        break;

      case event_type::text_input:
        m_data.emplace<text_input_event>(m_event.text);
        break;

      case event_type::keymap_changed:
        break;

      case event_type::mouse_motion:
        m_data.emplace<mouse_motion_event>(m_event.motion);
        break;

      case event_type::mouse_button_down:
      case event_type::mouse_button_up:
        m_data.emplace<mouse_button_event>(m_event.button);
        break;

      case event_type::mouse_wheel:
        m_data.emplace<mouse_wheel_event>(m_event.wheel);
        break;

      case event_type::joystick_axis_motion:
        m_data.emplace<joy_axis_event>(m_event.jaxis);
        break;

      case event_type::joystick_ball_motion:
        m_data.emplace<joy_ball_event>(m_event.jball);
        break;

      case event_type::joystick_hat_motion:
        m_data.emplace<joy_hat_event>(m_event.jhat);
        break;

      case event_type::joystick_button_down:
      case event_type::joystick_button_up:
        m_data.emplace<joy_button_event>(m_event.jbutton);
        break;

      case event_type::joystick_device_added:
      case event_type::joystick_device_removed:
        m_data.emplace<joy_device_event>(m_event.jdevice);
        break;

      case event_type::controller_axis_motion:
        m_data.emplace<controller_axis_event>(m_event.caxis);
        break;

      case event_type::controller_button_down:
      case event_type::controller_button_up:
        m_data.emplace<controller_button_event>(m_event.cbutton);
        break;

      case event_type::controller_device_added:
      case event_type::controller_device_removed:
      case event_type::controller_device_remapped:
        m_data.emplace<controller_device_event>(m_event.cdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case event_type::controller_touchpad_down:
      case event_type::controller_touchpad_up:
      case event_type::controller_touchpad_motion:
        m_data.emplace<controller_touchpad_event>(m_event.ctouchpad);
        break;

      case event_type::controller_sensor_update:
        m_data.emplace<controller_sensor_event>(m_event.csensor);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case event_type::touch_down:
      case event_type::touch_up:
      case event_type::touch_motion:
        m_data.emplace<touch_finger_event>(m_event.tfinger);
        break;

      case event_type::dollar_gesture:
      case event_type::dollar_record:
        m_data.emplace<dollar_gesture_event>(m_event.dgesture);
        break;

      case event_type::multi_gesture:
        m_data.emplace<multi_gesture_event>(m_event.mgesture);
        break;

      case event_type::clipboard_update:
        break;

      case event_type::drop_file:
      case event_type::drop_text:
      case event_type::drop_begin:
      case event_type::drop_complete:
        m_data.emplace<drop_event>(m_event.drop);
        break;

      case event_type::audio_device_added:
      case event_type::audio_device_removed:
        m_data.emplace<audio_device_event>(m_event.adevice);
        break;

      case event_type::sensor_update:
        m_data.emplace<sensor_event>(m_event.sensor);
        break;

      case event_type::render_targets_reset:
      case event_type::render_device_reset:
        break;

      case event_type::user:
        m_data.emplace<user_event>(m_event.user);
        break;

      default:
        m_data.emplace<std::monostate>();
        break;
    }
  }
};

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENT_HEADER