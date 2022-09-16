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

#ifndef CENTURION_JOYSTICK_EVENTS_HPP_
#define CENTURION_JOYSTICK_EVENTS_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"
#include "event_base.hpp"
#include "input.hpp"
#include "joystick.hpp"

namespace cen {

enum class joy_hat_position : uint8
{
  left_up = SDL_HAT_LEFTUP,
  left = SDL_HAT_LEFT,
  left_down = SDL_HAT_LEFTDOWN,
  up = SDL_HAT_UP,
  centered = SDL_HAT_CENTERED,
  down = SDL_HAT_DOWN,
  right_up = SDL_HAT_RIGHTUP,
  right = SDL_HAT_RIGHT,
  right_down = SDL_HAT_RIGHTDOWN
};

[[nodiscard]] constexpr auto to_string(const joy_hat_position position) -> std::string_view
{
  switch (position) {
    case joy_hat_position::left_up:
      return "left_up";

    case joy_hat_position::left:
      return "left";

    case joy_hat_position::left_down:
      return "left_down";

    case joy_hat_position::up:
      return "up";

    case joy_hat_position::centered:
      return "centered";

    case joy_hat_position::down:
      return "down";

    case joy_hat_position::right_up:
      return "right_up";

    case joy_hat_position::right:
      return "right";

    case joy_hat_position::right_down:
      return "right_down";

    default:
      throw exception{"Did not recognize joystick hat position!"};
  }
}

inline auto operator<<(std::ostream& stream, const joy_hat_position position) -> std::ostream&
{
  return stream << to_string(position);
}

class joy_axis_event final : public event_base<SDL_JoyAxisEvent>
{
 public:
  joy_axis_event() : event_base{event_type::joy_axis_motion} {}

  explicit joy_axis_event(const SDL_JoyAxisEvent& event) noexcept : event_base{event} {}

  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void set_axis(const uint8 axis) noexcept { mEvent.axis = axis; }

  void set_value(const int16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto axis() const noexcept -> uint8 { return mEvent.axis; }

  [[nodiscard]] auto value() const noexcept -> int16 { return mEvent.value; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

class joy_ball_event final : public event_base<SDL_JoyBallEvent>
{
 public:
  joy_ball_event() : event_base{event_type::joy_ball_motion} {}

  explicit joy_ball_event(const SDL_JoyBallEvent& event) noexcept : event_base{event} {}

  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void set_ball(const uint8 ball) noexcept { mEvent.ball = ball; }

  void set_dx(const int16 dx) noexcept { mEvent.xrel = dx; }

  void set_dy(const int16 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto ball() const noexcept -> uint8 { return mEvent.ball; }

  [[nodiscard]] auto dx() const noexcept -> int16 { return mEvent.xrel; }

  [[nodiscard]] auto dy() const noexcept -> int16 { return mEvent.yrel; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyBallEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

class joy_button_event final : public event_base<SDL_JoyButtonEvent>
{
 public:
  joy_button_event() : event_base{event_type::joy_button_down} {}

  explicit joy_button_event(const SDL_JoyButtonEvent& event) noexcept : event_base{event} {}

  void set_which(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void set_button(const uint8 index) noexcept { mEvent.button = index; }

  void set_state(const button_state state) noexcept { mEvent.state = to_underlying(state); }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto button() const noexcept -> uint8 { return mEvent.button; }

  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(mEvent.state);
  }

  [[nodiscard]] auto is_pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  [[nodiscard]] auto is_released() const noexcept -> bool
  {
    return state() == button_state::released;
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jbutton = event.get();
  return e;
}

class joy_device_event final : public event_base<SDL_JoyDeviceEvent>
{
 public:
  joy_device_event() : event_base{event_type::joy_device_added} {}

  explicit joy_device_event(const SDL_JoyDeviceEvent& event) noexcept : event_base{event} {}

  void set_which(const int32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto which() const noexcept -> int32 { return mEvent.which; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jdevice = event.get();
  return e;
}

class joy_hat_event final : public event_base<SDL_JoyHatEvent>
{
 public:
  joy_hat_event() : event_base{event_type::joy_hat_motion} {}

  explicit joy_hat_event(const SDL_JoyHatEvent& event) noexcept : event_base{event} {}

  void set_hat(const uint8 hat) noexcept { mEvent.hat = hat; }

  void set_position(const joy_hat_position value) noexcept
  {
    mEvent.value = to_underlying(value);
  }

  [[nodiscard]] auto hat() const noexcept -> uint8 { return mEvent.hat; }

  [[nodiscard]] auto position() const noexcept -> joy_hat_position
  {
    return static_cast<joy_hat_position>(mEvent.value);
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyHatEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jhat = event.get();
  return e;
}

#if SDL_VERSION_ATLEAST(2, 24, 0)

class joy_battery_event final : public event_base<SDL_JoyBatteryEvent>
{
 public:
  joy_battery_event() : event_base{event_type::joy_battery_updated} {}

  explicit joy_battery_event(const SDL_JoyBatteryEvent& event) noexcept : event_base{event} {}

  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void set_power_level(joystick_power level) noexcept
  {
    mEvent.level = static_cast<SDL_JoystickPowerLevel>(level);
  }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto power_level() const noexcept -> joystick_power
  {
    return static_cast<joystick_power>(mEvent.level);
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_JoyBatteryEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jbattery = event.get();
  return e;
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

}  // namespace cen

#endif  // CENTURION_JOYSTICK_EVENTS_HPP_
