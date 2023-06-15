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

#ifndef CENTURION_EVENTS_MOUSE_EVENTS_HPP_
#define CENTURION_EVENTS_MOUSE_EVENTS_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common/errors.hpp"
#include "../common/primitives.hpp"
#include "../input/button_state.hpp"
#include "../input/mouse.hpp"
#include "event_base.hpp"

namespace cen {

enum class mouse_wheel_direction : uint32 {
  normal = SDL_MOUSEWHEEL_NORMAL,
  flipped = SDL_MOUSEWHEEL_FLIPPED
};

[[nodiscard]] constexpr auto to_string(const mouse_wheel_direction dir) -> std::string_view
{
  switch (dir) {
    case mouse_wheel_direction::normal:
      return "normal";

    case mouse_wheel_direction::flipped:
      return "flipped";

    default:
      throw exception {"Did not recognize mouse wheel direction!"};
  }
}

inline auto operator<<(std::ostream& stream, const mouse_wheel_direction dir) -> std::ostream&
{
  return stream << to_string(dir);
}

class mouse_button_event final : public event_base<SDL_MouseButtonEvent> {
 public:
  mouse_button_event() : event_base {event_type::mouse_button_down} {}

  explicit mouse_button_event(const SDL_MouseButtonEvent& event) noexcept : event_base {event}
  {
  }

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  void set_which(const uint32 which) noexcept { mEvent.which = which; }

  void set_button(const mouse_button button) noexcept
  {
    mEvent.button = to_underlying(button);
  }

  void set_state(const button_state state) noexcept { mEvent.state = to_underlying(state); }

  void set_clicks(const uint8 clicks) noexcept { mEvent.clicks = clicks; }

  void set_x(const int32 x) noexcept { mEvent.x = x; }
  void set_y(const int32 y) noexcept { mEvent.y = y; }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto which() const noexcept -> uint32 { return mEvent.which; }

  [[nodiscard]] auto button() const noexcept -> mouse_button
  {
    return static_cast<mouse_button>(mEvent.button);
  }

  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(mEvent.state);
  }

  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  [[nodiscard]] auto clicks() const noexcept -> uint8 { return mEvent.clicks; }

  [[nodiscard]] auto x() const noexcept -> int32 { return mEvent.x; }
  [[nodiscard]] auto y() const noexcept -> int32 { return mEvent.y; }

  [[nodiscard]] auto position() const noexcept -> ipoint { return {x(), y()}; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_MouseButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

class mouse_motion_event final : public event_base<SDL_MouseMotionEvent> {
 public:
  mouse_motion_event() : event_base {event_type::mouse_motion} {}

  explicit mouse_motion_event(const SDL_MouseMotionEvent& event) noexcept : event_base {event}
  {
  }

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  void set_which(const uint32 which) noexcept { mEvent.which = which; }

  void set_state(const uint32 state) noexcept { mEvent.state = state; }

  void set_x(const int32 x) noexcept { mEvent.x = x; }
  void set_y(const int32 y) noexcept { mEvent.y = y; }

  void set_dx(const int32 dx) noexcept { mEvent.xrel = dx; }
  void set_dy(const int32 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto which() const noexcept -> uint32 { return mEvent.which; }

  [[nodiscard]] auto state() const noexcept -> uint32 { return mEvent.state; }

  [[nodiscard]] auto pressed(const mouse_button button) const noexcept -> bool
  {
    return mEvent.state & SDL_BUTTON(to_underlying(button));
  }

  [[nodiscard]] auto x() const noexcept -> int32 { return mEvent.x; }
  [[nodiscard]] auto y() const noexcept -> int32 { return mEvent.y; }

  [[nodiscard]] auto dx() const noexcept -> int32 { return mEvent.xrel; }
  [[nodiscard]] auto dy() const noexcept -> int32 { return mEvent.yrel; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_MouseMotionEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.motion = event.get();
  return e;
}

class mouse_wheel_event final : public event_base<SDL_MouseWheelEvent> {
 public:
  mouse_wheel_event() : event_base {event_type::mouse_wheel} {}

  explicit mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept : event_base {event} {}

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  void set_which(const uint32 which) noexcept { mEvent.which = which; }

  void set_x(const int32 x) noexcept { mEvent.x = x; }
  void set_y(const int32 y) noexcept { mEvent.y = y; }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  void set_precise_x(const float x) noexcept { mEvent.preciseX = x; }
  void set_precise_y(const float y) noexcept { mEvent.preciseY = y; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  void set_direction(const mouse_wheel_direction direction) noexcept
  {
    mEvent.direction = to_underlying(direction);
  }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto which() const noexcept -> uint32 { return mEvent.which; }

  [[nodiscard]] auto x() const noexcept -> int32 { return mEvent.x; }
  [[nodiscard]] auto y() const noexcept -> int32 { return mEvent.y; }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto precise_x() const noexcept -> float { return mEvent.preciseX; }
  [[nodiscard]] auto precise_y() const noexcept -> float { return mEvent.preciseY; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 26, 0)

  void set_mouse_x(const int32 x) noexcept { mEvent.mouseX = x; }
  void set_mouse_y(const int32 y) noexcept { mEvent.mouseY = y; }

  [[nodiscard]] auto mouse_x() const noexcept -> int32 { return mEvent.mouseX; }
  [[nodiscard]] auto mouse_y() const noexcept -> int32 { return mEvent.mouseY; }

#endif  // SDL_VERSION_ATLEAST(2, 26, 0)

  [[nodiscard]] auto direction() const noexcept -> mouse_wheel_direction
  {
    return static_cast<mouse_wheel_direction>(mEvent.direction);
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_MouseWheelEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.wheel = event.get();
  return e;
}

}  // namespace cen

#endif  // CENTURION_EVENTS_MOUSE_EVENTS_HPP_
