#ifndef CENTURION_KEYBOARD_EVENT_SOURCE
#define CENTURION_KEYBOARD_EVENT_SOURCE

#include "event.h"

namespace centurion {
namespace event {

CENTURION_DEF
KeyboardEvent::KeyboardEvent() noexcept : TEvent{{}}
{}

CENTURION_DEF
KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& event) noexcept
    : TEvent{event}
{}

CENTURION_DEF
KeyboardEvent::KeyboardEvent(SDL_KeyboardEvent&& event) noexcept : TEvent{event}
{}

CENTURION_DEF
void KeyboardEvent::set_modifier(KeyModifier modifier, bool active) noexcept
{
  const auto flag = static_cast<SDL_Keymod>(modifier);
  if (active) {
    m_event.keysym.mod |= flag;
  } else {
    m_event.keysym.mod &= ~flag;
  }
}

CENTURION_DEF
bool KeyboardEvent::is_key_active(SDL_Keycode keycode) const noexcept
{
  return m_event.keysym.sym == keycode;
}

CENTURION_DEF
bool KeyboardEvent::is_key_active(SDL_Scancode scancode) const noexcept
{
  return m_event.keysym.scancode == scancode;
}

CENTURION_DEF
bool KeyboardEvent::modifier_active(KeyModifier modifier) const noexcept
{
  return m_event.keysym.mod & static_cast<SDL_Keymod>(modifier);
}

CENTURION_DEF
bool KeyboardEvent::shift_active() const noexcept
{
  return modifier_active(KeyModifier::LeftShift) ||
         modifier_active(KeyModifier::RightShift);
}

CENTURION_DEF
bool KeyboardEvent::ctrl_active() const noexcept
{
  return modifier_active(KeyModifier::LeftControl) ||
         modifier_active(KeyModifier::RightControl);
}

CENTURION_DEF
bool KeyboardEvent::alt_active() const noexcept
{
  return modifier_active(KeyModifier::LeftAlt) ||
         modifier_active(KeyModifier::RightAlt);
}

CENTURION_DEF
bool KeyboardEvent::gui_active() const noexcept
{
  return modifier_active(KeyModifier::LeftGUI) ||
         modifier_active(KeyModifier::RightGUI);
}

CENTURION_DEF
bool KeyboardEvent::caps_active() const noexcept
{
  return modifier_active(KeyModifier::Caps);
}

CENTURION_DEF
bool KeyboardEvent::num_active() const noexcept
{
  return modifier_active(KeyModifier::Num);
}

CENTURION_DEF
bool KeyboardEvent::repeated() const noexcept
{
  return m_event.repeat;
}

CENTURION_DEF
ButtonState KeyboardEvent::state() const noexcept
{
  return static_cast<ButtonState>(m_event.state);
}

CENTURION_DEF
SDL_Scancode KeyboardEvent::scancode() const noexcept
{
  return m_event.keysym.scancode;
}

CENTURION_DEF
SDL_Keycode KeyboardEvent::keycode() const noexcept
{
  return m_event.keysym.sym;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_KEYBOARD_EVENT_SOURCE