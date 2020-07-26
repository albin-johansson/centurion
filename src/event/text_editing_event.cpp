#include <algorithm>

#include "centurion_utils.hpp"
#include "event.hpp"

namespace centurion {

text_editing_event::text_editing_event() noexcept : common_event{}
{
  check_length();
}

text_editing_event::text_editing_event(
    const SDL_TextEditingEvent& event) noexcept
    : common_event{event}
{
  check_length();
}

void text_editing_event::check_length() noexcept
{
  m_event.length = std::clamp(m_event.length, 0, 32);
}

void text_editing_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

void text_editing_event::set_start(i32 start) noexcept
{
  m_event.start = start;
}

void text_editing_event::set_length(i32 length) noexcept
{
  m_event.length = std::clamp(length, 0, 32);
}

auto text_editing_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

auto text_editing_event::text() const noexcept -> std::string_view
{
  return std::string_view{static_cast<czstring>(m_event.text)};
}

auto text_editing_event::start() const noexcept -> i32
{
  return m_event.start;
}

auto text_editing_event::length() const noexcept -> i32
{
  return m_event.length;
}

}  // namespace centurion
