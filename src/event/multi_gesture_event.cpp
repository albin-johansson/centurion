#include "event.hpp"

namespace cen {

multi_gesture_event::multi_gesture_event() noexcept : common_event{}
{}

multi_gesture_event::multi_gesture_event(
    const SDL_MultiGestureEvent& event) noexcept
    : common_event{event}
{}

void multi_gesture_event::set_touch_id(SDL_TouchID id) noexcept
{
  m_event.touchId = id;
}

void multi_gesture_event::set_delta_theta(float dTheta) noexcept
{
  m_event.dTheta = dTheta;
}

void multi_gesture_event::set_delta_distance(float dDistance) noexcept
{
  m_event.dDist = dDistance;
}

void multi_gesture_event::set_center_x(float centerX) noexcept
{
  m_event.x = centerX;
}

void multi_gesture_event::set_center_y(float centerY) noexcept
{
  m_event.y = centerY;
}

void multi_gesture_event::set_fingers(u16 nFingers) noexcept
{
  m_event.numFingers = nFingers;
}

auto multi_gesture_event::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

auto multi_gesture_event::delta_theta() const noexcept -> float
{
  return m_event.dTheta;
}

auto multi_gesture_event::delta_distance() const noexcept -> float
{
  return m_event.dDist;
}

auto multi_gesture_event::center_x() const noexcept -> float
{
  return m_event.x;
}

auto multi_gesture_event::center_y() const noexcept -> float
{
  return m_event.y;
}

auto multi_gesture_event::fingers() const noexcept -> float
{
  return m_event.numFingers;
}

}  // namespace cen
