#ifndef CENTURION_DOLLAR_GESTURE_EVENT_SOURCE
#define CENTURION_DOLLAR_GESTURE_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
DollarGestureEvent::DollarGestureEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
DollarGestureEvent::DollarGestureEvent(
    const SDL_DollarGestureEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void DollarGestureEvent::set_touch_id(TouchID id) noexcept
{
  m_event.touchId = id;
}

CENTURION_DEF
void DollarGestureEvent::set_gesture_id(GestureID id) noexcept
{
  m_event.gestureId = id;
}

CENTURION_DEF
void DollarGestureEvent::set_fingers(Uint32 fingers) noexcept
{
  m_event.numFingers = fingers;
}

CENTURION_DEF
void DollarGestureEvent::set_error(float error) noexcept
{
  m_event.error = error;
}

CENTURION_DEF
void DollarGestureEvent::set_x(float x) noexcept
{
  m_event.x = x;
}

CENTURION_DEF
void DollarGestureEvent::set_y(float y) noexcept
{
  m_event.y = y;
}

CENTURION_DEF
auto DollarGestureEvent::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

CENTURION_DEF
auto DollarGestureEvent::gesture_id() const noexcept -> SDL_GestureID
{
  return m_event.gestureId;
}

CENTURION_DEF
auto DollarGestureEvent::fingers() const noexcept -> Uint32
{
  return m_event.numFingers;
}

CENTURION_DEF
auto DollarGestureEvent::error() const noexcept -> float
{
  return m_event.error;
}

CENTURION_DEF
auto DollarGestureEvent::x() const noexcept -> float
{
  return m_event.x;
}

CENTURION_DEF
auto DollarGestureEvent::y() const noexcept -> float
{
  return m_event.y;
}

}  // namespace centurion::event

#endif  // CENTURION_DOLLAR_GESTURE_EVENT_SOURCE