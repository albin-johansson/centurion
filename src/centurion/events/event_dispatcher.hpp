#ifndef CENTURION_EVENTS_EVENT_DISPATCHER_HPP_
#define CENTURION_EVENTS_EVENT_DISPATCHER_HPP_

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function, bind
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...

#include "../common.hpp"
#include "../core/features.hpp"
#include "../detail/tuple_type_index.hpp"
#include "event.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/* Manages a subscription to an event. */
template <typename E>
class EventSink final {
 public:
  using event_type = std::decay_t<E>;              ///< Associated event type.
  using signature_type = void(const event_type&);  ///< Signature of handler.
  using function_type = std::function<signature_type>;

  /* Resets the event sink, removing any associated handler. */
  void Reset() noexcept { mFunction = nullptr; }

  /* Connects to a function object. */
  template <typename T>
  void To(T&& callable)
  {
    static_assert(std::is_invocable_v<T, const event_type&>,
                  "Callable must be invocable with subscribed event!");

    mFunction = function_type{callable};
  }

  /* Connects to a member function. */
  template <auto MemberFunc, typename Self>
  void To(Self* self)
  {
    static_assert(std::is_member_function_pointer_v<decltype(MemberFunc)>);
    static_assert(std::is_invocable_v<decltype(MemberFunc), Self*, const event_type&>,
                  "Member function must be invocable with subscribed event!");

    To(std::bind(MemberFunc, self, std::placeholders::_1));
  }

  /* Connects to a free function. */
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

/**
 * \brief An event dispatcher wrapper around a `cen::event` instance.
 *
 * \details This class is an attempt to simplify handling events in
 * applications, usually you'd check for all of the events that you'd be
 * interested in using `cen::event::try_get()` in a long `if-else if` statement.
 * By using this class, it's possible to automatically generate equivalent
 * checks by specifying the events that you want to subscribe to, and
 * subsequently connect lambdas, free functions or member functions to handle
 * the subscribed events. This can often lead to cleaner looking code, since the
 * manual checks will be replaced by a single call to
 * `event_dispatcher::poll()`.
 *
 * \details The runtime overhead of using this class compared to typical manual
 * event dispatching is minimal. However, the function objects for the
 * subscribed events are stored internally, so they can take up a bit of space.
 * It might be beneficial to allocate instances of this class on the heap,
 * depending on the amount of subscribed events.
 *
 * \details The signature of all event handlers should be `void(const Event&)`,
 * where `Event` is the subscribed event type.
 *
 * \note It is advisable to always typedef the signature of this class with
 * the events that you want to handle, since the class name quickly grows in
 * size.
 *
 * \tparam E the list of events to "subscribe" to. Events that are not present
 * in this list are ignored.
 *
 * \since 5.1.0
 *
 * \see `cen::event`
 */
template <typename... E>
class EventDispatcher final {
  static_assert((!std::is_const_v<E> && ...));
  static_assert((!std::is_volatile_v<E> && ...));
  static_assert((!std::is_reference_v<E> && ...));
  static_assert((!std::is_pointer_v<E> && ...));

  /* Returns the index of an event type in the function tuple. */
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

  /* Checks for the specified event type in the event handler, returns true upon a match. */
  template <typename Event>
  auto CheckFor() -> bool
  {
    if (const auto* event = mEvent.template TryGet<Event>()) {
      if (auto& function = GetSink<Event>().GetFunction()) {
        function(*event);
      }

      return true;
    }
    else {
      return false;
    }
  }

 public:
  /* Polls all events, checking for subscribed events. */
  void Poll()
  {
    while (mEvent.Poll()) {
      (CheckFor<E>() || ...); /* Use OR to exploit short-circuiting */
    }
  }

  /* Returns the event sink associated with the specified event. */
  template <typename Event>
  auto Bind() -> EventSink<Event>&
  {
    static_assert((std::is_same_v<std::decay_t<Event>, E> || ...),
                  "Cannot connect unsubscribed event! Make sure that the "
                  "event is provided as a class template parameter.");
    return GetSink<Event>();
  }

  /* Removes all set handlers from all the subscribed events. */
  void Reset() noexcept { (Bind<E>().Reset(), ...); }

  /* Returns the amount of set event handlers. */
  [[nodiscard]] auto GetActiveCount() const -> std::size_t
  {
    return (0u + ... + (GetSink<E>().GetFunction() ? 1u : 0u));
  }

  /* Returns the number of subscribed events. */
  [[nodiscard]] constexpr static auto GetSize() noexcept -> std::size_t
  {
    return sizeof...(E);
  }

 private:
  using sink_tuple = std::tuple<EventSink<E>...>;

  cen::Event mEvent;
  sink_tuple mSinks;
};

template <typename... E>
[[nodiscard]] inline auto to_string(const EventDispatcher<E...>& dispatcher) -> std::string
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
inline auto operator<<(std::ostream& stream, const EventDispatcher<E...>& dispatcher)
    -> std::ostream&
{
  return stream << to_string(dispatcher);
}

}  // namespace cen

#endif  // CENTURION_EVENT_DISPATCHER_HEADER