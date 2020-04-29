#ifndef CENTURION_QUIT_EVENT_SOURCE
#define CENTURION_QUIT_EVENT_SOURCE

#include "quit_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
QuitEvent::QuitEvent() noexcept : BaseEvent{}
{}

CENTURION_DEF
QuitEvent::QuitEvent(const SDL_QuitEvent& event) noexcept : BaseEvent{event}
{}

CENTURION_DEF
QuitEvent::QuitEvent(SDL_QuitEvent&& event) noexcept
    : BaseEvent{std::move(event)}
{}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_QUIT_EVENT_SOURCE