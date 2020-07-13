#ifndef CENTURION_KEY_STATE_SOURCE
#define CENTURION_KEY_STATE_SOURCE

#include "key_state.hpp"

#include <algorithm>
#include <string>

#include "centurion_utils.hpp"
#include "key_code.hpp"
#include "scan_code.hpp"

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
auto key_state::is_pressed(const scan_code& code) const noexcept -> bool
{
  const auto scanCode = code.get();
  if (scanCode >= 0 && scanCode < m_nKeys) {
    return m_states[scanCode];
  } else {
    return false;
  }
}

CENTURION_DEF
auto key_state::is_pressed(const key_code& code) const noexcept -> bool
{
  return is_pressed(scan_code{code.get()});
}

CENTURION_DEF
auto key_state::is_held(const scan_code& code) const noexcept -> bool
{
  const auto scanCode = code.get();
  if (scanCode >= 0 && scanCode < m_nKeys) {
    return m_states[scanCode] && m_previousStates[scanCode];
  } else {
    return false;
  }
}

auto key_state::is_held(const key_code& code) const noexcept -> bool
{
  return is_held(scan_code{code.get()});
}

CENTURION_DEF
auto key_state::was_just_pressed(const scan_code& code) const noexcept -> bool
{
  const auto scanCode = code.get();
  if (scanCode >= 0 && scanCode < m_nKeys) {
    return m_states[scanCode] && !m_previousStates[scanCode];
  } else {
    return false;
  }
}

auto key_state::was_just_pressed(const key_code& code) const noexcept -> bool
{
  return was_just_pressed(scan_code{code.get()});
}

CENTURION_DEF
auto key_state::was_just_released(const scan_code& code) const noexcept -> bool
{
  const auto scanCode = code.get();
  if (scanCode >= 0 && scanCode < m_nKeys) {
    return !m_states[scanCode] && m_previousStates[scanCode];
  } else {
    return false;
  }
}

auto key_state::was_just_released(const key_code& code) const noexcept -> bool
{
  return was_just_released(scan_code{code.get()});
}

CENTURION_DEF
auto key_state::modifier_active(key_modifier modifier) noexcept -> bool
{
  return static_cast<SDL_Keymod>(modifier) & SDL_GetModState();
}

}  // namespace centurion::input

#endif  // CENTURION_KEY_STATE_SOURCE