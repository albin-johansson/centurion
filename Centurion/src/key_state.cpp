#include "key_state.h"
#include <SDL_keyboard.h>

namespace centurion {
namespace input {

KeyState::KeyState() {
  nKeys = 0;
  stateArr = SDL_GetKeyboardState(&nKeys);
  prevStates = std::vector<Uint8>(nKeys);
  for (int i = 0; i < nKeys; i++) {
    prevStates[i] = 0;
  }
}

KeyState::~KeyState() { prevStates.clear(); }

void KeyState::CopyStates() noexcept {
  for (int i = 0; i < nKeys; i++) {
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

std::shared_ptr<KeyState> KeyState::CreateShared() {
  return std::shared_ptr<KeyState>();
}

std::unique_ptr<KeyState> KeyState::CreateUnique() {
  return std::make_unique<KeyState>();
}

std::weak_ptr<KeyState> KeyState::CreateWeak() {
  return std::make_shared<KeyState>();
}

}  // namespace input
}  // namespace centurion