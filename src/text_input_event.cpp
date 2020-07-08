#ifndef CENTURION_TEXT_INPUT_EVENT_SOURCE
#define CENTURION_TEXT_INPUT_EVENT_SOURCE

#include <utility>

#include "event.hpp"

namespace centurion {
namespace event {

CENTURION_DEF
TextInputEvent::TextInputEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
TextInputEvent::TextInputEvent(const SDL_TextInputEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void TextInputEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
Uint32 TextInputEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
CZString TextInputEvent::text() const noexcept
{
  return m_event.text;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_TEXT_INPUT_EVENT_SOURCE