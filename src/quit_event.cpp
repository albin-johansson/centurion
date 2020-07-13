#ifndef CENTURION_QUIT_EVENT_SOURCE
#define CENTURION_QUIT_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
quit_event::quit_event() noexcept : common_event{}
{}

CENTURION_DEF
quit_event::quit_event(const SDL_QuitEvent& event) noexcept
    : common_event{event}
{}

}  // namespace centurion

#endif  // CENTURION_QUIT_EVENT_SOURCE