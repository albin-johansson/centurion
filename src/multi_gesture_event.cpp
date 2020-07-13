#ifndef CENTURION_MULTI_GESTURE_EVENT_SOURCE
#define CENTURION_MULTI_GESTURE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
multi_gesture_event::multi_gesture_event() noexcept : common_event{}
{}

CENTURION_DEF
multi_gesture_event::multi_gesture_event(
    const SDL_MultiGestureEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void multi_gesture_event::set_touch_id(SDL_TouchID id) noexcept
{
  m_event.touchId = id;
}

CENTURION_DEF
void multi_gesture_event::set_delta_theta(float dTheta) noexcept
{
  m_event.dTheta = dTheta;
}

CENTURION_DEF
void multi_gesture_event::set_delta_distance(float dDistance) noexcept
{
  m_event.dDist = dDistance;
}

CENTURION_DEF
void multi_gesture_event::set_center_x(float centerX) noexcept
{
  m_event.x = centerX;
}

CENTURION_DEF
void multi_gesture_event::set_center_y(float centerY) noexcept
{
  m_event.y = centerY;
}

CENTURION_DEF
void multi_gesture_event::set_fingers(u16 nFingers) noexcept
{
  m_event.numFingers = nFingers;
}

CENTURION_DEF
auto multi_gesture_event::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

CENTURION_DEF
auto multi_gesture_event::delta_theta() const noexcept -> float
{
  return m_event.dTheta;
}

CENTURION_DEF
auto multi_gesture_event::delta_distance() const noexcept -> float
{
  return m_event.dDist;
}

CENTURION_DEF
auto multi_gesture_event::center_x() const noexcept -> float
{
  return m_event.x;
}

CENTURION_DEF
auto multi_gesture_event::center_y() const noexcept -> float
{
  return m_event.y;
}

CENTURION_DEF
auto multi_gesture_event::fingers() const noexcept -> float
{
  return m_event.numFingers;
}

}  // namespace centurion

#endif  // CENTURION_MULTI_GESTURE_EVENT_SOURCE