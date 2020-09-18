#include "event.hpp"

namespace cen {

quit_event::quit_event() noexcept : common_event{}
{}

quit_event::quit_event(const SDL_QuitEvent& event) noexcept
    : common_event{event}
{}

}  // namespace cen
