#include "event.hpp"

namespace centurion {

text_input_event::text_input_event() noexcept : common_event{}
{}

text_input_event::text_input_event(const SDL_TextInputEvent& event) noexcept
    : common_event{event}
{}

void text_input_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

auto text_input_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

auto text_input_event::text_utf8() const noexcept -> std::string_view
{
  return std::string_view{static_cast<czstring>(m_event.text)};
}

}  // namespace centurion
