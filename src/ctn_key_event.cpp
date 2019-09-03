#include "ctn_key_event.h"

namespace centurion {
namespace events {

KeyEvent::KeyEvent(SDL_Event event) { this->event = event; }

KeyEvent::~KeyEvent() = default;

bool KeyEvent::IsRepeated() const noexcept { return event.key.repeat; }

bool KeyEvent::WasPressed() const noexcept {
  return event.key.state == SDL_PRESSED;
}

bool KeyEvent::WasReleased() const noexcept {
  return event.key.state == SDL_RELEASED;
}

SDL_Keycode KeyEvent::GetKeycode() const noexcept {
  return event.key.keysym.sym;
}

Uint32 KeyEvent::GetKeyEventType() const noexcept { return event.key.type; }

}  // namespace events
}  // namespace centurion