/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_COMMON_EVENT_HEADER
#define CENTURION_COMMON_EVENT_HEADER

#include <type_traits>

#include "centurion_api.h"
#include "event_type.h"

namespace centurion {
namespace event {

/**
 * This is the templated base class of all Centurion events. This class
 * provides the common API of all events and the storage of the SDL2 event.
 *
 * @tparam T the SDL2 event type that the Centurion version represents.
 * @since 4.0.0
 */
template <typename T>
class CommonEvent {
 public:
  /**
   * Creates a CommonEvent and default-initializes the internal event.
   *
   * @since 4.0.0
   */
  CommonEvent() noexcept : m_event{} {}

  /**
   * Creates a CommonEvent and copies the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  explicit CommonEvent(const T& event) : m_event{event} {}

  /**
   * Creates a CommonEvent and moves the contents of the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  explicit CommonEvent(T&& event) : m_event{std::move(event)} {}

  /**
   * Default virtual destructor.
   *
   * @since 4.0.0
   */
  virtual ~CommonEvent() noexcept {}

  /**
   * Sets the timestamp that is associated with the creation of the event.
   *
   * @param timestamp the timestamp that should be associated with the creation
   * of the event.
   * @since 4.0.0
   */
  void set_time(Uint32 timestamp) noexcept { m_event.timestamp = timestamp; }

  /**
   * Sets the event type value associated with the event.
   *
   * @param type the event type value associated with the event.
   * @since 4.0.0
   */
  void set_type(EventType type) noexcept
  {
    m_event.type = static_cast<Uint32>(type);
  }

  /**
   * Returns the timestamp associated with the creation of the event.
   *
   * @return the timestamp associated with the creation of the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD Uint32 time() const noexcept { return m_event.timestamp; }

  /**
   * Returns the event type value associated with the event.
   *
   * @see EventType
   * @return the event type value associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD EventType type() const noexcept
  {
    return static_cast<EventType>(m_event.type);
  }

  /**
   * Implicitly converts the event to a reference to the SDL counterpart.
   *
   * @return a reference to the internal SDL event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD operator T&() noexcept { return m_event; }

  /**
   * Implicitly converts the event to a const reference to the SDL counterpart.
   *
   * @return a const reference to the internal SDL event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD operator const T&() const noexcept { return m_event; }

  /**
   * Implicitly converts the event to its SDL counterpart.
   *
   * @return a copy of the internal SDL event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD operator T() const noexcept { return m_event; }

 protected:
  T m_event{};
};

/**
 * Indicates whether or not a Centurion event type has the properties that is
 * expected of it.
 *
 * @tparam T the Centurion event type that will be checked.
 * @tparam E the SDL event type that the Centurion event is mirroring.
 * @return true if the supplied event type passed the requirements; false
 * otherwise.
 * @since 4.0.0
 */
template <typename T, typename E>
CENTURION_NODISCARD inline constexpr bool validate_event() noexcept
{
  return std::has_virtual_destructor<T>::value &&
         std::is_nothrow_copy_constructible<T>::value &&
         std::is_nothrow_copy_assignable<T>::value &&
         std::is_nothrow_move_constructible<T>::value &&
         std::is_nothrow_move_assignable<T>::value &&
         std::is_nothrow_constructible<T, E>::value
#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
         && !std::is_final<T>::value
#endif  // CENTURION_HAS_IS_FINAL_TYPE_TRAIT
      ;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_COMMON_EVENT_HEADER