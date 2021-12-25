#ifndef CENTURION_EVENT_HPP_
#define CENTURION_EVENT_HPP_

#include <SDL.h>

#include <optional>     // optional
#include <utility>      // move
#include <variant>      // variant, holds_alternative, monostate, get, get_if
#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function, bind
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...

#include "common.hpp"
#include "events.hpp"
#include "features.hpp"
#include "detail/tuple_type_index.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

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
  explicit Event(const EventBase<T>& event) noexcept : mEvent{AsSDLEvent(event)}
  {
    UpdateData(event.type());
  }

  /// Updates the event loop, gathering events from the input devices.
  static void Update() noexcept { SDL_PumpEvents(); }

  static auto Push(Event& event) noexcept -> Result
  {
    auto& sdlEvent = event.mEvent;
    return SDL_PushEvent(&sdlEvent) >= 0;
  }

  template <typename T>
  static auto Push(const EventBase<T>& event) noexcept -> Result
  {
    auto sdlEvent = AsSDLEvent(event);
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
  /// \return `true` if there are pending events; `false` otherwise.
  auto Poll() noexcept -> bool
  {
    const bool result = SDL_PollEvent(&mEvent);

    if (result) {
      UpdateData(EventType{mEvent.type});
    }
    else {
      mData.emplace<std::monostate>();
    }

    return result;
  }

  /// Returns the type of the current event, if there is one.
  [[nodiscard]] auto GetType() const noexcept -> std::optional<EventType>
  {
    if (IsEmpty()) {
      return std::nullopt;
    }
    else {
      return EventType{mEvent.type};
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

/// Manages a subscription to an event.
template <typename E>
class EventSink final {
 public:
  using event_type = std::decay_t<E>;              ///< Associated event type.
  using signature_type = void(const event_type&);  ///< Signature of handler.
  using function_type = std::function<signature_type>;

  /// Resets the event sink, removing any associated handler.
  void Reset() noexcept { mFunction = nullptr; }

  /// Connects to a function object.
  template <typename T>
  void To(T&& callable)
  {
    static_assert(std::is_invocable_v<T, const event_type&>,
                  "Callable must be invocable with subscribed event!");

    mFunction = function_type{callable};
  }

  /// Connects to a member function.
  template <auto MemberFunc, typename Self>
  void To(Self* self)
  {
    static_assert(std::is_member_function_pointer_v<decltype(MemberFunc)>);
    static_assert(std::is_invocable_v<decltype(MemberFunc), Self*, const event_type&>,
                  "Member function must be invocable with subscribed event!");

    To(std::bind(MemberFunc, self, std::placeholders::_1));
  }

  /// Connects to a free function.
  template <auto Function>
  void To()
  {
    To(Function);
  }

  [[nodiscard]] auto GetFunction() -> function_type& { return mFunction; }
  [[nodiscard]] auto GetFunction() const -> const function_type& { return mFunction; }

 private:
  function_type mFunction;
};

/// An event dispatcher, implemented as wrapper of an `Event` instance.
///
/// This class is an attempt to simplify handling events in applications, usually you'd check
/// for all of the events that you'd be interested in using `cen::Event::TryGet()` in a long
/// `if-else if` statement. By using this class, it's possible to automatically generate
/// equivalent checks by specifying the events that you want to subscribe to, and subsequently
/// connect lambdas, free functions or member functions to handle the subscribed events. This
/// can often lead to cleaner looking code, since the manual checks will be replaced by a
/// single call to `EventDispatcher::Poll()`.
///
/// The runtime overhead of using this class compared to typical manual event dispatching is
/// minimal. However, the function objects for the subscribed events are stored internally, so
/// they can take up a bit of space. It might be beneficial to allocate instances of this class
/// on the heap, depending on the amount of subscribed events.
///
/// The signature of all event handlers should be `void(const Event&)`, where `Event` is the
/// subscribed event type.
///
/// Note, it is advisable to always typedef the signature of this class with the events that
/// you want to handle, since the class name quickly grows in size.
///
/// \tparam Events the list of events to "subscribe" to, all other events are ignored.
template <typename... Events>
class EventDispatcher final {
  static_assert((!std::is_const_v<Events> && ...));
  static_assert((!std::is_volatile_v<Events> && ...));
  static_assert((!std::is_reference_v<Events> && ...));
  static_assert((!std::is_pointer_v<Events> && ...));

  using sink_tuple = std::tuple<EventSink<Events>...>;

  /// Returns the index of an event type in the function tuple.
  template <typename Event>
  [[nodiscard]] constexpr static auto IndexOf() -> std::size_t
  {
    using sink_type = EventSink<std::decay_t<Event>>;

    constexpr auto index = detail::tuple_type_index_v<sink_type, sink_tuple>;
    static_assert(index != -1, "Invalid event type!");

    return index;
  }

  template <typename Event>
  [[nodiscard]] auto GetSink() -> EventSink<Event>&
  {
    constexpr auto index = IndexOf<Event>();
    return std::get<index>(mSinks);
  }

  template <typename Event>
  [[nodiscard]] auto GetSink() const -> const EventSink<Event>&
  {
    constexpr auto index = IndexOf<Event>();
    return std::get<index>(mSinks);
  }

  /// Checks for the specified event type in the event handler, returns true upon a match.
  template <typename Event>
  auto CheckFor() -> bool
  {
    if (const auto* event = mEvent.template TryGet<Event>()) {
      auto& function = GetSink<Event>().GetFunction();

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
  void Poll()
  {
    while (mEvent.Poll()) {
      (CheckFor<Events>() || ...); /* Use OR to exploit short-circuiting */
    }
  }

  /// Returns the event sink associated with the specified event.
  template <typename Event>
  auto Bind() -> EventSink<Event>&
  {
    static_assert((std::is_same_v<std::decay_t<Event>, Events> || ...),
                  "Cannot connect unsubscribed event! Make sure that the "
                  "event is provided as a class template parameter.");
    return GetSink<Event>();
  }

  /// Removes all set handlers from all the subscribed events.
  void Reset() noexcept { (Bind<Events>().Reset(), ...); }

  /// Returns the amount of set event handlers.
  [[nodiscard]] auto GetActiveCount() const -> std::size_t
  {
    return (0u + ... + (GetSink<Events>().GetFunction() ? 1u : 0u));
  }

  /// Returns the number of subscribed events.
  [[nodiscard]] constexpr static auto GetSize() noexcept -> std::size_t
  {
    return sizeof...(Events);
  }

 private:
  cen::Event mEvent;
  sink_tuple mSinks;
};

template <typename... E>
[[nodiscard]] auto to_string(const EventDispatcher<E...>& dispatcher) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("EventDispatcher(size: {}, #active: {})",
                     dispatcher.GetSize(),
                     dispatcher.GetActiveCount());
#else
  return "EventDispatcher(size: " + std::to_string(dispatcher.GetSize()) +
         ", #active: " + std::to_string(dispatcher.GetActiveCount()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename... E>
auto operator<<(std::ostream& stream, const EventDispatcher<E...>& dispatcher) -> std::ostream&
{
  return stream << to_string(dispatcher);
}

}  // namespace cen

#endif  // CENTURION_EVENT_HPP_