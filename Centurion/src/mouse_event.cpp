#include "mouse_event.h"

namespace centurion {
namespace events {

MouseEvent::MouseEvent(SDL_Event event) { this->event = event; }

MouseEvent::~MouseEvent() = default;

int MouseEvent::GetMousePressedX() const { return event.button.x; }

int MouseEvent::GetMousePressedY() const { return event.button.y; }

int MouseEvent::GetPressedButtonID() const { return event.button.button; }

bool MouseEvent::WasButtonReleased() const {
  return event.button.state == SDL_PRESSED;
}

bool MouseEvent::WasButtonPressed() const {
  return event.button.state == SDL_RELEASED;
}

bool MouseEvent::WasDoubleClick() const { return event.button.clicks == 2; }

bool MouseEvent::IsMouseButtonEvent() const {
  return event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP;
}

bool MouseEvent::IsMouseMotionEvent() const {
  return event.type == SDL_MOUSEMOTION;
}

bool MouseEvent::IsMouseWheelEvent() const {
  return event.type == SDL_MOUSEWHEEL;
}

}  // namespace events
}  // namespace centurion