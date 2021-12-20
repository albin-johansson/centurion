#ifndef CENTURION_MOUSE_EVENTS_HPP_
#define CENTURION_MOUSE_EVENTS_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"
#include "../core/exception.hpp"
#include "../input/button_state.hpp"
#include "../mouse.hpp"
#include "event_base.hpp"

namespace cen {

enum class MouseWheelDirection : Uint32 {
  Normal = SDL_MOUSEWHEEL_NORMAL,
  Flipped = SDL_MOUSEWHEEL_FLIPPED
};

class MouseButtonEvent final : public EventBase<SDL_MouseButtonEvent> {
 public:
  MouseButtonEvent() noexcept : EventBase{EventType::MouseButtonDown} {}

  explicit MouseButtonEvent(const SDL_MouseButtonEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetButton(const MouseButton button) noexcept { mEvent.button = ToUnderlying(button); }
  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  void SetClicks(const Uint8 clicks) noexcept { mEvent.clicks = clicks; }

  void SetX(const Sint32 x) noexcept { mEvent.x = x; }
  void SetY(const Sint32 y) noexcept { mEvent.y = y; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> MouseButton
  {
    return static_cast<MouseButton>(mEvent.button);
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

  [[nodiscard]] auto GetClicks() const noexcept -> Uint8 { return mEvent.clicks; }

  [[nodiscard]] auto GetX() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> Sint32 { return mEvent.y; }
};

class MouseMotionEvent final : public EventBase<SDL_MouseMotionEvent> {
 public:
  MouseMotionEvent() noexcept : EventBase{EventType::MouseMotion} {}

  explicit MouseMotionEvent(const SDL_MouseMotionEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetState(const Uint32 state) noexcept { mEvent.state = state; }

  void SetX(const Sint32 x) noexcept { mEvent.x = x; }
  void SetY(const Sint32 y) noexcept { mEvent.y = y; }

  void SetDeltaX(const Sint32 dx) noexcept { mEvent.xrel = dx; }
  void SetDeltaY(const Sint32 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetState() const noexcept -> Uint32 { return mEvent.state; }

  [[nodiscard]] auto IsPressed(const MouseButton button) const noexcept -> bool
  {
    return mEvent.state & SDL_BUTTON(ToUnderlying(button));
  }

  [[nodiscard]] auto GetX() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> Sint32 { return mEvent.y; }

  [[nodiscard]] auto GetDeltaX() const noexcept -> Sint32 { return mEvent.xrel; }
  [[nodiscard]] auto GetDeltaY() const noexcept -> Sint32 { return mEvent.yrel; }
};

class MouseWheelEvent final : public EventBase<SDL_MouseWheelEvent> {
 public:
  MouseWheelEvent() noexcept : EventBase{EventType::MouseWheel} {}

  explicit MouseWheelEvent(const SDL_MouseWheelEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetXScroll(const Sint32 xScroll) noexcept { mEvent.x = xScroll; }
  void SetYScroll(const Sint32 yScroll) noexcept { mEvent.y = yScroll; }

  void SetDirection(const MouseWheelDirection direction) noexcept
  {
    mEvent.direction = ToUnderlying(direction);
  }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetXScroll() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetYScroll() const noexcept -> Sint32 { return mEvent.y; }

  [[nodiscard]] auto GetDirection() const noexcept -> MouseWheelDirection
  {
    return static_cast<MouseWheelDirection>(mEvent.direction);
  }
};

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseMotionEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.motion = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseWheelEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.wheel = event.get();
  return e;
}

[[nodiscard]] constexpr auto to_string(const MouseWheelDirection dir) -> std::string_view
{
  switch (dir) {
    case MouseWheelDirection::Normal:
      return "Normal";

    case MouseWheelDirection::Flipped:
      return "Flipped";

    default:
      throw Error{"Did not recognize mouse wheel direction!"};
  }
}

inline auto operator<<(std::ostream& stream, const MouseWheelDirection dir) -> std::ostream&
{
  return stream << to_string(dir);
}

}  // namespace cen

#endif  // CENTURION_MOUSE_EVENTS_HPP_
