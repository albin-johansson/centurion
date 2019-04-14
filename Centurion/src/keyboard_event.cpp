#include "keyboard_event.h"

namespace centurion {
namespace events {

KeyboardEvent::KeyboardEvent(SDL_Event event) { this->event = event; }

KeyboardEvent::~KeyboardEvent() = default;

bool KeyboardEvent::IsRepeated() const noexcept { return event.key.repeat; }

bool KeyboardEvent::WasPressed() const noexcept {
  return event.key.state == SDL_PRESSED;
}

bool KeyboardEvent::WasReleased() const noexcept {
  return event.key.state == SDL_RELEASED;
}

SDL_Keycode KeyboardEvent::GetKeycode() const noexcept {
  return event.key.keysym.sym;
}

uint32_t KeyboardEvent::GetKeyEventType() const noexcept {
  return event.key.type;
}

}  // namespace events
}  // namespace centurion