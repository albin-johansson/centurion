#ifndef CENTURION_CONTROLLER_EVENTS_HPP_
#define CENTURION_CONTROLLER_EVENTS_HPP_

#include <SDL.h>

#include <array>  // array

#include "../common.hpp"
#include "../detail/array_utils.hpp"
#include "../detail/stdlib.hpp"
#include "../input/controller.hpp"
#include "../input/sensor.hpp"
#include "event_base.hpp"

namespace cen {

class ControllerAxisEvent final : public EventBase<SDL_ControllerAxisEvent> {
 public:
  ControllerAxisEvent() noexcept : EventBase{EventType::ControllerAxisMotion} {}

  explicit ControllerAxisEvent(const SDL_ControllerAxisEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }
  void SetAxis(const ControllerAxis axis) noexcept { mEvent.axis = static_cast<Uint8>(axis); }
  void SetValue(const Sint16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }
  [[nodiscard]] auto GetAxis() const noexcept -> ControllerAxis
  {
    return static_cast<ControllerAxis>(mEvent.axis);
  }
  [[nodiscard]] auto GetValue() const noexcept -> Sint16 { return mEvent.value; }
};

class ControllerButtonEvent final : public EventBase<SDL_ControllerButtonEvent> {
 public:
  ControllerButtonEvent() noexcept : EventBase{EventType::ControllerButtonDown} {}

  explicit ControllerButtonEvent(const SDL_ControllerButtonEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetButton(const ControllerButton button) noexcept
  {
    mEvent.button = static_cast<Uint8>(button);
  }

  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> ControllerButton
  {
    return static_cast<ControllerButton>(mEvent.button);
  }

  [[nodiscard]] auto GetState() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
  }

  [[nodiscard]] auto IsPressed() const noexcept -> bool
  {
    return GetState() == ButtonState::Pressed;
  }

  [[nodiscard]] auto IsReleased() const noexcept -> bool
  {
    return GetState() == ButtonState::Released;
  }
};

class ControllerDeviceEvent final : public EventBase<SDL_ControllerDeviceEvent> {
 public:
  ControllerDeviceEvent() noexcept : EventBase{EventType::ControllerDeviceAdded} {}

  explicit ControllerDeviceEvent(const SDL_ControllerDeviceEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const Sint32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto GetWhich() const noexcept -> Sint32 { return mEvent.which; }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

class ControllerSensorEvent final : public EventBase<SDL_ControllerSensorEvent> {
 public:
  ControllerSensorEvent() noexcept : EventBase{EventType::ControllerSensorUpdate} {}

  explicit ControllerSensorEvent(const SDL_ControllerSensorEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetSensor(const sensor_type sensor) noexcept { mEvent.sensor = ToUnderlying(sensor); }

  void SetData(const std::array<float, 3>& values) { detail::assign(values, mEvent.data); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetSensor() const noexcept -> sensor_type
  {
    return sensor_type{mEvent.sensor};
  }

  [[nodiscard]] auto GetData() const -> std::array<float, 3>
  {
    return detail::to_array(mEvent.data);
  }
};

class ControllerTouchpadEvent final : public EventBase<SDL_ControllerTouchpadEvent> {
 public:
  ControllerTouchpadEvent() noexcept : EventBase{EventType::ControllerTouchpadDown} {}

  explicit ControllerTouchpadEvent(const SDL_ControllerTouchpadEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetTouchpadIndex(const Sint32 index) noexcept { mEvent.touchpad = index; }
  void SetFingerIndex(const Sint32 index) noexcept { mEvent.finger = index; }

  void SetX(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }
  void SetY(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  void SetPressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetTouchpadIndex() const noexcept -> Sint32 { return mEvent.touchpad; }
  [[nodiscard]] auto GetFingerIndex() const noexcept -> Sint32 { return mEvent.finger; }

  [[nodiscard]] auto GetX() const noexcept -> float { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto GetPressure() const noexcept -> float { return mEvent.pressure; }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cbutton = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerSensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.csensor = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerTouchpadEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.ctouchpad = event.get();
  return e;
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_CONTROLLER_EVENTS_HPP_
