#ifndef CENTURION_KEYBOARD_EVENT_SOURCE
#define CENTURION_KEYBOARD_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
keyboard_event::keyboard_event() noexcept : common_event{}
{}

CENTURION_DEF
keyboard_event::keyboard_event(const SDL_KeyboardEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void keyboard_event::set_scan_code(const scan_code& code) noexcept
{
  m_event.keysym.scancode = code.get();
}

CENTURION_DEF
void keyboard_event::set_key_code(const key_code& code) noexcept
{
  m_event.keysym.sym = code.get();
}

CENTURION_DEF
void keyboard_event::set_button_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
void keyboard_event::set_modifier(key_modifier modifier, bool active) noexcept
{
  if (active) {
    m_event.keysym.mod |= static_cast<u16>(modifier);
  } else {
    m_event.keysym.mod &= ~static_cast<u16>(modifier);
  }
}

CENTURION_DEF
void keyboard_event::set_repeated(bool repeated) noexcept
{
  m_event.repeat = repeated;
}

CENTURION_DEF
void keyboard_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto keyboard_event::is_active(const scan_code& code) const noexcept -> bool
{
  return m_event.keysym.scancode == code.get();
}

CENTURION_DEF
auto keyboard_event::is_active(const key_code& code) const noexcept -> bool
{
  return static_cast<SDL_KeyCode>(m_event.keysym.sym) == code.get();
}

CENTURION_DEF
auto keyboard_event::modifier_active(key_modifier modifier) const noexcept
    -> bool
{
  return m_event.keysym.mod & static_cast<u16>(modifier);
}

CENTURION_DEF
auto keyboard_event::shift_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_shift) ||
         modifier_active(key_modifier::right_shift);
}

CENTURION_DEF
auto keyboard_event::ctrl_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_ctrl) ||
         modifier_active(key_modifier::right_ctrl);
}

CENTURION_DEF
auto keyboard_event::alt_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_alt) ||
         modifier_active(key_modifier::right_alt);
}

CENTURION_DEF
auto keyboard_event::gui_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_gui) ||
         modifier_active(key_modifier::right_gui);
}

CENTURION_DEF
auto keyboard_event::caps_active() const noexcept -> bool
{
  return modifier_active(key_modifier::caps);
}

CENTURION_DEF
auto keyboard_event::num_active() const noexcept -> bool
{
  return modifier_active(key_modifier::num);
}

CENTURION_DEF
auto keyboard_event::repeated() const noexcept -> bool
{
  return m_event.repeat;
}

CENTURION_DEF
auto keyboard_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

CENTURION_DEF
auto keyboard_event::get_scan_code() const noexcept -> scan_code
{
  return m_event.keysym.scancode;
}

CENTURION_DEF
auto keyboard_event::get_key_code() const noexcept -> key_code
{
  return static_cast<SDL_KeyCode>(m_event.keysym.sym);
}

CENTURION_DEF
auto keyboard_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

}  // namespace centurion

#endif  // CENTURION_KEYBOARD_EVENT_SOURCE