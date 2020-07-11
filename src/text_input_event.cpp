#ifndef CENTURION_TEXT_INPUT_EVENT_SOURCE
#define CENTURION_TEXT_INPUT_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
TextInputEvent::TextInputEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
TextInputEvent::TextInputEvent(const SDL_TextInputEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void TextInputEvent::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto TextInputEvent::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

CENTURION_DEF
auto TextInputEvent::text() const noexcept -> std::string_view
{
  return std::string_view{static_cast<czstring>(m_event.text)};
}

}  // namespace centurion

#endif  // CENTURION_TEXT_INPUT_EVENT_SOURCE