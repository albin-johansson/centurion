#include "event.h"

namespace centurion {
namespace events {

Event::Event(SDL_Event event) { this->event = event; }

Event::~Event() = default;

}  // namespace events
}  // namespace centurion