#ifndef CENTURION_TEXT_EDITING_EVENT_SOURCE
#define CENTURION_TEXT_EDITING_EVENT_SOURCE

#include "centurion_utils.hpp"
#include "event.hpp"

namespace centurion {

CENTURION_DEF
text_editing_event::text_editing_event() noexcept : common_event{}
{
  check_length();
}

CENTURION_DEF
text_editing_event::text_editing_event(
    const SDL_TextEditingEvent& event) noexcept
    : common_event{event}
{
  check_length();
}

CENTURION_DEF
void text_editing_event::check_length() noexcept
{
  m_event.length = detail::clamp_inclusive({0, 32}, m_event.length);
}

CENTURION_DEF
void text_editing_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void text_editing_event::set_start(i32 start) noexcept
{
  m_event.start = start;
}

CENTURION_DEF
void text_editing_event::set_length(i32 length) noexcept
{
  m_event.length = detail::clamp_inclusive({0, 32}, length);
}

CENTURION_DEF
auto text_editing_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto text_editing_event::text() const noexcept -> std::string_view
{
  return std::string_view{static_cast<czstring>(m_event.text)};
}

CENTURION_DEF
auto text_editing_event::start() const noexcept -> i32
{
  return m_event.start;
}

CENTURION_DEF
auto text_editing_event::length() const noexcept -> i32
{
  return m_event.length;
}

}  // namespace centurion

#endif  // CENTURION_TEXT_EDITING_EVENT_SOURCE