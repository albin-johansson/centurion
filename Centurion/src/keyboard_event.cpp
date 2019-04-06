#include "keyboard_event.h"

namespace centurion {
namespace events {

KeyboardEvent::KeyboardEvent(SDL_Event event) { this->event = event; }

KeyboardEvent::~KeyboardEvent() = default;

bool KeyboardEvent::IsRepeated() const { return event.key.repeat; }

bool KeyboardEvent::WasPressed() const {
  return event.key.state == SDL_PRESSED;
}

bool KeyboardEvent::WasReleased() const {
  return event.key.state == SDL_RELEASED;
}

SDL_Keycode KeyboardEvent::GetKeycode() const { return event.key.keysym.sym; }

uint32_t KeyboardEvent::GetKeyEventType() const { return event.key.type; }

}  // namespace events
}  // namespace centurion