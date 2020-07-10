#ifndef CENTURION_QUIT_EVENT_SOURCE
#define CENTURION_QUIT_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
QuitEvent::QuitEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
QuitEvent::QuitEvent(const SDL_QuitEvent& event) noexcept : CommonEvent{event}
{}

}  // namespace centurion

#endif  // CENTURION_QUIT_EVENT_SOURCE