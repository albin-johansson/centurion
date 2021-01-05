#pragma once

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...

#include "detail/tuple_type_index.hpp"
#include "event.hpp"

namespace cen::experimental {

template <typename... E>
class event_dispatcher final
{
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

  template <typename... Event>
  void check_all()
  {
    // TODO Could take bool NTTP that dictates the short-circuit behaviour
    /*
      if constexpr (shortCircuit) {
        (check_for<Event>() || ...);
      } else {
        (check_for<Event>(), ...);
      }
     */

    (check_for<Event>() || ...);
  }

 public:
  void update()
  {
    while (m_event.poll()) {
      check_all<E...>();
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

 private:
  using function_tuple = std::tuple<std::function<void(const E&)>...>;

  cen::event m_event;
  function_tuple m_functions;
};

}  // namespace cen::experimental
