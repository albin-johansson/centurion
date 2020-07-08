#ifndef CENTURION_KEY_STATE_SOURCE
#define CENTURION_KEY_STATE_SOURCE

#include "key_state.hpp"

#include <algorithm>
#include <string>

#include "centurion_utils.hpp"

namespace centurion {
namespace input {

CENTURION_DEF
KeyState::KeyState() noexcept
{
  m_states = SDL_GetKeyboardState(&m_nKeys);
  std::fill(m_previousStates.begin(), m_previousStates.end(), 0);
}

CENTURION_DEF
std::unique_ptr<KeyState> KeyState::unique()
{
  return std::make_unique<KeyState>();
}

CENTURION_DEF
std::shared_ptr<KeyState> KeyState::shared()
{
  return std::make_shared<KeyState>();
}

CENTURION_DEF
void KeyState::update() noexcept
{
  std::copy(m_states, m_states + m_nKeys, m_previousStates.begin());
}

CENTURION_DEF
bool KeyState::is_pressed(const Key& key) const noexcept
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code];
  } else {
    return false;
  }
}

CENTURION_DEF
bool KeyState::is_held(const Key& key) const noexcept
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code] && m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
bool KeyState::was_just_pressed(const Key& key) const noexcept
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code] && !m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
bool KeyState::was_just_released(const Key& key) const noexcept
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return !m_states[code] && m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
bool KeyState::modifier_active(KeyModifier modifier) const noexcept
{
  return static_cast<SDL_Keymod>(modifier) & SDL_GetModState();
}

}  // namespace input
}  // namespace centurion

#endif  // CENTURION_KEY_STATE_SOURCE