#ifndef CENTURION_QUIT_EVENT_SOURCE
#define CENTURION_QUIT_EVENT_SOURCE

#include "new_event.h"

namespace centurion {

CENTURION_DEF
QuitEvent::QuitEvent() noexcept : TEvent{}
{}

CENTURION_DEF
QuitEvent::QuitEvent(const SDL_QuitEvent& event) noexcept : TEvent{event}
{}

CENTURION_DEF
QuitEvent::QuitEvent(SDL_QuitEvent&& event) noexcept : TEvent{std::move(event)}
{}

}  // namespace centurion

#endif  // CENTURION_QUIT_EVENT_SOURCE