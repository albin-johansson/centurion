#include "key_state.hpp"

#include <algorithm>
#include <string>
#include <type_traits>

#include "detail/utils.hpp"
#include "key_code.hpp"
#include "scan_code.hpp"

namespace centurion {

static_assert(std::is_final_v<key_state>);
static_assert(std::is_default_constructible_v<key_state>);
static_assert(std::is_nothrow_destructible_v<key_state>);
static_assert(std::is_nothrow_move_constructible_v<key_state>);
static_assert(std::is_nothrow_move_assignable_v<key_state>);
static_assert(std::is_nothrow_copy_constructible_v<key_state>);
static_assert(std::is_nothrow_copy_assignable_v<key_state>);

key_state::key_state() noexcept
{
  m_states = SDL_GetKeyboardState(&m_nKeys);
  std::fill(m_previousStates.begin(), m_previousStates.end(), 0);
}

void key_state::update() noexcept
{
  std::copy(m_states, m_states + m_nKeys, m_previousStates.begin());
}

auto key_state::is_pressed(const scan_code& code) const noexcept -> bool
{
  const auto scanCode = code.get();
  if (scanCode >= 0 && scanCode < m_nKeys) {
    return m_states[scanCode];
  } else {
    return false;
  }
}

auto key_state::is_pressed(const key_code& code) const noexcept -> bool
{
  return is_pressed(scan_code{code.get()});
}

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

auto key_state::modifier_active(key_modifier modifier) noexcept -> bool
{
  return static_cast<SDL_Keymod>(modifier) & SDL_GetModState();
}

}  // namespace centurion
