/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_EVENTS_EVENT_BASE_HPP_
#define CENTURION_EVENTS_EVENT_BASE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view
#include <utility>      // move

#include "../common.hpp"
#include "event_type.hpp"

namespace cen {

/// The base class of all events.
template <typename T>
class event_base {
 public:
  explicit event_base(const event_type type)
  {
    set_timestamp(u32ms {SDL_GetTicks()});
    set_type(type);
  }

  explicit event_base(const T& event) noexcept : mEvent {event} {}

  explicit event_base(T&& event) noexcept : mEvent {std::move(event)} {}

  void set_timestamp(const u32ms timestamp) noexcept(on_msvc)
  {
    mEvent.timestamp = timestamp.count();
  }

  void set_type(const event_type type) noexcept { mEvent.type = to_underlying(type); }

  [[nodiscard]] auto timestamp() const -> u32ms { return u32ms {mEvent.timestamp}; }

  [[nodiscard]] auto type() const noexcept -> event_type { return event_type {mEvent.type}; }

  [[nodiscard]] auto get() const noexcept -> const T& { return mEvent; }

 protected:
  T mEvent {};
};

/// Extracts the underlying SDL event from a Centurion event.
template <typename T>
[[nodiscard]] auto as_sdl_event(const event_base<T>& event) -> SDL_Event;

}  // namespace cen

#endif  // CENTURION_EVENTS_EVENT_BASE_HPP_
