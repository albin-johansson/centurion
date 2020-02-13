#ifndef CENTURION_KEY_STATE_SOURCE
#define CENTURION_KEY_STATE_SOURCE

#include "key_state.h"

#include <algorithm>
#include <cassert>
#include <string>

#include "centurion_exception.h"
#include "error.h"

namespace centurion {

CENTURION_DEF KeyState::KeyState() {
  states = SDL_GetKeyboardState(&nKeys);
  if (!states) {
    throw CenturionException("Failed to obtain key state! " + Error::msg());
  }
  assert(static_cast<unsigned long long>(nKeys) == previousStates.size());
  std::fill(previousStates.begin(), previousStates.end(), 0);
}

CENTURION_DEF std::unique_ptr<KeyState> KeyState::unique() {
  return std::make_unique<KeyState>();
}

CENTURION_DEF std::shared_ptr<KeyState> KeyState::shared() {
  return std::make_shared<KeyState>();
}

CENTURION_DEF void KeyState::update() noexcept {
  std::copy(states, states + nKeys, previousStates.begin());
}

CENTURION_DEF bool KeyState::is_pressed(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return states[code];
}

CENTURION_DEF bool KeyState::is_held(SDL_Scancode code) const noexcept {
  assert(code < nKeys);
  return states[code] && previousStates[code];
}

CENTURION_DEF bool KeyState::was_just_pressed(SDL_Scancode code) const
    noexcept {
  assert(code < nKeys);
  return states[code] && !previousStates[code];
}

CENTURION_DEF bool KeyState::was_just_released(SDL_Scancode code) const
    noexcept {
  assert(code < nKeys);
  return !states[code] && previousStates[code];
}

CENTURION_DEF int KeyState::get_amount_of_keys() const noexcept {
  return nKeys;
}

}  // namespace centurion

#endif  // CENTURION_KEY_STATE_SOURCE