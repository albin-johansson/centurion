#include "key_handler.h"
#include <SDL_events.h>
#include <stdexcept>
#include "key_trigger.h"

using centurion::events::KeyTrigger;

namespace centurion {
namespace keys {

KeyHandler::KeyHandler() {
  nKeys = 0;
  stateArr = SDL_GetKeyboardState(&nKeys);
  prevStates = std::vector<Uint8>(nKeys);
}

KeyHandler::~KeyHandler() {}

bool KeyHandler::ShouldTriggerKeyAction(const Key_sptr key) const {
  if (key == nullptr) {
    throw std::invalid_argument("Null key pointer!");
  }

  SDL_Scancode code = key->GetScancode();
  if (stateArr[code]) {
    return (key->GetKeyTrigger() == KeyTrigger::IMMEDIATE);
  } else {
    return ((key->GetKeyTrigger() == KeyTrigger::RELEASE) && WasReleased(code));
  }
}

void KeyHandler::CopyStates() {
  for (int i = 0; i < nKeys; i++) {
    prevStates.at(i) = stateArr[i];
  }
}

void KeyHandler::Update() {
  SDL_PumpEvents();
  for (Key_sptr key : keys) {
    if ((key != nullptr) && (ShouldTriggerKeyAction(key))) {
      key->Trigger();
    }
  }
  CopyStates();
}

void KeyHandler::AddKey(Key_sptr key) {
  if (key == nullptr) {
    throw std::invalid_argument("Null key pointer!");
  } else {
    keys.push_back(key);
  }
}

}  // namespace keys
}  // namespace centurion