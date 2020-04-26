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

#ifndef CENTURION_BASE_EVENT_HEADER
#define CENTURION_BASE_EVENT_HEADER

#include "centurion_api.h"

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
class TEvent {
 public:
  /**
   * Creates a TEvent and default-initializes the internal event.
   *
   * @since 4.0.0
   */
  TEvent() noexcept : m_event{} {}

  /**
   * Creates a TEvent and copies the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  explicit TEvent(const T& event) : m_event{event} {}

  /**
   * Creates a TEvent and moves the contents of the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  explicit TEvent(T&& event) : m_event{std::move(event)} {}

  /**
   * Default virtual destructor.
   *
   * @since 4.0.0
   */
  virtual ~TEvent() noexcept {};

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD uint32_t window_id() const noexcept
  {
    return m_event.windowID;
  }

  /**
   * Returns the timestamp associated with the creation of the event.
   *
   * @return the timestamp associated with the creation of the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD uint32_t time() const noexcept
  {
    return m_event.timestamp;
  }

 protected:
  T m_event;
};

}
}

#endif // CENTURION_BASE_EVENT_HEADER