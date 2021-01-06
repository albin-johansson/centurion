#pragma once

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function, bind
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...

#include "detail/tuple_type_index.hpp"
#include "event.hpp"

namespace cen::experimental {

/// \addtogroup event
/// \{

/**
 * \brief Manages a subscription to an event.
 *
 * \tparam E the event type, e.g. `window_event`.
 *
 * \headerfile event_dispatcher.hpp
 *
 * \see `event_dispatcher`
 *
 * \since 5.1.0
 */
template <typename E>
class event_sink final
{
 public:
  using event_type = std::decay_t<E>;              ///< Associated event type.
  using signature_type = void(const event_type&);  ///< Signature of handler.

  /**
   * \brief Resets the event sink, removing any associated handler.
   *
   * \since 5.1.0
   */
  void reset() noexcept
  {
    m_function = nullptr;
  }

  /**
   * \brief Connects to a function object.
   *
   * \note This function will overwrite any previously set handler.
   *
   * \tparam T the type of the function object.
   *
   * \param callable the callable that will be invoked when an event is
   * received.
   *
   * \since 5.1.0
   */
  template <typename T>
  void bind(T&& callable)
  {
    static_assert(std::is_invocable_v<T, const event_type&>,
                  "Callable must be invocable with subscribed event!");

    m_function = std::function<signature_type>{callable};
  }

  /**
   * \brief Connects to a member function.
   *
   * \note The event sink does *not* take ownership of the supplied pointer.
   *
   * \note This function will overwrite any previously set handler.
   *
   * \tparam memberFunction a pointer to a member function.
   * \tparam Self the type of the object that owns the function.
   *
   * \param self a pointer to the object that will handle the event.
   *
   * \since 5.1.0
   */
  template <auto memberFunc, typename Self>
  void bind(Self* self)
  {
    static_assert(std::is_member_function_pointer_v<decltype(memberFunc)>,
                  "\"memberFunc\" must be member function pointer!");
    static_assert(
        std::is_invocable_v<decltype(memberFunc), Self*, const event_type&>,
        "Member function must be invocable with subscribed event!");

    bind(std::bind(memberFunc, self, std::placeholders::_1));
  }

  /**
   * \brief Connects to a free function.
   *
   * \note This function will overwrite any previously set handler.
   *
   * \tparam function a function pointer.
   *
   * \since 5.1.0
   */
  template <auto function>
  void bind()
  {
    bind(function);
  }

  /**
   * \brief Returns the function associated with the sink.
   *
   * \return the function associated with the sink, might be invalid.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto function() -> std::function<signature_type>&
  {
    return m_function;
  }

 private:
  std::function<signature_type> m_function;
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
 *
 * \headerfile event_dispatcher.hpp
 */
template <typename... E>
class event_dispatcher final
{
  static_assert((!std::is_const_v<E>, ...),
                "Can't use \"const\" on template parameter!");

  static_assert((!std::is_volatile_v<E>, ...),
                "Can't use \"volatile\" on template parameter!");

  static_assert((!std::is_reference_v<E>, ...),
                "Reference types can't be used as template parameters!");

  static_assert((!std::is_pointer_v<E>, ...),
                "Pointer types can't be used as template parameters!");

  /**
   * \brief Returns the index of an event type in the function tuple.
   *
   * \tparam Event the event type.
   *
   * \return the index of the event type.
   *
   * \since 5.1.0
   */
  template <typename Event>
  [[nodiscard]] constexpr static auto index_of()
  {
    using sink_t = event_sink<Event>;

    constexpr auto index = detail::tuple_type_index_v<sink_t, sink_tuple>;
    static_assert(index != -1);

    return index;
  }

  /**
   * \brief Checks for the specified event type in the event handler.
   *
   * \tparam Event the event to look for.
   *
   * \return `true` if there was a match; `false` otherwise.
   *
   * \since 5.1.0
   */
  template <typename Event>
  auto check_for() -> bool
  {
    if (const auto* e = m_event.template try_get<Event>()) {
      constexpr auto index = index_of<Event>();

      if (auto& func = std::get<index>(m_sinks).function()) {
        func(*e);
      }

      return true;
    } else {
      return false;
    }
  }

 public:
  /**
   * \brief Polls all events, checking for subscribed events.
   *
   * \details This function corresponds to the usual inner event `while`-loop
   * used to manage events. You should call this function once for every
   * iteration in your game loop.
   *
   * \since 5.1.0
   */
  void poll()
  {
    while (m_event.poll()) {
      (check_for<E>() || ...);
    }
  }

  /**
   * \brief Returns the event sink associated with the specified event.
   *
   * \tparam Event the subscribed event to obtain the event sink for. This
   * function will not accept an event type that isn't one of the subscribed
   * events (i.e. on of the class template arguments).
   *
   * \return the associated event sink.
   *
   * \since 5.1.0
   */
  template <typename Event>
  auto on() -> event_sink<Event>&
  {
    using event_t = std::decay_t<Event>;

    static_assert(((std::is_same_v<event_t, E>) || ...),
                  "Cannot connect unsubscribed event! Make sure that the "
                  "event is listed as a class template parameter.");

    constexpr auto index = index_of<event_t>();
    static_assert(index != -1);

    return std::get<index>(m_sinks);
  }

  /**
   * \brief Removes all set handlers from all of the subscribed events.
   *
   * \since 5.1.0
   */
  void reset() noexcept
  {
    (on<E>().reset(), ...);
  }

  /**
   * \brief Removes any set handler from the specified subscribed event.
   *
   * \tparam Event the subscribed event to reset the handler for.
   *
   * \since 5.1.0
   */
  template <typename Event>
  void reset() noexcept
  {
    on<Event>().reset();
  }

  /**
   * \brief Connects a function object to a subscribed event.
   *
   * \note This will overwrite any previously set handler for the event.
   *
   * \remarks This is a convenience function that calls `on()`
   * behind-the-scenes.
   *
   * \tparam Event the subscribed event type. Must be present in the class
   * template argument list.
   * \tparam T the type of the function object.
   *
   * \param callable the function object that will handle the event.
   *
   * \since 5.1.0
   */
  template <typename Event, typename T>
  void bind(T&& callable)
  {
    on<Event>().template bind<T>(std::forward<T>(callable));
  }

  /**
   * \brief Connects a member function to a subscribed event.
   *
   * \note This will overwrite any previously set handler for the event.
   *
   * \note The event sink does *not* take ownership of the supplied pointer.
   *
   * \remarks This is a convenience function that calls `on()`
   * behind-the-scenes.
   *
   * \tparam Event the subscribed event type. Must be present in the class
   * template argument list.
   * \tparam memberFunc the member function pointer.
   * \tparam Self the type of the object that features the member function.
   *
   * \param self a pointer to the instance that will handle the event.
   *
   * \since 5.1.0
   */
  template <typename Event, auto memberFunc, typename Self>
  void bind(Self* self)
  {
    on<Event>().template bind<memberFunc>(self);
  }

  /**
   * \brief Connects a free function to a subscribed event.
   *
   * \note This will overwrite any previously set handler for the event.
   *
   * \remarks This is a convenience function that calls `on()`
   * behind-the-scenes.
   *
   * \tparam Event the subscribed event type. Must be present in the class
   * template argument list.
   * \tparam function a function pointer.
   *
   * \since 5.1.0
   */
  template <typename Event, auto func>
  void bind()
  {
    on<Event>().template bind<func>();
  }

 private:
  using sink_tuple = std::tuple<event_sink<E>...>;

  cen::event m_event;
  sink_tuple m_sinks;
};

/// \}

}  // namespace cen::experimental
