#include "key_state.h"
#include <string>
#include <algorithm>
#include <cassert>
#include "centurion_exception.h"

namespace centurion {

KeyState::KeyState() {
  states = SDL_GetKeyboardState(&nKeys);
  if (!states) {
    throw CenturionException("Failed to obtain key state! Error: " + std::string{SDL_GetError()});
  }
  assert(nKeys == previousStates.size());
  std::fill(previousStates.begin(), previousStates.end(), 0);
}

KeyState::~KeyState() noexcept = default;

void KeyState::update() noexcept {
  std::copy(states, states + nKeys, previousStates.begin());
}

bool KeyState::is_pressed(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return states[code];
}

bool KeyState::is_held(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return states[code] && previousStates[code];
}

bool KeyState::was_just_pressed(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return states[code] && !previousStates[code];
}

bool KeyState::was_just_released(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return !states[code] && previousStates[code];
}

int KeyState::get_amount_of_keys() const noexcept {
  return nKeys;
}

}
