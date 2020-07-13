#ifndef CENTURION_WINDOW_EVENT_SOURCE
#define CENTURION_WINDOW_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
window_event::window_event() noexcept : common_event{}
{}

CENTURION_DEF
window_event::window_event(const SDL_WindowEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
auto window_event::event_id() const noexcept -> window_event_id
{
  return static_cast<window_event_id>(m_event.event);
}

CENTURION_DEF
auto window_event::data_1() const noexcept -> i32
{
  return m_event.data1;
}

CENTURION_DEF
auto window_event::data_2() const noexcept -> i32
{
  return m_event.data2;
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_EVENT_SOURCE
