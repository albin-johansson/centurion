#ifndef CENTURION_CONTROLLER_EVENTS_HPP_
#define CENTURION_CONTROLLER_EVENTS_HPP_

#include <SDL.h>

#include <array>  // array

#include "common.hpp"
#include "controller.hpp"
#include "detail/array_utils.hpp"
#include "detail/stdlib.hpp"
#include "event_base.hpp"
#include "sensor.hpp"

namespace cen {

/// \addtogroup event
/// \{

class controller_axis_event final : public event_base<SDL_ControllerAxisEvent>
{
 public:
  controller_axis_event() : event_base{event_type::controller_axis_motion} {}

  explicit controller_axis_event(const SDL_ControllerAxisEvent& event) noexcept
      : event_base{event}
  {}

  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void set_axis(const controller_axis axis) noexcept
  {
    mEvent.axis = static_cast<uint8>(axis);
  }

  void set_value(const int16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto axis() const noexcept -> controller_axis
  {
    return static_cast<controller_axis>(mEvent.axis);
  }

  [[nodiscard]] auto value() const noexcept -> int16 { return mEvent.value; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_ControllerAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

class controller_button_event final : public event_base<SDL_ControllerButtonEvent>
{
 public:
  controller_button_event() : event_base{event_type::controller_button_down} {}

  explicit controller_button_event(const SDL_ControllerButtonEvent& event) noexcept
      : event_base{event}
  {}

  void set_which(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void set_button(const controller_button button) noexcept
  {
    mEvent.button = static_cast<uint8>(button);
  }

  void set_state(const button_state state) noexcept { mEvent.state = to_underlying(state); }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto button() const noexcept -> controller_button
  {
    return static_cast<controller_button>(mEvent.button);
  }

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
inline auto as_sdl_event(const event_base<SDL_ControllerButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cbutton = event.get();
  return e;
}

class controller_device_event final : public event_base<SDL_ControllerDeviceEvent>
{
 public:
  controller_device_event() : event_base{event_type::controller_device_added} {}

  explicit controller_device_event(const SDL_ControllerDeviceEvent& event) noexcept
      : event_base{event}
  {}

  void set_which(const int32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto which() const noexcept -> int32 { return mEvent.which; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_ControllerDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

class controller_sensor_event final : public event_base<SDL_ControllerSensorEvent>
{
 public:
  controller_sensor_event() : event_base{event_type::controller_sensor_update} {}

  explicit controller_sensor_event(const SDL_ControllerSensorEvent& event) noexcept
      : event_base{event}
  {}

  void set_which(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void set_sensor(const sensor_type sensor) noexcept { mEvent.sensor = to_underlying(sensor); }

  void set_data(const std::array<float, 3>& values) { detail::assign(values, mEvent.data); }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto sensor() const noexcept -> sensor_type
  {
    return sensor_type{mEvent.sensor};
  }

  [[nodiscard]] auto data() const -> std::array<float, 3>
  {
    return detail::to_array(mEvent.data);
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_ControllerSensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.csensor = event.get();
  return e;
}

class controller_touchpad_event final : public event_base<SDL_ControllerTouchpadEvent>
{
 public:
  controller_touchpad_event() : event_base{event_type::controller_touchpad_down} {}

  explicit controller_touchpad_event(const SDL_ControllerTouchpadEvent& event) noexcept
      : event_base{event}
  {}

  void set_which(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void set_touchpad_index(const int32 index) noexcept { mEvent.touchpad = index; }

  void set_finger_index(const int32 index) noexcept { mEvent.finger = index; }

  void set_x(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }

  void set_y(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  void set_pressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto touchpad_index() const noexcept -> int32 { return mEvent.touchpad; }

  [[nodiscard]] auto finger_index() const noexcept -> int32 { return mEvent.finger; }

  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto pressure() const noexcept -> float { return mEvent.pressure; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_ControllerTouchpadEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.ctouchpad = event.get();
  return e;
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_CONTROLLER_EVENTS_HPP_
