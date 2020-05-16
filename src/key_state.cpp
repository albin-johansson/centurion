#ifndef CENTURION_KEY_STATE_SOURCE
#define CENTURION_KEY_STATE_SOURCE

#include "key_state.h"

#include <algorithm>
#include <cassert>
#include <string>

#include "centurion_utils.h"

namespace centurion {
namespace input {

CENTURION_DEF
KeyState::KeyState() noexcept
{
  m_states = SDL_GetKeyboardState(&m_nKeys);
  assert(static_cast<unsigned long long>(m_nKeys) == m_previousStates.size());
  std::fill(m_previousStates.begin(), m_previousStates.end(), 0);
}

CENTURION_DEF
UniquePtr<KeyState> KeyState::unique()
{
  return centurion::detail::make_unique<KeyState>();
}

CENTURION_DEF
SharedPtr<KeyState> KeyState::shared()
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
  assert(code < m_nKeys);
  return m_states[code];
}

CENTURION_DEF
bool KeyState::is_held(const Key& key) const noexcept
{
  const auto code = key.scancode();
  assert(code < m_nKeys);
  return m_states[code] && m_previousStates[code];
}

CENTURION_DEF
bool KeyState::was_just_pressed(const Key& key) const noexcept
{
  const auto code = key.scancode();
  assert(code < m_nKeys);
  return m_states[code] && !m_previousStates[code];
}

CENTURION_DEF
bool KeyState::was_just_released(const Key& key) const noexcept
{
  const auto code = key.scancode();
  assert(code < m_nKeys);
  return !m_states[code] && m_previousStates[code];
}

}  // namespace input
}  // namespace centurion

#endif  // CENTURION_KEY_STATE_SOURCE