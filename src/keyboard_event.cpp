#ifndef CENTURION_KEYBOARD_EVENT_SOURCE
#define CENTURION_KEYBOARD_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
KeyboardEvent::KeyboardEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void KeyboardEvent::set_key(const Key& key, button_state state) noexcept
{
  m_event.keysym.scancode = key.scancode();
  m_event.keysym.sym = key.keycode();
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
void KeyboardEvent::set_modifier(key_modifier modifier, bool active) noexcept
{
  if (active) {
    m_event.keysym.mod |= static_cast<u16>(modifier);
  } else {
    m_event.keysym.mod &= ~static_cast<u16>(modifier);
  }
}

CENTURION_DEF
void KeyboardEvent::set_repeated(bool repeated) noexcept
{
  m_event.repeat = repeated;
}

CENTURION_DEF
void KeyboardEvent::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto KeyboardEvent::is_active(const Key& key) const noexcept -> bool
{
  return m_event.keysym.sym == key.keycode();
}

CENTURION_DEF
auto KeyboardEvent::modifier_active(key_modifier modifier) const noexcept -> bool
{
  return m_event.keysym.mod & static_cast<u16>(modifier);
}

CENTURION_DEF
auto KeyboardEvent::shift_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_shift) ||
         modifier_active(key_modifier::right_shift);
}

CENTURION_DEF
auto KeyboardEvent::ctrl_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_ctrl) ||
         modifier_active(key_modifier::right_ctrl);
}

CENTURION_DEF
auto KeyboardEvent::alt_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_alt) ||
         modifier_active(key_modifier::right_alt);
}

CENTURION_DEF
auto KeyboardEvent::gui_active() const noexcept -> bool
{
  return modifier_active(key_modifier::left_gui) ||
         modifier_active(key_modifier::right_gui);
}

CENTURION_DEF
auto KeyboardEvent::caps_active() const noexcept -> bool
{
  return modifier_active(key_modifier::caps);
}

CENTURION_DEF
auto KeyboardEvent::num_active() const noexcept -> bool
{
  return modifier_active(key_modifier::num);
}

CENTURION_DEF
auto KeyboardEvent::repeated() const noexcept -> bool
{
  return m_event.repeat;
}

CENTURION_DEF
auto KeyboardEvent::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

CENTURION_DEF
auto KeyboardEvent::key() const noexcept -> Key
{
  return Key{m_event.keysym.scancode};
}

CENTURION_DEF
auto KeyboardEvent::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

}  // namespace centurion

#endif  // CENTURION_KEYBOARD_EVENT_SOURCE