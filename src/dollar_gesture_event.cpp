#ifndef CENTURION_DOLLAR_GESTURE_EVENT_SOURCE
#define CENTURION_DOLLAR_GESTURE_EVENT_SOURCE

#include "dollar_gesture_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
DollarGestureEvent::DollarGestureEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
DollarGestureEvent::DollarGestureEvent(
    const SDL_DollarGestureEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
DollarGestureEvent::DollarGestureEvent(SDL_DollarGestureEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
TouchID DollarGestureEvent::touch_id() const noexcept
{
  return m_event.touchId;
}

CENTURION_DEF
GestureID DollarGestureEvent::gesture_id() const noexcept
{
  return m_event.gestureId;
}

CENTURION_DEF
Uint32 DollarGestureEvent::fingers() const noexcept
{
  return m_event.numFingers;
}

CENTURION_DEF
float DollarGestureEvent::error() const noexcept
{
  return m_event.error;
}

CENTURION_DEF
float DollarGestureEvent::x() const noexcept
{
  return m_event.x;
}

CENTURION_DEF
float DollarGestureEvent::y() const noexcept
{
  return m_event.y;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_DOLLAR_GESTURE_EVENT_SOURCE