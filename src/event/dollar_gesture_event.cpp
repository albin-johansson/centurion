#include "event.hpp"

namespace centurion {

dollar_gesture_event::dollar_gesture_event() noexcept : common_event{}
{}

dollar_gesture_event::dollar_gesture_event(
    const SDL_DollarGestureEvent& event) noexcept
    : common_event{event}
{}

void dollar_gesture_event::set_touch_id(SDL_TouchID id) noexcept
{
  m_event.touchId = id;
}

void dollar_gesture_event::set_gesture_id(SDL_GestureID id) noexcept
{
  m_event.gestureId = id;
}

void dollar_gesture_event::set_fingers(u32 fingers) noexcept
{
  m_event.numFingers = fingers;
}

void dollar_gesture_event::set_error(float error) noexcept
{
  m_event.error = error;
}

void dollar_gesture_event::set_x(float x) noexcept
{
  m_event.x = x;
}

void dollar_gesture_event::set_y(float y) noexcept
{
  m_event.y = y;
}

auto dollar_gesture_event::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

auto dollar_gesture_event::gesture_id() const noexcept -> SDL_GestureID
{
  return m_event.gestureId;
}

auto dollar_gesture_event::fingers() const noexcept -> u32
{
  return m_event.numFingers;
}

auto dollar_gesture_event::error() const noexcept -> float
{
  return m_event.error;
}

auto dollar_gesture_event::x() const noexcept -> float
{
  return m_event.x;
}

auto dollar_gesture_event::y() const noexcept -> float
{
  return m_event.y;
}

}  // namespace centurion
