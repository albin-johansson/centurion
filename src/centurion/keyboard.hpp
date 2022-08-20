/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_KEYBOARD_HPP_
#define CENTURION_KEYBOARD_HPP_

#include <SDL.h>

#include <algorithm>  // copy
#include <array>      // array
#include <cassert>    // assert
#include <ostream>    // ostream
#include <sstream>    // stringstream
#include <string>     // string, to_string

#include "common.hpp"
#include "features.hpp"
#include "version.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class key_mod : uint16
{
  none = KMOD_NONE,

  lshift = KMOD_LSHIFT,
  rshift = KMOD_RSHIFT,
  shift = KMOD_SHIFT,

  lctrl = KMOD_LCTRL,
  rctrl = KMOD_RCTRL,
  ctrl = KMOD_CTRL,

  lalt = KMOD_LALT,
  ralt = KMOD_RALT,
  alt = KMOD_ALT,

  lgui = KMOD_LGUI,
  rgui = KMOD_RGUI,
  gui = KMOD_GUI,

  num = KMOD_NUM,
  caps = KMOD_CAPS,
  mode = KMOD_MODE
};

namespace detail {

[[nodiscard]] inline auto is_active(const key_mod modifiers, const uint16 currentMask) noexcept
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
                                         const uint16 currentMask) noexcept -> bool
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

[[nodiscard]] inline auto is_only_subset_active(const key_mod modifiers,
                                                const uint16 currentMask) noexcept -> bool
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

[[nodiscard]] constexpr auto operator~(const key_mod mods) noexcept -> key_mod
{
  return static_cast<key_mod>(~to_underlying(mods));
}

[[nodiscard]] constexpr auto operator&(const key_mod a, const key_mod b) noexcept -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) & to_underlying(b));
}

[[nodiscard]] constexpr auto operator|(const key_mod a, const key_mod b) noexcept -> key_mod
{
  return static_cast<key_mod>(to_underlying(a) | to_underlying(b));
}

[[nodiscard]] inline auto to_string(const key_mod mods) -> std::string
{
  if (mods == key_mod::none) {
    return "none";
  }

  const auto mask = to_underlying(mods);
  std::stringstream stream;

  auto check = [&stream, mask, count = 0](const key_mod mod, const char* name) mutable {
    if (mask & to_underlying(mod)) {
      if (count != 0) {
        stream << ',';
      }

      stream << name;
      ++count;
    }
  };

  check(key_mod::lshift, "lshift");
  check(key_mod::rshift, "rshift");

  check(key_mod::lctrl, "lctrl");
  check(key_mod::rctrl, "rctrl");

  check(key_mod::lalt, "lalt");
  check(key_mod::ralt, "ralt");

  check(key_mod::lgui, "lgui");
  check(key_mod::rgui, "rgui");

  check(key_mod::num, "num");
  check(key_mod::caps, "caps");
  check(key_mod::mode, "mode");

  return stream.str();
}

inline auto operator<<(std::ostream& stream, const key_mod& mods) -> std::ostream&
{
  return stream << to_string(mods);
}

inline void set_modifiers(const key_mod mods) noexcept
{
  SDL_SetModState(static_cast<SDL_Keymod>(mods));
}

[[nodiscard]] inline auto get_modifiers() noexcept -> key_mod
{
  return static_cast<key_mod>(SDL_GetModState());
}

/// Indicates whether any of the specified modifiers are active.
[[nodiscard]] inline auto is_active(const key_mod mods) noexcept -> bool
{
  return detail::is_active(mods, static_cast<uint16>(SDL_GetModState()));
}

/**
 * Indicates whether the specified modifiers are solely active.
 *
 * This function differs from `is_active(key_mod)` in that this function will return `false` if
 * modifiers other than those specified are active. For example, if the `shift` and `alt`
 * modifiers are being pressed, then `is_only_active(cen::key_mod::shift)` would evaluate to
 * `false`.
 *
 * \param mods the modifiers to check for.
 *
 * \return `true` if only the specified modifiers are active; `false` otherwise.
 */
[[nodiscard]] inline auto is_only_active(const key_mod mods) noexcept -> bool
{
  return detail::is_only_active(mods, static_cast<uint16>(SDL_GetModState()));
}

/**
 * Indicates whether only a subset the specified modifiers are active.
 *
 * This function is very similar to `is_only_active()`, but differs in that not all of the
 * specified modifiers need to be active for this function to return `true`. For example, if
 * you supply `shift` to this function, and only the left shift key is being pressed, then
 * `is_only_subset_active(cen::key_mod::shift)` would evaluate to `true`. However, if some
 * other modifiers were also being pressed other than the left shift key, the same function
 * call would instead evaluate to `false`.
 *
 * \param mods the modifiers to check for.
 *
 * \return `true` if a subset of the supplied modifiers are active, but no others;
 *         `false` otherwise.
 */
[[nodiscard]] inline auto is_only_subset_active(const key_mod mods) noexcept -> bool
{
  return detail::is_only_subset_active(mods, static_cast<uint16>(SDL_GetModState()));
}

/**
 * Represents a key code (or virtual key).
 *
 * \see scan_code
 * \see cen::keycodes
 */
class key_code final
{
 public:
  constexpr key_code() noexcept = default;

  constexpr key_code(const key_code&) noexcept = default;

  constexpr key_code(key_code&&) noexcept = default;

  constexpr /*implicit*/ key_code(const SDL_KeyCode key) noexcept : mKey{key} {}

  explicit key_code(const SDL_Scancode scancode) noexcept
      : mKey{static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode))}
  {}

  explicit key_code(const char* name) noexcept
      : mKey{static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name))}
  {}

  explicit key_code(const std::string& name) noexcept : key_code{name.c_str()} {}

  constexpr auto operator=(const key_code&) noexcept -> key_code& = default;

  constexpr auto operator=(key_code&&) noexcept -> key_code& = default;

  constexpr auto operator=(const SDL_KeyCode key) noexcept -> key_code&
  {
    mKey = key;
    return *this;
  }

  auto operator=(const SDL_Scancode scancode) noexcept -> key_code&
  {
    mKey = static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode));
    return *this;
  }

  auto operator=(const char* name) noexcept -> key_code&
  {
    assert(name);
    mKey = static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name));
    return *this;
  }

  auto operator=(const std::string& name) noexcept -> key_code&
  {
    return this->operator=(name.c_str());  // NOLINT
  }

  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return mKey == SDLK_UNKNOWN;
  }

  [[nodiscard]] auto name() const -> std::string { return SDL_GetKeyName(mKey); }

  [[nodiscard]] auto to_scancode() const noexcept -> SDL_Scancode
  {
    return SDL_GetScancodeFromKey(mKey);
  }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mKey);
  }

  [[nodiscard]] constexpr auto get() const noexcept -> SDL_KeyCode { return mKey; }

 private:
  SDL_KeyCode mKey{SDLK_UNKNOWN};
};

[[nodiscard]] constexpr auto operator==(const key_code& a, const key_code& b) noexcept -> bool
{
  return a.get() == b.get();
}

[[nodiscard]] constexpr auto operator!=(const key_code& a, const key_code& b) noexcept -> bool
{
  return !(a == b);
}

[[nodiscard]] inline auto to_string(const key_code& code) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("key_code(key: '{}')", code.name());
#else
  return "key_code(key: '" + code.name() + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const key_code& code) -> std::ostream&
{
  return stream << to_string(code);
}

/**
 * Represents a scan code.
 *
 * \see key_code
 * \see cen::scancodes
 */
class scan_code final
{
 public:
  constexpr scan_code() noexcept = default;

  constexpr scan_code(const scan_code&) noexcept = default;

  constexpr scan_code(scan_code&&) noexcept = default;

  constexpr /*implicit*/ scan_code(const SDL_Scancode scancode) noexcept : mCode{scancode} {}

  explicit scan_code(const SDL_Keycode key) noexcept : mCode{SDL_GetScancodeFromKey(key)} {}

  explicit scan_code(const char* name) noexcept : mCode{SDL_GetScancodeFromName(name)} {}

  explicit scan_code(const std::string& name) noexcept : scan_code{name.c_str()} {}

  constexpr auto operator=(const scan_code&) noexcept -> scan_code& = default;

  constexpr auto operator=(scan_code&&) noexcept -> scan_code& = default;

  constexpr auto operator=(const SDL_Scancode code) noexcept -> scan_code&
  {
    mCode = code;
    return *this;
  }

  auto operator=(const SDL_Keycode keycode) noexcept -> scan_code&
  {
    mCode = SDL_GetScancodeFromKey(keycode);
    return *this;
  }

  auto operator=(const char* name) noexcept -> scan_code&
  {
    assert(name);
    mCode = SDL_GetScancodeFromName(name);
    return *this;
  }

  auto operator=(const std::string& name) noexcept -> scan_code&
  {
    return operator=(name.c_str());  // NOLINT
  }

  [[nodiscard]] constexpr static auto count() noexcept -> int { return SDL_NUM_SCANCODES; }

  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return mCode == SDL_SCANCODE_UNKNOWN;
  }

  [[nodiscard]] auto name() const -> std::string { return SDL_GetScancodeName(mCode); }

  [[nodiscard]] auto to_key() const noexcept -> SDL_KeyCode
  {
    return static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(mCode));
  }

  [[nodiscard]] constexpr auto get() const noexcept -> SDL_Scancode { return mCode; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mCode);
  }

 private:
  SDL_Scancode mCode{SDL_SCANCODE_UNKNOWN};
};

[[nodiscard]] constexpr auto operator==(const scan_code& a, const scan_code& b) noexcept
    -> bool
{
  return a.get() == b.get();
}

[[nodiscard]] constexpr auto operator!=(const scan_code& a, const scan_code& b) noexcept
    -> bool
{
  return !(a == b);
}

[[nodiscard]] inline auto to_string(const scan_code& code) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("scan_code(key: '{}')", code.name());
#else
  return "scan_code(key: '" + code.name() + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const scan_code& code) -> std::ostream&
{
  return stream << to_string(code);
}

/**
 * Provides a view into the keyboard state.
 *
 * \see mouse
 */
class keyboard final
{
 public:
  keyboard() noexcept { mState = SDL_GetKeyboardState(&mKeyCount); }

#if SDL_VERSION_ATLEAST(2, 24, 0)

  static void reset() noexcept { SDL_ResetKeyboard(); }

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  void refresh() { std::copy(mState, mState + mKeyCount, mPrevious.begin()); }

  /// Indicates whether a key is being pressed.
  [[nodiscard]] auto is_pressed(const scan_code& code) const noexcept -> bool
  {
    return check(code, [this](const SDL_Scancode sc) noexcept { return mState[sc]; });
  }

  [[nodiscard]] auto is_pressed(const key_code& code) const noexcept -> bool
  {
    return is_pressed(code.to_scancode());
  }

  /// Indicates whether a key is held, i.e. pressed for at least two consecutive updates.
  [[nodiscard]] auto is_held(const scan_code& code) const noexcept(on_msvc) -> bool
  {
    return check(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return mState[sc] && mPrevious[sc];
    });
  }

  [[nodiscard]] auto is_held(const key_code& code) const noexcept(on_msvc) -> bool
  {
    return is_held(code.to_scancode());
  }

  /// Indicates whether a key was initially pressed during the the last update.
  [[nodiscard]] auto just_pressed(const scan_code& code) const noexcept(on_msvc) -> bool
  {
    return check(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return mState[sc] && !mPrevious[sc];
    });
  }

  [[nodiscard]] auto just_pressed(const key_code& code) const noexcept(on_msvc) -> bool
  {
    return just_pressed(code.to_scancode());
  }

  /// Indicates whether a key was released during the the last update.
  [[nodiscard]] auto just_released(const scan_code& code) const noexcept(on_msvc) -> bool
  {
    return check(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return !mState[sc] && mPrevious[sc];
    });
  }

  [[nodiscard]] auto just_released(const key_code& code) const noexcept(on_msvc) -> bool
  {
    return just_released(code.to_scancode());
  }

  [[nodiscard]] auto size() const noexcept -> int { return mKeyCount; }

 private:
  const uint8* mState{};
  std::array<uint8, cen::scan_code::count()> mPrevious{};
  int mKeyCount{};

  template <typename Predicate>
  auto check(const cen::scan_code& code, Predicate&& predicate) const
      noexcept(noexcept(predicate(code.get()))) -> bool
  {
    const auto sc = code.get();
    if (sc >= 0 && sc < mKeyCount) {
      return predicate(sc);
    }
    else {
      return false;
    }
  }
};

[[nodiscard]] inline auto has_screen_keyboard() noexcept -> bool
{
  return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}

[[nodiscard]] inline auto to_string(const keyboard& keyboard) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("keyboard(size: {})", keyboard.size());
#else
  return "keyboard(size: " + std::to_string(keyboard.size()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const keyboard& keyboard) -> std::ostream&
{
  return stream << to_string(keyboard);
}

namespace keycodes {

inline constexpr key_code unknown;

inline constexpr key_code a{SDLK_a};
inline constexpr key_code b{SDLK_b};
inline constexpr key_code c{SDLK_c};
inline constexpr key_code d{SDLK_d};
inline constexpr key_code e{SDLK_e};
inline constexpr key_code f{SDLK_f};
inline constexpr key_code g{SDLK_g};
inline constexpr key_code h{SDLK_h};
inline constexpr key_code i{SDLK_i};
inline constexpr key_code j{SDLK_j};
inline constexpr key_code k{SDLK_k};
inline constexpr key_code l{SDLK_l};
inline constexpr key_code m{SDLK_m};
inline constexpr key_code n{SDLK_n};
inline constexpr key_code o{SDLK_o};
inline constexpr key_code p{SDLK_p};
inline constexpr key_code q{SDLK_q};
inline constexpr key_code r{SDLK_r};
inline constexpr key_code s{SDLK_s};
inline constexpr key_code t{SDLK_t};
inline constexpr key_code u{SDLK_u};
inline constexpr key_code v{SDLK_v};
inline constexpr key_code w{SDLK_w};
inline constexpr key_code x{SDLK_x};
inline constexpr key_code y{SDLK_y};
inline constexpr key_code z{SDLK_z};

inline constexpr key_code one{SDLK_1};
inline constexpr key_code two{SDLK_2};
inline constexpr key_code three{SDLK_3};
inline constexpr key_code four{SDLK_4};
inline constexpr key_code five{SDLK_5};
inline constexpr key_code six{SDLK_6};
inline constexpr key_code seven{SDLK_7};
inline constexpr key_code eight{SDLK_8};
inline constexpr key_code nine{SDLK_9};
inline constexpr key_code zero{SDLK_0};

inline constexpr key_code f1{SDLK_F1};
inline constexpr key_code f2{SDLK_F2};
inline constexpr key_code f3{SDLK_F3};
inline constexpr key_code f4{SDLK_F4};
inline constexpr key_code f5{SDLK_F5};
inline constexpr key_code f6{SDLK_F6};
inline constexpr key_code f7{SDLK_F7};
inline constexpr key_code f8{SDLK_F8};
inline constexpr key_code f9{SDLK_F9};
inline constexpr key_code f10{SDLK_F10};
inline constexpr key_code f11{SDLK_F11};
inline constexpr key_code f12{SDLK_F12};

inline constexpr key_code left{SDLK_LEFT};
inline constexpr key_code right{SDLK_RIGHT};
inline constexpr key_code up{SDLK_UP};
inline constexpr key_code down{SDLK_DOWN};

inline constexpr key_code space{SDLK_SPACE};
inline constexpr key_code enter{SDLK_RETURN};
inline constexpr key_code escape{SDLK_ESCAPE};
inline constexpr key_code backspace{SDLK_BACKSPACE};
inline constexpr key_code tab{SDLK_TAB};

inline constexpr key_code caps_lock{SDLK_CAPSLOCK};
inline constexpr key_code left_shift{SDLK_LSHIFT};
inline constexpr key_code right_shift{SDLK_RSHIFT};
inline constexpr key_code left_ctrl{SDLK_LCTRL};
inline constexpr key_code right_ctrl{SDLK_RCTRL};
inline constexpr key_code left_alt{SDLK_LALT};
inline constexpr key_code right_alt{SDLK_RALT};
inline constexpr key_code left_gui{SDLK_LGUI};
inline constexpr key_code right_gui{SDLK_RGUI};

}  // namespace keycodes

namespace scancodes {

inline constexpr scan_code unknown;

inline constexpr scan_code a{SDL_SCANCODE_A};
inline constexpr scan_code b{SDL_SCANCODE_B};
inline constexpr scan_code c{SDL_SCANCODE_C};
inline constexpr scan_code d{SDL_SCANCODE_D};
inline constexpr scan_code e{SDL_SCANCODE_E};
inline constexpr scan_code f{SDL_SCANCODE_F};
inline constexpr scan_code g{SDL_SCANCODE_G};
inline constexpr scan_code h{SDL_SCANCODE_H};
inline constexpr scan_code i{SDL_SCANCODE_I};
inline constexpr scan_code j{SDL_SCANCODE_J};
inline constexpr scan_code k{SDL_SCANCODE_K};
inline constexpr scan_code l{SDL_SCANCODE_L};
inline constexpr scan_code m{SDL_SCANCODE_M};
inline constexpr scan_code n{SDL_SCANCODE_N};
inline constexpr scan_code o{SDL_SCANCODE_O};
inline constexpr scan_code p{SDL_SCANCODE_P};
inline constexpr scan_code q{SDL_SCANCODE_Q};
inline constexpr scan_code r{SDL_SCANCODE_R};
inline constexpr scan_code s{SDL_SCANCODE_S};
inline constexpr scan_code t{SDL_SCANCODE_T};
inline constexpr scan_code u{SDL_SCANCODE_U};
inline constexpr scan_code v{SDL_SCANCODE_V};
inline constexpr scan_code w{SDL_SCANCODE_W};
inline constexpr scan_code x{SDL_SCANCODE_X};
inline constexpr scan_code y{SDL_SCANCODE_Y};
inline constexpr scan_code z{SDL_SCANCODE_Z};

inline constexpr scan_code one{SDL_SCANCODE_1};
inline constexpr scan_code two{SDL_SCANCODE_2};
inline constexpr scan_code three{SDL_SCANCODE_3};
inline constexpr scan_code four{SDL_SCANCODE_4};
inline constexpr scan_code five{SDL_SCANCODE_5};
inline constexpr scan_code six{SDL_SCANCODE_6};
inline constexpr scan_code seven{SDL_SCANCODE_7};
inline constexpr scan_code eight{SDL_SCANCODE_8};
inline constexpr scan_code nine{SDL_SCANCODE_9};
inline constexpr scan_code zero{SDL_SCANCODE_0};

inline constexpr scan_code f1{SDL_SCANCODE_F1};
inline constexpr scan_code f2{SDL_SCANCODE_F2};
inline constexpr scan_code f3{SDL_SCANCODE_F3};
inline constexpr scan_code f4{SDL_SCANCODE_F4};
inline constexpr scan_code f5{SDL_SCANCODE_F5};
inline constexpr scan_code f6{SDL_SCANCODE_F6};
inline constexpr scan_code f7{SDL_SCANCODE_F7};
inline constexpr scan_code f8{SDL_SCANCODE_F8};
inline constexpr scan_code f9{SDL_SCANCODE_F9};
inline constexpr scan_code f10{SDL_SCANCODE_F10};
inline constexpr scan_code f11{SDL_SCANCODE_F11};
inline constexpr scan_code f12{SDL_SCANCODE_F12};

inline constexpr scan_code left{SDL_SCANCODE_LEFT};
inline constexpr scan_code right{SDL_SCANCODE_RIGHT};
inline constexpr scan_code up{SDL_SCANCODE_UP};
inline constexpr scan_code down{SDL_SCANCODE_DOWN};

inline constexpr scan_code space{SDL_SCANCODE_SPACE};
inline constexpr scan_code enter{SDL_SCANCODE_RETURN};
inline constexpr scan_code escape{SDL_SCANCODE_ESCAPE};
inline constexpr scan_code backspace{SDL_SCANCODE_BACKSPACE};
inline constexpr scan_code tab{SDL_SCANCODE_TAB};

inline constexpr scan_code caps_lock{SDL_SCANCODE_CAPSLOCK};
inline constexpr scan_code left_shift{SDL_SCANCODE_LSHIFT};
inline constexpr scan_code right_shift{SDL_SCANCODE_RSHIFT};
inline constexpr scan_code left_ctrl{SDL_SCANCODE_LCTRL};
inline constexpr scan_code right_ctrl{SDL_SCANCODE_RCTRL};
inline constexpr scan_code left_alt{SDL_SCANCODE_LALT};
inline constexpr scan_code right_alt{SDL_SCANCODE_RALT};
inline constexpr scan_code left_gui{SDL_SCANCODE_LGUI};
inline constexpr scan_code right_gui{SDL_SCANCODE_RGUI};

}  // namespace scancodes

}  // namespace cen

#endif  // CENTURION_KEYBOARD_HPP_
