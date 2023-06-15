/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_EVENTS_EVENT_SINK_HPP_
#define CENTURION_EVENTS_EVENT_SINK_HPP_

#include <functional>   // function, bind, placeholders
#include <type_traits>  // decay_t, is_invocable_v, is_member_function_pointer_v

namespace cen {

/**
 * Manages a subscription to an event.
 *
 * \details This class is used in the interface of `event_dispatcher`, and isn't meant to be
 *          used directly in client code.
 *
 * \tparam E the event type.
 *
 * \see event_dispatcher
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

    mFunction = function_type {callable};
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

}  // namespace cen

#endif  // CENTURION_EVENTS_EVENT_SINK_HPP_
