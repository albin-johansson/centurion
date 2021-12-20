#ifndef CENTURION_JOYSTICK_EVENTS_HPP_
#define CENTURION_JOYSTICK_EVENTS_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"
#include "../core/exception.hpp"
#include "../input/button_state.hpp"
#include "event_base.hpp"

namespace cen {

enum class JoyHatPosition : Uint8 {
  LeftUp = SDL_HAT_LEFTUP,
  Left = SDL_HAT_LEFT,
  LeftDown = SDL_HAT_LEFTDOWN,
  Up = SDL_HAT_UP,
  Centered = SDL_HAT_CENTERED,
  Down = SDL_HAT_DOWN,
  RightUp = SDL_HAT_RIGHTUP,
  Right = SDL_HAT_RIGHT,
  RightDown = SDL_HAT_RIGHTDOWN
};

class JoyAxisEvent final : public EventBase<SDL_JoyAxisEvent> {
 public:
  JoyAxisEvent() noexcept : EventBase{EventType::JoyAxisMotion} {}

  explicit JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void SetAxis(const Uint8 axis) noexcept { mEvent.axis = axis; }

  void SetValue(const Sint16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetAxis() const noexcept -> Uint8 { return mEvent.axis; }

  [[nodiscard]] auto GetValue() const noexcept -> Sint16 { return mEvent.value; }
};

class JoyBallEvent final : public EventBase<SDL_JoyBallEvent> {
 public:
  JoyBallEvent() noexcept : EventBase{EventType::JoyBallMotion} {}

  explicit JoyBallEvent(const SDL_JoyBallEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }
  void SetBall(const Uint8 ball) noexcept { mEvent.ball = ball; }

  void SetDeltaX(const Sint16 dx) noexcept { mEvent.xrel = dx; }
  void SetDeltaY(const Sint16 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }
  [[nodiscard]] auto GetBall() const noexcept -> Uint8 { return mEvent.ball; }

  [[nodiscard]] auto GetDeltaX() const noexcept -> Sint16 { return mEvent.xrel; }
  [[nodiscard]] auto GetDeltaY() const noexcept -> Sint16 { return mEvent.yrel; }
};

class JoyButtonEvent final : public EventBase<SDL_JoyButtonEvent> {
 public:
  JoyButtonEvent() noexcept : EventBase{EventType::JoyButtonDown} {}

  explicit JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetButton(const Uint8 index) noexcept { mEvent.button = index; }

  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> Uint8 { return mEvent.button; }

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

class JoyDeviceEvent final : public EventBase<SDL_JoyDeviceEvent> {
 public:
  JoyDeviceEvent() noexcept : EventBase{EventType::JoyDeviceAdded} {}

  explicit JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const Sint32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto GetWhich() const noexcept -> Sint32 { return mEvent.which; }
};

class JoyHatEvent final : public EventBase<SDL_JoyHatEvent> {
 public:
  JoyHatEvent() noexcept : EventBase{EventType::JoyHatMotion} {}

  explicit JoyHatEvent(const SDL_JoyHatEvent& event) noexcept : EventBase{event} {}

  void SetHat(const Uint8 hat) noexcept { mEvent.hat = hat; }

  void SetPosition(const JoyHatPosition value) noexcept { mEvent.value = ToUnderlying(value); }

  [[nodiscard]] auto GetHat() const noexcept -> Uint8 { return mEvent.hat; }

  [[nodiscard]] auto GetPosition() const noexcept -> JoyHatPosition
  {
    return static_cast<JoyHatPosition>(mEvent.value);
  }
};

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyBallEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jbutton = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jdevice = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyHatEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jhat = event.get();
  return e;
}

[[nodiscard]] constexpr auto to_string(const JoyHatPosition position) -> std::string_view
{
  switch (position) {
    case JoyHatPosition::LeftUp:
      return "LeftUp";

    case JoyHatPosition::Left:
      return "Left";

    case JoyHatPosition::LeftDown:
      return "LeftDown";

    case JoyHatPosition::Up:
      return "Up";

    case JoyHatPosition::Centered:
      return "Centered";

    case JoyHatPosition::Down:
      return "Down";

    case JoyHatPosition::RightUp:
      return "RightUp";

    case JoyHatPosition::Right:
      return "Right";

    case JoyHatPosition::RightDown:
      return "RightDown";

    default:
      throw Error{"Did not recognize joystick hat position!"};
  }
}

inline auto operator<<(std::ostream& stream, const JoyHatPosition position) -> std::ostream&
{
  return stream << to_string(position);
}

}  // namespace cen

#endif  // CENTURION_JOYSTICK_EVENTS_HPP_
