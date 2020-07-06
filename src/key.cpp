#ifndef CENTURION_KEY_SOURCE
#define CENTURION_KEY_SOURCE

#include "key.hpp"

#include <SDL.h>

namespace centurion {

CENTURION_DEF
Key::Key() noexcept : m_scancode{SDL_SCANCODE_UNKNOWN}, m_keycode{SDLK_UNKNOWN}
{}

CENTURION_DEF
Key::Key(SDL_Keycode keycode) noexcept
{
  set(keycode);
}

CENTURION_DEF
Key::Key(CZString name) noexcept : Key{}
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
std::string Key::name() const noexcept
{
  return SDL_GetScancodeName(m_scancode);
}

CENTURION_DEF
bool operator==(const Key& lhs, const Key& rhs) noexcept
{
  return lhs.scancode() == rhs.scancode();
}

CENTURION_DEF
bool operator!=(const Key& lhs, const Key& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_KEY_SOURCE
