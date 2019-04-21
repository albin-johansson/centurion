#include "ctn_event.h"

namespace centurion {
namespace events {

Event::Event(SDL_Event event)
    : mouseEvent(MouseEvent(event)), keyEvent(KeyEvent(event)) {
  this->event = event;
}

Event::~Event() = default;

bool Event::IsKeyEvent() const noexcept {
  return (event.type == SDL_KEYUP) || (event.type == SDL_KEYDOWN);
}

bool Event::IsMouseEvent() const noexcept {
  return event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP ||
         event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEWHEEL;
}

}  // namespace events
}  // namespace centurion