#ifndef CENTURION_TEXT_EDITING_EVENT_SOURCE
#define CENTURION_TEXT_EDITING_EVENT_SOURCE

#include "centurion_utils.hpp"
#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
TextEditingEvent::TextEditingEvent() noexcept : CommonEvent{}
{
  check_length();
}

CENTURION_DEF
TextEditingEvent::TextEditingEvent(const SDL_TextEditingEvent& event) noexcept
    : CommonEvent{event}
{
  check_length();
}

CENTURION_DEF
void TextEditingEvent::check_length() noexcept
{
  m_event.length = detail::clamp_inclusive({0, 32}, m_event.length);
}

CENTURION_DEF
void TextEditingEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void TextEditingEvent::set_start(Sint32 start) noexcept
{
  m_event.start = start;
}

CENTURION_DEF
void TextEditingEvent::set_length(Sint32 length) noexcept
{
  m_event.length = detail::clamp_inclusive({0, 32}, length);
}

CENTURION_DEF
auto TextEditingEvent::window_id() const noexcept -> Uint32
{
  return m_event.windowID;
}

CENTURION_DEF
auto TextEditingEvent::text() const noexcept -> czstring
{
  return m_event.text;
}

CENTURION_DEF
auto TextEditingEvent::start() const noexcept -> Sint32
{
  return m_event.start;
}

CENTURION_DEF
auto TextEditingEvent::length() const noexcept -> Sint32
{
  return m_event.length;
}

}  // namespace centurion::event

#endif  // CENTURION_TEXT_EDITING_EVENT_SOURCE