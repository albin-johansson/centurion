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
  template <typename T>
  using strip_type = std::remove_cv_t<std::remove_reference_t<T>>;

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
    using func_t = std::function<void(const Event&)>;

    constexpr auto index = detail::tuple_type_index_v<func_t, function_tuple>;
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

      if (auto func = std::get<index>(m_functions)) {
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
   * \brief Connects an event to a function object.
   *
   * \note This function will overwrite any previously set handler for the
   * specified event type.
   *
   * \tparam Event the event that will be handled by the function object.
   * \tparam T the type of the function object.
   *
   * \param callable the callable that will be invoked when an event of the
   * specified type is received.
   *
   * \since 5.1.0
   */
  template <typename Event, typename T>
  void on(T&& callable)
  {
    static_assert(!std::is_reference_v<Event>,
                  "\"Event\" template parameter can't be reference type!");

    static_assert(!std::is_pointer_v<Event>,
                  "\"Event\" template parameter can't be pointer type!");

    static_assert(!std::is_volatile_v<Event>,
                  "\"Event\" template parameter can't be marked as volatile!");

    static_assert(!std::is_const_v<Event>,
                  "\"Event\" template parameter can't be marked as const!");

    static_assert(((std::is_same_v<Event, E>) || ...),
                  "Cannot connect to unsubscribed event! Make sure that the "
                  "event is listed as a class template parameter.");

    static_assert(std::is_invocable_v<T, const Event&>,
                  "Function object must be invocable with subscribed event!");

    constexpr auto index = index_of<Event>();
    std::get<index>(m_functions) = std::function<void(const Event&)>(callable);
  }

  /**
   * \brief Connects an event to a member function.
   *
   * \note The event dispatcher does *not* take ownership of the supplied
   * pointer.
   *
   * \note This function will overwrite any previously set handler for the
   * specified event type.
   *
   * \tparam Event the event that will be handled by the object.
   * \tparam memFun a pointer to a member function.
   * \tparam Self the type of the object that owns the function.
   *
   * \param self a pointer to the object that will handle the event.
   *
   * \since 5.1.0
   */
  template <typename Event, auto memFun, typename Self>
  void on(Self* self)
  {
    using mem_fun_t = std::decay_t<decltype(memFun)>;
    using event_t = strip_type<Event>;
    using self_t = strip_type<Self>;

    static_assert(std::is_member_function_pointer_v<mem_fun_t>,
                  "\"memFun\" must be a pointer to a member function!");

    static_assert(
        std::is_invocable_v<mem_fun_t, self_t*, const event_t&>,
        "\"memFun\" must be invocable with object pointer and event!");

    on<event_t>(std::bind(memFun, self, std::placeholders::_1));
  }

  /**
   * \brief Connects an event to a free function.
   *
   * \note This function will overwrite any previously set handler for the
   * specified event type.
   *
   * \tparam Event the event that will be handled by the function pointer.
   * \tparam function a function pointer.
   *
   * \since 5.1.0
   */
  template <typename Event, auto function>
  void on()
  {
    on<Event>(function);
  }

 private:
  using function_tuple = std::tuple<std::function<void(const E&)>...>;

  cen::event m_event;
  function_tuple m_functions;
};

/// \}

}  // namespace cen::experimental
