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

enum class KeyMod : Uint16 {
  None = KMOD_NONE,
  LShift = KMOD_LSHIFT,
  RShift = KMOD_RSHIFT,
  LCtrl = KMOD_LCTRL,
  RCtrl = KMOD_RCTRL,
  LAlt = KMOD_LALT,
  RAlt = KMOD_RALT,
  LGui = KMOD_LGUI,
  RGui = KMOD_RGUI,
  Shift = KMOD_SHIFT,
  Ctrl = KMOD_CTRL,
  Alt = KMOD_ALT,
  Gui = KMOD_GUI,
  Num = KMOD_NUM,
  Caps = KMOD_CAPS,
  Mode = KMOD_MODE
};

namespace detail {

[[nodiscard]] inline auto IsActive(const KeyMod modifiers, const Uint16 currentMask) noexcept
    -> bool
{
  if (modifiers == KeyMod::None) {
    return !currentMask;
  }
  else {
    return currentMask & ToUnderlying(modifiers);
  }
}

[[nodiscard]] inline auto IsOnlyActive(const KeyMod modifiers,
                                       const Uint16 currentMask) noexcept -> bool
{
  if (modifiers == KeyMod::None) {
    return !currentMask;
  }

  const auto mask = ToUnderlying(modifiers);
  const auto hits = currentMask & mask;

  if (hits != mask) {
    return false;  // The specified modifiers were a combo that wasn't fully active
  }
  else {
    const auto others = currentMask & ~hits;
    return hits && !others;
  }
}

[[nodiscard]] inline auto IsOnlyAnyOfActive(const KeyMod modifiers,
                                            const Uint16 currentMask) noexcept -> bool
{
  if (modifiers == KeyMod::None) {
    return !currentMask;
  }

  const auto mask = ToUnderlying(modifiers);

  const auto hits = currentMask & mask;
  const auto others = currentMask & ~hits;

  return hits && !others;
}

}  // namespace detail

/// Sets the current key modifiers.
inline void SetModifiers(const KeyMod mods) noexcept
{
  SDL_SetModState(static_cast<SDL_Keymod>(mods));
}

/// Returns the current key modifier state.
[[nodiscard]] inline auto GetModifiers() noexcept -> KeyMod
{
  return static_cast<KeyMod>(SDL_GetModState());
}

/// Represents a virtual key.
class KeyCode final {
 public:
  /** Creates a key with the `SDLK_UNKNOWN` key code. */
  constexpr KeyCode() noexcept = default;

  constexpr KeyCode(const KeyCode&) noexcept = default;

  constexpr KeyCode(KeyCode&&) noexcept = default;

  constexpr /*implicit*/ KeyCode(const SDL_KeyCode key) noexcept : mKey{key} {}  // NOLINT

  explicit KeyCode(const SDL_Scancode scancode) noexcept
      : mKey{static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode))}
  {}

  /** Creates a key code based on a key name. */
  explicit KeyCode(const char* name) noexcept
      : mKey{static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name))}
  {}

  explicit KeyCode(const std::string& name) noexcept : KeyCode{name.c_str()} {}

  constexpr auto operator=(const KeyCode&) noexcept -> KeyCode& = default;

  constexpr auto operator=(KeyCode&&) noexcept -> KeyCode& = default;

  constexpr auto operator=(const SDL_KeyCode key) noexcept -> KeyCode&
  {
    mKey = key;
    return *this;
  }

  auto operator=(const SDL_Scancode scancode) noexcept -> KeyCode&
  {
    mKey = static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode));
    return *this;
  }

  auto operator=(const char* name) noexcept -> KeyCode&
  {
    assert(name);
    mKey = static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name));
    return *this;
  }

  auto operator=(const std::string& name) noexcept -> KeyCode&
  {
    return this->operator=(name.c_str());  // NOLINT
  }

  [[nodiscard]] constexpr auto IsUnknown() const noexcept -> bool
  {
    return mKey == SDLK_UNKNOWN;
  }

  [[nodiscard]] auto GetName() const -> std::string { return SDL_GetKeyName(mKey); }

  [[nodiscard]] auto ToScanCode() const noexcept -> SDL_Scancode
  {
    return SDL_GetScancodeFromKey(mKey);
  }

  [[nodiscard]] constexpr auto get() const noexcept -> SDL_KeyCode { return mKey; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mKey);
  }

 private:
  SDL_KeyCode mKey{SDLK_UNKNOWN};
};

class ScanCode final {
 public:
  /** Creates a scan code with the value `SDL_SCANCODE_UNKNOWN`. */
  constexpr ScanCode() noexcept = default;

  constexpr ScanCode(const ScanCode&) noexcept = default;

  constexpr ScanCode(ScanCode&&) noexcept = default;

  constexpr /*implicit*/ ScanCode(const SDL_Scancode scancode) noexcept : mCode{scancode} {}

  explicit ScanCode(const SDL_Keycode key) noexcept : mCode{SDL_GetScancodeFromKey(key)} {}

  explicit ScanCode(const char* name) noexcept : mCode{SDL_GetScancodeFromName(name)} {}

  explicit ScanCode(const std::string& name) noexcept : ScanCode{name.c_str()} {}

  constexpr auto operator=(const ScanCode&) noexcept -> ScanCode& = default;

  constexpr auto operator=(ScanCode&&) noexcept -> ScanCode& = default;

  constexpr auto operator=(const SDL_Scancode code) noexcept -> ScanCode&
  {
    mCode = code;
    return *this;
  }

  auto operator=(const SDL_Keycode keycode) noexcept -> ScanCode&
  {
    mCode = SDL_GetScancodeFromKey(keycode);
    return *this;
  }

  auto operator=(const char* name) noexcept -> ScanCode&
  {
    assert(name);
    mCode = SDL_GetScancodeFromName(name);
    return *this;
  }

  auto operator=(const std::string& name) noexcept -> ScanCode&
  {
    return operator=(name.c_str());  // NOLINT
  }

  [[nodiscard]] constexpr auto IsUnknown() const noexcept -> bool
  {
    return mCode == SDL_SCANCODE_UNKNOWN;
  }

  [[nodiscard]] auto GetName() const -> std::string { return SDL_GetScancodeName(mCode); }

  [[nodiscard]] auto ToKeyCode() const noexcept -> SDL_KeyCode
  {
    return static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(mCode));
  }

  [[nodiscard]] constexpr auto get() const noexcept -> SDL_Scancode { return mCode; }

  [[nodiscard]] constexpr static auto GetAmount() noexcept -> int { return SDL_NUM_SCANCODES; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mCode);
  }

 private:
  SDL_Scancode mCode{SDL_SCANCODE_UNKNOWN};
};

/// Provides information about the keyboard state.
class Keyboard final {
 public:
  Keyboard() noexcept { mState = SDL_GetKeyboardState(&mKeyCount); }

  /** Refreshes the key state. */
  void Update() { std::copy(mState, mState + mKeyCount, mPrevious.begin()); }

  /** Indicates whether the specified key is being pressed. */
  [[nodiscard]] auto IsPressed(const ScanCode& code) const noexcept -> bool
  {
    return CheckState(code, [this](const SDL_Scancode sc) noexcept { return mState[sc]; });
  }

  [[nodiscard]] auto IsPressed(const KeyCode& code) const noexcept -> bool
  {
    return IsPressed(code.ToScanCode());
  }

  /** Indicates whether the specified key is being held. */
  [[nodiscard]] auto IsHeld(const ScanCode& code) const noexcept(on_msvc) -> bool
  {
    return CheckState(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return mState[sc] && mPrevious[sc];
    });
  }

  [[nodiscard]] auto IsHeld(const KeyCode& code) const noexcept(on_msvc) -> bool
  {
    return IsHeld(code.ToScanCode());
  }

  /** Indicates whether the specified key was just pressed. */
  [[nodiscard]] auto JustPressed(const ScanCode& code) const noexcept(on_msvc) -> bool
  {
    return CheckState(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return mState[sc] && !mPrevious[sc];
    });
  }

  [[nodiscard]] auto JustPressed(const KeyCode& code) const noexcept(on_msvc) -> bool
  {
    return JustPressed(code.ToScanCode());
  }

  /** Indicates whether the specified key was just released. */
  [[nodiscard]] auto JustReleased(const ScanCode& code) const noexcept(on_msvc) -> bool
  {
    return CheckState(code, [this](const SDL_Scancode sc) noexcept(on_msvc) {
      return !mState[sc] && mPrevious[sc];
    });
  }

  [[nodiscard]] auto JustReleased(const KeyCode& code) const noexcept(on_msvc) -> bool
  {
    return JustReleased(code.ToScanCode());
  }

  /** Indicates whether any of the specified key modifiers are active. */
  [[nodiscard]] static auto IsActive(const KeyMod modifiers) noexcept -> bool
  {
    return detail::IsActive(modifiers, static_cast<Uint16>(SDL_GetModState()));
  }

  /**
   * Indicates whether the specified modifiers are solely active.
   *
   * This function differs from `IsActive(KeyMod)` in that this function will return `false`
   * if modifiers other than those specified are active. For example, if the `Shift` and `Alt`
   * modifiers are being pressed, then `IsOnlyActive(cen::KeyMod::Shift)` would evaluate to
   * `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *only* the specified modifiers are active; false otherwise.
   */
  [[nodiscard]] static auto IsOnlyActive(const KeyMod modifiers) noexcept -> bool
  {
    return detail::IsOnlyActive(modifiers, static_cast<Uint16>(SDL_GetModState()));
  }

  /**
   * Indicates whether or not only any of the specified modifiers are active.
   *
   * This function is very similar to `IsOnlyActive()`, but differs in that not all of the
   * specified modifiers need to be active for this function to return `true`. For example, if
   * you supply `Shift` to this function, and only the left shift key is being pressed, then
   * `IsOnlyAnyOfActive(cen::KeyMod::Shift)` would evaluate to `true`. However, if some
   * other modifiers were also being pressed other than the left shift key, the same function
   * call would instead evaluate to `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *any* of the specified modifiers are active, but none others; `false`
   * otherwise.
   */
  [[nodiscard]] static auto IsOnlyAnyOfActive(const KeyMod modifiers) noexcept -> bool
  {
    return detail::IsOnlyAnyOfActive(modifiers, static_cast<Uint16>(SDL_GetModState()));
  }

  [[nodiscard]] auto GetNumKeys() const noexcept -> int { return mKeyCount; }

 private:
  const Uint8* mState{};
  std::array<Uint8, cen::ScanCode::GetAmount()> mPrevious{};
  int mKeyCount{};

  template <typename Predicate>
  auto CheckState(const cen::ScanCode& code, Predicate&& predicate) const
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

[[nodiscard]] inline auto HasScreenKeyboard() noexcept -> bool
{
  return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}

[[nodiscard]] inline auto to_string(const KeyMod mods) -> std::string
{
  if (mods == KeyMod::None) {
    return "None";
  }

  const auto mask = ToUnderlying(mods);
  std::stringstream stream;

  auto check = [&stream, mask, count = 0](const KeyMod mod, const char* name) mutable {
    if (mask & ToUnderlying(mod)) {
      if (count != 0) {
        stream << ',';
      }

      stream << name;
      ++count;
    }
  };

  check(KeyMod::LShift, "LShift");
  check(KeyMod::RShift, "RShift");

  check(KeyMod::LCtrl, "LCtrl");
  check(KeyMod::RCtrl, "RCtrl");

  check(KeyMod::LAlt, "LAlt");
  check(KeyMod::RAlt, "RAlt");

  check(KeyMod::LGui, "LGui");
  check(KeyMod::RGui, "RGui");

  check(KeyMod::Num, "Num");
  check(KeyMod::Caps, "Caps");
  check(KeyMod::Mode, "Mode");

  return stream.str();
}

[[nodiscard]] inline auto to_string(const KeyCode& code) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("KeyCode(key: {})", code.GetName());
#else
  return "KeyCode(key: " + code.GetName() + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

[[nodiscard]] inline auto to_string(const ScanCode& code) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("ScanCode(key: {})", code.GetName());
#else
  return "ScanCode(key: " + code.GetName() + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

[[nodiscard]] inline auto to_string(const Keyboard& keyboard) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Keyboard(#keys: {})", keyboard.GetNumKeys());
#else
  return "Keyboard(#keys: " + std::to_string(keyboard.GetNumKeys()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const KeyMod& mods) -> std::ostream&
{
  return stream << to_string(mods);
}

inline auto operator<<(std::ostream& stream, const KeyCode& code) -> std::ostream&
{
  return stream << to_string(code);
}

inline auto operator<<(std::ostream& stream, const ScanCode& code) -> std::ostream&
{
  return stream << to_string(code);
}

inline auto operator<<(std::ostream& stream, const Keyboard& keyboard) -> std::ostream&
{
  return stream << to_string(keyboard);
}

[[nodiscard]] constexpr auto operator&(const KeyMod a, const KeyMod b) noexcept -> KeyMod
{
  return static_cast<KeyMod>(ToUnderlying(a) & ToUnderlying(b));
}

[[nodiscard]] constexpr auto operator|(const KeyMod a, const KeyMod b) noexcept -> KeyMod
{
  return static_cast<KeyMod>(ToUnderlying(a) | ToUnderlying(b));
}

[[nodiscard]] constexpr auto operator~(const KeyMod mods) noexcept -> KeyMod
{
  return static_cast<KeyMod>(~ToUnderlying(mods));
}

[[nodiscard]] constexpr auto operator==(const KeyCode& lhs, const KeyCode& rhs) noexcept
    -> bool
{
  return lhs.get() == rhs.get();
}

[[nodiscard]] constexpr auto operator!=(const KeyCode& lhs, const KeyCode& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] constexpr auto operator==(const ScanCode& lhs, const ScanCode& rhs) noexcept
    -> bool
{
  return lhs.get() == rhs.get();
}

[[nodiscard]] constexpr auto operator!=(const ScanCode& lhs, const ScanCode& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

namespace keycodes {

/// \name Key code constants
/// \{

inline constexpr KeyCode unknown;

inline constexpr KeyCode a{SDLK_a};
inline constexpr KeyCode b{SDLK_b};
inline constexpr KeyCode c{SDLK_c};
inline constexpr KeyCode d{SDLK_d};
inline constexpr KeyCode e{SDLK_e};
inline constexpr KeyCode f{SDLK_f};
inline constexpr KeyCode g{SDLK_g};
inline constexpr KeyCode h{SDLK_h};
inline constexpr KeyCode i{SDLK_i};
inline constexpr KeyCode j{SDLK_j};
inline constexpr KeyCode k{SDLK_k};
inline constexpr KeyCode l{SDLK_l};
inline constexpr KeyCode m{SDLK_m};
inline constexpr KeyCode n{SDLK_n};
inline constexpr KeyCode o{SDLK_o};
inline constexpr KeyCode p{SDLK_p};
inline constexpr KeyCode q{SDLK_q};
inline constexpr KeyCode r{SDLK_r};
inline constexpr KeyCode s{SDLK_s};
inline constexpr KeyCode t{SDLK_t};
inline constexpr KeyCode u{SDLK_u};
inline constexpr KeyCode v{SDLK_v};
inline constexpr KeyCode w{SDLK_w};
inline constexpr KeyCode x{SDLK_x};
inline constexpr KeyCode y{SDLK_y};
inline constexpr KeyCode z{SDLK_z};

inline constexpr KeyCode one{SDLK_1};
inline constexpr KeyCode two{SDLK_2};
inline constexpr KeyCode three{SDLK_3};
inline constexpr KeyCode four{SDLK_4};
inline constexpr KeyCode five{SDLK_5};
inline constexpr KeyCode six{SDLK_6};
inline constexpr KeyCode seven{SDLK_7};
inline constexpr KeyCode eight{SDLK_8};
inline constexpr KeyCode nine{SDLK_9};
inline constexpr KeyCode zero{SDLK_0};

inline constexpr KeyCode f1{SDLK_F1};
inline constexpr KeyCode f2{SDLK_F2};
inline constexpr KeyCode f3{SDLK_F3};
inline constexpr KeyCode f4{SDLK_F4};
inline constexpr KeyCode f5{SDLK_F5};
inline constexpr KeyCode f6{SDLK_F6};
inline constexpr KeyCode f7{SDLK_F7};
inline constexpr KeyCode f8{SDLK_F8};
inline constexpr KeyCode f9{SDLK_F9};
inline constexpr KeyCode f10{SDLK_F10};
inline constexpr KeyCode f11{SDLK_F11};
inline constexpr KeyCode f12{SDLK_F12};

inline constexpr KeyCode left{SDLK_LEFT};
inline constexpr KeyCode right{SDLK_RIGHT};
inline constexpr KeyCode up{SDLK_UP};
inline constexpr KeyCode down{SDLK_DOWN};

inline constexpr KeyCode space{SDLK_SPACE};
inline constexpr KeyCode enter{SDLK_RETURN};
inline constexpr KeyCode escape{SDLK_ESCAPE};
inline constexpr KeyCode backspace{SDLK_BACKSPACE};
inline constexpr KeyCode tab{SDLK_TAB};

inline constexpr KeyCode caps_lock{SDLK_CAPSLOCK};
inline constexpr KeyCode left_shift{SDLK_LSHIFT};
inline constexpr KeyCode right_shift{SDLK_RSHIFT};
inline constexpr KeyCode left_ctrl{SDLK_LCTRL};
inline constexpr KeyCode right_ctrl{SDLK_RCTRL};
inline constexpr KeyCode left_alt{SDLK_LALT};
inline constexpr KeyCode right_alt{SDLK_RALT};
inline constexpr KeyCode left_gui{SDLK_LGUI};
inline constexpr KeyCode right_gui{SDLK_RGUI};

/// \} End of key code constants

}  // namespace keycodes

namespace scancodes {

/// \name Scan code constants
/// \{

inline constexpr ScanCode unknown;

inline constexpr ScanCode a{SDL_SCANCODE_A};
inline constexpr ScanCode b{SDL_SCANCODE_B};
inline constexpr ScanCode c{SDL_SCANCODE_C};
inline constexpr ScanCode d{SDL_SCANCODE_D};
inline constexpr ScanCode e{SDL_SCANCODE_E};
inline constexpr ScanCode f{SDL_SCANCODE_F};
inline constexpr ScanCode g{SDL_SCANCODE_G};
inline constexpr ScanCode h{SDL_SCANCODE_H};
inline constexpr ScanCode i{SDL_SCANCODE_I};
inline constexpr ScanCode j{SDL_SCANCODE_J};
inline constexpr ScanCode k{SDL_SCANCODE_K};
inline constexpr ScanCode l{SDL_SCANCODE_L};
inline constexpr ScanCode m{SDL_SCANCODE_M};
inline constexpr ScanCode n{SDL_SCANCODE_N};
inline constexpr ScanCode o{SDL_SCANCODE_O};
inline constexpr ScanCode p{SDL_SCANCODE_P};
inline constexpr ScanCode q{SDL_SCANCODE_Q};
inline constexpr ScanCode r{SDL_SCANCODE_R};
inline constexpr ScanCode s{SDL_SCANCODE_S};
inline constexpr ScanCode t{SDL_SCANCODE_T};
inline constexpr ScanCode u{SDL_SCANCODE_U};
inline constexpr ScanCode v{SDL_SCANCODE_V};
inline constexpr ScanCode w{SDL_SCANCODE_W};
inline constexpr ScanCode x{SDL_SCANCODE_X};
inline constexpr ScanCode y{SDL_SCANCODE_Y};
inline constexpr ScanCode z{SDL_SCANCODE_Z};

inline constexpr ScanCode one{SDL_SCANCODE_1};
inline constexpr ScanCode two{SDL_SCANCODE_2};
inline constexpr ScanCode three{SDL_SCANCODE_3};
inline constexpr ScanCode four{SDL_SCANCODE_4};
inline constexpr ScanCode five{SDL_SCANCODE_5};
inline constexpr ScanCode six{SDL_SCANCODE_6};
inline constexpr ScanCode seven{SDL_SCANCODE_7};
inline constexpr ScanCode eight{SDL_SCANCODE_8};
inline constexpr ScanCode nine{SDL_SCANCODE_9};
inline constexpr ScanCode zero{SDL_SCANCODE_0};

inline constexpr ScanCode f1{SDL_SCANCODE_F1};
inline constexpr ScanCode f2{SDL_SCANCODE_F2};
inline constexpr ScanCode f3{SDL_SCANCODE_F3};
inline constexpr ScanCode f4{SDL_SCANCODE_F4};
inline constexpr ScanCode f5{SDL_SCANCODE_F5};
inline constexpr ScanCode f6{SDL_SCANCODE_F6};
inline constexpr ScanCode f7{SDL_SCANCODE_F7};
inline constexpr ScanCode f8{SDL_SCANCODE_F8};
inline constexpr ScanCode f9{SDL_SCANCODE_F9};
inline constexpr ScanCode f10{SDL_SCANCODE_F10};
inline constexpr ScanCode f11{SDL_SCANCODE_F11};
inline constexpr ScanCode f12{SDL_SCANCODE_F12};

inline constexpr ScanCode left{SDL_SCANCODE_LEFT};
inline constexpr ScanCode right{SDL_SCANCODE_RIGHT};
inline constexpr ScanCode up{SDL_SCANCODE_UP};
inline constexpr ScanCode down{SDL_SCANCODE_DOWN};

inline constexpr ScanCode space{SDL_SCANCODE_SPACE};
inline constexpr ScanCode enter{SDL_SCANCODE_RETURN};
inline constexpr ScanCode escape{SDL_SCANCODE_ESCAPE};
inline constexpr ScanCode backspace{SDL_SCANCODE_BACKSPACE};
inline constexpr ScanCode tab{SDL_SCANCODE_TAB};

inline constexpr ScanCode caps_lock{SDL_SCANCODE_CAPSLOCK};
inline constexpr ScanCode left_shift{SDL_SCANCODE_LSHIFT};
inline constexpr ScanCode right_shift{SDL_SCANCODE_RSHIFT};
inline constexpr ScanCode left_ctrl{SDL_SCANCODE_LCTRL};
inline constexpr ScanCode right_ctrl{SDL_SCANCODE_RCTRL};
inline constexpr ScanCode left_alt{SDL_SCANCODE_LALT};
inline constexpr ScanCode right_alt{SDL_SCANCODE_RALT};
inline constexpr ScanCode left_gui{SDL_SCANCODE_LGUI};
inline constexpr ScanCode right_gui{SDL_SCANCODE_RGUI};

/// \} End of scan code constants

}  // namespace scancodes

}  // namespace cen

#endif  // CENTURION_KEYBOARD_HPP_
