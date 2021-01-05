#pragma once

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function
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
 * interested in using `cen::event::try_get()` in a long `if-else` statement. By
 * using this class, it's possible to automatically generate equivalent checks
 * by specifying the events that you want to subscribe to, and subsequently
 * connect lambdas, free functions or member functions to handle the
 * subscribed events. This can often lead to cleaner looking code, since the
 * manual checks will be replaced by a single call to
 * `event_dispatcher::update()`.
 *
 * \details The runtime overhead of using this class compared to typical manual
 * event dispatching is minimal. However, the function objects for the
 * subscribed events are stored internally, so they can take up a bit of space.
 * It might be beneficial to allocate instances of this class on the heap,
 * depending on the amount of subscribed events.
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

  template <typename Event>
  [[nodiscard]] constexpr static auto index_of()
  {
    using func_t = std::function<void(const Event&)>;

    constexpr auto index = detail::tuple_type_index_v<func_t, function_tuple>;
    static_assert(index != -1);

    return index;
  }

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
  void update()
  {
    while (m_event.poll()) {
      (check_for<E>() || ...);
    }
  }

  template <typename Event, typename T>
  void on(T&& callable)
  {
    static_assert(!std::is_reference_v<Event>,
                  "\"Event\" can't be reference type!");

    static_assert(!std::is_pointer_v<Event>,
                  "\"Event\" can't be pointer type!");

    static_assert(((std::is_same_v<Event, E>) || ...),
                  "Cannot subscribe to unknown event type! Make sure that the "
                  "event is listed as a class template parameter.");

    static_assert(std::is_invocable_v<T, const Event&>,
                  "Function object must be invocable with specified event!");

    constexpr auto index = index_of<Event>();
    std::get<index>(m_functions) = std::function<void(const Event&)>(callable);
  }

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

  template <typename Event, auto fn>
  void on()
  {
    on<Event>(fn);
  }

 private:
  using function_tuple = std::tuple<std::function<void(const E&)>...>;

  cen::event m_event;
  function_tuple m_functions;
};

/// \}

}  // namespace cen::experimental
