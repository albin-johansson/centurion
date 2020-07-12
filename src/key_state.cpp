#ifndef CENTURION_KEY_STATE_SOURCE
#define CENTURION_KEY_STATE_SOURCE

#include "key_state.hpp"

#include <algorithm>
#include <string>

#include "centurion_utils.hpp"

namespace centurion::input {

CENTURION_DEF
key_state::key_state() noexcept
{
  m_states = SDL_GetKeyboardState(&m_nKeys);
  std::fill(m_previousStates.begin(), m_previousStates.end(), 0);
}

CENTURION_DEF
auto key_state::unique() -> std::unique_ptr<key_state>
{
  return std::make_unique<key_state>();
}

CENTURION_DEF
auto key_state::shared() -> std::shared_ptr<key_state>
{
  return std::make_shared<key_state>();
}

CENTURION_DEF
void key_state::update() noexcept
{
  std::copy(m_states, m_states + m_nKeys, m_previousStates.begin());
}

CENTURION_DEF
auto key_state::is_pressed(const key& key) const noexcept -> bool
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code];
  } else {
    return false;
  }
}

CENTURION_DEF
auto key_state::is_held(const key& key) const noexcept -> bool
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code] && m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
auto key_state::was_just_pressed(const key& key) const noexcept -> bool
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return m_states[code] && !m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
auto key_state::was_just_released(const key& key) const noexcept -> bool
{
  const auto code = key.scancode();
  if (code >= 0 && code < m_nKeys) {
    return !m_states[code] && m_previousStates[code];
  } else {
    return false;
  }
}

CENTURION_DEF
auto key_state::modifier_active(key_modifier modifier) noexcept -> bool
{
  return static_cast<SDL_Keymod>(modifier) & SDL_GetModState();
}

}  // namespace centurion::input

#endif  // CENTURION_KEY_STATE_SOURCE