#ifndef CENTURION_KEY_MODIFIER_HEADER
#define CENTURION_KEY_MODIFIER_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <sstream>  // stringstream
#include <string>   // string

#include "../core/integers.hpp"
#include "../core/str.hpp"
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

/**
 * \typedef key_mod
 *
 * \brief Simple shorthand for `key_modifier`.
 *
 * \note In a future major release, `key_modifier` will likely be renamed to `key_mod`.
 *
 * \since 6.2.0
 */
using key_mod = key_modifier;

/**
 * \brief Sets the current key modifier flags.
 *
 * \param mods the modifier flags that will be used.
 *
 * \see `get_modifiers()`
 *
 * \since 6.2.0
 */
inline void set_modifiers(const key_mod mods) noexcept
{
  SDL_SetModState(static_cast<SDL_Keymod>(mods));
}

/**
 * \brief Returns the current key modifier state.
 *
 * \return the current key modifier flags.
 *
 * \see `set_modifiers()`
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto get_modifiers() noexcept -> key_mod
{
  return static_cast<key_mod>(SDL_GetModState());
}

/// \name Key modifier bitwise operators
/// \{

/**
 * \brief Returns the bitwise negation of the supplied modifiers.
 *
 * \param mods the modifiers that will be inverted.
 *
 * \return the bitwise negation of the supplied modifiers.
 *
 * \since 6.1.0
 */
[[nodiscard]] constexpr auto operator~(const key_mod mods) noexcept -> key_mod
{
  return static_cast<key_mod>(~to_underlying(mods));
}

/**
 * \brief Combines two groups of modifiers by applying bitwise OR.
 *
 * \param a the first group of modifiers.
 * \param b the second group of modifiers.
 *
 * \return the bitwise combination of the two groups of modifiers.
 *
 * \since 6.1.0
 */
[[nodiscard]] constexpr auto operator|(const key_mod a, const key_mod b) noexcept -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) | to_underlying(b));
}

/**
 * \brief Combines two groups of modifiers by applying bitwise AND.
 *
 * \param a the first group of modifiers.
 * \param b the second group of modifiers.
 *
 * \return the result of applying bitwise AND between the two modifier groups.
 *
 * \since 6.1.0
 */
[[nodiscard]] constexpr auto operator&(const key_mod a, const key_mod b) noexcept -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) & to_underlying(b));
}

/// \} End of key modifier bitwise operators

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied key modifiers.
 *
 * \details This function returns a string of comma separated values (CSV) if the supplied
 * enumerator is a composite of more than one key modifier. For example,
 * `to_string(key_mod::left_shift | key_mod::right_ctrl) == "left_shift,right_ctrl"`. The
 * order of the enumerators in the returned string mirrors the enumerator declaration
 * order.
 *
 * \details The comma is omitted if you supply an enumerator that only represents a single
 * key modifier.
 *
 * \details The empty string is returned if an invalid enumerator is provided.
 *
 * \details Composite enumerators, such as `key_mod::shift`, will be printed as separate
 * enumerators, i.e. `"left_shift,right_shift"` in the case of `key_mod::shift`.
 *
 * \param mods the key modifiers that will be converted.
 *
 * \return a string of comma separated values of key modifier names.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const key_mod mods) -> std::string
{
  if (mods == key_mod::none) {
    return "none";
  }

  const auto mask = to_underlying(mods);
  std::stringstream stream;

  auto check = [&stream, mask, count = 0](const key_mod mod, const str name) mutable {
    if (mask & to_underlying(mod)) {
      if (count != 0) {
        stream << ',';
      }

      stream << name;
      ++count;
    }
  };

  check(key_mod::left_shift, "left_shift");
  check(key_mod::right_shift, "right_shift");

  check(key_mod::left_ctrl, "left_ctrl");
  check(key_mod::right_ctrl, "right_ctrl");

  check(key_mod::left_alt, "left_alt");
  check(key_mod::right_alt, "right_alt");

  check(key_mod::left_gui, "left_gui");
  check(key_mod::right_gui, "right_gui");

  check(key_mod::num, "num");
  check(key_mod::caps, "caps");
  check(key_mod::mode, "mode");

  return stream.str();
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of the supplied key modifiers.
 *
 * \param stream the output stream that will be used.
 * \param mods the key modifiers that will be printed.
 *
 * \see `to_string(key_mod)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const key_mod mods) -> std::ostream&
{
  return stream << to_string(mods);
}

/// \} End of streaming

/// \} End of group input

/// \cond FALSE

namespace detail {

[[nodiscard]] inline auto is_active(const key_mod modifiers, const u16 currentMask) noexcept
    -> bool
{
  if (modifiers == key_mod::none) {
    return !currentMask;
  }
  else {
    return currentMask & to_underlying(modifiers);
  }
}

[[nodiscard]] inline auto is_only_active(const key_mod modifiers,
                                         const u16 currentMask) noexcept -> bool
{
  if (modifiers == key_mod::none) {
    return !currentMask;
  }

  const auto mask = to_underlying(modifiers);
  const auto hits = currentMask & mask;

  if (hits != mask) {
    return false;  // The specified modifiers were a combo that wasn't fully active
  }
  else {
    const auto others = currentMask & ~hits;
    return hits && !others;
  }
}

[[nodiscard]] inline auto is_only_any_of_active(const key_mod modifiers,
                                                const u16 currentMask) noexcept -> bool
{
  if (modifiers == key_mod::none) {
    return !currentMask;
  }

  const auto mask = to_underlying(modifiers);

  const auto hits = currentMask & mask;
  const auto others = currentMask & ~hits;

  return hits && !others;
}

}  // namespace detail

/// \endcond

}  // namespace cen

#endif  // CENTURION_KEY_MODIFIER_HEADER