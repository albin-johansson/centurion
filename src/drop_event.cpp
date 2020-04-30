#ifndef CENTURION_DROP_EVENT_SOURCE
#define CENTURION_DROP_EVENT_SOURCE

#include "drop_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
DropEvent::DropEvent() noexcept : BaseEvent{}, m_willFreeFile{true}
{}

CENTURION_DEF
DropEvent::DropEvent(const SDL_DropEvent& event) noexcept
    : BaseEvent{event}, m_willFreeFile{true}
{}

CENTURION_DEF
DropEvent::DropEvent(SDL_DropEvent&& event) noexcept
    : BaseEvent{std::move(event)}, m_willFreeFile{true}
{}

CENTURION_DEF
DropEvent::~DropEvent() noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
}

CENTURION_DEF
void DropEvent::set_will_free_file(bool freeFile) noexcept
{
  m_willFreeFile = freeFile;
}

CENTURION_DEF
void DropEvent::set_file(char* file) noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
  m_event.file = file;
}

CENTURION_DEF
void DropEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
void DropEvent::set_type(DropEventType type) noexcept
{
  m_event.type = static_cast<Uint32>(type);
}

CENTURION_DEF
bool DropEvent::will_free_file() const noexcept
{
  return m_willFreeFile;
}

CENTURION_DEF
char* DropEvent::file() const noexcept
{
  return m_event.file;
}

CENTURION_DEF
Uint32 DropEvent::window_id() const noexcept
{
  return m_event.windowID;
}

CENTURION_DEF
DropEventType DropEvent::type() const noexcept
{
  return static_cast<DropEventType>(m_event.type);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_DROP_EVENT_SOURCE