#ifndef CENTURION_QUIT_EVENT_SOURCE
#define CENTURION_QUIT_EVENT_SOURCE

#include "quit_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
QuitEvent::QuitEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
QuitEvent::QuitEvent(const SDL_QuitEvent& event) noexcept : CommonEvent{event}
{}

CENTURION_DEF
QuitEvent::QuitEvent(SDL_QuitEvent&& event) noexcept
    : CommonEvent{std::forward<SDL_QuitEvent>(event)}
{}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_QUIT_EVENT_SOURCE