#include "event.hpp"

namespace centurion {

window_event::window_event() noexcept : common_event{}
{}

window_event::window_event(const SDL_WindowEvent& event) noexcept
    : common_event{event}
{}

auto window_event::event_id() const noexcept -> window_event_id
{
  return static_cast<window_event_id>(m_event.event);
}

auto window_event::data_1() const noexcept -> i32
{
  return m_event.data1;
}

auto window_event::data_2() const noexcept -> i32
{
  return m_event.data2;
}

}  // namespace centurion
