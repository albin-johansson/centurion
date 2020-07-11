#ifndef CENTURION_KEY_SOURCE
#define CENTURION_KEY_SOURCE

#include "key.hpp"

#include <SDL.h>

namespace centurion {

CENTURION_DEF
Key::Key(SDL_Keycode keycode) noexcept
{
  set(keycode);
}

CENTURION_DEF
Key::Key(czstring name) noexcept : Key{}
{
  if (name) {
    set(SDL_GetScancodeFromName(name));
  }
}

CENTURION_DEF
Key::Key(SDL_Scancode scancode) noexcept
{
  set(scancode);
}

CENTURION_DEF
void Key::set(SDL_Scancode scancode) noexcept
{
  m_scancode = scancode;
  m_keycode = SDL_GetKeyFromScancode(scancode);
}

CENTURION_DEF
void Key::set(SDL_Keycode keycode) noexcept
{
  m_scancode = SDL_GetScancodeFromKey(keycode);
  m_keycode = keycode;
}

CENTURION_DEF
auto Key::name() const -> std::string
{
  return SDL_GetScancodeName(m_scancode);
}

}  // namespace centurion

#endif  // CENTURION_KEY_SOURCE
