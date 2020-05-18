#ifndef CENTURION_MOUSE_BUTTON_EVENT_SOURCE
#define CENTURION_MOUSE_BUTTON_EVENT_SOURCE

#include "mouse_button_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
MouseButtonEvent::MouseButtonEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
MouseButtonEvent::MouseButtonEvent(const SDL_MouseButtonEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
MouseButtonEvent::MouseButtonEvent(SDL_MouseButtonEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void MouseButtonEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void MouseButtonEvent::set_which(Uint32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void MouseButtonEvent::set_button(MouseButton button) noexcept
{
  m_event.button = static_cast<Uint8>(button);
}

CENTURION_DEF
void MouseButtonEvent::set_state(ButtonState state) noexcept
{
  m_event.state = static_cast<Uint8>(state);
}

CENTURION_DEF
void MouseButtonEvent::set_clicks(Uint8 clicks) noexcept
{
  m_event.clicks = clicks;
}

CENTURION_DEF
void MouseButtonEvent::set_x(Sint32 x) noexcept
{
  m_event.x = x;
}

CENTURION_DEF
void MouseButtonEvent::set_y(Sint32 y) noexcept
{
  m_event.y = y;
}

CENTURION_DEF
Uint32 MouseButtonEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
Uint32 MouseButtonEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
MouseButton MouseButtonEvent::button() const noexcept
{
  return static_cast<MouseButton>(m_event.button);
}

CENTURION_DEF
ButtonState MouseButtonEvent::state() const noexcept
{
  return static_cast<ButtonState>(m_event.state);
}

CENTURION_DEF
Uint8 MouseButtonEvent::clicks() const noexcept
{
  return m_event.clicks;
}

CENTURION_DEF
Sint32 MouseButtonEvent::x() const noexcept
{
  return m_event.x;
}

CENTURION_DEF
Sint32 MouseButtonEvent::y() const noexcept
{
  return m_event.y;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_MOUSE_BUTTON_EVENT_SOURCE