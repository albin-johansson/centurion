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

#ifndef CENTURION_EVENTS_EVENT_DISPATCHER_HPP_
#define CENTURION_EVENTS_EVENT_DISPATCHER_HPP_

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <tuple>        // tuple
#include <type_traits>  // decay_t, is_const_v, is_volative_v, is_reference_v, is_pointer_v

#include "../common/primitives.hpp"
#include "../detail/tuple_type_index.hpp"
#include "../features.hpp"
#include "event_handler.hpp"
#include "event_sink.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

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
class event_dispatcher final {
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
  event_handler mEvent;
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

#endif  // CENTURION_EVENTS_EVENT_DISPATCHER_HPP_
