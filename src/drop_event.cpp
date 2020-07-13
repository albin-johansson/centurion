#ifndef CENTURION_DROP_EVENT_SOURCE
#define CENTURION_DROP_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
drop_event::drop_event() noexcept : common_event{}
{}

CENTURION_DEF
drop_event::drop_event(const SDL_DropEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
drop_event::drop_event(SDL_DropEvent&& event) noexcept : common_event{event}
{}

CENTURION_DEF
drop_event::~drop_event() noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
}

CENTURION_DEF
void drop_event::set_will_free_file(bool freeFile) noexcept
{
  m_willFreeFile = freeFile;
}

CENTURION_DEF
void drop_event::set_file(char* file) noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
  m_event.file = file;
}

CENTURION_DEF
void drop_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto drop_event::will_free_file() const noexcept -> bool
{
  return m_willFreeFile;
}

CENTURION_DEF
auto drop_event::file() const noexcept -> char*
{
  return m_event.file;
}

CENTURION_DEF
auto drop_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

}  // namespace centurion

#endif  // CENTURION_DROP_EVENT_SOURCE