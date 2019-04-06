#include "mouse_event.h"

namespace centurion {
namespace events {

MouseEvent::MouseEvent(SDL_Event event) { this->event = event; }

MouseEvent::~MouseEvent() = default;

int MouseEvent::GetMousePressedX() { return event.button.x; }

int MouseEvent::GetMousePressedY() { return event.button.y; }

int MouseEvent::GetPressedButtonID() { return event.button.button; }

bool MouseEvent::WasButtonReleased() {
  return event.button.state == SDL_PRESSED;
}

bool MouseEvent::WasButtonPressed() {
  return event.button.state == SDL_RELEASED;
}

bool MouseEvent::WasDoubleClick() { return event.button.clicks == 2; }

bool MouseEvent::IsMousePressedEvent() {
  return event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP;
}

bool MouseEvent::IsMouseMotionEvent() { return event.type == SDL_MOUSEMOTION; }

bool MouseEvent::IsMouseWheelEvent() { return event.type == SDL_MOUSEWHEEL; }

}  // namespace events
}  // namespace centurion