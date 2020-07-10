#ifndef CENTURION_MULTI_GESTURE_EVENT_SOURCE
#define CENTURION_MULTI_GESTURE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
MultiGestureEvent::MultiGestureEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
MultiGestureEvent::MultiGestureEvent(
    const SDL_MultiGestureEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void MultiGestureEvent::set_touch_id(TouchID id) noexcept
{
  m_event.touchId = id;
}

CENTURION_DEF
void MultiGestureEvent::set_delta_theta(float dTheta) noexcept
{
  m_event.dTheta = dTheta;
}

CENTURION_DEF
void MultiGestureEvent::set_delta_distance(float dDistance) noexcept
{
  m_event.dDist = dDistance;
}

CENTURION_DEF
void MultiGestureEvent::set_center_x(float centerX) noexcept
{
  m_event.x = centerX;
}

CENTURION_DEF
void MultiGestureEvent::set_center_y(float centerY) noexcept
{
  m_event.y = centerY;
}

CENTURION_DEF
void MultiGestureEvent::set_fingers(u16 nFingers) noexcept
{
  m_event.numFingers = nFingers;
}

CENTURION_DEF
auto MultiGestureEvent::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

CENTURION_DEF
auto MultiGestureEvent::delta_theta() const noexcept -> float
{
  return m_event.dTheta;
}

CENTURION_DEF
auto MultiGestureEvent::delta_distance() const noexcept -> float
{
  return m_event.dDist;
}

CENTURION_DEF
auto MultiGestureEvent::center_x() const noexcept -> float
{
  return m_event.x;
}

CENTURION_DEF
auto MultiGestureEvent::center_y() const noexcept -> float
{
  return m_event.y;
}

CENTURION_DEF
auto MultiGestureEvent::fingers() const noexcept -> float
{
  return m_event.numFingers;
}

}  // namespace centurion

#endif  // CENTURION_MULTI_GESTURE_EVENT_SOURCE