#ifndef CENTURION_SYSWM_EVENT_SOURCE
#define CENTURION_SYSWM_EVENT_SOURCE

#include "syswm_event.hpp"

namespace centurion {
namespace event {

CENTURION_DEF
SysWMEvent::SysWMEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
SysWMEvent::SysWMEvent(const SDL_SysWMEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
SysWMEvent::SysWMEvent(SDL_SysWMEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
SDL_SysWMmsg* SysWMEvent::message() const noexcept
{
  return m_event.msg;
}
}  // namespace event
}  // namespace centurion

#endif  // CENTURION_SYSWM_EVENT_SOURCE