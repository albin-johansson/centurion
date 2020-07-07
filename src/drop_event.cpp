#ifndef CENTURION_DROP_EVENT_SOURCE
#define CENTURION_DROP_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
DropEvent::DropEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
DropEvent::DropEvent(const SDL_DropEvent& event) noexcept : CommonEvent{event}
{}

CENTURION_DEF
DropEvent::DropEvent(SDL_DropEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
auto DropEvent::will_free_file() const noexcept -> bool
{
  return m_willFreeFile;
}

CENTURION_DEF
auto DropEvent::file() const noexcept -> char*
{
  return m_event.file;
}

CENTURION_DEF
auto DropEvent::window_id() const noexcept -> Uint32
{
  return m_event.windowID;
}

}  // namespace centurion::event

#endif  // CENTURION_DROP_EVENT_SOURCE