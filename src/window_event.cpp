#ifndef CENTURION_WINDOW_EVENT_SOURCE
#define CENTURION_WINDOW_EVENT_SOURCE

#include "window_event.hpp"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
WindowEvent::WindowEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
WindowEvent::WindowEvent(const SDL_WindowEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
WindowEvent::WindowEvent(SDL_WindowEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
WindowEventID WindowEvent::event_id() const noexcept
{
  return static_cast<WindowEventID>(m_event.event);
}

CENTURION_DEF
Sint32 WindowEvent::data_1() const noexcept
{
  return m_event.data1;
}

CENTURION_DEF
Sint32 WindowEvent::data_2() const noexcept
{
  return m_event.data2;
}

CENTURION_DEF
bool operator==(WindowEventID eventId, SDL_WindowEventID sdlEventId) noexcept
{
  return eventId == static_cast<WindowEventID>(sdlEventId);
}

CENTURION_DEF
bool operator==(SDL_WindowEventID sdlEventId, WindowEventID eventId) noexcept
{
  return static_cast<WindowEventID>(sdlEventId) == eventId;
}

CENTURION_DEF
bool operator!=(WindowEventID eventId, SDL_WindowEventID sdlEventId) noexcept
{
  return !(eventId == sdlEventId);
}

CENTURION_DEF
bool operator!=(SDL_WindowEventID sdlEventId, WindowEventID eventId) noexcept
{
  return !(sdlEventId == eventId);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_WINDOW_EVENT_SOURCE
