#include "event.hpp"

namespace cen {

keyboard_event::keyboard_event() noexcept : common_event{}
{}

keyboard_event::keyboard_event(const SDL_KeyboardEvent& event) noexcept
    : common_event{event}
{}

void keyboard_event::set_scan_code(const scan_code& code) noexcept
{
  m_event.keysym.scancode = code.get();
}

void keyboard_event::set_key_code(const key_code& code) noexcept
{
  m_event.keysym.sym = code.get();
}

void keyboard_event::set_button_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

void keyboard_event::set_modifier(key_modifier modifier, bool active) noexcept
{
  if (active) {
    m_event.keysym.mod |= static_cast<u16>(modifier);
  } else {
    m_event.keysym.mod &= ~static_cast<u16>(modifier);
  }
}

void keyboard_event::set_repeated(bool repeated) noexcept
{
  m_event.repeat = repeated;
}

void keyboard_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

auto keyboard_event::is_active(const scan_code& code) const noexcept -> bool
{
  return m_event.keysym.scancode == code.get();
}

auto keyboard_event::is_active(const key_code& code) const noexcept -> bool
{
  return static_cast<SDL_KeyCode>(m_event.keysym.sym) == code.get();
}

auto keyboard_event::modifier_active(key_modifier modifier) const noexcept
    -> bool
{
  return m_event.keysym.mod & static_cast<u16>(modifier);
}

auto keyboard_event::shift_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_shift) ||
         modifier_active(key_modifier::right_shift);
}

auto keyboard_event::ctrl_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_ctrl) ||
         modifier_active(key_modifier::right_ctrl);
}

auto keyboard_event::alt_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_alt) ||
         modifier_active(key_modifier::right_alt);
}

auto keyboard_event::gui_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_gui) ||
         modifier_active(key_modifier::right_gui);
}

auto keyboard_event::caps_active() const noexcept -> bool
{
  return modifier_active(key_modifier::caps);
}

auto keyboard_event::num_active() const noexcept -> bool
{
  return modifier_active(key_modifier::num);
}

auto keyboard_event::repeated() const noexcept -> bool
{
  return m_event.repeat;
}

auto keyboard_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

auto keyboard_event::released() const noexcept -> bool
{
  return state() == button_state::released;
}

auto keyboard_event::pressed() const noexcept -> bool
{
  return state() == button_state::pressed;
}

auto keyboard_event::get_scan_code() const noexcept -> scan_code
{
  return m_event.keysym.scancode;
}

auto keyboard_event::get_key_code() const noexcept -> key_code
{
  return static_cast<SDL_KeyCode>(m_event.keysym.sym);
}

auto keyboard_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

}  // namespace cen
