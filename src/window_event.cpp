#ifndef CENTURION_WINDOW_EVENT_SOURCE
#define CENTURION_WINDOW_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
WindowEvent::WindowEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
WindowEvent::WindowEvent(const SDL_WindowEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
auto WindowEvent::event_id() const noexcept -> WindowEventID
{
  return static_cast<WindowEventID>(m_event.event);
}

CENTURION_DEF
auto WindowEvent::data_1() const noexcept -> Sint32
{
  return m_event.data1;
}

CENTURION_DEF
auto WindowEvent::data_2() const noexcept -> Sint32
{
  return m_event.data2;
}

}  // namespace centurion::event

#endif  // CENTURION_WINDOW_EVENT_SOURCE
