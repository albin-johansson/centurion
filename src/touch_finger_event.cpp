#ifndef CENTURION_TOUCH_FINGER_EVENT_SOURCE
#define CENTURION_TOUCH_FINGER_EVENT_SOURCE

#include "centurion_utils.hpp"
#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
TouchFingerEvent::TouchFingerEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
TouchFingerEvent::TouchFingerEvent(const SDL_TouchFingerEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void TouchFingerEvent::set_touch_id(TouchID id) noexcept
{
  m_event.touchId = id;
}

CENTURION_DEF
void TouchFingerEvent::set_finger_id(FingerID id) noexcept
{
  m_event.fingerId = id;
}

CENTURION_DEF
void TouchFingerEvent::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void TouchFingerEvent::set_x(float x) noexcept
{
  m_event.x = detail::clamp_inclusive({0, 1}, x);
}

CENTURION_DEF
void TouchFingerEvent::set_y(float y) noexcept
{
  m_event.y = detail::clamp_inclusive({0, 1}, y);
}

CENTURION_DEF
void TouchFingerEvent::set_dx(float dx) noexcept
{
  m_event.dx = detail::clamp_inclusive({-1, 1}, dx);
}

CENTURION_DEF
void TouchFingerEvent::set_dy(float dy) noexcept
{
  m_event.dy = detail::clamp_inclusive({-1, 1}, dy);
}

CENTURION_DEF
void TouchFingerEvent::set_pressure(float pressure) noexcept
{
  m_event.pressure = detail::clamp_inclusive({0, 1}, pressure);
}

CENTURION_DEF
auto TouchFingerEvent::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

CENTURION_DEF
auto TouchFingerEvent::finger_id() const noexcept -> SDL_FingerID
{
  return m_event.fingerId;
}

CENTURION_DEF
auto TouchFingerEvent::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto TouchFingerEvent::x() const noexcept -> float
{
  return m_event.x;
}

CENTURION_DEF
auto TouchFingerEvent::y() const noexcept -> float
{
  return m_event.y;
}

CENTURION_DEF
auto TouchFingerEvent::dx() const noexcept -> float
{
  return m_event.dx;
}

CENTURION_DEF
auto TouchFingerEvent::dy() const noexcept -> float
{
  return m_event.dy;
}

CENTURION_DEF
auto TouchFingerEvent::pressure() const noexcept -> float
{
  return m_event.pressure;
}

}  // namespace centurion::event

#endif  // CENTURION_TOUCH_FINGER_EVENT_SOURCE