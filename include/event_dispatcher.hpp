#pragma once

#include <array>        // array
#include <cstddef>      // size_t
#include <functional>   // function
#include <tuple>        // tuple
#include <type_traits>  // is_same_v, is_invocable_v, is_reference_v, ...
#include <utility>      // index_sequence_for, index_sequence

#include "event.hpp"

namespace cen::experimental {

template <typename Target, typename Tuple>
class index_for_type;

template <typename Target, typename... T>
class index_for_type<Target, std::tuple<T...>>
{
  template <std::size_t... index>
  static constexpr int find(std::index_sequence<index...>)
  {
    return -1 + ((std::is_same_v<Target, T> ? index + 1 : 0) + ...);
  }

 public:
  inline static constexpr auto value = find(std::index_sequence_for<T...>{});
};

template <typename Target, typename... T>
inline constexpr int index_for_type_v = index_for_type<Target, T...>::value;

template <typename... E>
class event_dispatcher final
{
  //  template <typename T, T... Index>
  //  void visit(std::integer_sequence<T, Index...> sequence)
  //  {
  //    std::cout << "Visiting sequence: ";
  //    ((std::cout << "{" << Index << ", " << typeid(T).name() << "}, "), ...);
  //    std::cout << '\n';
  //  }

  template <typename Event>
  [[nodiscard]] constexpr static auto type_index()
  {
    using func_t = std::function<void(const Event&)>;

    constexpr auto index = index_for_type_v<func_t, functions_t>;
    static_assert(index != -1);

    return index;
  }

  template <typename Event>
  auto check_for() -> bool
  {
    if (const auto* e = m_event.template try_get<Event>()) {
      //      using func_t = std::function<void(const Event&)>;
      //      using func_t = void(const Event&);
      //      constexpr auto index = index_for_type<func_t, functions_t>::value;
      //      static_assert(index != -1);

      constexpr auto index = type_index<Event>();

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

    constexpr auto index = type_index<Event>();

    auto& func = std::get<index>(m_functions);
    func = std::function<void(const Event&)>(callable);
  }

 private:
//  inline constexpr static std::index_sequence_for<E...> m_indices;
  using functions_t = std::tuple<std::function<void(const E&)>...>;

  cen::event m_event;
  functions_t m_functions;
};

}  // namespace cen::experimental
