#ifndef CENTURION_DROP_EVENT_SOURCE
#define CENTURION_DROP_EVENT_SOURCE

#include "drop_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
DropEvent::DropEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
DropEvent::DropEvent(const SDL_DropEvent& event) noexcept : CommonEvent{event}
{}

CENTURION_DEF
DropEvent::DropEvent(SDL_DropEvent&& event) noexcept
    : CommonEvent{std::forward<SDL_DropEvent>(event)}
// FIXME can this introduce leak?
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

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_DROP_EVENT_SOURCE