#include "event.hpp"

namespace centurion {

quit_event::quit_event() noexcept : common_event{}
{}

quit_event::quit_event(const SDL_QuitEvent& event) noexcept
    : common_event{event}
{}

}  // namespace centurion
