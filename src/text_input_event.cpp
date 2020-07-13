#ifndef CENTURION_TEXT_INPUT_EVENT_SOURCE
#define CENTURION_TEXT_INPUT_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
text_input_event::text_input_event() noexcept : common_event{}
{}

CENTURION_DEF
text_input_event::text_input_event(const SDL_TextInputEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void text_input_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto text_input_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto text_input_event::text() const noexcept -> std::string_view
{
  return std::string_view{static_cast<czstring>(m_event.text)};
}

}  // namespace centurion

#endif  // CENTURION_TEXT_INPUT_EVENT_SOURCE