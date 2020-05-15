#ifndef CENTURION_TEXT_EDITING_EVENT_SOURCE
#define CENTURION_TEXT_EDITING_EVENT_SOURCE

#include "text_editing_event.h"

#include "centurion_utils.h"

namespace centurion {
namespace event {

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
TextEditingEvent::TextEditingEvent(SDL_TextEditingEvent&& event) noexcept
    : CommonEvent{std::forward<SDL_TextEditingEvent>(event)}
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
Uint32 TextEditingEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
CZString TextEditingEvent::text() const noexcept
{
  return m_event.text;
}

CENTURION_DEF
Sint32 TextEditingEvent::start() const noexcept
{
  return m_event.start;
}

CENTURION_DEF
Sint32 TextEditingEvent::length() const noexcept
{
  return m_event.length;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_TEXT_EDITING_EVENT_SOURCE