#ifndef CENTURION_KEY_MODIFIER_HEADER
#define CENTURION_KEY_MODIFIER_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum key_modifier
 *
 * \brief Represents different key modifiers.
 *
 * \note This is a flag enum, and provides overloads for the common bitwise operators.
 *
 * \todo Centurion 7: Rename this enum to `key_mod`.
 * \todo Centurion 7: Replace left_{}/right_{} prefixes with l{}/r{}.
 *
 * \see `key_mod`
 * \see `SDL_Keymod`
 * \see `operator~(key_mod)`
 * \see `operator|(key_mod, key_mod)`
 * \see `operator&(key_mod, key_mod)`
 *
 * \since 3.1.0
 */
enum class key_modifier : u16
{
  none = KMOD_NONE,
  left_shift = KMOD_LSHIFT,
  right_shift = KMOD_RSHIFT,
  left_ctrl = KMOD_LCTRL,
  right_ctrl = KMOD_RCTRL,
  left_alt = KMOD_LALT,
  right_alt = KMOD_RALT,
  left_gui = KMOD_LGUI,
  right_gui = KMOD_RGUI,
  shift = KMOD_SHIFT,
  ctrl = KMOD_CTRL,
  alt = KMOD_ALT,
  gui = KMOD_GUI,
  num = KMOD_NUM,
  caps = KMOD_CAPS,
  mode = KMOD_MODE,

  reserved = KMOD_RESERVED
};

using key_mod = key_modifier;

/// \since 6.1.0
[[nodiscard]] constexpr auto operator~(const key_mod mod) noexcept -> key_mod
{
  return static_cast<key_mod>(~to_underlying(mod));
}

/// \since 6.1.0
[[nodiscard]] constexpr auto operator|(const key_mod a, const key_mod b) noexcept
    -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) | to_underlying(b));
}

/// \since 6.1.0
[[nodiscard]] constexpr auto operator&(const key_mod a, const key_mod b) noexcept
    -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) & to_underlying(b));
}

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_KEY_MODIFIER_HEADER