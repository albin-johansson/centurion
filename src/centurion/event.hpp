/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_EVENT_HPP_
#define CENTURION_EVENT_HPP_

#include <SDL.h>

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function, bind
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...
#include <utility>      // move
#include <variant>      // variant, holds_alternative, monostate, get, get_if

#include "audio_events.hpp"
#include "common.hpp"
#include "controller_events.hpp"
#include "detail/tuple_type_index.hpp"
#include "event_base.hpp"
#include "features.hpp"
#include "joystick_events.hpp"
#include "misc_events.hpp"
#include "mouse_events.hpp"
#include "window_events.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// The main API for dealing with events.
class event_handler final
{
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

  /// Polls the next available event, if there is one.
  auto poll() noexcept -> bool
  {
    SDL_Event event{};
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

  SDL_Event mEvent{};  // Only needed to support the data member function
  event_type mType{event_type::last_event};
  data_type mData{};

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

/**
 * Manages a subscription to an event.
 *
 * This class is used in the interface of `event_dispatcher`, and isn't meant to be used
 * directly in client code.
 *
 * \tparam E the event type.
 *
 * \see event_dispatcher
 */
template <typename E>
class event_sink final
{
 public:
  using event_type = std::decay_t<E>;              ///< Associated event type.
  using signature_type = void(const event_type&);  ///< Signature of handler.
  using function_type = std::function<signature_type>;

  /// Resets the event sink, removing any associated handler.
  void reset() noexcept { mFunction = nullptr; }

  /// Connects to a function object.
  template <typename T>
  void to(T&& callable)
  {
    static_assert(std::is_invocable_v<T, const event_type&>,
                  "Callable must be invocable with subscribed event!");

    mFunction = function_type{callable};
  }

  /// Connects to a member function.
  template <auto MemberFunc, typename Self>
  void to(Self* self)
  {
    static_assert(std::is_member_function_pointer_v<decltype(MemberFunc)>);
    static_assert(std::is_invocable_v<decltype(MemberFunc), Self*, const event_type&>,
                  "Member function must be invocable with subscribed event!");

    to(std::bind(MemberFunc, self, std::placeholders::_1));
  }

  /// Connects to a free function.
  template <auto Function>
  void to()
  {
    to(Function);
  }

  [[nodiscard]] auto function() -> function_type& { return mFunction; }

  [[nodiscard]] auto function() const -> const function_type& { return mFunction; }

 private:
  function_type mFunction;
};

/**
 * An event dispatcher, implemented as wrapper around an event_handler instance.
 *
 * This class is an attempt to simplify handling events in applications, usually you'd
 * check for all of the events that you'd be interested in using event::try_get in a
 * long "if-else if" statement. By using this class, it's possible to automatically generate
 * equivalent checks by specifying the events that you want to subscribe to, and subsequently
 * connect lambdas, free functions or member functions to handle the subscribed events. This
 * can often lead to cleaner looking code, since the manual checks will be replaced by a
 * single call to the poll function.
 *
 * The runtime overhead of using this class compared to typical manual event dispatching is
 * minimal. However, the function objects for the subscribed events are stored internally, so
 * they can take up a bit of space. It might be beneficial to allocate instances of this class
 * on the heap, if the amount of subscribed events is very large.
 *
 * The signature of all event handlers should be `void(const Event&)`, where Event is the
 * subscribed event type.
 *
 * Note, it is advisable to always typedef the signature of this class with the events that you
 * want to handle, since the class name quickly grows in size.
 *
 * \tparam Events the list of events to "subscribe" to, all other events are ignored.
 */
template <typename... Events>
class event_dispatcher final
{
  static_assert((!std::is_const_v<Events> && ...));
  static_assert((!std::is_volatile_v<Events> && ...));
  static_assert((!std::is_reference_v<Events> && ...));
  static_assert((!std::is_pointer_v<Events> && ...));

  using sink_tuple = std::tuple<event_sink<Events>...>;

  /// Returns the index of an event type in the function tuple.
  template <typename Event>
  [[nodiscard]] constexpr static auto index_of() -> usize
  {
    using sink_type = event_sink<std::decay_t<Event>>;

    constexpr auto index = detail::tuple_type_index_v<sink_type, sink_tuple>;
    static_assert(index != -1, "Invalid event type!");

    return index;
  }

  template <typename Event>
  [[nodiscard]] auto get_sink() -> event_sink<Event>&
  {
    constexpr auto index = index_of<Event>();
    return std::get<index>(mSinks);
  }

  template <typename Event>
  [[nodiscard]] auto get_sink() const -> const event_sink<Event>&
  {
    constexpr auto index = index_of<Event>();
    return std::get<index>(mSinks);
  }

  /// Checks for the specified event type in the event handler, returns true upon a match.
  template <typename Event>
  auto check_for() -> bool
  {
    if (const auto* event = mEvent.template try_get<Event>()) {
      auto& function = get_sink<Event>().function();

      if (function) {
        function(*event);
      }

      return true;
    }
    else {
      return false;
    }
  }

 public:
  /// Polls all events, checking for subscribed events.
  void poll()
  {
    while (mEvent.poll()) {
      (check_for<Events>() || ...); /* Use OR to exploit short-circuiting */
    }
  }

  /**
   * Returns the event sink associated with the specified event.
   *
   * \tparam Event the subscribed event to obtain the event sink for.
   *
   * \return an event sink.
   */
  template <typename Event>
  auto bind() -> event_sink<Event>&
  {
    static_assert((std::is_same_v<std::decay_t<Event>, Events> || ...),
                  "Cannot connect unsubscribed event! Make sure that the "
                  "event is provided as a class template parameter.");
    return get_sink<Event>();
  }

  /// Removes all set handlers from all the subscribed events.
  void reset() noexcept { (bind<Events>().reset(), ...); }

  /// Returns the amount of set event handlers.
  [[nodiscard]] auto active_count() const -> usize
  {
    return (0u + ... + (get_sink<Events>().function() ? 1u : 0u));
  }

  /// Returns the total number of subscribed events.
  [[nodiscard]] constexpr static auto size() noexcept -> usize { return sizeof...(Events); }

 private:
  cen::event_handler mEvent;
  sink_tuple mSinks;
};

template <typename... E>
[[nodiscard]] auto to_string(const event_dispatcher<E...>& dispatcher) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("event_dispatcher(size: {}, #active: {})",
                     dispatcher.size(),
                     dispatcher.active_count());
#else
  return "event_dispatcher(size: " + std::to_string(dispatcher.size()) +
         ", #active: " + std::to_string(dispatcher.active_count()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename... E>
auto operator<<(std::ostream& stream, const event_dispatcher<E...>& dispatcher)
    -> std::ostream&
{
  return stream << to_string(dispatcher);
}

}  // namespace cen

#endif  // CENTURION_EVENT_HPP_