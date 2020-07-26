#include "event.hpp"

namespace centurion {

drop_event::drop_event() noexcept : common_event{}
{}

drop_event::drop_event(const SDL_DropEvent& event) noexcept
    : common_event{event}
{}

drop_event::drop_event(SDL_DropEvent&& event) noexcept : common_event{event}
{}

drop_event::~drop_event() noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
}

void drop_event::set_will_free_file(bool freeFile) noexcept
{
  m_willFreeFile = freeFile;
}

void drop_event::set_file(char* file) noexcept
{
  if (m_event.file && m_willFreeFile) {
    SDL_free(m_event.file);
  }
  m_event.file = file;
}

void drop_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

auto drop_event::will_free_file() const noexcept -> bool
{
  return m_willFreeFile;
}

auto drop_event::file() const noexcept -> char*
{
  return m_event.file;
}

auto drop_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

}  // namespace centurion
