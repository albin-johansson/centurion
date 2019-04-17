#include "key_state.h"
#include <SDL_keyboard.h>

namespace centurion {
namespace input {

KeyState::KeyState() {
  nKeys = 0;
  stateArr = SDL_GetKeyboardState(&nKeys);
  prevStates = std::vector<Uint8>(nKeys);
}

KeyState::~KeyState() {}

void KeyState::CopyStates() noexcept {
  for (Uint8 i = 0; i < nKeys; i++) {
    prevStates.at(i) = stateArr[i];
  }
}

void KeyState::Update() noexcept { CopyStates(); }

bool KeyState::IsPressed(const SDL_Scancode code) const {
  return stateArr[code];
}

bool KeyState::IsHeldDown(const SDL_Scancode code) const {
  return stateArr[code] && prevStates.at(code);
}

bool KeyState::WasReleased(const SDL_Scancode code) const {
  return !stateArr[code] && prevStates.at(code);
}

bool KeyState::IsFirstTrigger(const SDL_Scancode code) const {
  return stateArr[code] && !prevStates.at(code);
}

}  // namespace input
}  // namespace centurion