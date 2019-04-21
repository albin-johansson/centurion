#include "ctn_mouse_event.h"

namespace centurion {
namespace events {

MouseEvent::MouseEvent(SDL_Event event) { this->event = event; }

MouseEvent::~MouseEvent() = default;

int MouseEvent::GetMousePressedX() const noexcept { return event.button.x; }

int MouseEvent::GetMousePressedY() const noexcept { return event.button.y; }

int MouseEvent::GetPressedButtonID() const noexcept {
  return event.button.button;
}

bool MouseEvent::WasButtonReleased() const noexcept {
  return event.button.state == SDL_PRESSED;
}

bool MouseEvent::WasButtonPressed() const noexcept {
  return event.button.state == SDL_RELEASED;
}

bool MouseEvent::WasDoubleClick() const noexcept {
  return event.button.clicks == 2;
}

bool MouseEvent::IsMouseButtonEvent() const noexcept {
  return event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP;
}

bool MouseEvent::IsMouseMotionEvent() const noexcept {
  return event.type == SDL_MOUSEMOTION;
}

bool MouseEvent::IsMouseWheelEvent() const noexcept {
  return event.type == SDL_MOUSEWHEEL;
}

}  // namespace events
}  // namespace centurion