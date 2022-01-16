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

#include "common.hpp"
#include "detail/tuple_type_index.hpp"
#include "events.hpp"
#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup event
/// \{

/**
 * \brief The main interface for dealing with events.
 */
class event_handler final {
 public:
  /**
   * \brief Creates an empty event handler.
   */
  event_handler() noexcept = default;

  explicit event_handler(const SDL_Event& event) noexcept : mEvent{event}
  {
    update_data(static_cast<EventType>(event.type));
  }

  template <typename T>
  explicit event_handler(const EventBase<T>& event) noexcept : mEvent{AsSDLEvent(event)}
  {
    update_data(event.type());
  }

  /**
   * \brief Updates the event loop, gathering events from the input devices.
   *
   * \note You might not have to call this function by yourself.
   */
  static void update() noexcept { SDL_PumpEvents(); }

  static auto push(event_handler& event) noexcept -> result
  {
    auto& sdlEvent = event.mEvent;
    return SDL_PushEvent(&sdlEvent) >= 0;
  }

  template <typename T>
  static auto push(const EventBase<T>& event) noexcept -> result
  {
    auto sdlEvent = AsSDLEvent(event);
    return SDL_PushEvent(&sdlEvent) >= 0;
  }

  /**
   * \brief Flushes all current events from the event queue.
   */
  static void flush() noexcept { SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT); }

  /**
   * \brief Flushes all of the current events from the event queue, including pending events.
   */
  static void flush_all() noexcept
  {
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
  }

  /**
   * \brief Polls the next available event, if there is one.
   *
   * \return `true` if there are any pending events; `false` otherwise.
   */
  auto poll() noexcept -> bool
  {
    const bool result = SDL_PollEvent(&mEvent);

    if (result) {
      update_data(EventType{mEvent.type});
    }
    else {
      mData.emplace<std::monostate>();
    }

    return result;
  }

  /**
   * \brief Indicates whether the currently stored event is of a particular type.
   *
   * \tparam T the event type to check for.
   *
   * \return `true` if the stored event is of the specified type; `false` otherwise.
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(mData);
  }

  /**
   * \brief Returns the current event representation.
   *
   * \details Use this function if you're certain about the current event type.
   *
   * \details An exception is thrown if there is a mismatch between the requested type and the
   * actual current event type. Use `try_get()` for a non-throwing alternative to this
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

  /// \copydoc get()
  template <typename T>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(mData);
  }

  /**
   * \brief Attempts to return the current event representation.
   *
   * \details This function returns a null pointer if there is a mismatch between the requested
   * type and the current event type.
   *
   * \tparam T the type of the event to obtain.
   *
   * \return a pointer to the internal event type, might be null.
   */
  template <typename T>
  [[nodiscard]] auto try_get() noexcept -> T*
  {
    return std::get_if<T>(&mData);
  }

  /// \copydoc try_get()
  template <typename T>
  [[nodiscard]] auto try_get() const noexcept -> const T*
  {
    return std::get_if<T>(&mData);
  }

  /**
   * \brief Returns the type of the internal event.
   *
   * \return the type of the event;
   *         an empty optional is returned if there is no internal event.
   */
  [[nodiscard]] auto type() const noexcept -> std::optional<EventType>
  {
    if (empty()) {
      return std::nullopt;
    }
    else {
      return EventType{mEvent.type};
    }
  }

  /**
   * \brief Indicates whether there is no internal event.
   *
   * \return `true` if there is no internal event; `false` otherwise.
   */
  [[nodiscard]] auto empty() const noexcept -> bool { return is<std::monostate>(); }

  [[nodiscard]] auto data() const noexcept -> const SDL_Event* { return &mEvent; }

  /**
   * \brief Returns the current amount of events in the event queue.
   *
   * \return the current number of events in the event queue;
   *         an empty optional is returned if something goes wrong.
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
   * \brief Returns the number of events of a particular type that are in the event queue.
   *
   * \param type the type of event to count.
   *
   * \return the current number of events of the specified type that are in the event queue;
   *         an empty optional is returned if something goes wrong.
   */
  [[nodiscard]] static auto queue_count(const EventType type) noexcept -> std::optional<int>
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
   * \brief Indicates whether or not any events of the specified type is in the event queue.
   *
   * \param type the event type to look for in the event queue.
   *
   * \return `true` if there are events of the specified type in the event queue; `false`
   * otherwise.
   */
  [[nodiscard]] static auto in_queue(const EventType type) noexcept -> bool
  {
    return queue_count(type) > 0;
  }

 private:
  /* Behold, the beast! */
  using data_type = std::variant<std::monostate,
                                 AudioDeviceEvent,
                                 ControllerAxisEvent,
                                 ControllerButtonEvent,
                                 ControllerDeviceEvent,
                                 dollar_gesture_event,
                                 DropEvent,
                                 JoyAxisEvent,
                                 JoyBallEvent,
                                 JoyButtonEvent,
                                 JoyDeviceEvent,
                                 JoyHatEvent,
                                 KeyboardEvent,
                                 MouseButtonEvent,
                                 MouseMotionEvent,
                                 MouseWheelEvent,
                                 multi_gesture_event,
                                 quit_event,
                                 text_editing_event,
                                 text_input_event,
                                 touch_finger_event,
                                 sensor_event,
                                 UserEvent,

#if SDL_VERSION_ATLEAST(2, 0, 14)
                                 DisplayEvent,
                                 ControllerTouchpadEvent,
                                 ControllerSensorEvent,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

                                 WindowEvent>;

  SDL_Event mEvent{};
  data_type mData{};

  void update_data(const EventType type) noexcept
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
        mData.emplace<DisplayEvent>(mEvent.display);
        break;
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

      case EventType::Window:
        mData.emplace<WindowEvent>(mEvent.window);
        break;

      case EventType::System:
        break;

      case EventType::KeyDown:
      case EventType::KeyUp:
        mData.emplace<KeyboardEvent>(mEvent.key);
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
        mData.emplace<MouseMotionEvent>(mEvent.motion);
        break;

      case EventType::MouseButtonDown:
      case EventType::MouseButtonUp:
        mData.emplace<MouseButtonEvent>(mEvent.button);
        break;

      case EventType::MouseWheel:
        mData.emplace<MouseWheelEvent>(mEvent.wheel);
        break;

      case EventType::JoyAxisMotion:
        mData.emplace<JoyAxisEvent>(mEvent.jaxis);
        break;

      case EventType::JoyBallMotion:
        mData.emplace<JoyBallEvent>(mEvent.jball);
        break;

      case EventType::JoyHatMotion:
        mData.emplace<JoyHatEvent>(mEvent.jhat);
        break;

      case EventType::JoyButtonDown:
      case EventType::JoyButtonUp:
        mData.emplace<JoyButtonEvent>(mEvent.jbutton);
        break;

      case EventType::JoyDeviceAdded:
      case EventType::JoyDeviceRemoved:
        mData.emplace<JoyDeviceEvent>(mEvent.jdevice);
        break;

      case EventType::ControllerAxisMotion:
        mData.emplace<ControllerAxisEvent>(mEvent.caxis);
        break;

      case EventType::ControllerButtonDown:
      case EventType::ControllerButtonUp:
        mData.emplace<ControllerButtonEvent>(mEvent.cbutton);
        break;

      case EventType::ControllerDeviceAdded:
      case EventType::ControllerDeviceRemoved:
      case EventType::ControllerDeviceRemapped:
        mData.emplace<ControllerDeviceEvent>(mEvent.cdevice);
        break;

#if SDL_VERSION_ATLEAST(2, 0, 14)
      case EventType::ControllerTouchpadDown:
      case EventType::ControllerTouchpadUp:
      case EventType::ControllerTouchpadMotion:
        mData.emplace<ControllerTouchpadEvent>(mEvent.ctouchpad);
        break;

      case EventType::ControllerSensorUpdate:
        mData.emplace<ControllerSensorEvent>(mEvent.csensor);
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
        mData.emplace<DropEvent>(mEvent.drop);
        break;

      case EventType::AudioDeviceAdded:
      case EventType::AudioDeviceRemoved:
        mData.emplace<AudioDeviceEvent>(mEvent.adevice);
        break;

      case EventType::SensorUpdate:
        mData.emplace<sensor_event>(mEvent.sensor);
        break;

      case EventType::RenderTargetsReset:
      case EventType::RenderDeviceReset:
        break;

      case EventType::User:
        mData.emplace<UserEvent>(mEvent.user);
        break;

      default:
        mData.emplace<std::monostate>();
        break;
    }
  }
};

/**
 * \brief Manages a subscription to an event.
 *
 * \details This class is used in the interface of `event_dispatcher`, and isn't meant to be
 * used directly in client code.
 *
 * \tparam E the event type.
 *
 * \see `event_dispatcher`
 */
template <typename E>
class event_sink final {
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
 * \brief An event dispatcher, implemented as wrapper around an `event` instance.
 *
 * \details This class is an attempt to simplify handling events in applications, usually you'd
 * check for all of the events that you'd be interested in using `event::try_get()` in a
 * long `if-else if` statement. By using this class, it's possible to automatically generate
 * equivalent checks by specifying the events that you want to subscribe to, and subsequently
 * connect lambdas, free functions or member functions to handle the subscribed events. This
 * can often lead to cleaner looking code, since the manual checks will be replaced by a
 * single call to `poll()`.
 *
 * \details The runtime overhead of using this class compared to typical manual event
 * dispatching is minimal. However, the function objects for the subscribed events are stored
 * internally, so they can take up a bit of space. It might be beneficial to allocate instances
 * of this class on the heap, depending on the amount of subscribed events.
 *
 * \details The signature of all event handlers should be `void(const Event&)`, where `Event`
 * is the subscribed event type.
 *
 * \note It is advisable to always typedef the signature of this class with the events that you
 * want to handle, since the class name quickly grows in size.
 *
 * \tparam Events the list of events to "subscribe" to, all other events are ignored.
 */
template <typename... Events>
class event_dispatcher final {
  static_assert((!std::is_const_v<Events> && ...));
  static_assert((!std::is_volatile_v<Events> && ...));
  static_assert((!std::is_reference_v<Events> && ...));
  static_assert((!std::is_pointer_v<Events> && ...));

  using sink_tuple = std::tuple<event_sink<Events>...>;

  /// Returns the index of an event type in the function tuple.
  template <typename Event>
  [[nodiscard]] constexpr static auto index_of() -> std::size_t
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
  /**
   * \brief Polls all events, checking for subscribed events.
   */
  void poll()
  {
    while (mEvent.poll()) {
      (check_for<Events>() || ...); /* Use OR to exploit short-circuiting */
    }
  }

  /**
   * \brief Returns the event sink associated with the specified event.
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

  /**
   * \brief Removes all set handlers from all the subscribed events.
   */
  void reset() noexcept { (bind<Events>().reset(), ...); }

  /**
   * \brief Returns the amount of set event handlers.
   *
   * \return the amount of event handlers.
   */
  [[nodiscard]] auto active_count() const -> std::size_t
  {
    return (0u + ... + (get_sink<Events>().function() ? 1u : 0u));
  }

  /**
   * \brief Returns the total number of subscribed events.
   *
   * \return the amount of subscribed events.
   */
  [[nodiscard]] constexpr static auto size() noexcept -> std::size_t
  {
    return sizeof...(Events);
  }

 private:
  cen::event_handler mEvent;
  sink_tuple mSinks;
};

/// \name Event dispatcher functions
/// \{

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

/// \} End of event dispatcher functions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENT_HPP_